#include <iostream>
#include <fstream>
#include <QFile>
#include <QTextCodec>
#include <QtXml/QtXml>
#include <QMessageBox>

#include "fonction.h"
#include "notemanager.h"
#include "notefactory.h"

///Methodes de la classe NotesManager
void NotesManager::addNote(Note* n){
    notes.push_back(n);
}

NotesManager::NotesManager() : notes(0),nbNotes(0),nbMaxNotes(0),filename("tmp.dat"){}

NotesManager::~NotesManager(){
    //save();
    for(unsigned int i=0; i<nbNotes; i++) delete notes[i];
    notes.clear();
}

Note* NotesManager::getNewNote(QString& title,QString& type){
    NoteFactory* nf = NoteFactory::chooseFactory(type);
    Note* n = nf->createNewNote(title);
    this->addNote(n);
    return n;
}


NotesManager::Handler NotesManager::handler=Handler();

NotesManager& NotesManager::getInstance() {
  // Si le pointeur vers l'instance unique pointe vers 0
  if(!handler.instance) {
    handler.instance=new NotesManager;
  }
  // Retour par ref vers l'instance unique
  return *handler.instance;
}

void NotesManager::libererInstance() {
  // Liberation de la memoire allouee a l'instance unique
  delete handler.instance;
  // Repasse le pointeur a null/nullptr/0 pour que le prochain appel a getInstance recree bien une instance
  handler.instance=0;
}





void NotesManager::showAll() const {
    for (vector<Note*>::const_iterator it = notes.begin() ; it != notes.end(); ++it){
        (*it)->print();
    }
}

void NotesManager::deleteNote(QString id){
    int size_init = notes.size();
    for (unsigned int i=0; i<notes.size(); i++){
        if (notes[i]->getId() == id) {notes.erase(notes.begin()+i);}
    }
    if (size_init == notes.size()) { //cela signifie que l'on a rien supprime dans le tableau
        throw NotesException("L'element a supprimer n'a pas ete trouve..\n");
    }
}
/*void NotesManager::editNote(QString id){
    QString t;
    cout << "Quel nouveau titre pour cette note?\n";
    cin >> t;
    cin.ignore();
    for (vector<Note*>::iterator it = notes.begin() ; it != notes.end(); ++it){
                if ((*it)->getId() == id){
                        (*it)->addOldVersion();
                        (*it)->setTitle(t);
                }
    }
}*/

void NotesManager::showOldNotes(QString id){
    bool found = false;
    for (vector<Note*>::iterator it = notes.begin() ; it != notes.end(); ++it){
                if ((*it)->getId() == id){
                        found = true;
                        (*it)->printOldVersion();
                }
    }
    if (found == false){throw NotesException("Note non trouvee.. \n");}
}

void NotesManager::restaurerNote(QString id, QString title){
    bool found = false;
    OldVersions va;
    Note* tmp(0);
    for (vector<Note*>::iterator it = notes.begin() ; it != notes.end(); ++it){
                if ((*it)->getId() == id){
                        found = true;
                        va = (*it)->getVersionsAnt();
                        tmp = va.findVersion(title);
                        if (tmp != 0){
                            *it = tmp->clone();
                            (*it)->setVersionsAnt(va);
                        }
                }
    }
    if (found == false){throw NotesException("Note non trouvee.. \n");}
}

void NotesManager::saveNote(Note& n){
    n.save();
}
