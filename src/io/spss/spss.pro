TEMPLATE = lib
TARGET = aera1.io.spss
DESTDIR=../../../plugins/
DEPENDPATH += . ../../shared
INCLUDEPATH += . ../../shared

CONFIG+= plugin

QT = core

SOURCES += spssreader.cpp spsswriter.cpp
