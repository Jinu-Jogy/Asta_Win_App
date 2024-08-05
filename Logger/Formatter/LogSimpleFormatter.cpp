#include "LogSimpleFormatter.h"

using namespace logging::formatter;

#include <QString>
#include <QDateTime>

LogSimpleFormatter::LogSimpleFormatter()
{
}


LogSimpleFormatter::~LogSimpleFormatter()
{
}


QString LogSimpleFormatter::format(const logging::LogRecord &record) const
{
    QString message = QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss.zzz");
    if (record.getKbId()>0)
    {
        message += " [KB: " + QString::number(record.getKbId()) + "] ";
    } else {
        message += " ";
    }
    message += LogLevel::toString(record.getLevel()) + ":";

    if (record.getFunction().count()>0)
        message += " " + record.getFunction() + "@" + record.getFile() + ":" + QString::number(record.getLineNo());

    message += "\r\n" + record.getKbMessage();

    return message;
}

QStringList LogSimpleFormatter::getHead() const
{
    QStringList retval;

    retval << "----------------------------------------------------------------------";
    retval << QString(" Created: %1").arg(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss"));
    retval << "----------------------------------------------------------------------";

    return retval;
}

QStringList LogSimpleFormatter::getTail() const
{
    QStringList retval;

    retval << "----------------------------------------------------------------------";
    retval << QString(" Ended: %1").arg(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss"));
    retval << "----------------------------------------------------------------------";

    return retval;
}
