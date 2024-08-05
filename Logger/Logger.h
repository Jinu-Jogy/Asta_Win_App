#ifndef LOGGER_H
#define LOGGER_H

#include <QMutex>

#include "LogFlags.h"
#include "LogLevel.h"
#include "Handler/LogHandler.h"
#include "LogRecord.h"

namespace logging
{
/**
 * @brief The Logger class
 */
class Logger
{
private:
    Logger();
    ~Logger();

public: //static
    static void addHandler(const handler::LogHandler *handler);
    static const QList<const handler::LogHandler *> getHandlers();
    static void removeHandler(const handler::LogHandler *handler);

    static void log(LogFlags::LogFlagsEnum flags, LogLevel::LogLevelEnum level, long kbID, const QString &kbMessage, const QString &extMessage, const QString &filename = QString(), const QString &function = QString(), int lineNo = 0);
    static void fatal(LogFlags::LogFlagsEnum flags, long kbId, const QString &kbMessage, const QString &extMessage, const QString &filename = QString(), const QString &function = QString(), int lineNo = 0);
    static void fatal(LogFlags::LogFlagsEnum flags, long kbId, const QString &kbMessage, const QString &filename = QString(), const QString &function = QString(), int lineNo = 0);
    static void error(LogFlags::LogFlagsEnum flags, long kbId, const QString &kbMessage, const QString &extMessage, const QString &filename = QString(), const QString &function = QString(), int lineNo = 0);
    static void error(LogFlags::LogFlagsEnum flags, long kbId, const QString &kbMessage, const QString &filename = QString(), const QString &function = QString(), int lineNo = 0);
    static void warning(LogFlags::LogFlagsEnum flags, long kbId, const QString &kbMessage, const QString &extMessage, const QString &filename = QString(), const QString &function = QString(), int lineNo = 0);
    static void warning(LogFlags::LogFlagsEnum flags, long kbId, const QString &kbMessage, const QString &filename = QString(), const QString &function = QString(), int lineNo = 0);
    static void info(LogFlags::LogFlagsEnum flags, long kbId, const QString &kbMessage, const QString &extMessage, const QString &filename = QString(), const QString &function = QString(), int lineNo = 0);
    static void info(LogFlags::LogFlagsEnum flags, long kbId, const QString &kbMessage, const QString &filename = QString(), const QString &function = QString(), int lineNo = 0);
    static void info(LogFlags::LogFlagsEnum flags, const QString &kbMessage, const QString &extMessage, const QString &filename = QString(), const QString &function = QString(), int lineNo = 0);
    static void info(LogFlags::LogFlagsEnum flags, const QString &kbMessage, const QString &filename = QString(), const QString &function = QString(), int lineNo = 0);
    static void debug(LogFlags::LogFlagsEnum flags, const QString &kbMessage, const QString &extMessage, const QString &filename = QString(), const QString &function = QString(), int lineNo = 0);
    static void debug(LogFlags::LogFlagsEnum flags, const QString &kbMessage, const QString &filename = QString(), const QString &function = QString(), int lineNo = 0);

private: //static
    static void log(const LogRecord &record);

    static QList<const logging::handler::LogHandler *> s_handlers;
    static QMutex *s_mutex;
};
}

#define LOG_FATAL(kbId, kbMessage)                     logging::Logger::fatal(logging::LogFlags::APP_LEVL, kbId, kbMessage, __FILE__, __FUNCTION__, __LINE__)
#define LOG_FATAL_EXT(kbId, kbMessage, extMessage)     logging::Logger::fatal(logging::LogFlags::APP_LEVL, kbId, kbMessage, extMessage, __FILE__, __FUNCTION__, __LINE__)
#define LOG_ERROR(kbId, kbMessage)                     logging::Logger::error(logging::LogFlags::APP_LEVL, kbId, kbMessage, __FILE__, __FUNCTION__, __LINE__)
#define LOG_ERROR_EXT(kbId, kbMessage, extMessage)     logging::Logger::error(logging::LogFlags::APP_LEVL, kbId, kbMessage, extMessage, __FILE__, __FUNCTION__, __LINE__)
#define LOG_WARNING(kbId, kbMessage)                   logging::Logger::warning(logging::LogFlags::APP_LEVL, kbId, kbMessage, __FILE__, __FUNCTION__, __LINE__)
#define LOG_WARNING_EXT(kbId, kbMessage, extMessage)   logging::Logger::warning(logging::LogFlags::APP_LEVL, kbId, kbMessage, extMessage, __FILE__, __FUNCTION__, __LINE__)
#define LOG_INFO_KB(kbId, kbMessage)                   logging::Logger::info(logging::LogFlags::APP_LEVL, kbId, kbMessage, __FILE__, __FUNCTION__, __LINE__)
#define LOG_INFO_KB_EXT(kbId, kbMessage, extMessage)   logging::Logger::info(logging::LogFlags::APP_LEVL, kbId, kbMessage, extMessage, __FILE__, __FUNCTION__, __LINE__)
#define LOG_INFO(kbMessage)                            logging::Logger::info(logging::LogFlags::APP_LEVL, kbMessage, __FILE__, __FUNCTION__, __LINE__)
#define LOG_INFO_EXT(kbMessage, extMessage)            logging::Logger::info(logging::LogFlags::APP_LEVL, kbMessage, extMessage, __FILE__, __FUNCTION__, __LINE__)
#define LOG_DEBUG(kbMessage)                           logging::Logger::debug(logging::LogFlags::APP_LEVL, kbMessage, __FILE__, __FUNCTION__, __LINE__)
#define LOG_DEBUG_EXT(kbMessage, extMessage)           logging::Logger::debug(logging::LogFlags::APP_LEVL, kbMessage, extMessage, __FILE__, __FUNCTION__, __LINE__)

#define DLG_FATAL(kbId, kbMessage)                     logging::Logger::fatal(logging::LogFlags::DEV_LEVEL, kbId, kbMessage, __FILE__, __FUNCTION__, __LINE__)
#define DLG_FATAL_EXT(kbId, kbMessage, extMessage)     logging::Logger::fatal(logging::LogFlags::DEV_LEVEL, kbId, kbMessage, extMessage, __FILE__, __FUNCTION__, __LINE__)
#define DLG_ERROR(kbId, kbMessage)                     logging::Logger::error(logging::LogFlags::DEV_LEVEL, kbId, kbMessage, __FILE__, __FUNCTION__, __LINE__)
#define DLG_ERROR_EXT(kbId, kbMessage, extMessage)     logging::Logger::error(logging::LogFlags::DEV_LEVEL, kbId, kbMessage, extMessage, __FILE__, __FUNCTION__, __LINE__)
#define DLG_WARNING(kbId, kbMessage)                   logging::Logger::warning(logging::LogFlags::DEV_LEVEL, kbId, kbMessage, __FILE__, __FUNCTION__, __LINE__)
#define DLG_WARNING_EXT(kbId, kbMessage, extMessage)   logging::Logger::warning(logging::LogFlags::DEV_LEVEL, kbId, kbMessage, extMessage, __FILE__, __FUNCTION__, __LINE__)
#define DLG_INFO_KB(kbId, kbMessage)                   logging::Logger::info(logging::LogFlags::DEV_LEVEL, kbId, kbMessage, __FILE__, __FUNCTION__, __LINE__)
#define DLG_INFO_KB_EXT(kbId, kbMessage, extMessage)   logging::Logger::info(logging::LogFlags::DEV_LEVEL, kbId, kbMessage, extMessage, __FILE__, __FUNCTION__, __LINE__)
#define DLG_INFO(kbMessage)                            logging::Logger::info(logging::LogFlags::DEV_LEVEL, kbMessage, __FILE__, __FUNCTION__, __LINE__)
#define DLG_INFO_EXT(kbMessage, extMessage)            logging::Logger::info(logging::LogFlags::DEV_LEVEL, kbMessage, extMessage, __FILE__, __FUNCTION__, __LINE__)


#endif // LOGGER_H
