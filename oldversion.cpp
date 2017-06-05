#ifndef OLDVERSION_CPP_INCLUDED
#define OLDVERSION_CPP_INCLUDED
#include "oldversions.h"
#include "fonction.h"
#include "notemanager.h"

///Fonctions de Old Versions
OldVersions::~OldVersions(){
        for(unsigned int i=0; i<nbNotes; i++) delete oldNotes[i];
        oldNotes.clear();
}

void OldVersions::addNote(Note* n){oldNotes.push_back(n);}

void OldVersions::printVersions(){
    std::cout << "|------Anciennes Versions------|\n\n";

    for (vector<Note*>::const_iterator it = oldNotes.begin() ; it != oldNotes.end(); ++it){
        (*it)->print();
        std::cout << "------------------\n";
    }
}

Note* OldVersions::findVersion(QString title){
    bool found = false;
    for (vector<Note*>::iterator it = oldNotes.begin() ; it != oldNotes.end(); ++it){
                if ((*it)->getTitle() == title){
                        found = true;
                        return *it;
                }
    }
    if (found == false){throw NotesException("Note non trouvee.. \n");}

}

Note* OldVersions::getNoteWithVersionNumber(unsigned int nb){
    for(unsigned int i=0; i<oldNotes.size(); i++){
        if(oldNotes[i]->getNumVersion() == nb){return oldNotes[i];}
    }
    throw NotesException("La note n'a pas ete trouvee..");
}

unsigned int OldVersions::getNotePosition(Note* n){
    for(unsigned int i=0;i<oldNotes.size();i++){
        if(oldNotes[i]==n){return i;}
    }
    throw NotesException("La note n'a pas ete trouvee..");
}

void OldVersions::restorNote(Note* n){
    unsigned int j=getNotePosition(n);
    NotesManager::getInstance().deleteNote(n->getId());
    NotesManager::getInstance().addNote(n);
    oldNotes.erase(oldNotes.begin()+j);
}
#endif // OLDVERSION_CPP_INCLUDED
