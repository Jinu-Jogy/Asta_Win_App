#ifndef LOGLEVEL_H
#define LOGLEVEL_H

#include <QString>

namespace logging
{
/**
 * @brief The LogLevel class
 */
class LogLevel
{
public: //static
    enum LogLevelEnum
    {
        LEVEL_INTERNAL = 0,
        LEVEL_OFF = 1,
        LEVEL_FATAL = 10,
        LEVEL_ERROR = 20,
        LEVEL_WARNING = 30,
        LEVEL_INFO = 40,
        LEVEL_DEBUG = 50,
        LEVEL_ALL = 60
    };

    static QString toString(LogLevelEnum logLevel);
    static LogLevelEnum fromString(const QString &logLevelString);

private:
    LogLevel();
};
}
#endif // LOGLEVEL_H
