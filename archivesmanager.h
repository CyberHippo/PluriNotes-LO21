#ifndef ARCHIVESMANAGER_H
#define ARCHIVESMANAGER_H

#include "corbeille.h"

// Manager d'archives
class ArchivesManager{
private:
    vector<Note*> notesArchive;  /// Conteneur séquentielle qui encapsule un tableau de Note, de taille dynamique
    ArchivesManager() : notesArchive(0) {}    /// Constructeur en privé. On crée une seule instance d'ArchivesManager (Design Pattern Singleton)
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
    static ArchivesManager& getInstance(); /// Accesseur pour obtenir l'instance si elle existe, sinon on la crée
    static void libererInstance();
    void addNote(Note* n); /// Vu que l'on travaille sur un vector, il suffit de faire appel à la fonction push_back() pour augmenter la taille du tableau.
    unsigned int getNotePosition(Note* n);
    Note* getNoteWithTitle(QString title);
    vector<Note*>::iterator getIteratorBegin() { return notesArchive.begin();}  /// Il n'est pas nécessaire de créer le Design Pattern Iterator comme vu en TD, car le Vector contient un Iterator. On peut directement utiliser les fonctions de l'Iterator.
    vector<Note*>::iterator getIteratorEnd() { return notesArchive.end();}
    void deleteNote(Note* n);
    void restorNote(Note* n);

};

#endif // ARCHIVESMANAGER_H

