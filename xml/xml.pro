TEMPLATE = lib
TARGET = aera-xml
DEPENDPATH += .
INCLUDEPATH += .

CONFIG += plugin

QT = core

QMAKE_CXXFLAGS+=-fvisibility=hidden

HEADERS += ../plugin.h
SOURCES += xmlplugin.cpp
