#include "Controller.h"
#include "network/OnlineWatcher.h"

#include <QMessageBox>

Controller::Controller(MainWindow *view, ApiBroker *api, HibernationClock *hibernationClock):
    m_view(view),
    m_apiBroker(api),
    m_hibernationClock(hibernationClock),m_online(true)
{
    connect(&OnlineWatcher::get(), &OnlineWatcher::backOnline,this,&Controller::online);
    connect(&OnlineWatcher::get(), &OnlineWatcher::goneOffline,this,&Controller::offline);

}

Controller::~Controller()
{

}

void Controller::appStarting()
{
    m_view->showMaximized();
}

void Controller::online()
{
    LOG_INFO("Network is ONLINE now");

    if(!m_online)
        QMessageBox::information(m_view,"Network Status","Online");

    m_online = true;

    QString date = QDate::currentDate().toString("dd-MM-yyyy");
    QFile networkStatusLogFile(AppSettings::defaultAppDataLocation()+"/NetworkStatus_"+date+".txt");
    if(!networkStatusLogFile.open(QIODevice::WriteOnly  | QIODevice::Append))
    {
        LOG_ERROR(0,"Failed to create logs file for writeonly " + networkStatusLogFile.fileName());
    }
    QTextStream stream(&networkStatusLogFile);
    stream << "Network is ONLINE - " << QDateTime::currentDateTime().toString("hh:mm:ss ,dd-MM-yyyy")<<endl;

    networkStatusLogFile.flush();
    networkStatusLogFile.close();
}

void Controller::offline()
{
    LOG_INFO("Network is OFFLINE now");

    if(m_online)
        QMessageBox::information(m_view,"Network Status","Offline");

    m_online = false;

    QString date = QDate::currentDate().toString("dd-MM-yyyy");
    QFile networkStatusLogFile(AppSettings::defaultAppDataLocation()+"/NetworkStatus_"+date+".txt");
    if(!networkStatusLogFile.open(QIODevice::WriteOnly  | QIODevice::Append))
    {
        LOG_ERROR(0,"Failed to create logs file for writeonly " + networkStatusLogFile.fileName());
    }
    QTextStream stream(&networkStatusLogFile);
    stream << "Network is OFFLINE - " << QDateTime::currentDateTime().toString("hh:mm:ss ,dd-MM-yyyy")<<endl;
    networkStatusLogFile.flush();
    networkStatusLogFile.close();
}
