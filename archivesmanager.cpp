#include "archivesmanager.h"
#include "notemanager.h"

ArchivesManager::~ArchivesManager(){
    //save();
    /// Lors de la destruction dee l'ArchiveManager, on fais attention a bien supprimer toutes les archives de notes.
    for(unsigned int i=0; i<notesArchive.size(); i++){delete notesArchive[i];}
    notesArchive.clear();
}

ArchivesManager::AMHandler ArchivesManager::am_handler=AMHandler();

/// On créee une nouvelle instance d'ArchivesManager si elle n'existe pas déja
ArchivesManager& ArchivesManager::getInstance() {
  // Si le pointeur vers l'instance unique pointe vers 0
  if(!am_handler.instance) {
    am_handler.instance=new ArchivesManager;
  }
  /// Retour par référence vers l'instance unique
  return *am_handler.instance;
}

void ArchivesManager::libererInstance() {
  /// Liberation de la memoire allouee a l'instance unique
  delete am_handler.instance;
  /// Repasse le pointeur a null/nullptr/0 pour que le prochain appel a getInstance recree bien une instance
  am_handler.instance=0;
}
/// Ajout d'une note via la fonction push_back
void ArchivesManager::addNote(Note* n){
    notesArchive.push_back(n);
}
///Permet de retrouver la position d'une Note dans le vector, ou d'afficher une Exception le cas échéant
unsigned int ArchivesManager::getNotePosition(Note* n){
    for(unsigned int i=0;i<notesArchive.size();i++){
        if(notesArchive[i]==n){return i;}
    }
    throw NotesException("La note n'a pas ete trouvee..");
}
/* Suppression d'une note via la fonction erase().
Cette fonction ne supprime pas la note, elle supprime le pointeur de note dans le tableau de pointeur
Elle est appelé que quand on restaure la note*/
void ArchivesManager::deleteNote(Note* n){
    bool del = false;
    /// La boucle For vérifie la suppression de la note. Si la note n'existe pas à l'indice i, on va à i+1. Le vector prend en charge le Design Pattern Iterator pour parcourir les Notes. Si la note n'est pas à l'indice i, pas de changement de statut de la variable booléeenne. Si elle y est, on supprime la note, puis on met le statut de la variable bool sur True. A la fin du parcours du tableau, si la variable est toujours sur False, on affiche une Exception.
    for (unsigned int i=0; i<notesArchive.size(); i++){
        if (notesArchive[i] == n) {
            notesArchive.erase(notesArchive.begin()+i);
            del = true;
        }
    }
    if (del == false){throw NotesException("La note n'a pas ete trouvee..");}
}
/// Restauration d'une Note
void ArchivesManager::restorNote(Note* n){
  /// On fait appel à la fonction getNotePosition(Note* ) pour retrouver la position de la note
    unsigned int i = getNotePosition(n);
    /// on rajoute cette note dans l'instance NotesManager.
    NotesManager::getInstance().addNote(n);
    notesArchive.erase(notesArchive.begin()+i);
}

/// Permet de retrouver une note via son titre
Note* ArchivesManager::getNoteWithTitle(QString title){
    for(unsigned int i=0; i<notesArchive.size(); i++){
        if(notesArchive[i]->getTitle() == title){ return notesArchive[i];}
    }
    throw NotesException("La note n'a pas ete trouvee..");
}
