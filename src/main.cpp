#define _HAS_STD_BYTE 0

#include "MainWindow.h"


#include <QApplication>
#include <QTranslator>
#include <QThread>
#include <QTimer>

#include "singleapplication.h"
#include "components/AppSettings.h"
#include "components/HibernationClock.h"
#include "utils/Globals.h"
#include "utils/Constants.h"
#include "redux/ActionDispatcher.h"
#include "redux/Controller.h"
#include "network/OnlineWatcher.h"
#include "network/ApiBroker.h"

#include "../Logger/Logger.h"
#include "../Logger/Handler/LogFileHandler.h"
#include "../Logger/Formatter/LogTextFomatter.h"
#include <QSettings>

LONG WINAPI CustomExceptionHandler(EXCEPTION_POINTERS* ExceptionInfo)
{
    // Check the exception code
    if (ExceptionInfo->ExceptionRecord->ExceptionCode == 0x8007277C)
    {
        // This is the specific error code to ignore
        return EXCEPTION_CONTINUE_EXECUTION;
    }
    // For other exceptions, continue the search
    return EXCEPTION_CONTINUE_SEARCH;
}

void make_startup_app()
{
    LOG_INFO(QCoreApplication::applicationFilePath());
    QSettings settings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run",
                       QSettings::NativeFormat);
    settings.setValue("AstaCMS",
                      QCoreApplication::applicationFilePath().replace('/', '\\'));

}


#define EXIT_CODE_REBOOT -1

void configureModernLogging()
{
    logging::formatter::LogTextFomatter *logTextFormatter = new logging::formatter::LogTextFomatter(true);
    QString logFilename = AppSettings::get().getSetting(AppSettings::LogFilePath).toString();
    logFilename = logFilename.split(".").first();
    logging::handler::LogFileHandler *logFileHandler = new logging::handler::LogFileHandler(logTextFormatter, logFilename, TE::Constants::app_log_file_extension);
    logFileHandler->setLevel(logging::LogLevel::LEVEL_ALL);
    logging::Logger::addHandler(logFileHandler);

    LOG_INFO("Configuring Log with App is success");
}

void installTranslator()
{
    QString m_langPath = "://translations";
    QDir dir(QDir::toNativeSeparators(m_langPath));
    LOG_INFO("Dir exists : " + QVariant(dir.exists()).toString());
    LOG_INFO("Language file Path : " + m_langPath);

    QTranslator translator;

    QString currentLanguage = QLocale::system().name();
    LOG_INFO("currentLanguage before truncate : " + currentLanguage);

    currentLanguage.truncate(currentLanguage.lastIndexOf('_'));
    LOG_INFO("currentLanguage after truncate : " + currentLanguage);

    QLocale locale = QLocale(currentLanguage);
    LOG_INFO("locale name : " + QVariant(locale).toString());

    QLocale::setDefault(locale);
    QString languageName = QLocale::languageToString(locale.language());
    LOG_INFO("locale name : " + QVariant(languageName).toString());

    QString resourceFileName = QDir::toNativeSeparators(QString("%1/astaCMSApp%2.qm").arg(m_langPath).arg(currentLanguage));
    LOG_INFO("resourceFileName : " + QVariant(resourceFileName).toString());

    // load the new translator
    bool result = translator.load(resourceFileName);
    LOG_INFO("translator.load(" + QVariant(resourceFileName).toString() + ") value : " + QVariant(result).toString());

    if(!result)
    {
        resourceFileName = QDir::toNativeSeparators(QString("%1/astaCMSApp%2.qm").arg(m_langPath).arg("en"));
        result = translator.load(resourceFileName);
        LOG_INFO("translator.load(" + QVariant(resourceFileName).toString() + ") value : " + QVariant(result).toString());
    }

    qApp->installTranslator(&translator);
}

int main(int argc, char *argv[])
{
    // the below line should be the first in main to write the logs properly
    configureModernLogging();
    int currentExitCode = 0;
    do
    {

        LOG_INFO("Executing Main Function");
        LOG_INFO(QString("Command Line Argument Count %1").arg(argc));
        QStringList list;
        for (int a = 0; a < argc; ++a)
        {
            LOG_INFO(QString("Command Line Argument Index %1").arg(a));
            LOG_INFO(QString("Command Line Argument Index's value %1").arg( QString::fromLocal8Bit(argv[a])));
        }

        AddVectoredExceptionHandler(1, CustomExceptionHandler);

        // Set the error mode to avoid system error dialogs
        SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX);

        SingleApplication  astaCMSApp(argc, argv);
        astaCMSApp.setWindowIcon(QIcon("://resources/ico.ico"));
        astaCMSApp.setQuitOnLastWindowClosed(false);

        make_startup_app();

        installTranslator();

        QFile SystemScreenStatusLogFile(AppSettings::defaultAppDataLocation()+"/SystemScreenStatus.txt");
        if(!SystemScreenStatusLogFile.open(QIODevice::WriteOnly  | QIODevice::Append))
        {
            LOG_ERROR(0,"Failed to create logs file for writeonly " + SystemScreenStatusLogFile.fileName());
        }
        QTextStream stream(&SystemScreenStatusLogFile);
        stream << "SYSTEM SCREEN ON - " << QTime::currentTime().toString("hh:mm:ss")<<endl;
        SystemScreenStatusLogFile.flush();
        SystemScreenStatusLogFile.close();


        QThread::currentThread()->setObjectName("Main GUI");
        LOG_INFO("Main GUI");

        AppSettings::get().initSettings();
        LOG_INFO("AstaCMS App Settings Initiated");


        OnlineWatcher::startThread();

        QTimer::singleShot(10000,[&]
        {
            LOG_INFO("Thread is " + QThread::currentThread()->objectName());
        });

        MainWindow mainView;
        HibernationClock  hibernationClock;
        ApiBroker apiBroker;

        QObject::connect( &astaCMSApp, &SingleApplication::instanceStarted, [ &]()
        {
            LOG_INFO(QString("%1").arg(astaCMSApp.isPrimary()));
            LOG_INFO("Thread is " + QThread::currentThread()->objectName());
//            mainView.silentInfo("Application is already running!");
        });

        LOG_INFO("App is about to start");
        Controller controller(&mainView,&apiBroker,&hibernationClock);
        controller.appStarting();

        currentExitCode  = astaCMSApp.exec();

        OnlineWatcher::stopThread();
    } while( currentExitCode == EXIT_CODE_REBOOT );

    return currentExitCode ;
}
