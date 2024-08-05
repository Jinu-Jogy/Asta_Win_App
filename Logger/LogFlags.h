#ifndef LOGFLAGS_H
#define LOGFLAGS_H

#include <QFlags>

namespace logging
{
/**
 * @brief The LogFlags class
 */
class LogFlags
{
public: //static
    enum LogFlag
    {
        APP_LEVL = 0x0000,
        DEV_LEVEL = 0x0001
    };
    Q_DECLARE_FLAGS(LogFlagsEnum, LogFlag);

private:
    LogFlags();
};
}
#endif // LOGFLAGS_H
