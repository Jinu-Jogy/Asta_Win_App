#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QSettings>
#include <QCoreApplication>
#include <QStandardPaths>
#include <QDir>
#include <QTime>
#include <QDebug>
#include "../utils/Constants.h"
#include "../utils/Globals.h"

/**
 * A singleton wrapper class around QSettings providing:
 * An enumerated and to string translatable settings entries.
 * Hard coded default values for the necessary settings.
 */
class AppSettings final
{
public:
    /**
     * @brief The SettingsKeys enum enumerates the settings handled by this class.
     */
    enum SettingsKeys
    {
        HibernateManagerCheckInterval,
        LogFilePath,
        StreamsLogDir,
        StreamsThumbnailsDir,
        SessionFile,
        StreamerCommandLinePattern,
        ApiUrl
    };

    /**
     * @brief get : AppSettings is intended to be a singleton.
     * @return A reference to the static instance of the singleton.
     */
    static AppSettings& get() noexcept
    {
        
        static AppSettings instance;
        return instance;
    }

    AppSettings(AppSettings const&) = delete;
    AppSettings(AppSettings&&) = delete;
    AppSettings& operator=(AppSettings const&) = delete;
    AppSettings& operator=(AppSettings&&) = delete;
    ~AppSettings() = default;

    /**
     * @brief getDefaultSetting : returns the default built-in setting value of the given settings
     * key.
     * @param settingKey
     * @return
     */
    QVariant getDefaultSetting(const SettingsKeys& settingKey)  noexcept
    {
        switch (settingKey)
        {
            case HibernateManagerCheckInterval:     return 1000;
            case LogFilePath:                       return defaultLogFilePath();
            case SessionFile:                       return defaultSessionFilePath();
            case StreamsLogDir:                     return defaultStreamsLogDir();
            case StreamsThumbnailsDir:              return defaultStreamsThumbnailsDir();
            case StreamerCommandLinePattern:        return QString(TE::Constants::streamer_cli_pattern);
            default:                                return QVariant();
        }
    }

    /**
     * @brief getSetting : returns the current setting value of the given settings
     * @param settingKey
     * @return
     */
    QVariant getSetting(SettingsKeys settingKey) noexcept
    {
        QSettings settings(configFilePath(),QSettings::IniFormat);
        const auto settingName = get().translateSettingEnum(settingKey);
        const auto  value = settings.value(settingName, get().getDefaultSetting(settingKey));
        return value;
    }

    /**
     * @brief setSetting : sets the value of a given setting key.
     * @param settingKey
     * @param value
     */
    void setSetting(SettingsKeys settingKey, const QVariant& value) noexcept
    {
        QSettings settings(configFilePath(),QSettings::IniFormat);
        const auto settingName = get().translateSettingEnum(settingKey);
        settings.setValue(settingName, value);
    }

    /**
     * @brief initSettings : syncs the default settings to the backend storage (the ini file) , this should be called
     * when the app is starting
     */
    void initSettings()
    {
        QSettings settings(configFilePath(),QSettings::IniFormat);
        if (settings.childKeys().count() == 0)
        {
            setSetting(SettingsKeys::ApiUrl,                        getDefaultSetting(SettingsKeys::ApiUrl));
            setSetting(SettingsKeys::LogFilePath,                   getDefaultSetting(SettingsKeys::LogFilePath));
            setSetting(SettingsKeys::SessionFile,                   getDefaultSetting(SettingsKeys::SessionFile));
            setSetting(SettingsKeys::StreamsLogDir,                 getDefaultSetting(SettingsKeys::StreamsLogDir));
            setSetting(SettingsKeys::StreamsThumbnailsDir,          getDefaultSetting(SettingsKeys::StreamsThumbnailsDir));
            setSetting(SettingsKeys::HibernateManagerCheckInterval, getDefaultSetting(SettingsKeys::HibernateManagerCheckInterval));
            setSetting(SettingsKeys::StreamerCommandLinePattern,    getDefaultSetting(SettingsKeys::StreamerCommandLinePattern));
        }
    }

    /**
     * @brief defaultAppDataLocation: returns the writable app location that we will be suing
     * to write the session file and log and thumbnails etc...
     * @return
     */
    static QString defaultAppDataLocation()
    {
        //app should run with admin rights
        const auto list = QStandardPaths::standardLocations(QStandardPaths::DataLocation);
        Q_ASSERT(list.count()>0);
#if WIN32 || WIN64
        //we want to return C:\AppData
        if (list.count()==1)  return list.at(0);
        const auto location = list.at(1);
#else
        const auto location = list.at(0);
#endif
        return location;
    }

    /**
     * @brief appLockFilePath:
     * @returns the path to the updater lock file. this is a sepcial readonly "by this function" setting.
     */
    static QString appLockFilePath()
    {
        const auto dir =QDir(defaultAppDataLocation());
        const auto result =dir.absoluteFilePath(TE::Constants::app_lock_file);
        return result;
    }

    QString defaultLogFilePath() const
    {
        const auto dir =QDir(defaultAppDataLocation());
        const auto result =dir.absoluteFilePath(TE::Constants::app_log_file);
        return result;
    }

private:
    AppSettings()
    {
        //avoid paths with spaces
        QCoreApplication::setOrganizationName(replaceSpaces(QString(ORGANIZATION_NAME)));
        QCoreApplication::setOrganizationDomain(replaceSpaces(QString(ORGANIZATION_DOMAIN)));
        QCoreApplication::setApplicationName(replaceSpaces(QString(APPLICATION_NAME)));
        QSettings::setDefaultFormat(QSettings::IniFormat);
        QSettings::setPath(QSettings::IniFormat,QSettings::SystemScope,configFilePath());
    }
    QString translateSettingEnum(SettingsKeys settings) noexcept
    {
        switch (settings)
        {
            case HibernateManagerCheckInterval:     return "HibernateManagerCheckInterval";
            case LogFilePath:                       return "LogFilePath";
            case SessionFile:                       return "SessionFile";
            case StreamsLogDir:                     return "StreamsLogDir";
            case StreamsThumbnailsDir :             return "StreamsThumbnailsDir";
            case StreamerCommandLinePattern :       return "StreamerCommandLinePattern";
            default:                                return "";
        }
    }
    QString replaceSpaces(const QString& name) const
    {
        return name.trimmed().replace(" ","_");
    }
    QString defaultSessionFilePath()  const
    {
        const auto dir = QDir(defaultAppDataLocation());
        const auto result = dir.absoluteFilePath(TE::Constants::app_session_file);
        return result;
    }
    QString configFilePath()  const
    {
        const auto dir = QDir(defaultAppDataLocation());
        const auto result = dir.absoluteFilePath(TE::Constants::app_config_file);
        return result;
    }
    QString defaultStreamsLogDir()const
    {
        const auto dir = QDir(defaultAppDataLocation());
        const auto result = dir.path()+ QDir::separator()+ QString(TE::Constants::streams_logs_dir);
        return result;
    }
    QString defaultStreamsThumbnailsDir()const
    {
        const auto dir = QDir(defaultAppDataLocation());
        const auto result = dir.path()+ QDir::separator()+ QString(TE::Constants::streams_thumbnails_dir);
        return result;
    }

};
#endif // APPSETTINGS_H
