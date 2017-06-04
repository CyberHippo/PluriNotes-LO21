#include "archivesmanager.h"
#include "notemanager.h"

ArchivesManager::~ArchivesManager(){
    //save();
    for(unsigned int i=0; i<notesArchive.size(); i++){delete notesArchive[i];}
    notesArchive.clear();
}

ArchivesManager::AMHandler ArchivesManager::am_handler=AMHandler();

ArchivesManager& ArchivesManager::getInstance() {
  // Si le pointeur vers l'instance unique pointe vers 0
  if(!am_handler.instance) {
    am_handler.instance=new ArchivesManager;
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

unsigned int ArchivesManager::getNotePosition(Note* n){
    for(unsigned int i=0;i<notesArchive.size();i++){
        if(notesArchive[i]==n){return i;}
    }
    throw NotesException("La note n'a pas ete trouvee..");
}

void ArchivesManager::deleteNote(Note* n){
    bool del = false;
    for (unsigned int i=0; i<notesArchive.size(); i++){
        if (notesArchive[i] == n) {
            notesArchive.erase(notesArchive.begin()+i);
            del = true;
        }
    }
    if (del == false){throw NotesException("La note n'a pas ete trouvee..");}
}

void ArchivesManager::restorNote(Note* n){
    unsigned int j=getNotePosition(n);
    NotesManager::getInstance().addNote(n);
    deleteNote(n);
}


Note* ArchivesManager::getNoteWithTitle(QString title){
    for(unsigned int i=0; i<notesArchive.size(); i++){
        if(notesArchive[i]->getTitle() == title){ return notesArchive[i];}
    }
    throw NotesException("La note n'a pas ete trouvee..");
}
