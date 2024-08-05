#ifndef LOGXMLFORMATTER_H
#define LOGXMLFORMATTER_H

#include "LogFormatter.h"
#include "LogRecord.h"

namespace logging
{
namespace formatter
{
/**
 * @brief The LogXMLFormatter class
 */
class LogXMLFormatter : public LogFormatter
{
public:
    LogXMLFormatter(bool logSourceInfos);
    virtual ~LogXMLFormatter();

    QString formatAsString(const LogRecord &record) const;
    QByteArray formatAsByteArray(const LogRecord &record) const;

    virtual QStringList getHead() const;
    virtual QStringList getTail() const;

private:
    bool m_logSourceInfos;
};

} // namespace formatter
} // namespace logging

#endif // LOGXMLFORMATTER_H
