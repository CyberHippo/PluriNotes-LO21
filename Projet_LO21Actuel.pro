QT += widgets
QT += xml

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
    relation.cpp \
    corbeille.cpp \
    corbeilleediteur.cpp \
    editeurfactory.cpp \
    mainwindow.cpp \
    notesmanagerwindow.cpp \
    relationediteur.cpp \
    archivesmanager.cpp  \
    archivesmanagerwindow.cpp \
    oldversionswindow.cpp \
    relationsmanagerwindow.cpp

HEADERS += \
    fenetres.h \
    fonction.h \
    noteediteur.h \
    notefactory.h \
    notemanager.h \
    oldversions.h \
    relation.h \
    corbeille.h \
    corbeilleediteur.h \
    editeurfactory.h \
    mainwindow.h \
    notesmanagerwindow.h \
    relationediteur.h   \
    archivesmanager.h   \
    archivesmanagerwindow.h \
    oldversionswindow.h \
    relationsmanagerwindow.h
