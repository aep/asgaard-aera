
TEMPLATE = lib
TARGET = aera1-spss
DESTDIR=../../../plugins/
DEPENDPATH += . ../../shared
INCLUDEPATH += . ../../shared

CONFIG+= plugin

QT = core

SOURCES += spssreader.cpp spsswriter.cpp
