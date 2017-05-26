#ifndef RELATION_H_INCLUDED
#define RELATION_H_INCLUDED

#include <iostream>
#include <fstream>
#include "fonction.h"

class Couple {
    Note* first;
    Note* second;
    string label;
public:
    Note& getFirst() const {return *first;}
    Note& getSecond() const {return *second;}
    Couple(Note& p, Note& s) : first(&p), second(&s) {}
    string getLabel() const {return label;}
    void setLabel(const string& s) {label=s;}
    void print() const;
};


class Relation {
    string title;
    string description;
    vector<Couple> couples;
public:
    void getCouples() const;
    void addRelation(Note& a, Note& b);
    void addRelation(Couple& c);
    void addRelationNonOrientee(Note& a, Note& b);
    void addRelationNonOrientee(Couple& c);
    void showAscendants(Note& n) const;
    void showDescendants(Note& n) const;
};

//"Une relation est seulement définie entre les dernières versions des notes."
//Ce n'est pas un problème car on ne modifie pas l'id quand on modifie une note.

//L’application doit aussi permettre de visualiser pour une note choisie, l’arborescence des ascendants
//et l’arborescence des descendants de la note dans l’ensemble des relations existantes de manière simultanée.

#endif // RELATION_H_INCLUDED
