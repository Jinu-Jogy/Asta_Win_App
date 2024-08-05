#include "LogFileHandler.h"

#include <QDir>
#include <QDateTime>
#include <QCoreApplication>
#include "components/AppSettings.h"

using namespace logging::formatter;
using namespace logging::handler;

/**
 * @brief LogFileHandler::LogFileHandler
 * @param formatter
 * @param filename
 * @param filenameExtension
 */
LogFileHandler::LogFileHandler(const LogFormatter *formatter, const QString &filename, const QString &filenameExtension)
    : LogHandler(formatter), m_file(NULL), m_stream(NULL), m_handlerFailed(false), m_currentDate(QDateTime::currentDateTime().date())

{
    m_filenamePre = filename;

    m_filenamePost = QString(".%1").arg(filenameExtension);
    m_currentFilename = m_filenamePre + m_currentDate.toString("ddMMyyyy") + m_filenamePost;

    m_maxFileSize = 10*1024*1024 ;
    m_maxFilesPerDay =  24;
    m_maxDaysOfLogging = 30;

    logFileRotation();
}

/**
 * @brief LogFileHandler::~LogFileHandler
 */
LogFileHandler::~LogFileHandler()
{
    if (m_stream!=NULL)
    {
        publish( getFormatter()->getTail() );
        delete m_stream;
    }

    if (m_file!=NULL)
    {
        m_file->close();
        delete m_file;
    }
}

/**
 * @brief LogFileHandler::publish
 * @param record
 */
void LogFileHandler::publish(const logging::LogRecord &record) const
{
    if (/*m_stream==NULL ||*/ !isLoggable(record) /*|| m_handlerFailed*/)
    {
        return;
    }

    LogFileHandler *logFileHandlerNonConst = const_cast<LogFileHandler*>(this);
    if (logFileHandlerNonConst!=NULL) logFileHandlerNonConst->logFileRotation();

    if (m_stream!=NULL)
    {
        (*m_stream) << getFormatter()->formatAsString(record) << "\r\n";
        m_stream->flush();
    }
}

/**
 * @brief LogFileHandler::publish
 * @param message
 */
void LogFileHandler::publish(const QStringList &message) const
{
    if (m_stream==NULL || m_handlerFailed)
    {
        return;
    }

    foreach (QString mStr, message)
    {
        if (m_stream!=NULL) (*m_stream) << mStr << "\r\n";
    }

    m_stream->flush();
}

const QString &LogFileHandler::currentFilename() const
{
    return m_currentFilename;
}

/**
 * @brief LogFileHandler::getFileName
 * @param filePath
 * @return
 */
QString LogFileHandler::getFileName(const QString &filePath)
{
    if(filePath.contains(QDir::separator()))
        return filePath.split(QDir::separator()).last();

    return filePath;
}

/**
 * @brief LogFileHandler::logFileRotation
 */
void LogFileHandler::logFileRotation()
{
    bool rotateRequired = false;

    // check if Stream is NULL
    if (m_stream == NULL) rotateRequired = true;

    // check if date has changed
    if (!rotateRequired && QDateTime::currentDateTime().daysTo(m_currentDate)!=0) rotateRequired = true;

    if (!rotateRequired)
    {
        QFile fileToCheckForSize(m_currentFilename);

        //int temp = fileToCheckForSize.size();

        // check for filesize reached
        if (m_maxFileSize>0 && fileToCheckForSize.exists() && fileToCheckForSize.size()>m_maxFileSize ) rotateRequired = true;
    }

    if (!rotateRequired) return;

    if (m_stream != NULL)
    {
        publish( getFormatter()->getTail() );

        delete m_stream;
        m_stream = NULL;
    }

    if (m_file != NULL)
    {
        m_file->close();
        delete m_file;
        m_file = NULL;
    }

    if (m_maxFilesPerDay<=1)
    {
        QFile::remove(m_filenamePre + m_currentDate.toString("ddMMyyyy") + m_filenamePost);
    } else {
        for (int i = m_maxFilesPerDay; i>=2; i--)
        {
            QString from   = m_filenamePre + m_currentDate.toString("ddMMyyyy") + "_" + QString::number(i - 2) + m_filenamePost;
            if (i==2) from = m_filenamePre + m_currentDate.toString("ddMMyyyy") + m_filenamePost;
            QString to     = m_filenamePre + m_currentDate.toString("ddMMyyyy") + "_" + QString::number(i - 1) + m_filenamePost;

            if (i==m_maxFilesPerDay) QFile::remove(to);

            QFile::rename(from, to);
        }
    }

    //added
    int dateDifference;
    QString path = QCoreApplication::applicationDirPath();
    QDir dir(path);
    dir.setFilter(QDir::Files | QDir::NoDotAndDotDot);

    QString fileNameFilter = QString("%1*%2").arg(getFileName(m_filenamePre.split("/").last())).arg(m_filenamePost);
    dir.setNameFilters(QStringList() << fileNameFilter);

    QFileInfoList fileList = dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot);

    foreach (QFileInfo fileInfo, fileList)
    {
        QDateTime currentTime = QDateTime::currentDateTime();
        if(fileInfo.created().daysTo(currentTime)> fileInfo.lastModified().daysTo(currentTime)) dateDifference = fileInfo.created().daysTo(currentTime);
        else dateDifference = fileInfo.lastModified().daysTo(currentTime);
        if(dateDifference > m_maxDaysOfLogging)
        {
            QFile fileDelete(QCoreApplication::applicationDirPath() + QDir::separator() + fileInfo.fileName());
            fileDelete.remove();
        }
    }


    // set new current date, as time has to count from now on
    m_currentDate = QDateTime::currentDateTime();

    m_currentFilename = m_filenamePre + m_currentDate.toString("ddMMyyyy") + m_filenamePost;

    QFile m_newFile(m_currentFilename);

    if (m_newFile.exists() && m_stream)
    {
        m_handlerFailed = true;

        // Here we write later our error message to the logger - Rotate failed

        return;
    }

    m_file = new QFile(m_currentFilename);

//    if (!m_file->open(QFile::WriteOnly | QIODevice::Append)) {
//        qWarning() << "Failed to open" << m_file->fileName() << "for write:" << m_file->errorString();
//    }

    if (!m_file->open(QIODevice::WriteOnly | QIODevice::Append))
    {
        delete m_file;
        m_file = NULL;

        m_handlerFailed = true;

        // Here we write later our error message to the logger - File open failed

        return;
    }

    m_stream = new QTextStream(m_file);

    // We add the filename to the crash reporter
    //LiCrashRpt::addFile(m_currentFilename, "Log File");

    publish( getFormatter()->getHead() );
}
