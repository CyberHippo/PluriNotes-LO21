#ifndef RELATION_H_INCLUDED
#define RELATION_H_INCLUDED

#include <iostream>
#include <fstream>
#include "fonction.h"
#include "notemanager.h"

class Couple {
    Note* first;
    Note* second;
    QString label;
public:
    Note& getFirst() const {return *first;}
    Note& getSecond() const {return *second;}
    Couple(Note& p, Note& s) : first(&p), second(&s) {}
    QString getLabel() const {return label;}
    void setLabel(const QString& s) {label=s;}
    void print() const;
};


class Relation {
    QString title;
    QString description;
    vector<Couple> couples;
public:
    void getCouples() const;
    void addRelation(Note& a, Note& b);
    void addRelation(Couple& c);
    void addRelationNonOrientee(Note& a, Note& b);
    void addRelationNonOrientee(Couple& c);
    void showAscendants(Note& n) const;
    void showDescendants(Note& n) const;
    //void deleteRelation(){ couples.clear();}
    vector<Couple>::iterator getIteratorBegin() { return couples.begin();}
    vector<Couple>::iterator getIteratorEnd() { return couples.end();}
};


//"Une relation est seulement définie entre les dernières versions des notes."
//Ce n'est pas un problème car on ne modifie pas l'id quand on modifie une note.



class Reference : public Relation {

};

///Class Relations Manager
class RelationsManager
{

private:
    vector<Relation*> relations;
    unsigned int nbRelations;
    unsigned int nbMaxRelations;

    RelationsManager();
    RelationsManager(const RelationsManager& r);     /// constructeur de recopie
    ~RelationsManager(); ///destructeur

    ///surcharge de =
    RelationsManager& operator=(const RelationsManager&);

    ///static RelationsManager *instance;
    struct Handler3{
        RelationsManager* instance;
        Handler3() : instance(0){}
        ~Handler3(){if(instance) delete instance; instance = 0;}
    };
    static Handler3 handler3;


public:
    void addRelation(Relation* r);
    void showRelation (const Note& note) const;
    //void load(const QString& f);
    //void save() const;
    static RelationsManager& getInstance();
    static void libererInstance();
    void showAll() const;
    ///A ecrire
    void deleteRelation(Note& n);
    //void editRelation(QString id);
    //void showOldNotes(QString id);
    //void restaurerNote(QString id, QString title);
    bool checkReference(Article& a) const;
    bool checkRelation(Note& n);

    vector<Relation*>::iterator getIteratorBegin() { return relations.begin();}
    vector<Relation*>::iterator getIteratorEnd() { return relations.end();}

};



#endif // RELATION_H_INCLUDED
