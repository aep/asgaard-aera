TEMPLATE = lib
TARGET = aera-csv
DEPENDPATH += .
INCLUDEPATH += .

CONFIG+= plugin


QT = core

# Input
HEADERS += ../plugin.h
SOURCES += csvplugin.cpp
