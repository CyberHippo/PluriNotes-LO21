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

};

#endif // ARCHIVESMANAGER_H

