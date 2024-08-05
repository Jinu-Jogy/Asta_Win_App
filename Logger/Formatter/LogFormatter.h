#ifndef LOGFORMATTER_H
#define LOGFORMATTER_H

#include <QStringList>
#include "LogRecord.h"

namespace logging
{
namespace formatter
{
/**
 * @brief The LogFormatter class represents the base class of which format should we should use it for logging.
 */
class LogFormatter
{
protected:
    LogFormatter();
    virtual ~LogFormatter();

public:
    virtual QString formatAsString(const LogRecord &record) const = 0;
    virtual QByteArray formatAsByteArray(const LogRecord &record) const = 0;

    virtual QStringList getHead() const;
    virtual QStringList getTail() const;
};
}
}
#endif // LOGFORMATTER_H
