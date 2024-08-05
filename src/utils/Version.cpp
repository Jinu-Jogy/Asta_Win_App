#include "Version.h"
#include <QDataStream>
#include "CurrentVersion.h"
#include "Logger.h"

/**
 * @brief Version::Version - Constructor for the class
 * @param major
 * @param minor
 * @param build
 */
Version::Version(int major, int minor,int build)
{
//    LOG_INFO("Versioning as " + QString(major) + "." + QString(minor) + "." + QString(build));

    m_major = major;
    m_minor = minor;
    m_buildNumber = build;
}

/**
 * @brief Version::Version - Destructor for the class
 */
Version::Version()
{
    m_major = 0;
    m_minor = 0;
    m_buildNumber = 0;
//    LOG_INFO("Versioning as " + QString(m_major) + "." + QString(m_minor) + "." + QString(m_buildNumber));
}

Version& Version::operator=(const Version & left) = default;

/**
 * @brief Version::Version - Versioning for the app
 * @param label
 */
Version::Version(const QString& label)
{
//    LOG_INFO("Versioning as " + label);

    const auto versionParts = label.split(QChar('.'), QString::SkipEmptyParts);
    auto major = 0, minor = 0, buildNumber = 0;
    do
    {
        if (versionParts.count() == 0)
            break;
        if (versionParts.count() >= 1)
            major = versionParts.at(0).toInt();
        if (versionParts.count() >= 2)
            minor = versionParts.at(1).toInt();
        if (versionParts.count() >= 3)
            buildNumber = versionParts.at(2).toInt();
    }
    while (false);

    m_major = major;
    m_minor = minor;
    m_buildNumber = buildNumber;
}

/**
 * @brief Version::operator < - Overload the operator < for versioning
 * @param left
 * @return
 */
bool Version::operator<(const Version & left)const
{
//    LOG_INFO("Overloading the operator < for versioning");

    bool success =  (left.m_major > m_major);
    if (success)
        return true;
    if (left.m_major < m_major)
        return false;
    success = (left.m_minor > m_minor);
    if (success)
        return true;
    if (left.m_minor< m_minor)
        return false;
    return left.m_buildNumber > m_buildNumber;
}

/**
 * @brief Version::operator == - Overload the operator == for versioning
 * @param left
 * @return
 */
bool Version::operator==(const Version & left) const
{
//    LOG_INFO("Overloading the operator == for versioning");

    return (left.m_major == m_major) &&
            (left.m_minor == m_minor) &&
            (left.m_buildNumber == m_buildNumber);
}

/**
 * @brief operator << - Overload the operator << for versioning
 * @param stream
 * @param version
 * @return
 */
QDataStream & operator << ( QDataStream & stream, const Version & version )
{
//    LOG_INFO("Overloading the operator << for versioning");

    stream.setVersion(QDataStream::Qt_5_14);
    stream << version.major()<< version.minor() << version.buildNumber();
    return stream;
}

/**
 * @brief operator >> - Overload the operator >> for versioning
 * @param stream
 * @param version
 * @return
 */
QDataStream & operator >> ( QDataStream & stream, Version & version )
{
//    LOG_INFO("Overloading the operator >> for versioning");

    stream.setVersion(QDataStream::Qt_5_14);
    int major,minor,buildNumber;
    stream >> major >> minor >> buildNumber;
    version = Version(major,minor,buildNumber);
    return stream;
}
