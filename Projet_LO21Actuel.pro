QT += widgets
QMAKE_CXXFLAGS = -std=c++11
QMAKE_LFLAGS = -std=c++11
QT += core

SOURCES += \
    fenetres.cpp \
    main.cpp \
    fonction.cpp \
    noteediteur.cpp \
    notefactory.cpp \
    notemanager.cpp \
    oldversion.cpp \
    relation.cpp

HEADERS += \
    fenetres.h \
    fonction.h \
    noteediteur.h \
    notefactory.h \
    notemanager.h \
    oldversions.h \
    relation.h
