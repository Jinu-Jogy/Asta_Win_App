#ifndef HIBERNATIONCLOCK_H
#define HIBERNATIONCLOCK_H

#include <QTime>
#include <QMutex>
#include <QTimer>
#include "AppSettings.h"
#include "../redux/ActionDispatcher.h"

/**
 * @brief The HibernationClock class is the implementation of the @see @interface IHibernationClock
 */
class HibernationClock
{
public:
    /**
     * @param updateInterval : time interval to check if
     * the app should hibernate, wake up or remain active.
     */
    HibernationClock();
    ~HibernationClock();

};
#endif // HIBERNATIONCLOCK_H
