#include "LogConsoleHandler.h"

using namespace logging;
using namespace logging::formatter;
using namespace logging::handler;

#include <QString>

#ifdef Q_OS_WIN
    #include <Windows.h>
#endif

#include <iostream>
using namespace std;

LogConsoleHandler::LogConsoleHandler(const LogFormatter *formatter) : LogHandler(formatter)
{
    publish( getFormatter()->getHead() );
}

LogConsoleHandler::~LogConsoleHandler()
{
    publish( getFormatter()->getTail() );
}

void LogConsoleHandler::publish(const LogRecord &record) const
{
    if (!isLoggable(record))
    {
        return;
    }

#ifdef Q_OS_WIN
    WORD wOldColorAttrs;
    WORD wNewColorAttrs;
    DWORD stdHandleType = (record.getLevel() <= LogLevel::LEVEL_WARNING ? STD_ERROR_HANDLE : STD_OUTPUT_HANDLE );

    HANDLE handle = GetStdHandle(stdHandleType);
    if (handle!=INVALID_HANDLE_VALUE && handle!=NULL)
    {
        switch (record.getLevel())
        {
        case LogLevel::LEVEL_FATAL:
            wNewColorAttrs = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
            break;
        case LogLevel::LEVEL_ERROR:
            wNewColorAttrs = FOREGROUND_RED | FOREGROUND_INTENSITY;
            break;
        case LogLevel::LEVEL_WARNING:
            wNewColorAttrs = FOREGROUND_RED | FOREGROUND_GREEN;
            break;
        case LogLevel::LEVEL_DEBUG:
            wNewColorAttrs = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
            break;
        case LogLevel::LEVEL_INTERNAL:
        case LogLevel::LEVEL_OFF:
        case LogLevel::LEVEL_INFO:
        case LogLevel::LEVEL_ALL:
        default:
            wNewColorAttrs = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
            break;
        }

        CONSOLE_SCREEN_BUFFER_INFO csbiInfo;

        if (GetConsoleScreenBufferInfo(handle, &csbiInfo))
        {
            wOldColorAttrs = csbiInfo.wAttributes;

            SetConsoleTextAttribute(handle, wNewColorAttrs);
        }
    }

    if (record.getLevel() <= LogLevel::LEVEL_WARNING)
        wcerr << getFormatter()->formatAsString(record).toStdWString().c_str() << endl;
    else
        wcout << getFormatter()->formatAsString(record).toStdWString().c_str() << endl;

    if (handle!=INVALID_HANDLE_VALUE && handle!=NULL)
    {
        SetConsoleTextAttribute(handle, wOldColorAttrs);
    }
#else
    if (record.getLevel() <= LogLevel::LEVEL_WARNING)
        cerr << getFormatter()->formatAsString(record).toStdString().c_str() << endl;
    else
        cout << getFormatter()->formatAsString(record).toStdString().c_str() << endl;
#endif
}

void LogConsoleHandler::publish(const QStringList &message) const
{
    foreach (QString mStr, message)
    {
#ifdef Q_OS_WIN
        wcout << mStr.toStdWString() << endl;
#else
        cout << mStr.toStdString() << endl;
#endif
    }
}
