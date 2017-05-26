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




