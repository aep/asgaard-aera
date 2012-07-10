
TEMPLATE = lib
TARGET = aera-json
DEPENDPATH += .
INCLUDEPATH += .

CONFIG+= plugin

CONFIG -= qt


QMAKE_CFLAGS=-std=c99

SOURCES += jsonwriter.c
