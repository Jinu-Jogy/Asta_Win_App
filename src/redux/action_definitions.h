/**
  This macro list all action dispatched by the ActionDispatcher and handled by the controller.
 */

#ifndef ACTION_DEFINITIONS
#define ACTION_DEFINITIONS \
    ReturnResult<QJsonObject> saveDataModel(int  dmType = 60,bool isStream = false); \
    void appStarting(); \
    void appStarted(); \
    void loginPending(); \
    void login(QString); \
    void loginSucceeded(); \
    void loginFailed(QString); \
    void addStream(VideoStreamDataModel*); \
    void streamingProcessStarting(QString); \
    void streamingProcessStartingFailed(QString,QString); \
    void streamingProcessStartingUp(QString,QString); \
    void streamingProcessStarted(QString); \
    void streamingProcessStopping(QString); \
    void streamingProcessStopped(QString); \
    void startStreamingProcessRequest(QString,bool isUpdateToServer); \
    void stopStreamingProcessRequest(QString,bool isUpdateToServer); \
    void killStreamingProcessRequest(QString); \
    void removeStreamRequest(QString); \
    void removeSelectedStreams(); \
    void updateVideoStream(QString,VideoStreamDataModel*,bool,bool,bool); \
    void updateStreamRequest(QString); \
    void setHibernationParameters(HibernationDataModel*); \
    void enteredHibernation(); \
    bool getEdgeAppConfigs(); \
    void exitHibernation(); \
    void online(); \
    void offline(); \
    void checkUpdate(bool); \
    void update(Version,QString); \
    void exitingApp(); \
    void appExit(); \
    void editStreamerCommandLinePattern(QString); \
    void notifyStreamDownEvent(QString); \
    void notifyStreamUpEvent(QString); \
    void notifyLauncherMissingEvent();  \
    void notifyLauncherAvailableEvent(); \
    void UpdateCamDownInUi(QString); \
    bool isLauncherMissing(); \
    void logServerSuccessEvent(QString); \
    void logServerFailedEvent(QString); \
    bool wasAppCrashed(); \
    void sendBase64API(QString rtspUrl,QString streamId); \
    bool getpreview(QString url,QString streamId, QPixmap& preview); \
    void notifyErrorEvent(QString, bool); \
    void checkIfIpaddChanged1(QString url); \
    void DelBackUpFiles(); \
    void reLoginForTokenExpiry(); \
    void writeSystemScreenOffLogsToDB(); \
    void writeSystemScreenOnLogsToDB(); \
    bool checkNetworkStatus(); \
    bool checkEdgeAppServerIsReachable(); \
    QString getWindowsSpec(); \
    QJsonObject getWindowsSpecJsonData(); \
    int getSystemRAMUsage(); \
    bool runPreRequisite(bool updateUI, bool writeToEdgeAppDB = false,bool showLoginPage = true); \
    ReturnResult<QJsonObject> getPreRequisiteConfigs();\
    void updateLocalStreamToServer(VideoStreamDataModel *vsDataModel);

#endif //ACTION_DEFINITIONS
