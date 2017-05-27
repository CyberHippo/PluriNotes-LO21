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



class Reference : public Relation {

};

///Class Relations Manager
class RelationsManager
{
private:
    vector<Relation*> relations;
    unsigned int nbRelations;
    unsigned int nbMaxRelations;

    //RelationsManager();
    RelationsManager(const RelationsManager& r);     /// constructeur de recopie
    //~RelationsManager(); ///destructeur

    string filename;

    ///surcharge de =
    RelationsManager& operator=(const RelationsManager&);
    /*
    ///static NotesManager *instance;
    struct Handler{
        RelationsManager* instance;
        Handler() : instance(0){}
        ~Handler(){if(instance) delete instance; instance = 0;}
    };*/
    //static Handler handler;


public:
    RelationsManager(){}
    ~RelationsManager(){}
    void addRelation(Relation* r);
    //Note& getNewNote(const string& id);
    //Note& getNote(const string& id);
    void showRelation (const Note& note) const;
    void load(const string& f);
	void save() const;
    static RelationsManager& getInstance();
    static void libererInstance();
    void showAll() const;
    ///A ecrire
    //void deleteRelation(string &id);
    //void editRelation(string id);
    //void showOldNotes(string id);
    //void restaurerNote(string id, string title);
    Relation* checkReference(Note& n) const;
};



#endif // RELATION_H_INCLUDED
