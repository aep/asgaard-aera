TEMPLATE = lib
TARGET = aera-xml
DEPENDPATH += . ../../shared
INCLUDEPATH += . ../../shared

CONFIG += plugin

QT = core

QMAKE_CXXFLAGS+=-fvisibility=hidden

HEADERS += ../../shared/plugin.h
SOURCES += xmlplugin.cpp
