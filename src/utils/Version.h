#ifndef VERSION_H
#define VERSION_H

class  QDataStream;
class Version;
QDataStream & operator << ( QDataStream & stream, const Version & version );
QDataStream & operator >> ( QDataStream & stream, Version & version );

#include <QString>
#include <QStringList>
#include <QMetaType>
#include "Globals.h"

/**
 * @brief The Version class represents a version info, it possess
 * a static member  Version::CurrentAppversion  which should be initialized
 * with the current software version, this static member should be initialized
 * once and then used as a read only
 */
class  Version final
{

    int m_major;
    int m_minor;
    int m_buildNumber;

public:
    Version(int major, int minor,int build);
    Version();
    ~Version() = default;

    QString toString()  const
    {
        //Not handling the commit hash currently
        //return QString("%1.%2.%3 \n commit hash : %4").arg(m_major).arg(m_minor).arg(m_buildNumber).arg(commit_hash);
        return QString("%1.%2.%3").arg(m_major).arg(m_minor).arg(m_buildNumber);
    }

    int major() const
    {
        return m_major;
    }
    int minor() const
    {
        return m_minor;
    }
    int buildNumber() const
    {
        return m_buildNumber;
    }

    Version(const QString & label);

    bool isZero()
    {
        return major()==0 && minor()==0 && buildNumber()==0;
    }

    Version & operator=(const Version & left);
    bool operator <(const Version & left) const;
    bool operator==(const Version & left) const;


    static Version currentVersion()
    {
        return Version::CurrentAppversion;
    }

private:
    static Version CurrentAppversion;
};
Q_DECLARE_METATYPE(Version)

#endif // VERSION_H
