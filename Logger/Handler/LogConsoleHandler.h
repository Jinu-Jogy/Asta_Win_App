#ifndef LOGCONSOLEHANDLER_H
#define LOGCONSOLEHANDLER_H

#include "LogHandler.h"
#include "LogRecord.h"
#include "Formatter/LogFormatter.h"

namespace logging
{
namespace handler
{
/**
 * @brief The LogConsoleHandler class
 */
class LogConsoleHandler: public LogHandler
{
public:
    LogConsoleHandler(const formatter::LogFormatter *formatter);

    virtual ~LogConsoleHandler();

    virtual void publish(const LogRecord &record) const;

protected:
    virtual void publish(const QStringList &message) const;
};

} // namespace logging
} // namespace core

#endif // LOGCONSOLEHANDLER_H
