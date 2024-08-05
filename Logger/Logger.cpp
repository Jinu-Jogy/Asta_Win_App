#include "Logger.h"

using namespace logging;

QList<const logging::handler::LogHandler *> Logger::s_handlers;
QMutex *Logger::s_mutex = new QMutex(QMutex::Recursive);

/**
 * @brief Logger::Logger
 */
Logger::Logger()
{
}

/**
 * @brief Logger::fatal
 * @param flags
 * @param kbId
 * @param kbMessage
 * @param extMessage
 * @param filename
 * @param function
 * @param lineNo
 */
void Logger::fatal(LogFlags::LogFlagsEnum flags, long kbId, const QString &kbMessage, const QString &extMessage, const QString &filename, const QString &function, int lineNo)
{
    log(flags, LogLevel::LEVEL_FATAL, kbId, kbMessage, extMessage, filename, function, lineNo);
}

/**
 * @brief Logger::fatal
 * @param flags
 * @param kbId
 * @param kbMessage
 * @param filename
 * @param function
 * @param lineNo
 */
void Logger::fatal(LogFlags::LogFlagsEnum flags, long kbId, const QString &kbMessage, const QString &filename, const QString &function, int lineNo)
{
    log(flags, LogLevel::LEVEL_FATAL, kbId, kbMessage, "", filename, function, lineNo);
}

/**
 * @brief Logger::error
 * @param flags
 * @param kbId
 * @param kbMessage
 * @param extMessage
 * @param filename
 * @param function
 * @param lineNo
 */
void Logger::error(LogFlags::LogFlagsEnum flags, long kbId, const QString &kbMessage, const QString &extMessage, const QString &filename, const QString &function, int lineNo)
{
    log(flags, LogLevel::LEVEL_ERROR, kbId, kbMessage, extMessage, filename, function, lineNo);
}

/**
 * @brief Logger::error
 * @param flags
 * @param kbId
 * @param kbMessage
 * @param filename
 * @param function
 * @param lineNo
 */
void Logger::error(LogFlags::LogFlagsEnum flags, long kbId, const QString &kbMessage, const QString &filename, const QString &function, int lineNo)
{
    log(flags, LogLevel::LEVEL_ERROR, kbId, kbMessage, QString(), filename, function, lineNo);
}

/**
 * @brief Logger::warning
 * @param flags
 * @param kbId
 * @param kbMessage
 * @param extMessage
 * @param filename
 * @param function
 * @param lineNo
 */
void Logger::warning(LogFlags::LogFlagsEnum flags, long kbId, const QString &kbMessage, const QString &extMessage, const QString &filename, const QString &function, int lineNo)
{
    log(flags, LogLevel::LEVEL_WARNING, kbId, kbMessage, extMessage, filename, function, lineNo);
}

/**
 * @brief Logger::warning
 * @param flags
 * @param kbId
 * @param kbMessage
 * @param filename
 * @param function
 * @param lineNo
 */
void Logger::warning(LogFlags::LogFlagsEnum flags, long kbId, const QString &kbMessage, const QString &filename, const QString &function, int lineNo)
{
    log(flags, LogLevel::LEVEL_WARNING, kbId, kbMessage, "", filename, function, lineNo);
}

/**
 * @brief Logger::info
 * @param flags
 * @param kbId
 * @param kbMessage
 * @param extMessage
 * @param filename
 * @param function
 * @param lineNo
 */
void Logger::info(LogFlags::LogFlagsEnum flags, long kbId, const QString &kbMessage, const QString &extMessage, const QString &filename, const QString &function, int lineNo)
{
    log(flags, LogLevel::LEVEL_INFO, kbId, kbMessage, extMessage, filename, function, lineNo);
}

/**
 * @brief Logger::info
 * @param flags
 * @param kbId
 * @param kbMessage
 * @param filename
 * @param function
 * @param lineNo
 */
void Logger::info(LogFlags::LogFlagsEnum flags, long kbId, const QString &kbMessage, const QString &filename, const QString &function, int lineNo)
{
    log(flags, LogLevel::LEVEL_INFO, kbId, kbMessage, "", filename, function, lineNo);
}

/**
 * @brief Logger::info
 * @param flags
 * @param kbMessage
 * @param extMessage
 * @param filename
 * @param function
 * @param lineNo
 */
void Logger::info(LogFlags::LogFlagsEnum flags, const QString &kbMessage, const QString &extMessage, const QString &filename, const QString &function, int lineNo)
{
    log(flags, LogLevel::LEVEL_INFO, 0, kbMessage, extMessage, filename, function, lineNo);
}

/**
 * @brief Logger::info
 * @param flags
 * @param kbMessage
 * @param filename
 * @param function
 * @param lineNo
 */
void Logger::info(LogFlags::LogFlagsEnum flags, const QString &kbMessage, const QString &filename, const QString &function, int lineNo)
{
    log(flags, LogLevel::LEVEL_INFO, 0, kbMessage, "", filename, function, lineNo);
}

/**
 * @brief Logger::debug
 * @param flags
 * @param kbMessage
 * @param extMessage
 * @param filename
 * @param function
 * @param lineNo
 */
void Logger::debug(LogFlags::LogFlagsEnum flags, const QString &kbMessage, const QString &extMessage, const QString &filename, const QString &function, int lineNo)
{
    log(flags, LogLevel::LEVEL_DEBUG, 0, kbMessage, extMessage, filename, function, lineNo);
}

/**
 * @brief Logger::debug
 * @param flags
 * @param kbMessage
 * @param filename
 * @param function
 * @param lineNo
 */
void Logger::debug(LogFlags::LogFlagsEnum flags, const QString &kbMessage, const QString &filename, const QString &function, int lineNo)
{
    log(flags, LogLevel::LEVEL_DEBUG, 0, kbMessage, "", filename, function, lineNo);
}

/**
 * @brief Logger::log
 * @param flags
 * @param level
 * @param kbId
 * @param kbMessage
 * @param extMessage
 * @param filename
 * @param function
 * @param lineNo
 */
void Logger::log( LogFlags::LogFlagsEnum flags,
                  LogLevel::LogLevelEnum level,
                    long kbId,
                    const QString &kbMessage,
                    const QString &extMessage,
                    const QString &filename,
                    const QString &function,
                    int lineNo)
{
    LogRecord logRecord(flags, level, kbId, kbMessage, extMessage, filename, function, lineNo);
    log(logRecord);
}

/**
 * @brief Logger::log
 * @param record
 */
void Logger::log(const LogRecord &record)
{
    QMutexLocker locker(s_mutex);

    // Send the LogRecord  to all our Handlers.
    const handler::LogHandler *handler;
    foreach (handler, getHandlers())
    {
        //handler->publish(record);
        const_cast<handler::LogHandler *>(handler)->publish_TS(record);
    }
}

/**
 * @brief Logger::addHandler
 * @param handler
 */
void Logger::addHandler(const handler::LogHandler *handler)
{
    QMutexLocker locker(s_mutex);

    s_handlers.append(handler);
}

/**
 * @brief Logger::removeHandler
 * @param handler
 */
void Logger::removeHandler(const handler::LogHandler *handler)
{
    QMutexLocker locker(s_mutex);

    s_handlers.removeAll(handler);
}

/**
 * @brief Logger::getHandlers
 * @return
 */
const QList<const handler::LogHandler *> Logger::getHandlers()
{
    QMutexLocker locker(s_mutex);

    return s_handlers;
}
