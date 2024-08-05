#ifndef ACTIONDISPATCHER_H
#define ACTIONDISPATCHER_H

#include <QObject>
#include "../components/AppSettings.h"
#include "../components/HibernationClock.h"
#include "../redux/action_definitions.h"
#include "../utils/Version.h"

/**
 * @brief The ActionDispatcher class will be used as a singleton and
 *  represents the main action dispatcher of the application.
 *  Actions are dispatched through signals and the action payload willl be transfered by copy arguments
 *  of thourought these signals.
 */
class ActionDispatcher final :public QObject
{
    Q_OBJECT
public:
    static ActionDispatcher& get() noexcept {static ActionDispatcher instance;return instance;}
    ActionDispatcher(AppSettings const&) = delete;
    ActionDispatcher(ActionDispatcher&&) = delete;
    ActionDispatcher& operator=(ActionDispatcher const&) = delete;
    ActionDispatcher& operator=(ActionDispatcher &&) = delete;
    ~ActionDispatcher() = default;

protected:
    ActionDispatcher() : QObject(nullptr){}
};
#endif // ACTIONDISPATCHER_H
