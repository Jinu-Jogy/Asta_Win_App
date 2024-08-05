#ifndef LOGFILEHANDLER_H
#define LOGFILEHANDLER_H

#include "LogHandler.h"
#include "LogRecord.h"
#include "Formatter/LogFormatter.h"

#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QVector>

namespace logging
{
namespace handler
{
/**
 * @brief The LogFileHandler class
 */
class LogFileHandler: public LogHandler
{
public:
    LogFileHandler(const formatter::LogFormatter *formatter, const QString &filename, const QString &filenameExtension);
    virtual ~LogFileHandler();

    void logFileRotation();

    const QString &currentFilename() const;

public slots:
    virtual void publish(const LogRecord &record) const;

protected:
    virtual void publish(const QStringList &message) const;

private:
    QFile *m_file;
    QTextStream *m_stream;

    bool m_handlerFailed;

    QDateTime m_currentDate;
    long m_maxFileSize;
    long m_maxFilesPerDay;
    long m_maxDaysOfLogging;

    QString m_currentFilename;
    QString m_filenamePre;
    QString m_filenamePost;

private: // Functions
    QString getFileName(const QString &filePath);
};

} // namespace handler
} // namespace logging


#endif // LOGFILEHANDLER_H
