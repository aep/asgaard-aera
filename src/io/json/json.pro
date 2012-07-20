TEMPLATE = lib
TARGET = aera1.io.json
DESTDIR=../../../plugins
DEPENDPATH += .
INCLUDEPATH += .


CONFIG += plugin
CONFIG -= qt

QMAKE_CFLAGS+=-std=c99
QMAKE_CFLAGS+=-fvisibility=hidden

SOURCES += jsonwriter.c
