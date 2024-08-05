#include "LogTextFomatter.h"
#include "qdebug.h"

using namespace logging;
using namespace logging::formatter;

#include <QString>
#include <QDateTime>
#include <QObject>
#include <QDebug>

LogTextFomatter::LogTextFomatter(bool logSourceInfos) : m_logSourceInfos(logSourceInfos)
{
}


LogTextFomatter::~LogTextFomatter()
{
}

QString LogTextFomatter::getLogLevelAsString(const LogLevel::LogLevelEnum &level) const
{
    switch (level)
    {
        case LogLevel::LEVEL_INTERNAL:
                return "Internal";
            break;
        case LogLevel::LEVEL_OFF:
                return "OFF";
            break;
        case LogLevel::LEVEL_FATAL:
                return "Critical";
            break;
        case LogLevel::LEVEL_ERROR:
                return "Error";
            break;
        case LogLevel::LEVEL_WARNING:
                return "Warning";
            break;
        case LogLevel::LEVEL_INFO:
                return "Info";
            break;
        case LogLevel::LEVEL_DEBUG:
                return "Debug";
            break;
        case LogLevel::LEVEL_ALL:
                return "All";
            break;
        default:
            break;
    }
    return "";
}

QString LogTextFomatter::formatAsString(const LogRecord &record) const
{
//    QString message = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss.zzz");
//    if (record.getKbId()>0)
//    {
//        message += QString(" [KB: %1] ").arg(record.getKbId(), 6);
//    } else {
//        message += " [KB: ------] ";
//    }
//    message += LogLevel::toString(record.getLevel()) + ": " + record.getKbMessage();

//    if (m_logSourceInfos && record.getFunction().count()>0)
//        message += "\r\n" + record.getFunction() + "@" + record.getFile() + ":" + QString::number(record.getLineNo());

    QString message = QObject::tr("%1 | %2 | %3 | %4 | %5 | %6").
        arg(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss")).
        arg(getLogLevelAsString(record.getLevel())).
        arg(record.getLineNo()).
        arg(QString(record.getFile()).
            section('\\', -1)).			// File name without file path
        arg(QString(record.getFunction().split("::").last())).
        arg(record.getKbMessage());


    if (record.getKbId() > 0)
        message += QString(" | [KB: %1] ").arg(record.getKbId(), 6);

    QString extMessage = record.getExtMessage();
    if (!extMessage.isEmpty()) message += " | " + extMessage;

    qDebug() << message;

    return message;
}

QByteArray LogTextFomatter::formatAsByteArray(const LogRecord &record) const
{
    return formatAsString(record).toUtf8();
}

QStringList LogTextFomatter::getHead() const
{
    QStringList retval;

    retval << "----------------------------------------------------------------------";
    retval << QString(" Created: %1").arg(QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss"));
    retval << "----------------------------------------------------------------------";

    return retval;
}

QStringList LogTextFomatter::getTail() const
{
    QStringList retval;

    retval << "----------------------------------------------------------------------";
    retval << QString(" Ended: %1").arg(QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss"));
    retval << "----------------------------------------------------------------------";

    return retval;
}
