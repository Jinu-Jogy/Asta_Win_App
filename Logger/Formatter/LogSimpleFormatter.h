#ifndef LOGSIMPLEFORMATTER_H
#define LOGSIMPLEFORMATTER_H

#include "LogFormatter.h"
#include "LogRecord.h"

namespace logging
{
namespace formatter
{
/**
 * @brief The LogSimpleFormatter class
 */
class LogSimpleFormatter : public LogFormatter
{
public:
    LogSimpleFormatter();
    virtual ~LogSimpleFormatter();
    QString format(const logging::LogRecord &record) const;

    virtual QStringList getHead() const;
    virtual QStringList getTail() const;
};

} // namespace formatter
} // namespace logging

#endif // LOGSIMPLEFORMATTER_H
