#ifndef CORBEILLE_H
#define CORBEILLE_H

#include <iostream>
#include <QSet>
#include <QList>
#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include "fonction.h"

class Corbeille{

private :
    QList<Note*> dustBin;
    Corbeille();
    Corbeille(const Corbeille& c);
    Corbeille& operator=(const Corbeille& c);
    ~Corbeille();

    ///static Corbeille *instance;
    struct Handler2{
        Corbeille* instance;
        Handler2() : instance(0){}
        ~Handler2(){if(instance) delete instance; instance = 0;}
    };
    static Handler2 handler2;

public :
    static Corbeille& getInstance();
    static void libererInstance();
    int getDustBinSize() const {return dustBin.size();}
    void RestoreNote(Note* n);
    Note* getNoteWithTitle(QString title);
    Note* getNoteWithId(QString id);
    Note* getNoteWithPosition(unsigned int position);
    void deleteNote(Note* n);
    void addNote(Note*n);
    unsigned int getNotePosition(Note*n);
    void emptyDustBin(){dustBin.clear();}
    void callEditeur();
};



#endif // CORBEILLE_H

