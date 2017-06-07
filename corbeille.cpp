#include "corbeille.h"
#include "notemanager.h"

Corbeille::Corbeille(){}

Corbeille::~Corbeille(){
    for(unsigned int i=0; i<dustBin.size(); i++){ delete dustBin[i];}
    dustBin.clear();
}

Corbeille::Handler2 Corbeille::handler2=Handler2();

Corbeille& Corbeille::getInstance() {
  // Si le pointeur vers l'instance unique pointe vers 0
  if(!handler2.instance) {
    handler2.instance = new Corbeille;
  }
  // Retour par ref vers l'instance unique
  return *handler2.instance;
}

void Corbeille::libererInstance() {
  // Liberation de la memoire allouee a l'instance unique
  delete handler2.instance;
  // Repasse le pointeur a null/nullptr/0 pour que le prochain appel a getInstance recree bien une instance
  handler2.instance=0;
}

Note* Corbeille::getNoteWithId(QString id){
    for(unsigned int i=0; i<dustBin.size();i++){
        if(dustBin[i]->getId() == id) {return dustBin[i];}
        else {throw NotesException("La note n'a pas ete trouvee..");}
    }
}

Note* Corbeille::getNoteWithPosition(unsigned int position){
    if(position<dustBin.size()) {return dustBin[position];}
    else throw NotesException ("La note n'a pas ete trouvee..");
}

void Corbeille::addNote(Note* n){
  dustBin.push_back(n);
}

unsigned int Corbeille::getNotePosition(Note* n){
    for(unsigned int i=0;i<dustBin.size();i++){
        if(dustBin[i]==n){return i;}
    }
    throw NotesException("La note n'a pas ete trouvee..");
}

void Corbeille::RestoreNote(Note* n){
    unsigned int i=getNotePosition(n);
    NotesManager::getInstance().addNote(n);
    dustBin.erase(dustBin.begin()+i);
}


Note* Corbeille::getNoteWithTitle(QString title){
    for(unsigned int i=0; i<dustBin.size(); i++){
        if(dustBin[i]->getTitle()== title) return dustBin[i];
    }
    throw NotesException("La note n'a pas ete trouvee..");
}


void Corbeille::deleteNote(Note* n){
    unsigned int i = Corbeille::getInstance().getNotePosition(n);
    dustBin.erase(dustBin.begin()+i);
}

