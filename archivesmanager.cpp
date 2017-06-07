#include "archivesmanager.h"
#include "notemanager.h"

ArchivesManager::~ArchivesManager(){
    //save();
    for(unsigned int i=0; i<notesArchive.size(); i++){delete notesArchive[i];} /// Lors de la destruction dee l'ArchiveManager, on fais attention
    notesArchive.clear();                                                      /// a bien supprimer toutes les archives de notes.
}

ArchivesManager::AMHandler ArchivesManager::am_handler=AMHandler();

ArchivesManager& ArchivesManager::getInstance() {
  // Si le pointeur vers l'instance unique pointe vers 0
  if(!am_handler.instance) {
    am_handler.instance=new ArchivesManager;   /// On créee une nouvelle instance d'ArchivesManager
  }
  // Retour par ref vers l'instance unique
  return *am_handler.instance;
}

void ArchivesManager::libererInstance() {
  // Liberation de la memoire allouee a l'instance unique
  delete am_handler.instance;
  // Repasse le pointeur a null/nullptr/0 pour que le prochain appel a getInstance recree bien une instance
  am_handler.instance=0;
}

void ArchivesManager::addNote(Note* n){
    notesArchive.push_back(n);
}

unsigned int ArchivesManager::getNotePosition(Note* n){  ///Permet de retrouver la position d'une Note dans le vector, ou d'afficher une Exception le cas échéant
    for(unsigned int i=0;i<notesArchive.size();i++){
        if(notesArchive[i]==n){return i;}
    }
    throw NotesException("La note n'a pas ete trouvee..");
}

void ArchivesManager::deleteNote(Note* n){ /// Suppression d'une note via la fonction erase().
    bool del = false;
    for (unsigned int i=0; i<notesArchive.size(); i++){/// La boucle For vérifie la suppression de la note. Si la note n'existe pas à l'indice i, on va à i+1. Le vector prend en charge le Design Pattern Iterator pour parcourir les Notes. Si la note n'est pas à l'indice i, pas de changement de statut de la variable booléeenne. Si elle y est, on supprime la note, puis on met le statut de la variable bool sur True. A la fin du parcours du tableau, si la variable est toujorus sur False, on affiche une Exception.
        if (notesArchive[i] == n) {
            notesArchive.erase(notesArchive.begin()+i);
            del = true;
        }
    }
    if (del == false){throw NotesException("La note n'a pas ete trouvee..");}
}

void ArchivesManager::restorNote(Note* n){
    unsigned int j=getNotePosition(n); /// On fait appel à la fonction getNotePosition(Note* ) pour retrouver la position de la note
    NotesManager::getInstance().addNote(n); /// on rajoute cette note dans l'instance NotesManager.
    deleteNote(n);
}


Note* ArchivesManager::getNoteWithTitle(QString title){  /// Permet de retrouver une note via son titre
    for(unsigned int i=0; i<notesArchive.size(); i++){
        if(notesArchive[i]->getTitle() == title){ return notesArchive[i];}
    }
    throw NotesException("La note n'a pas ete trouvee..");
}
