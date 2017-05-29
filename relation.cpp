#include "relation.h"


void Couple::print() const{
    std::cout << "[ " << getFirst().getId();
    std::cout << " - ";
    std::cout << getSecond().getId();
    std::cout << " ]" << "\n";
}

void Relation::getCouples() const{
    for (vector<Couple>::const_iterator it = couples.begin() ; it != couples.end(); ++it){
        it->print();
        std::cout << "\n";
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
            std::cout << "\n";
        }
    }

}



void Relation::showDescendants(Note& n) const{
    for (vector<Couple>::const_iterator it = couples.begin() ; it != couples.end(); ++it){
        if(it->getFirst() == n){
           it->print();
            std::cout << "\n";
        }
    }
}
void RelationsManager::addRelation(Relation* r){
    relations.push_back(r);
}

//attention le \r de \ref n'est pas pris en compte il faudra peut être changer en \\ref..

Relation* RelationsManager::checkReference(Note& n) const{
    NotesManager& nm = NotesManager::getInstance();
    //RelationsManager& rm = RelationsManager::getInstance();
    //On parcourt les notes du notesManager
    for (vector<Note*>::iterator it = nm.getIteratorBegin() ; it != nm.getIteratorEnd(); ++it){
        if((*it)->getClassName() == "Article"){ //si c'est un article
            string temp = "\ref{" + (*it)->getId() + "}"; //on crée un string personnalisé avec son id
            cout << temp<< " ";
            NotesManager::SearchIterator s = NotesManager::SearchIterator("Nada"); //on crée un searchiterator qui renvoie le premier article
            Article* res = s.NotesManager::SearchIterator::SearchTextArticle(temp);
            if (dynamic_cast<Article&>(n).getText().find(temp) != string::npos){
                    //on crée la référence
                    //Note* resTemp = dynamic_cast<Note*>(res);
                    Couple c = Couple(n,*(*it));
                    Relation* r = new Relation;
                    r->addRelation(c);
                    //rm.addRelation(r);
                    cout << ": Présent dans " << (*it)->getId() << "\n";
                    return r;
            }
            else{cout << ": Pas présent dans " << (*it)->getId() << "\n";}
        }
    }

}
/*
RelationsManager& RelationsManager::getInstance() {
  // Si le pointeur vers l'instance unique pointe vers 0
  if(!handler.instance) {
    handler.instance = new RelationsManager;
  }
  // Retour par ref vers l'instance unique
  return *handler.instance;
}

void RelationsManager::libererInstance() {
  // Libération de la mémoire allouée à l'instance unique
  delete handler.instance;
  // Repasse le pointeur à null/nullptr/0 pour que le prochain appel à getInstance recrée bien une instance
  handler.instance=0;
}

RelationsManager::Handler RelationsManager::handler=Handler();*/
