#include <iostream>
#include <QSet>
#include <QList>
#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include "relation.h"
#include "notemanager.h"

RelationsManager::RelationsManager(){}

RelationsManager::~RelationsManager(){
    for(unsigned int i=0; i<relations.size(); i++){ delete relations[i];}
    relations.clear();
}


void Couple::print() const{
    qDebug() << "[ " << getFirst().getId();
    qDebug() << " - ";
    qDebug() << getSecond().getId();
    qDebug() << " ]" << "\n";
}

void Relation::getCouples() const{
    for (vector<Couple>::const_iterator it = couples.begin() ; it != couples.end(); ++it){
        it->print();
        qDebug() << "\n";
    }
}

void Relation::addRelation(Note& a, Note& b){
    Couple* c = new Couple(a,b);
    couples.push_back(*c);
}

void Relation::addRelation(Couple& c){
    couples.push_back(c);
}


void Relation::addRelationNonOrientee(Note& a, Note& b){
    Couple* c1 = new Couple(a,b);
    couples.push_back(*c1);
    Couple* c2 = new Couple(b,a);
    couples.push_back(*c2);
}

void Relation::addRelationNonOrientee(Couple& c){
    couples.push_back(c);
    Couple* c2 = new Couple(c.getSecond(),c.getFirst());
    couples.push_back(*c2);
}


void Relation::showAscendants(Note& n) const {
    for (vector<Couple>::const_iterator it = couples.begin() ; it != couples.end(); ++it){
        if(it->getSecond() == n){
           it->print();
            qDebug() << "\n";
        }
    }
}



void Relation::showDescendants(Note& n) const{
    for (vector<Couple>::const_iterator it = couples.begin() ; it != couples.end(); ++it){
        if(it->getFirst() == n){
           it->print();
            qDebug() << "\n";
        }
    }
}
void RelationsManager::addRelation(Relation* r){
    relations.push_back(r);
}

//attention le \r de \ref n'est pas pris en compte il faudra peut être changer en \\ref..

//Relation* RelationsManager::checkReference(Note& n) const{
//    NotesManager& nm = NotesManager::getInstance();
//    //RelationsManager& rm = RelationsManager::getInstance();
//    //On parcourt les notes du notesManager
//    for (vector<Note*>::iterator it = nm.getIteratorBegin() ; it != nm.getIteratorEnd(); ++it){
//        if((*it)->getClassName() == "Article"){ //si c'est un article
//            QString temp = "\ref{" + (*it)->getId() + "}"; //on crée un QString personnalisé avec son id
//            qDebug() << temp<< " ";
//            NotesManager::SearchIterator s = NotesManager::SearchIterator("Nada"); //on crée un searchiterator qui renvoie le premier article
//            Article* res = s.NotesManager::SearchIterator::SearchTextArticle(temp);
//            if (dynamic_cast<Article&>(n).getText().find(temp) != QString::npos){
//                    //on crée la référence
//                    //Note* resTemp = dynamic_cast<Note*>(res);
//                    Couple c = Couple(n,*(*it));
//                    Relation* r = new Relation;
//                    r->addRelation(c);
//                    //rm.addRelation(r);
//                    cout << ": Présent dans " << (*it)->getId() << "\n";
//                    return r;
//            }
//            else{cout << ": Pas présent dans " << (*it)->getId() << "\n";}
//        }
//    }
//}

RelationsManager& RelationsManager::getInstance() {
  // Si le pointeur vers l'instance unique pointe vers 0
  if(!handler3.instance) {
    handler3.instance = new RelationsManager;
  }
  // Retour par ref vers l'instance unique
  return *handler3.instance;
}

void RelationsManager::libererInstance() {
  // Libération de la mémoire allouée à l'instance unique
  delete handler3.instance;
  // Repasse le pointeur à null/nullptr/0 pour que le prochain appel à getInstance recrée bien une instance
  handler3.instance=0;
}

RelationsManager::Handler3 RelationsManager::handler3=Handler3();


bool RelationsManager::checkRelation(Note& n) {
    for (vector<Relation*>::iterator it1 = getIteratorBegin() ; it1 != getIteratorEnd(); ++it1){
        for (vector<Couple>::iterator it2 = (*it1)->getIteratorBegin() ; it2 != (*it1)->getIteratorEnd(); ++it2){
            if(it2->getFirst() == n || it2->getSecond() == n){
               return true;
            }
        }
    }
    return false;
}

void RelationsManager::deleteRelation(Note& n){
    for (vector<Relation*>::iterator it1 = getIteratorBegin() ; it1 != getIteratorEnd(); ++it1){
        qDebug() << "ok1\n";
        for (vector<Couple>::iterator it2 = (*it1)->getIteratorBegin() ; it2 != (*it1)->getIteratorEnd(); ++it2){
            qDebug() << "ok2\n";
            if(it2->getFirst() == n || it2->getSecond() == n){
                qDebug() << "ok3\n";
               //(*it1)->couples.clear();//(*it1)->deleteRelation();
               //relations.erase(it1);
                it1 = relations.erase(it1);
                qDebug() << "ok4\n";
            }
        }
    }qDebug() << "end\n";
}
