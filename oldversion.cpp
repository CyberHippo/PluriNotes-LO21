#ifndef OLDVERSION_CPP_INCLUDED
#define OLDVERSION_CPP_INCLUDED
#include "oldversions.h"
#include "fonction.h"
#include "notemanager.h"

///Fonctions de Old Versions

///Destructeur de OldVersions
OldVersions::~OldVersions(){
    ///Pour chaque ancienne note présente dans oldNotes, on la supprime
    for(unsigned int i=0; i<nbNotes; i++) delete oldNotes[i];
    ///On supprime le vector oldnotes
        oldNotes.clear();
}

///Fonction qui permet d'ajouter une note à la fin du vecteur de notes oldNotes
void OldVersions::addNote(Note* n){oldNotes.push_back(n);}

///Fonction qui permet d'afficher toutes les notes contenues dans le vecteur oldnotes
void OldVersions::printVersions(){
    std::cout << "|------Anciennes Versions------|\n\n";
    ///On itère sur le vecteur de notes oldNotes et pour chaque note, on appelle la fonction print()
    for (vector<Note*>::const_iterator it = oldNotes.begin() ; it != oldNotes.end(); ++it){
        (*it)->print();
        qDebug() << "------------------\n";
    }
}

///Fonction qui permet de retrouver la version d'une note à partir d'un titre
Note* OldVersions::findVersion(QString title){
    bool found = false;
    ///On itère les notes de OldNotes et si on trouve une note dont le titre est identique à la QString passée en argument, on la retourne
    for (vector<Note*>::iterator it = oldNotes.begin() ; it != oldNotes.end(); ++it){
                if ((*it)->getTitle() == title){
                        found = true;
                        return *it;
                }
    }
    ///Sinon on lance une exception
    if (found == false){throw NotesException("Note non trouvee.. \n");}

}

///Fonction qui permet de retrouver une note en fonction de son numéro de version
Note* OldVersions::getNoteWithVersionNumber(unsigned int nb){
    ///On itère sur les notes du vecteur oldNotes
    for(unsigned int i=0; i<oldNotes.size(); i++){
        ///Si le numéro de version de la note correspond au numéro passé en argument, on retourne la note
        if(oldNotes[i]->getNumVersion() == nb){return oldNotes[i];}
    }
    ///Sinon on lance une exception
    throw NotesException("La note n'a pas ete trouvee..");
}

///Fonction qui permet de retourner la position d'une note dans le vecteur oldnotes
unsigned int OldVersions::getNotePosition(Note* n){
    ///On itère les notes de OldNotes
    for(unsigned int i=0;i<oldNotes.size();i++){
        ///Si la note est identique à la note passée en argument alors on retourne l'entier indiquant sa position
        if(oldNotes[i]==n){return i;}
    }
    ///Sinon on lance une exception
    throw NotesException("La note n'a pas ete trouvee..");
}

///Fonction permettant de restaurer une note
void OldVersions::restorNote(Note* n){
    ///On récupère la position de la note
    unsigned int j=getNotePosition(n);
    ///On supprime la version actuelle dans le notesmanager
    NotesManager::getInstance().deleteNote(n->getId());
    ///On ajoute au notesmanager la version à restaurer de la note
    NotesManager::getInstance().addNote(n);
    ///On supprime la version à restaurer de Oldversions
    oldNotes.erase(oldNotes.begin()+j);
}
#endif // OLDVERSION_CPP_INCLUDED
