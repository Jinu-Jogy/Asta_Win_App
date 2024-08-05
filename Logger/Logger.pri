# This module includes all the files and folders to inlcude logger module in the App
INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/Formatter/LogFormatter.h \
    $$PWD/Formatter/LogSimpleFormatter.h \
    $$PWD/Formatter/LogTextFomatter.h \
    $$PWD/Formatter/LogXMLFormatter.h \
    $$PWD/Handler/LogConsoleHandler.h \
    $$PWD/Handler/LogFileHandler.h \
    $$PWD/Handler/LogHandler.h \
    $$PWD/LogFlags.h \
    $$PWD/LogLevel.h \
    $$PWD/Logger.h \
    $$PWD/LogRecord.h

SOURCES += \
        $$PWD/Formatter/LogFormatter.cpp \
        $$PWD/Formatter/LogSimpleFormatter.cpp \
        $$PWD/Formatter/LogTextFomatter.cpp \
        $$PWD/Formatter/LogXMLFormatter.cpp \
        $$PWD/Handler/LogConsoleHandler.cpp \
        $$PWD/Handler/LogFileHandler.cpp \
        $$PWD/Handler/LogHandler.cpp \
        $$PWD/LogFlags.cpp \
        $$PWD/LogLevel.cpp \
        $$PWD/Logger.cpp \
        $$PWD/LogRecord.cpp
