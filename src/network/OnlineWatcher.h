#ifndef ONLINE_WATCHER_H
#define ONLINE_WATCHER_H
#include <QtNetwork>
#include "../redux/ActionDispatcher.h"
#include <QEventLoop>
#include <QNetworkAccessManager>
#include "Logger.h"

/**
 * @brief The OnlineWatcher class is the implementation of the @see @interface IOnlineWatcher,
 * Its is used a singleton instance that runs in its own thread.
 * This class runs a thread to detect the online and offline state of the astaCMSApp
 */
class OnlineWatcher final: public QThread
{
    Q_OBJECT
public:
    ~OnlineWatcher(){};
    OnlineWatcher(OnlineWatcher const&) = delete;
    OnlineWatcher(OnlineWatcher&&) = delete;

    OnlineWatcher& operator = (OnlineWatcher const&) = delete;
    OnlineWatcher& operator = (OnlineWatcher&&) = delete;

    /**
     * @brief get gets the singleton instance
     * @return
     */
    static OnlineWatcher& get()
    {
        static OnlineWatcher instance;
        return instance;
    }

    /**
     * @brief startThread starts the current thread
     */
    static void startThread()
    {
        auto& thread = get();        
        if (!thread.isRunning()) thread.start();
    }

    /**
     * @brief stopThread stops the current thread
     */
    static void stopThread()
    {
        auto& thread = get();
        thread.requestInterruption();
        //wait for thread to join within 5 secs.
        thread.wait(5000);
    }

signals:

    void backOnline() ;
    void goneOffline() ;

protected:

    /**
     * @brief OnlineWatcher constructor for OnlineWatcher
     */
    OnlineWatcher():QThread()
    {
        moveToThread(this);
//        auto& dispatcher = ActionDispatcher::get();
//        connect(this, &OnlineWatcher::backOnline,&dispatcher,&ActionDispatcher::online);
//        connect(this, &OnlineWatcher::goneOffline,&dispatcher,&ActionDispatcher::offline);
    }

    /**
     * @brief run
     * This method will run as a background process through out the application to detect the application network status
     */
    void run() override
    {
        const auto checkPeriodInterval = AppSettings::get().getSetting(AppSettings::HibernateManagerCheckInterval);

        //sanity check
        bool ok;
        auto period = checkPeriodInterval.toInt(&ok);

        // the checking period should be less than the join delay (5 seconds)
        // we need tp coerce it if necessary!
        if (!ok || period == 0 || period > 5)
            period = 2;

        do
        {
            QNetworkConfigurationManager  networkConfigurationManager;
            if (!networkConfigurationManager.isOnline())
            {
                if (m_lastOnlineState)
                    goneOffline();
                m_lastOnlineState = false;
            }
            QEventLoop  loop(this);
            QNetworkAccessManager nam;
            // An enhancement here could be checking the API and amazon end points as well.
            QNetworkRequest req((QUrl(QString("http://www.google.com"))));

            QSslConfiguration config = req.sslConfiguration();
            config.setPeerVerifyMode(QSslSocket::VerifyNone);
            config.setProtocol(QSsl::TlsV1_2);
            req.setSslConfiguration(config);

            if (QSslSocket::supportsSsl()) {
//                qDebug() << "SSL is supported.";
            } else {
//                qDebug() << "SSL is not supported.";
//                qDebug() << "Build Version:" << QSslSocket::sslLibraryBuildVersionString();
//                qDebug() << "Loaded Version:" << QSslSocket::sslLibraryVersionString();
            }

            QNetworkReply* reply = nam.get(req);
            connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
            loop.exec();
            bool online = (reply->error() == QNetworkReply::NoError);
            if (online)
            {
                if (!m_lastOnlineState)
                    emit backOnline();
                m_lastOnlineState = true;
            }
            else
            {
                LOG_INFO("Network Offline | Unable to reach http://www.google.com");
                QEventLoop  _loop(this);
                QNetworkAccessManager _nam;
                // Check if OpenDns server is reachable or not
                QNetworkRequest _req(QUrl("https://208.67.222.222"));

                QSslConfiguration config = _req.sslConfiguration();
                config.setPeerVerifyMode(QSslSocket::VerifyNone);
                config.setProtocol(QSsl::TlsV1_2);
                _req.setSslConfiguration(config);

                QNetworkReply* _reply = _nam.get(_req);
                connect(_reply, SIGNAL(finished()), &_loop, SLOT(quit()));
                _loop.exec();
                bool _online = (_reply->error() == QNetworkReply::NoError);
                if (_online)
                {
                    LOG_INFO("Network Online | Open DNS server(https://208.67.222.222) is reachable");
                    if (!m_lastOnlineState)
                        emit backOnline();
                    m_lastOnlineState = true;
                }
                else
                {
                    LOG_INFO("Network Offline | Unable to reach https://208.67.222.222");
                    if (m_lastOnlineState)
                        emit goneOffline();
                    m_lastOnlineState = false;
                }
            }
            if (!isInterruptionRequested())
                sleep(period);
        }
        while(!isInterruptionRequested());
    }

public:
    static inline bool m_lastOnlineState = false;
};

#endif // OnlineWatcher_H
