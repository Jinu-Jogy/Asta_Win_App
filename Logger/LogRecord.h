#ifndef LOGRECORD_H
#define LOGRECORD_H

#include <QMetaType>
#include <QString>
#include "LogFlags.h"
#include "LogLevel.h"

namespace logging
{
/**
 * @brief The LogRecord class
 */
class LogRecord
{
public:
    LogRecord();
    LogRecord(LogFlags::LogFlagsEnum flags, LogLevel::LogLevelEnum level, int kbId, const QString &kbMessage, const QString &extMessage, const QString &filename, const QString &function, int lineNo);
    virtual ~LogRecord();

    LogFlags::LogFlagsEnum getFlags() const;

    LogLevel::LogLevelEnum getLevel() const;

    int getKbId() const;
    QString getKbMessage() const;
    QString getExtMessage() const;
    bool hasExtMessage() const;

    QString getFile() const;
    QString getFunction() const;
    int getLineNo() const;

private:
    LogFlags::LogFlagsEnum m_flags;
    LogLevel::LogLevelEnum m_level;

    int m_kbId;
    QString m_kbMessage;
    QString m_extMessage;
    QString m_filename;
    QString m_function;
    int m_lineNo;
};

} // namespace logging

Q_DECLARE_METATYPE(logging::LogRecord)


#endif // LOGRECORD_H
