#ifndef LOGHANDLER_H
#define LOGHANDLER_H

#include <QObject>

#include "LogLevel.h"
#include "LogRecord.h"
#include "Formatter/LogFormatter.h"

namespace logging
{
namespace handler
{
/**
 * @brief The LogHandler class
 */
class LogHandler: public QObject
{
    Q_OBJECT

public:
    LogHandler(const formatter::LogFormatter *formatter, QObject *parent = 0);

    virtual ~LogHandler();

    LogLevel::LogLevelEnum getLevel() const;

    void setLevel(LogLevel::LogLevelEnum level);

    const formatter::LogFormatter *getFormatter() const;

    bool isLoggable(const LogRecord &record) const;

private:
    LogLevel::LogLevelEnum m_level;
    const formatter::LogFormatter *m_formatter;

public slots:

    virtual void publish_TS(const logging::LogRecord &record);
    virtual void publish(const logging::LogRecord &record) const = 0;


protected slots:

    virtual void publish_TS(const QStringList &message);
    virtual void publish(const QStringList &message) const = 0;
};
}
}

#endif // LOGHANDLER_H
