#include "LogHandler.h"

#include <QMetaObject>

using namespace logging;
using namespace logging::handler;

/**
 * @brief LogHandler::LogHandler Constructs a new logHandler object with the given \e formatter
 * @param formatter
 * @param parent
 */
LogHandler::LogHandler(const logging::formatter::LogFormatter *formatter, QObject *parent)
    : QObject(parent), m_formatter(formatter)
{
}

/**
 * @brief LogHandler::~LogHandler Destroys the  logHandler object.
 */
LogHandler::~LogHandler()
{
}

/**
 * @brief LogHandler::isLoggable
 * @param record
 * @return @e false if the current @e record to be logged has value/level less than the logHandlers level or if the logHandlers level is set to @e LEVEL_OFF
 *  <br> else return @e true
 */
bool LogHandler::isLoggable(const LogRecord &record) const
{
    int levelValue = getLevel();

    if (levelValue == LogLevel::LEVEL_OFF || record.getLevel() > levelValue)
    {
        return false;
    }

    return true;
}

/**
 * @brief LogHandler::publish_TS Writes the log @e record to the logger instance
 * This function is called everytime when the user tries to log a @e record to the LogHandler instance .
 * This pure abstract function must be reimplemented if you want to provide custom format for logging the messages.
 * @param record
 */
void LogHandler::publish_TS(const logging::LogRecord &record)
{
    QMetaObject::invokeMethod(this, "publish", Q_ARG(logging::LogRecord, record));
}

/**
 * @brief LogHandler::publish_TS Writes the log  @e message to the logger instance .
 * This function is called by the logHandler to publish each @e QString in @e message.
 * This pure abstract function must be reimplemented if you want to provide custom format for logging the messages.
 * @param message
 */
void LogHandler::publish_TS(const QStringList &message)
{
    QMetaObject::invokeMethod(this, "publish", Q_ARG(QStringList, message));
}

/**
 * @brief LogHandler::getLevel Gets the log level of the logHandler
 * @return
 */
LogLevel::LogLevelEnum LogHandler::getLevel() const
{
    return m_level;
}

/**
 * @brief LogHandler::setLevel Sets the logging level.
 * @param level specifies the log level for current instance of logHandler.
 */
void LogHandler::setLevel(LogLevel::LogLevelEnum level)
{
    m_level = level;
}

/**
 * @brief LogHandler::getFormatter Gets the \e formatter specified in the constructor of LogHandler
 * @return
 */
const logging::formatter::LogFormatter *LogHandler::getFormatter() const
{
    return m_formatter;
}
