#include "corbeille.h"
#include "notemanager.h"
#include "relation.h"


Corbeille::Corbeille(){}

///Destructeur de la corbeille
Corbeille::~Corbeille(){
    ///On vide bien toutes les notes présentes dans le vecteur de pointeur de notes dustBin
    for(unsigned int i=0; i<dustBin.size(); i++){ delete dustBin[i];}
    ///On libère le vecteur dustBin
    dustBin.clear();
}

Corbeille::Handler2 Corbeille::handler2=Handler2();


///Retourne l'instance unique de la courbeille, ou en crée une si il n'y en a pas
Corbeille& Corbeille::getInstance() {
  /// Si le pointeur vers l'instance unique pointe vers 0
  if(!handler2.instance) {
    ///Création d'une nouvelle instance unique
    handler2.instance = new Corbeille;
  }
  /// Retour par ref vers l'instance unique
  return *handler2.instance;
}


/// Libérer l'instance
void Corbeille::libererInstance() {
  /// Liberation de la memoire allouee a l'instance unique
  delete handler2.instance;
  /// Repasse le pointeur a null/nullptr/0 pour que le prochain appel a getInstance recree bien une instance
  handler2.instance=0;
}


///Renvoie un pointeur sur une note en fonction de son id
Note* Corbeille::getNoteWithId(QString id){
    ///itération sur les notes de dustbin
    for(unsigned int i=0; i<dustBin.size();i++){
        ///Si l'id de la note correspond à l'id passé en argument, on renvoie un pointeur vers cette note
        if(dustBin[i]->getId() == id) {return dustBin[i];}
        ///sinon on lance une exception pour dire que la note n'a pas été trouvée.
        else {throw NotesException("La note n'a pas ete trouvee..");}
    }
}


///Fonction permettant de renvoyer un pointeur vers une note en fonction du numéro de sa position
Note* Corbeille::getNoteWithPosition(unsigned int position){
    if(position<dustBin.size()) {return dustBin[position];}
    ///Si la position passée en argument est supérieure à la taille du vecteur, on lance une exception
    else throw NotesException ("La note n'a pas ete trouvee..");
}



/// Ajout d'une note via la fonction push_back de vector
void Corbeille::addNote(Note* n){
  dustBin.push_back(n);
}


///Fonction qui renvoie la position d'une note passée en argument
unsigned int Corbeille::getNotePosition(Note* n){
    ///itération sur les notes de dustbin
    for(unsigned int i=0;i<dustBin.size();i++){
        ///Si la note itérée correspond à la note apssée en argument, on renvoie un pointeur vers cette note itérée
        if(dustBin[i]==n){return i;}
    }
    ///sinon on lance une exception pour dire que la note n'a pas été trouvée.
    throw NotesException("La note n'a pas ete trouvee..");
}


///fonction permettant de restaurer une note
void Corbeille::RestoreNote(Note* n){
    ///On récupère la position de la note dans le vecteur
    unsigned int i=getNotePosition(n);
    ///On ajoute la note dans notesmanager
    NotesManager::getInstance().addNote(n);
    ///On supprime la note du vecteur de notes dustBin
    dustBin.erase(dustBin.begin()+i);
}


///Fonction permettant de retourner un pointeur vers une note ayant un titre identique à celui passé en paramètre
Note* Corbeille::getNoteWithTitle(QString title){
    ///itération sur les notes de dustbin
    for(unsigned int i=0; i<dustBin.size(); i++){
        ///Si le titre de la note correspond au titre passé en argument, on renvoie un pointeur vers cette note
        if(dustBin[i]->getTitle()== title) return dustBin[i];
    }
    ///sinon on lance une exception pour dire que la note n'a pas été trouvée.
    throw NotesException("La note n'a pas ete trouvee..");
}


///Fonction permettant de supprimer une note du vecteur de notes
void Corbeille::deleteNote(Note* n){
    ///On récupère sa position
    unsigned int i = Corbeille::getInstance().getNotePosition(n);
    ///Apple de l'instance unique de relationsmanager
    RelationsManager& rm = RelationsManager::getInstance();
    ///Suppression de toutes les relations correspondant à cette note
    rm.deleteRelationOfNote(*n);
    ///Suppression de la note du vecteur de notes
    dustBin.erase(dustBin.begin()+i);
    ///Suppression de la note de notesmanager
    NotesManager::getInstance().deleteNote(n);
}
