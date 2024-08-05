#include "LogLevel.h"

using namespace logging;

/**
 * @brief LogLevel::LogLevel
 */
LogLevel::LogLevel()
{
}

/**
 * @brief LogLevel::toString
 * @param logLevel
 * @return
 */
QString LogLevel::toString(LogLevel::LogLevelEnum logLevel)
{
    switch (logLevel)
    {
    case LEVEL_INTERNAL: return "INTERNAL";
    case LEVEL_OFF: return "OFF";
    case LEVEL_FATAL: return "FATAL";
    case LEVEL_ERROR: return "ERROR";
    case LEVEL_WARNING: return "WARNING";
    case LEVEL_INFO: return "INFO";
    case LEVEL_DEBUG: return "DEBUG";
    case LEVEL_ALL: return "ALL";
    default: return "OFF";
    }
}

/**
 * @brief LogLevel::fromString
 * @param logLevelString
 * @return
 */
LogLevel::LogLevelEnum LogLevel::fromString(const QString &logLevelString)
{
    if (logLevelString.compare("INTERNAL", Qt::CaseInsensitive)==0) return LEVEL_INTERNAL;
    else if (logLevelString.compare("OFF", Qt::CaseInsensitive)==0) return LEVEL_OFF;
    else if (logLevelString.compare("FATAL", Qt::CaseInsensitive)==0) return LEVEL_FATAL;
    else if (logLevelString.compare("ERROR", Qt::CaseInsensitive)==0) return LEVEL_ERROR;
    else if (logLevelString.compare("WARNING", Qt::CaseInsensitive)==0) return LEVEL_WARNING;
    else if (logLevelString.compare("INFO", Qt::CaseInsensitive)==0) return LEVEL_INFO;
    else if (logLevelString.compare("DEBUG", Qt::CaseInsensitive)==0) return LEVEL_DEBUG;
    else if (logLevelString.compare("ALL", Qt::CaseInsensitive)==0) return LEVEL_ALL;
    else return LEVEL_OFF;
}
