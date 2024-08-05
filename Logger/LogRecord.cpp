#include "LogRecord.h"

using namespace logging;


LogRecord::LogRecord() :
    m_flags(0), m_level(LogLevel::LEVEL_OFF), m_kbId(0), m_kbMessage(""),
    m_extMessage(""), m_filename(""), m_function(""), m_lineNo(0)
{

}

/**
 * @brief LogRecord::LogRecord
 * @param flags
 * @param level
 * @param kbId
 * @param kbMessage
 * @param extMessage
 * @param filename
 * @param function
 * @param lineNo
 */
LogRecord::LogRecord( LogFlags::LogFlagsEnum flags,
                          LogLevel::LogLevelEnum level,
                          int kbId,
                          const QString
                          &kbMessage,
                          const QString &extMessage,
                          const QString &filename,
                          const QString &function,
                          int lineNo
                          ) :
    m_flags(flags), m_level(level), m_kbId(kbId), m_kbMessage(kbMessage),
    m_extMessage(extMessage), m_filename(filename), m_function(function),
    m_lineNo(lineNo)
{

}

/**
 * @brief LogRecord::~LogRecord
 */
LogRecord::~LogRecord()
{
}

/**
 * @brief LogRecord::getFlags
 * @return
 */
LogFlags::LogFlagsEnum LogRecord::getFlags() const
{
    return m_flags;
}

/**
 * @brief LogRecord::getLevel
 * @return
 */
LogLevel::LogLevelEnum LogRecord::getLevel() const
{
    return m_level;
}

/**
 * @brief LogRecord::getFile
 * @return
 */
QString LogRecord::getFile() const
{
    return m_filename;
}

/**
 * @brief LogRecord::getFunction
 * @return
 */
QString LogRecord::getFunction() const
{
    return m_function;
}

/**
 * @brief LogRecord::getLineNo
 * @return
 */
int LogRecord::getLineNo() const
{
    return m_lineNo;
}

/**
 * @brief LogRecord::getKbMessage
 * @return
 */
QString LogRecord::getKbMessage() const
{
    return m_kbMessage;
}

/**
 * @brief LogRecord::getExtMessage
 * @return
 */
QString LogRecord::getExtMessage() const
{
    return m_extMessage;
}

bool LogRecord::hasExtMessage() const
{
    return !m_extMessage.isEmpty();
}

/**
 * @brief LogRecord::getKbId
 * @return
 */
int LogRecord::getKbId() const
{
    return m_kbId;
}
