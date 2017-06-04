#include "archivesmanager.h"

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
