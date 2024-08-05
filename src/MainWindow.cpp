#include "MainWindow.h"
#include "Logger.h"
#include "components/AppSettings.h"
#include "qboxlayout.h"
#include "ui_MainWindow.h"
#include "utils/utils.h"
#include <strsafe.h>
#include <tchar.h>
#include <tchar.h>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>
#include <QMessageBox>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QBuffer>
#include <QImageReader>
#include <QApplication>
#include <QDir>
#include <QFile>
#include <QProcess>
#include <QLibrary>
#include <QErrorMessage>
#include <QScreen>
#include <QTimer>
#include <QVariant>
#include <QMediaPlayer>
#include <cstddef> // For std::byte

#include <mmdeviceapi.h>
#include <endpointvolume.h>
#undef byte           // Undefine byte to avoid conflicts
#include <wbemcli.h>
#include <comutil.h>  // For _bstr_t and SysAllocString
#include <oleauto.h>   // Required for SysAllocString
#include <comutil.h>  // For _bstr_t and SysAllocString
#include <combaseapi.h>
#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "oleaut32.lib")
#pragma comment(lib, "wbemuuid.lib")
#pragma comment(lib, "comsuppw.lib") // Required for _bstr_t
#pragma comment(lib, "Dxva2.lib")               // pragma directive instructs the linker to link the Dxva2.lib library. The library contains functions and resources related to DirectX Video Acceleration (DXVA), which is a Microsoft API for hardware-accelerated video decoding.


#include <objbase.h>                            // provides COM (Component Object Model) initialization and uninitialization functions. COM is a binary interface standard for software components to interact with each other.
#include <stdio.h>                              // provides standard I/O functions like printf and scanf for input and output operations.
#include <comdef.h>                             // provides COM utility functions, including helper classes and macros for COM programming.
#include <wbemidl.h>                            // provides WMI (Windows Management Instrumentation) COM interfaces. WMI is a Microsoft technology for managing and accessing system information in a Windows environment.
#include <windows.h>                            // provides the Windows API, which includes functions, constants, and data types for interacting with the Windows operating system.
#include <ShellAPI.h>                           // provides the ShellExecute function, which allows you to execute a file or open it with its associated application.
#include <string>                               // provides the std::wstring class, which represents a wide string of characters. Wide strings are used to store Unicode text.
#include <iostream>                             // provides the std::cout and std::cerr objects for console output. std::cout is used for standard output, while std::cerr is used for error output.
#include <highlevelmonitorconfigurationapi.h>   // provides functions for controlling display brightness at a high level. It allows you to adjust the brightness of monitors connected to the system.
#include <chrono>                               // provides facilities for measuring and manipulating time. It includes the std::chrono namespace, which contains classes and functions for time-related operations.
#include <thread>                               // provides facilities for creating and managing threads. It includes the std::thread class, which represents a single thread of execution.

using namespace std; // directive that allows you to use names from the std namespace without explicitly qualifying them with the namespace prefix.
#define EXIT_CODE_REBOOT -1

HANDLE hMonitor{ nullptr };  // Handle to the monitor

int videoDownloadCount = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),m_imageLabel(NULL),
      m_videoWidget(NULL),m_mediaPlayer(NULL),m_textLabel(NULL),
      m_imageFile(NULL),m_videoFile(NULL)
{
    LOG_INFO("");

    ui->setupUi(this);

    if(!m_textLabel)
        m_textLabel = new QLabel(this);

    if(!m_imageLabel)
        m_imageLabel = new QLabel(this);

    ui->previewWidget->layout()->addWidget(m_textLabel);
    ui->previewWidget->layout()->addWidget(m_imageLabel);

    if(!m_videoWidget)
        this->m_videoWidget = new QVideoWidget(this);
    if(!m_mediaPlayer)
        this->m_mediaPlayer = new QMediaPlayer(this);

    this->m_mediaPlayer->setVideoOutput(this->m_videoWidget);
    connect(m_mediaPlayer, &QMediaPlayer::mediaStatusChanged,this, &MainWindow::onMediaStatusChanged);
    connect(m_mediaPlayer, SIGNAL(error(QMediaPlayer::Error)), this, SLOT(onErrorOccurred(QMediaPlayer::Error)));

    ui->previewWidget->layout()->addWidget(m_videoWidget);

    QTimer::singleShot(1000,[&]
    {
        ui->brightnessSlider->setRange(0, 100);  // Brightness range from 0 to 100
        ui->brightnessSlider->setValue(getBrightness());
        connect(ui->brightnessSlider, &QSlider::valueChanged, this,&::MainWindow::onValueChanged);
    });

    ui->playerVolumeSlider->setRange(0, 100);  // Volume range from 0 to 100
    ui->playerVolumeSlider->setValue(getSystemVolumeLevel());
    connect(ui->playerVolumeSlider, &QSlider::valueChanged, this, &MainWindow::setVolume);
    connect(&m_manager, &QNetworkAccessManager::finished, [&](QNetworkReply* reply)
    {
        onVideoDownloadFinished(reply);
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    QMediaPlayer::Error error = m_mediaPlayer->error();
    switch (status)
    {
        case QMediaPlayer::NoMedia:
            LOG_INFO("No media loaded.");
            break;
        case QMediaPlayer::LoadingMedia:
            LOG_INFO("Media is loading.");
            break;
        case QMediaPlayer::LoadedMedia:
            LOG_INFO("Media loaded.");
            break;
        case QMediaPlayer::StalledMedia:
            LOG_INFO("Media playback stalled.");
            break;
        case QMediaPlayer::BufferingMedia:
            LOG_INFO("Media buffering.");
            break;
        case QMediaPlayer::BufferedMedia:
            LOG_INFO("Media buffered.");
            break;
        case QMediaPlayer::EndOfMedia:
            LOG_INFO("End of media.");
            break;
        case QMediaPlayer::InvalidMedia:
            LOG_INFO("Invalid media.");
            break;
        case QMediaPlayer::UnknownMediaStatus:
            LOG_INFO("Unknown media status.");
            break;
    }
}

void MainWindow::onErrorOccurred(QMediaPlayer::Error error)
{
    LOG_INFO("Error occurred: " + QVariant(error).toString());
}


QString MainWindow::getLastErrorAsString(DWORD errorMessageID)
{
    LOG_INFO("");

    // Get the error message ID, if any.
    if(errorMessageID == 0)
    {
        return QString(); // No error message has been recorded
    }

    LPWSTR messageBuffer = nullptr;
    size_t size = FormatMessageW(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPWSTR)&messageBuffer, 0, NULL
    );

    QString message = QString::fromWCharArray(messageBuffer, size);

    // Free the buffer allocated by FormatMessage
    LocalFree(messageBuffer);

    return message;
}

// Function to retrieve the handle of the monitor
HANDLE MainWindow::GetMonitor()
{
    LOG_INFO("");

    DWORD NumberOfPhysicalMonitors{ 0 };
    PHYSICAL_MONITOR* PhysicalMonitors{ nullptr };

    // Get the handle of the monitor from the top-level window
    HMONITOR hMonitor{ MonitorFromWindow(GetTopWindow(nullptr), NULL) };

    // Return INVALID_HANDLE_VALUE if the monitor handle is invalid
    if (!hMonitor || hMonitor == INVALID_HANDLE_VALUE)
    {
        return INVALID_HANDLE_VALUE;
    }

    // Get the number of physical monitors and allocate memory for the physical monitors
    if (!GetNumberOfPhysicalMonitorsFromHMONITOR(hMonitor, &NumberOfPhysicalMonitors))
    {
        return INVALID_HANDLE_VALUE;
    }

    PhysicalMonitors = static_cast<PHYSICAL_MONITOR*>(malloc(
                                                          NumberOfPhysicalMonitors * sizeof(PHYSICAL_MONITOR)
                                                          ));

    // Get the physical monitors from the monitor handle
    if (!GetPhysicalMonitorsFromHMONITOR(hMonitor,
                                         NumberOfPhysicalMonitors,
                                         PhysicalMonitors))
    {
        free(PhysicalMonitors);
        return INVALID_HANDLE_VALUE;
    }

    // Return the handle of the physical monitor
    return PhysicalMonitors->hPhysicalMonitor;
}

int MainWindow::getBrightness()
{
    LOG_INFO("");

    QString command = "powershell.exe";
    QStringList arguments;
    arguments << "-Command" << "(Get-WmiObject -Namespace root\\wmi -Class WmiMonitorBrightness).CurrentBrightness";

    QProcess process;
    process.start(command, arguments);
    process.waitForFinished();

    QString output = process.readAllStandardOutput().trimmed();

    int n = output.toInt();

    return n;
}

void MainWindow::onValueChanged(int value)
{
    LOG_INFO("");

    setHDMIDisplayBrightness_WinAPI(value);         // use WinAPI to set HDMI display brightness level

    setNotebookDisplayBrightness_WMI(value);        // use WMI Class to change Notebook Display Brightness level

    setNotebookDisplayBrightness_PShell(value);     // use Power Shell command to change Notebook Display Brightness level
}

void MainWindow::onVideoDownloadFinished(QNetworkReply* reply)
{
    bool result = false;

    ui->downloadWidgetButton->setDisabled(false);

    QUrl url = reply->url();
    LOG_INFO("QNetworkAccessManager::finished reply->url() : " + m_currentVideoFileName);

    if (reply->error())
    {
        LOG_ERROR(0, "Download of %s failed: " + url.toEncoded() + reply->errorString());
    }
    else
    {
        QString locationPath = AppSettings::defaultAppDataLocation() + QDir::separator();
        QString fileName;
        if(videoDownloadCount == 0)
            fileName = locationPath + "testVideo.mp4";
        else
            fileName = locationPath + "testVideo" + "_" + QString::number(videoDownloadCount) + ".mp4";
        videoDownloadCount++;

        m_currentVideoFileName = fileName;

        LOG_INFO("Current video filename to write the downloaded buffer data : " + m_currentVideoFileName);

        result = writeFile(QDir::toNativeSeparators(fileName), reply);
    }
    reply->deleteLater();

    // Hide the progress bar when the download is finished
    ui->progressBar->setVisible(false);

    if (result)
        m_eventLoop.exit(0);
    else
        m_eventLoop.exit(-1);
    m_eventLoop.exec();
}

bool MainWindow::download()
{
    LOG_INFO("");
    ui->downloadWidgetButton->setDisabled(true);

    QString updaterUrl = "https://astacms-app.s3.us-west-2.amazonaws.com/LOOK+14+-+N21+BLACK+HEELS+3840x2160.mp4";

    bool result = false;
    QUrl url(updaterUrl);
    QNetworkRequest request(url);

    QSslConfiguration config = request.sslConfiguration();
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    config.setProtocol(QSsl::TlsV1_2);
    request.setSslConfiguration(config);

    if (QSslSocket::supportsSsl())
    {
        LOG_INFO("SSL is supported.");
    }
    else
    {
        LOG_INFO("SSL is not supported.");
        LOG_INFO("Build Version:" + QSslSocket::sslLibraryBuildVersionString());
        LOG_INFO("Loaded Version:" + QSslSocket::sslLibraryVersionString());
    }

    QNetworkReply *reply = m_manager.get(request);

    // Show the progress bar
    ui->progressBar->setValue(0);
    ui->progressBar->setVisible(true);

    m_textLabel->hide();
    m_imageLabel->hide();
    m_videoWidget->hide();

#if QT_CONFIG(ssl)
    connect(reply, &QNetworkReply::sslErrors, [&](const QList<QSslError> &sslErrors)
    {
        for (const QSslError &error : sslErrors)
            LOG_ERROR(0, "SSL error: " + error.errorString());
        m_eventLoop.exit(-1);
    });
#endif

    connect(reply, &QNetworkReply::downloadProgress, [&](qint64 bytesReceived, qint64 bytesTotal)
    {
        if (bytesTotal > 0) {
            float bytesReceivedPercentage = static_cast<float>(bytesReceived) / static_cast<float>(bytesTotal);
            float calcPercentage = bytesReceivedPercentage * 100;
            int progress = static_cast<int>(calcPercentage);
            ui->progressBar->setValue(progress);
        }
    });

    return result;
}


bool MainWindow::writeFile(QString filePath, QNetworkReply* reply)
{
    LOG_INFO("");

    bool written = true;
    int bytesWritten = 0;

    if(filePath.isEmpty())
        return written;


    QString cleanPath = QDir::cleanPath(filePath);
    QFile f(cleanPath);
    if(f.open(QIODevice::WriteOnly))
    {
        bytesWritten = f.write(reply->readAll());
        f.close();
        reply->readAll().size();
    }
    else
        written = false;

    if(bytesWritten)
    {

        m_textLabel->setText("Media has been saved in the path " + filePath);
        LOG_INFO("Video file has been successfully written under the name : " + filePath);

        m_textLabel->show();
        m_imageLabel->hide();
        m_videoWidget->hide();
    }

    return written;
}


void MainWindow::on_downloadWidgetButton_clicked()
{
    LOG_INFO("");

    download();
}

void MainWindow::on_playWidgetButton_clicked()
{
    LOG_INFO("");
    ui->progressBar->setVisible(false);

//    QString locationPath = AppSettings::defaultAppDataLocation() + QDir::separator();
    QString filePath = m_currentVideoFileName;

    if(!QFile(filePath).exists())
    {
        QMessageBox::information(this,"Info","Please download the video first");
        return;
    }
    else
    {
        LOG_INFO("File is prepared to load in video widget : " + filePath);
    }

    this->m_mediaPlayer->setMedia(QUrl::fromLocalFile(filePath));

    m_mediaPlayer->play();
    if (m_mediaPlayer->state() == QMediaPlayer::PlayingState) {
        LOG_INFO("The media player is playing.");
    } else {
        LOG_INFO("The media player is not playing.");
    }

    m_textLabel->hide();
    m_imageLabel->hide();
    m_videoWidget->show();
}

void MainWindow::on_readWidgetButton_clicked()
{
    LOG_INFO("");

    if(!m_imageLabel)
        m_imageLabel = new QLabel(this);

    QString locationPath = AppSettings::defaultAppDataLocation() + QDir::separator();
    QString filePath = locationPath + "testImage.png";

    if (!filePath.isEmpty())
    {
        if(!QFile(filePath).exists())
        {
            QMessageBox::information(this,"Info","Please download the image first");
            return;
        }

        QPixmap pixmap(filePath);
        if (!pixmap.isNull())
            m_imageLabel->setPixmap(pixmap.scaled(ui->previewWidget->size()));
        //        else
        //            QMessageBox::information(this,"Info","Failed to load image.");
    }

    m_textLabel->hide();
    m_imageLabel->show();
    m_videoWidget->hide();
    ui->progressBar->setVisible(false);
}

void MainWindow::on_writeWidgetButton_clicked()
{
    LOG_INFO("");

    QString imageDownloadUrl = "https://astacms-app.s3.us-west-2.amazonaws.com/pexels-pixabay-3840x2160.jpg";

    QUrl url(imageDownloadUrl);
    QNetworkRequest request(url);

    QSslConfiguration config = request.sslConfiguration();
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    config.setProtocol(QSsl::TlsV1_2);
    request.setSslConfiguration(config);

    QNetworkReply *reply = m_ImageManager.get(request);
    QString locationPath = AppSettings::defaultAppDataLocation() + QDir::separator();
    QString fileName = locationPath + "testImage.png";

    // Show the progress bar
    ui->progressBar->setValue(0);
    ui->progressBar->setVisible(true);
    m_textLabel->hide();
    m_imageLabel->hide();
    m_videoWidget->hide();


#if QT_CONFIG(ssl)
    connect(reply, &QNetworkReply::sslErrors,[&](const QList<QSslError> &sslErrors)
    {
        for (const QSslError &error : sslErrors)
            LOG_ERROR(0, "SSL error: " + error.errorString());
        m_eventLoop.exit(-1);
    });
#endif

    connect(reply, &QNetworkReply::downloadProgress, [&](qint64 bytesReceived, qint64 bytesTotal)
    {
        if (bytesTotal > 0) {
            float bytesReceivedPercentage = static_cast<float>(bytesReceived) / static_cast<float>(bytesTotal);
            float calcPercentage = bytesReceivedPercentage * 100;
            int progress = static_cast<int>(calcPercentage);
            ui->progressBar->setValue(progress);
        }
    });

    connect(&m_ImageManager, &QNetworkAccessManager::finished, [&](QNetworkReply* reply)
    {
        bool result = false;
        QUrl url = reply->url();
        if (reply->error())
        {
            LOG_ERROR(0, "Download of %s failed: " + url.toEncoded() + reply->errorString());
        }
        else
        {
            QString locationPath = AppSettings::defaultAppDataLocation() + QDir::separator();
            QString fileName = locationPath + "testImage.png";

            result = writeFile(QDir::toNativeSeparators(fileName), reply);
        }
        reply->deleteLater();

        // Hide the progress bar when the download is finished
        ui->progressBar->setVisible(false);

        if (result)
            m_eventLoop.exit(0);
        else
            m_eventLoop.exit(-1);
    });

    m_eventLoop.exec();


    m_eventLoop.exec();

}


void MainWindow::on_muteButton_clicked()
{
    LOG_INFO("");

    toggleSystemSounds(true);
}

void MainWindow::on_unmuteButton_clicked()
{
    LOG_INFO("");

    toggleSystemSounds(false);
}

void MainWindow::toggleSystemSounds(bool mute)
{
    LOG_INFO("");

    HRESULT hr;
    IMMDeviceEnumerator* pDeviceEnumerator = NULL;
    IMMDevice* pDevice = NULL;
    IAudioEndpointVolume* pEndpointVolume = NULL;

    // Initialize the COM library
    hr = CoInitialize(NULL);
    if (FAILED(hr)) {
        LOG_INFO("CoInitialize failed: " + checkHRESULT(hr));
        return;
    }

    // Create a device enumerator
    hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (void**)&pDeviceEnumerator);
    if (FAILED(hr))
    {
        LOG_INFO("CoCreateInstance for MMDeviceEnumerator failed: " + checkHRESULT(hr));
        CoUninitialize();
        return;
    }

    // Get the default audio endpoint
    hr = pDeviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pDevice);
    if (FAILED(hr))
    {
        LOG_INFO("GetDefaultAudioEndpoint failed: " + checkHRESULT(hr));
        pDeviceEnumerator->Release();
        CoUninitialize();
        return;
    }

    // Get the endpoint volume interface
    hr = pDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL, (void**)&pEndpointVolume);
    if (FAILED(hr))
    {
        LOG_INFO("Activate for IAudioEndpointVolume failed: " + checkHRESULT(hr));
        pDevice->Release();
        pDeviceEnumerator->Release();
        CoUninitialize();
        return;
    }


    if(mute)    // Mute the volume
    {
        hr = pEndpointVolume->SetMute(TRUE, NULL);
        if (FAILED(hr))
            LOG_INFO("SetMute failed: " + checkHRESULT(hr));
        else
            LOG_INFO("System sounds muted successfully.");
    }
    else    // UnMute the volume
    {
        hr = pEndpointVolume->SetMute(FALSE, NULL);
        if (FAILED(hr))
            LOG_INFO("SetMute failed: "  + checkHRESULT(hr));
        else
            LOG_INFO("System sounds muted successfully.");
    }

    // Clean up
    pEndpointVolume->Release();
    pDevice->Release();
    pDeviceEnumerator->Release();
    CoUninitialize();
}

bool MainWindow::deleteDirectory(bool doLog)
{
    if(doLog)
        LOG_INFO("");

    QString appDataLocationString = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    if(doLog)
        LOG_INFO("App Data Location: " + appDataLocationString);

    if(m_mediaPlayer)
    {
        m_mediaPlayer->stop();
        m_mediaPlayer->setMedia(QMediaContent());
    }

    QDir appDataDir(appDataLocationString);

    if(doLog)
        LOG_INFO("Checking directory:" + appDataDir.absolutePath());

    QDir appdir = QDir(AppSettings::defaultAppDataLocation());

    QFileInfoList entList = appdir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot);

    for (int i = 0; i < entList.size(); ++i)
    {
        QFileInfo fileInfo = entList.at(i);
        if(doLog)
            LOG_INFO(fileInfo.filePath());
        bool isRemoved = QFile::remove(fileInfo.absoluteFilePath());
        if(!isRemoved)
        {
            QFile file(fileInfo.absoluteFilePath());
            if (!file.remove())
            {
                if(doLog)
                    LOG_ERROR(0,"Failed to remove file: " + fileInfo.absoluteFilePath()
                           + " Error: " + file.errorString());
            }

        }
        if(doLog)
            LOG_INFO("Remove " + QVariant(isRemoved).toString() + " " + fileInfo.absoluteFilePath());
    }
    return true;
}

void MainWindow::restartApplication()
{
    LOG_INFO("");

    LOG_INFO("startDetached is success");
    deleteDirectory(false);
    qApp->exit(EXIT_CODE_REBOOT);
}


void MainWindow::on_deleteDeviceDataAndRestartButton_clicked()
{
    LOG_INFO("");

    if (deleteDirectory())
    {
        QMessageBox::information(nullptr, "Info", "Data deleted successfully. The application will now restart.");
        restartApplication();
    }
    else
    {
        QMessageBox::warning(nullptr, "Warning", "Failed to delete data.");
    }

}

void MainWindow::on_restartAppButton_clicked()
{
    LOG_INFO("");

    restartApplication();
}

void MainWindow::on_turnUIOffButton_clicked()
{
    LOG_INFO("");

    ui->blackPage->setStyleSheet("background-color: black");
    ui->stackedWidget->setCurrentWidget(ui->blackPage);
}

void MainWindow::on_turnUIOnButton_clicked()
{
    LOG_INFO("");

    ui->stackedWidget->setCurrentWidget(ui->mainPage);
}

void MainWindow::setVolume(int value)
{
    LOG_INFO("");

    if(!m_mediaPlayer)
        QMessageBox::information(this,"Info","Please download the video first");

    QString locationPath = AppSettings::defaultAppDataLocation() + QDir::separator();
    QString filePath = locationPath + "testVideo.mp4";

    if(!QFile(filePath).exists())
        QMessageBox::information(this,"Info","Please download the video first");

    setSystemVolumeLevel(value);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    LOG_INFO("");

    qApp->quit();
}

float MainWindow::getSystemVolumeLevel()
{
    LOG_INFO("");

    CoInitialize(nullptr);

    IMMDeviceEnumerator* pDeviceEnumerator = nullptr;
    IMMDevice* pDevice = nullptr;
    IAudioEndpointVolume* pEndpointVolume = nullptr;
    float fVolume = 0.0f;

    HRESULT hr = CoCreateInstance(
        __uuidof(MMDeviceEnumerator), nullptr,
        CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator),
        (void**)&pDeviceEnumerator
    );

    if (SUCCEEDED(hr))
    {
        hr = pDeviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pDevice);
    }

    if (SUCCEEDED(hr))
    {
        hr = pDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, nullptr, (void**)&pEndpointVolume);
    }

    if (SUCCEEDED(hr))
    {
        hr = pEndpointVolume->GetMasterVolumeLevelScalar(&fVolume);
    }

    if (pEndpointVolume)
    {
        pEndpointVolume->Release();
    }

    if (pDevice)
    {
        pDevice->Release();
    }

    if (pDeviceEnumerator)
    {
        pDeviceEnumerator->Release();
    }

    CoUninitialize();
    fVolume *= 100;
    return fVolume;
}

bool MainWindow::setSystemVolumeLevel(float volume)
{
    LOG_INFO("");

    volume = volume / 100.0f;

    if (volume < 0.0f || volume > 1.0f) {
        qWarning() << "Volume level must be between 0.0 and 1.0";
        return false;
    }

    CoInitialize(nullptr);

    IMMDeviceEnumerator* pDeviceEnumerator = nullptr;
    IMMDevice* pDevice = nullptr;
    IAudioEndpointVolume* pEndpointVolume = nullptr;

    HRESULT hr = CoCreateInstance(
        __uuidof(MMDeviceEnumerator), nullptr,
        CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator),
        (void**)&pDeviceEnumerator
    );

    if (SUCCEEDED(hr))
    {
        hr = pDeviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pDevice);
    }

    if (SUCCEEDED(hr))
    {
        hr = pDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, nullptr, (void**)&pEndpointVolume);
    }

    if (SUCCEEDED(hr))
    {
        hr = pEndpointVolume->SetMasterVolumeLevelScalar(volume, nullptr);
    }

    if (pEndpointVolume)
    {
        pEndpointVolume->Release();
    }

    if (pDevice)
    {
        pDevice->Release();
    }

    if (pDeviceEnumerator)
    {
        pDeviceEnumerator->Release();
    }

    CoUninitialize();
    return SUCCEEDED(hr);
}


// Function to set HDMI display brightness using WinAPI
int MainWindow::setHDMIDisplayBrightness_WinAPI(uint8_t brightness)
{
    LOG_INFO("brightness : " + QVariant(brightness).toString());

    if (brightness > 100) brightness = 100; // check if brightness value is out of range

    // Get the current brightness of the of the HDMI display
    DWORD Min, Current, Max;
    if (!GetMonitorBrightness(hMonitor = GetMonitor(), &Min, &Current, &Max))
    {
        DWORD err = GetLastError();
        LOG_ERROR(0,"Failed to get display brightness. Error code: " + getLastErrorAsString(err));

        return -1;
    }

    // Set the brightness of the HDMI display
    if (!SetMonitorBrightness(hMonitor, brightness))
    {
        DWORD err = GetLastError();
        LOG_ERROR(0,"Failed to set HDMI display brightness. Error code: " + getLastErrorAsString(err));
        return -1;
    }
}

QString MainWindow::checkHRESULT(HRESULT hr)
{
    QString str;
    if (SUCCEEDED(hr))
    {
        str = "Operation succeeded with HRESULT:" + QString::number(hr, 16).toUpper();
    }
    else
    {
        str = "Operation failed with HRESULT:" + QString::number(hr, 16).toUpper();
    }
    return str;
}

// Function to set notebook display brightness using Windows Management Instrumentation (WMI)
int MainWindow::setNotebookDisplayBrightness_WMI(uint8_t brightness)
{
    LOG_INFO("brightness : " + QVariant(brightness).toString());

    if (brightness > 100) brightness = 100;     // check if brightness value is out of range

    IWbemLocator* pLocator = NULL;              // Pointer to the IWbemLocator interface
    IWbemServices* pNamespace = 0;              // Pointer to the IWbemServices interface
    IWbemClassObject* pClass = NULL;            // Pointer to the IWbemClassObject interface
    IWbemClassObject* pInClass = NULL;          // Pointer to the IWbemClassObject interface for input arguments
    IWbemClassObject* pInInst = NULL;           // Pointer to the IWbemClassObject interface for input instance
    IEnumWbemClassObject* pEnum = NULL;         // Pointer to the IEnumWbemClassObject interface for enumerating objects
    HRESULT hr = S_OK;                          // HRESULT variable for storing function return values

    BSTR path = SysAllocString(L"root\\wmi");                                           // Allocate a BSTR and initialize it with the specified string
    BSTR ClassPath = SysAllocString(L"WmiMonitorBrightnessMethods");                    // Allocate a BSTR and initialize it with the specified string
    BSTR MethodName = SysAllocString(L"WmiSetBrightness");                              // Allocate a BSTR and initialize it with the specified string
    BSTR ArgName0 = SysAllocString(L"Timeout");                                         // Allocate a BSTR and initialize it with the specified string
    BSTR ArgName1 = SysAllocString(L"Brightness");                                      // Allocate a BSTR and initialize it with the specified string
    BSTR bstrQuery = SysAllocString(L"Select * from WmiMonitorBrightnessMethods");      // Allocate a BSTR and initialize it with the specified string


    // Checks if any of the variables path, ClassPath, MethodName, or ArgName0 is null
    if (!path || !ClassPath || !MethodName || !ArgName0)
    {
        LOG_INFO("SysAllocString failed. Out of memory.\n");
        goto cleanup;
    }

    // Initialize Component Object Model (COM)
    hr = CoInitialize(0);
    if (FAILED(hr))
    {
        LOG_INFO("Failed to initialize security. Error code = 0x" + checkHRESULT(hr) );
        goto cleanup;
    }

    // Initialize COM security settings
    hr = CoInitializeSecurity(NULL, -1, NULL, NULL,
        RPC_C_AUTHN_LEVEL_PKT_PRIVACY,
        RPC_C_IMP_LEVEL_IMPERSONATE,
        NULL,
        EOAC_SECURE_REFS, //change to EOAC_NONE if you change dwAuthnLevel to RPC_C_AUTHN_LEVEL_NONE
        NULL);
    if (FAILED(hr))
    {
        LOG_INFO("CoInitializeSecurity returned 0x%x:" + checkHRESULT(hr));
        goto cleanup;
    }

    // Create an instance of the WbemLocator object
    hr = CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER,
        IID_IWbemLocator, (LPVOID*)&pLocator);
    if (FAILED(hr))
    {
        LOG_INFO("CoCreateInstance returned 0x%x:" + checkHRESULT(hr));
        goto cleanup;
    }

    // Connect to the WMI server
    hr = pLocator->ConnectServer(path, NULL, NULL, NULL, 0, NULL, NULL, &pNamespace);
    LOG_INFO("\n\nConnectServer returned 0x%x:" + checkHRESULT(hr));
    if (hr != WBEM_S_NO_ERROR)
        goto cleanup;

    // Set the security blanket on the proxy
    hr = CoSetProxyBlanket(pNamespace,
        RPC_C_AUTHN_WINNT,
        RPC_C_AUTHZ_NONE,
        NULL,
        RPC_C_AUTHN_LEVEL_PKT,
        RPC_C_IMP_LEVEL_IMPERSONATE,
        NULL,
        EOAC_NONE
    );

    if (hr != WBEM_S_NO_ERROR)
        goto cleanup;

    // Execute a query on the namespace
    hr = pNamespace->ExecQuery(_bstr_t(L"WQL"), //Query Language
        bstrQuery, //Query to Execute
        WBEM_FLAG_RETURN_IMMEDIATELY, //Make a semi-synchronous call
        NULL, //Context
        &pEnum //Enumeration Interface
    );

    if (hr != WBEM_S_NO_ERROR)
        goto cleanup;

    hr = WBEM_S_NO_ERROR;

    // Iterate through the objects returned by the query
    while (WBEM_S_NO_ERROR == hr)
    {
        // Get the next object from the collection
        ULONG ulReturned;
        IWbemClassObject* pObj;
        DWORD retVal = 0;

        hr = pEnum->Next(WBEM_INFINITE, //Timeout
            1, //No of objects requested
            &pObj, //Returned Object
            &ulReturned //No of object returned
        );

        if (hr != WBEM_S_NO_ERROR)
            goto cleanup;

        // Get the class object
        hr = pNamespace->GetObject(ClassPath, 0, NULL, &pClass, NULL);
        LOG_INFO("\nGetObject returned 0x%x:" + checkHRESULT(hr));
        if (hr != WBEM_S_NO_ERROR)
            goto cleanup;

        // Get the input argument and set the property
        hr = pClass->GetMethod(MethodName, 0, &pInClass, NULL);
        LOG_INFO("\nGetMethod returned 0x%x:" + checkHRESULT(hr));
        if (hr != WBEM_S_NO_ERROR)
            goto cleanup;

        // Create an instance of the input argument class
        hr = pInClass->SpawnInstance(0, &pInInst);
        LOG_INFO("\nSpawnInstance returned 0x%x:" + checkHRESULT(hr));
        if (hr != WBEM_S_NO_ERROR)
            goto cleanup;

        // Set the value of the first argument (timeout)
        VARIANT var1;
        VariantInit(&var1);
        V_VT(&var1) = VT_BSTR;
        V_BSTR(&var1) = SysAllocString(L"0");
        hr = pInInst->Put(ArgName0, 0, &var1, CIM_UINT32); //CIM_UINT64
        LOG_INFO("\nPut ArgName0 returned 0x%x:" + checkHRESULT(hr));
        VariantClear(&var1);
        if (hr != WBEM_S_NO_ERROR)
            goto cleanup;

        // Set the value of the second argument (brightness)
        VARIANT var;
        VariantInit(&var);
        var.vt = VT_UI1;
        var.uiVal = brightness;
        hr = pInInst->Put(ArgName1, 0, &var, 0);
        VariantClear(&var);
        LOG_INFO("\nPut ArgName1 returned 0x%x:" + checkHRESULT(hr));
        if (hr != WBEM_S_NO_ERROR)
            goto cleanup;

        // Call the method
        VARIANT pathVariable;
        VariantInit(&pathVariable);
        hr = pObj->Get(_bstr_t(L"__PATH"), 0, &pathVariable, NULL, NULL);
        LOG_INFO("\npObj Get returned 0x%x:" + checkHRESULT(hr));
        if (hr != WBEM_S_NO_ERROR)
            goto cleanup;

        hr = pNamespace->ExecMethod(pathVariable.bstrVal, MethodName, 0, NULL, pInInst, NULL, NULL);
        VariantClear(&pathVariable);
        LOG_INFO("\nExecMethod returned 0x%x:" + checkHRESULT(hr));
        if (hr != WBEM_S_NO_ERROR)
            goto cleanup;
    }

    LOG_INFO("Terminating normally\n");


    // Free up resources
cleanup:
    SysFreeString(path);   // Free the BSTR
    SysFreeString(ClassPath);   // Free the BSTR
    SysFreeString(MethodName);   // Free the BSTR
    SysFreeString(ArgName0);   // Free the BSTR
    SysFreeString(ArgName1);   // Free the BSTR
    SysFreeString(bstrQuery);   // Free the BSTR

    if (pClass)
        pClass->Release();   // Release the IWbemClassObject interface
    if (pInInst)
        pInInst->Release();   // Release the IWbemClassObject interface
    if (pInClass)
        pInClass->Release();   // Release the IWbemClassObject interface
    if (pLocator)
        pLocator->Release();   // Release the IWbemLocator interface
    if (pNamespace)
        pNamespace->Release();   // Release the IWbemServices interface
    CoUninitialize();   // Uninitialize the COM library
    return 0;   // Return 0 to indicate successful execution
}

// Function to set notebook display brightness using Windows PowerShell
int MainWindow::setNotebookDisplayBrightness_PShell(uint8_t brightness)
{
    LOG_INFO("brightness : " + QVariant(brightness).toString());

    if (brightness > 100) brightness = 100; // check if brightness value is out of range

    // Set the brightness of the laptop display using PowerShell command
    std::wstring command = L"powershell.exe -Command \"(Get-WmiObject -Namespace root\\wmi -Class WmiMonitorBrightnessMethods).WmiSetBrightness(0," + std::to_wstring(brightness) + L")\"";
    int result = (int)ShellExecute(nullptr, L"open", L"powershell.exe", command.c_str(), nullptr, SW_HIDE);
    if (result <= 32)
    {
        std::cout << "Failed to execute PowerShell command. Error code: " << result << std::endl;
        return -1;
    }
}
