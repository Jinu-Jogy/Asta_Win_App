#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qlabel.h"
#include "qmediaplayer.h"
#include <QMainWindow>
#include <QNetworkReply>
#include <QEventLoop>
#include <QStackedWidget>
#include <QFile>

#include <Windows.h>
#include <physicalmonitorenumerationapi.h>
#include <highlevelmonitorconfigurationapi.h>
#include <QDebug>
#include <QGraphicsOpacityEffect>
#include <iostream>
#pragma comment(lib, "Dxva2.lib")

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    static void SetWmiMonitorBrightness(BYTE targetBrightness);
    int setHDMIDisplayBrightness_WinAPI(uint8_t brightness);
public slots:
    void onValueChanged(int value);
    void on_downloadWidgetButton_clicked();
    void on_playWidgetButton_clicked();
    void on_writeWidgetButton_clicked();
    void on_readWidgetButton_clicked();
    void on_muteButton_clicked();
    void on_unmuteButton_clicked();
    void on_deleteDeviceDataAndRestartButton_clicked();
    void on_restartAppButton_clicked();
    void on_turnUIOffButton_clicked();
    void on_turnUIOnButton_clicked();
    void setVolume(int value);

protected:
     void closeEvent(QCloseEvent *event);

private slots:
     void onMediaStatusChanged(QMediaPlayer::MediaStatus status);
     void onErrorOccurred(QMediaPlayer::Error error);

private:
    Ui::MainWindow *ui;
    bool download();
    bool writeFile(QString filePath, QNetworkReply *reply);

    void toggleSystemSounds(bool mute);
    void restartApplication();

    QEventLoop m_eventLoop;
    QNetworkAccessManager m_manager;
    QNetworkAccessManager m_ImageManager;
    QMediaPlayer* m_mediaPlayer;
    QVideoWidget* m_videoWidget;
    QByteArray m_downloadedData;
    QLabel *m_imageLabel;
    QLabel *m_textLabel;
    QFile *m_imageFile;
    QFile *m_videoFile;

    QString m_currentVideoFileName = "";

    bool isBlackScreen;
    bool deleteDirectory(bool doLog = true);
    HANDLE GetMonitor();
    int getBrightness();
    float getSystemVolumeLevel();
    bool setSystemVolumeLevel(float volume);
    QString getLastErrorAsString(DWORD errorMessageID);
    int setNotebookDisplayBrightness_WMI(uint8_t brightness);
    int setNotebookDisplayBrightness_PShell(uint8_t brightness);
    QString checkHRESULT(HRESULT hr);
    void onVideoDownloadFinished(QNetworkReply *reply);
};
#endif // MAINWINDOW_H
