DEFINES += QAPPLICATION_CLASS=QApplication
DEFINES += ELPP_FEATURE_CRASH_LOG=1
DEFINES += ELPP_NO_DEFAULT_LOG_FILE=1

include ($$PWD/../Logger/Logger.pri)
include ($$PWD/../thirdparty/thirdparty.pri)

CONFIG -= debug_and_release debug_and_release_target
TEMPLATE = app
TARGET = AstaCMSApp

QT += core widgets network concurrent websockets multimedia multimediawidgets

# Include paths
win32: INCLUDEPATH += $$PWD
win32: LIBS += -lstrsafe

CONFIG += c++17 embed_manifest_exe
#CONFIG += c++11

LIBS += -lIphlpapi -lws2_32 -lwtsapi32
LIBS += -lole32
LIBS += -lUser32
LIBS += -ldxva2

# Link against the necessary libraries
win32: LIBS += -ldxva2

# Include paths for the Windows SDK
win32: INCLUDEPATH += $$(INCLUDE)
win32: LIBS += -L$$(LIB)

INCLUDEPATH += $$quote(C:\Program Files (x86)\Windows Kits\10\Include)
LIBS += -L$$quote(C:\Program Files (x86)\Windows Kits\10\Lib)


# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
     $$PWD/main.cpp \
     $$PWD/MainWindow.cpp \
     components/HibernationClock.cpp \
     network/ApiBroker.cpp \
     redux/Controller.cpp \
     utils/Version.cpp

HEADERS += \
     $$PWD/MainWindow.h \
     components/AppSettings.h \
     components/HibernationClock.h \
     network/ApiBroker.h \
     network/OnlineWatcher.h \
     network/RestfulClient.h \
     redux/ActionDispatcher.h \
     redux/Controller.h \
     redux/action_definitions.h \
     utils/Constants.h \
     utils/CurrentVersion.h \
     utils/Globals.h \
     utils/Version.h \
     utils/utils.h

FORMS += \
    MainWindow.ui

TRANSLATIONS += \
    AstaCMS_en_IN.ts


RESOURCES += resources.qrc
RC_ICONS += $$PWD/../src/resources/ico.ico


DISTFILES += \
    DeleteFilesAfterDelay.ps1 \
    resources/readVideo.mp4

#contains(DEFINES,BUILD_x64)
#{
#    message( "Src Configuring OpenCV Library for BUILD_x64..." )
#    win32:CONFIG(release, debug|release): LIBS += -L$$PWD/thirdparty/libvlc/include1/lib/ -VLCQtCore -VLCQtQml -VLCQtWidgets
#    else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/thirdparty/libvlc/include1/lib/ -VLCQtCored -VLCQtQmld -VLCQtWidgetsd
#}

#INCLUDEPATH += $$PWD/thirdparty/libvlc/include1
#DEPENDPATH += $$PWD/thirdparty/libvlc/include1
