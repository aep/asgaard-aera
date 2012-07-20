TEMPLATE = lib
TARGET = aera1.io.csv
DESTDIR=../../../plugins
DEPENDPATH += . ../../shared
INCLUDEPATH += . ../../shared

CONFIG+= plugin

QT = core

HEADERS += ../../shared/plugin.h
SOURCES += csvplugin.cpp
