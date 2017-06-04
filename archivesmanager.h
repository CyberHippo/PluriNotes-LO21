#ifndef ARCHIVESMANAGER_H
#define ARCHIVESMANAGER_H

#include "corbeille.h"

class ArchivesManager{
private:
    vector<Note*> notesArchive;
    ArchivesManager() : notesArchive(0) {}
    ArchivesManager(const ArchivesManager& am);     /// constructeur de recopie
    ~ArchivesManager(); ///destructeur

    ///surcharge de =
    ArchivesManager& operator=(const ArchivesManager&);

    ///static NotesManager *instance;
    struct AMHandler{
        ArchivesManager* instance;
        AMHandler() : instance(0){}
        ~AMHandler(){if(instance) delete instance; instance = 0;}
    };
    static AMHandler am_handler;
public:
    static ArchivesManager& getInstance();
    static void libererInstance();
    void addNote(Note* n);
    unsigned int getNotePosition(Note* n);
    Note* getNoteWithTitle(QString title);
    vector<Note*>::iterator getIteratorBegin() { return notesArchive.begin();}
    vector<Note*>::iterator getIteratorEnd() { return notesArchive.end();}
    void deleteNote(Note* n);
    void restorNote(Note* n);

};

#endif // ARCHIVESMANAGER_H

