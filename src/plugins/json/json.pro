TEMPLATE = lib
TARGET = aera1-json
DESTDIR=../../../plugins
DEPENDPATH += .
INCLUDEPATH += .

CONFIG+= plugin

CONFIG -= qt


QMAKE_CFLAGS=-std=c99

SOURCES += jsonwriter.c
