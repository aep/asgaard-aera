TEMPLATE =app
TARGET =  xml2sql
DEPENDPATH += .
INCLUDEPATH += .
QT+=sql xmlpatterns
CONFIG+=qxt
CONFIG+=debug
QXT+=core

SOURCES+=main.cpp

HEADERS += db.h   analyser.h    import.h
SOURCES += db.cpp analyser.cpp  import.cpp
