#ifndef LOGTEXTFOMATTER_H
#define LOGTEXTFOMATTER_H

#include "LogFormatter.h"

namespace logging
{
namespace formatter
{
/**
 * @brief The LogTextFomatter class
 */
class LogTextFomatter : public LogFormatter
{
public:
    LogTextFomatter(bool logSourceInfos);
    virtual ~LogTextFomatter();

    QString formatAsString(const LogRecord &record) const;
    QByteArray formatAsByteArray(const LogRecord &record) const;

    virtual QStringList getHead() const;
    virtual QStringList getTail() const;

    QString getLogLevelAsString(const LogLevel::LogLevelEnum &level) const;
private:
    bool m_logSourceInfos;
};

} // namespace formatter
} // namespace logging

#endif // LOGTEXTFOMATTER_H
