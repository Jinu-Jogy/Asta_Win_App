#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

#include "action_definitions.h"
#include "MainWindow.h"
#include "network/ApiBroker.h"
#include "components/HibernationClock.h"

/**
 * @brief The Controller class is where all actions take places and play the role of
 *  the reducers hub and MVC controller of the APP itself.
 * The controller instance can runs solely on fakes or stubs because all that it interac with are passed through pointed
 * pure virtual interfaces.
 */
class Controller final : public QObject
{
    Q_OBJECT

public:
    Controller(MainWindow *view,ApiBroker *api,HibernationClock *hibernationClock);
    ~Controller();

public slots:
//    ACTION_DEFINITIONS;

    void online();
    void offline();
public:
    void appStarting();

private:

    MainWindow * m_view;
    ApiBroker* m_apiBroker;
    HibernationClock*  m_hibernationClock;

    bool m_online;

};
#endif // CONTROLLER_H
