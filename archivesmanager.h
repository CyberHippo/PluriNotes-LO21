#ifndef ARCHIVESMANAGER_H
#define ARCHIVESMANAGER_H

#include "corbeille.h"

/// Manager d'archives
class ArchivesManager{
private:
  /// Conteneur séquentielle qui encapsule un tableau de Note, de taille dynamique
    vector<Note*> notesArchive;
    /// Constructeur en privé. On crée une seule instance d'ArchivesManager (Design Pattern Singleton)
    ArchivesManager() : notesArchive(0) {}
    /// constructeur de recopie
    ArchivesManager(const ArchivesManager& am);
    ///destructeur
    ~ArchivesManager();

    ///surcharge de =
    ArchivesManager& operator=(const ArchivesManager&);

  ///static NotesManager *instance. Sert à gérer le singleton
    struct AMHandler{
        ArchivesManager* instance;
        AMHandler() : instance(0){}
        ~AMHandler(){if(instance) delete instance; instance = 0;}
    };
    static AMHandler am_handler;
public:
  /// Accesseur pour obtenir l'instance si elle existe, sinon on la crée
    static ArchivesManager& getInstance();
    static void libererInstance();
    /// Vu que l'on travaille sur un vector, il suffit de faire appel à la fonction push_back() pour augmenter la taille du tableau.
    void addNote(Note* n);
    unsigned int getNotePosition(Note* n);
    Note* getNoteWithTitle(QString title);
    /// Il n'est pas nécessaire de créer le Design Pattern Iterator comme vu en TD, car le Vector contient un Iterator. On peut directement utiliser les fonctions de l'Iterator.
    vector<Note*>::iterator getIteratorBegin() { return notesArchive.begin();}
    vector<Note*>::iterator getIteratorEnd() { return notesArchive.end();}
    void deleteNote(Note* n);
    void restorNote(Note* n);

};

#endif // ARCHIVESMANAGER_H
