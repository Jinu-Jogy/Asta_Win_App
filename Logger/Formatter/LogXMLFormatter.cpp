#include "LogXMLFormatter.h"

#include <Logger.h>

#include <QString>
#include <QDateTime>
#include <QFile>
#include <QDir>

using namespace logging;
using namespace logging::formatter;


LogXMLFormatter::LogXMLFormatter(bool logSourceInfos) :  m_logSourceInfos(logSourceInfos)
{
}

LogXMLFormatter::~LogXMLFormatter()
{
}

QString LogXMLFormatter::formatAsString(const LogRecord &record) const
{
    QString message = "";
    message += "<LogEntry level=\"" + LogLevel::toString(record.getLevel()) + "\" time=\"" +  QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss.zzz") + "\"";
    if (m_logSourceInfos) message += " file=\"" + record.getFile() + "\" line=\"" + QString::number(record.getLineNo()) + "\" function=\"" + record.getFunction() + "\">";
    message += ">";

    message += "\r\n";

    message += "<KB id=\"" + QString::number(record.getKbId()) + "\">";
    message += "\r\n";
    message += "<![CDATA[" + record.getKbMessage() + "]]>";
    message += "\r\n";
    message += "</KB>";
    message += "\r\n";

    if (record.getExtMessage().count()>0)
    {
        message += "<ExtMsg>";
        message += "\r\n";
        message += "<![CDATA[" + record.getExtMessage() + "]]>";
        message += "\r\n";
        message += "</ExtMsg>";
        message += "\r\n";
    }

    message += "</LogEntry>";

    return message;
}

QByteArray LogXMLFormatter::formatAsByteArray(const LogRecord &record) const
{
    return formatAsString(record).toUtf8();
}

QStringList LogXMLFormatter::getHead() const
{
    QStringList retval;

    retval << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
    retval << QString("<TangoInterface type=\"LogFile\">");

    return retval;
}

QStringList LogXMLFormatter::getTail() const
{
    QStringList retval;
    retval << QString("</TangoInterface>");

    return retval;
}
