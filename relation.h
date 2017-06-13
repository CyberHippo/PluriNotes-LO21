#ifndef RELATION_H_INCLUDED
#define RELATION_H_INCLUDED

#include <iostream>
#include <fstream>
#include "fonction.h"
#include "notemanager.h"

/// Un couple signifie qu'il y a une relation depuis la note x vers la note y, x est le first et y est le second. Il peut y avoir un label pour chaque couple.
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

///Classe Relation
class Relation {
    friend class RelationsManager;
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
    QXmlStreamWriter& save(QXmlStreamWriter& stream) const;
    vector<Couple>::iterator getIteratorBegin() { return couples.begin();}
    vector<Couple>::iterator getIteratorEnd() { return couples.end();}
};


///Classe Reference qui est une spécialisation de la classe Relation
class Reference : public Relation {

};

///Class Relations Manager {singleton}
class RelationsManager
{

private:
    ///Vecteur contenant toutes les relations
    vector<Relation*> relations;
    ///Nom du fichier pour sauvegarder toutes les relations
    mutable QString filename;

    RelationsManager();
    /// constructeur de recopie
    RelationsManager(const RelationsManager& r);
    ///destructeur
    ~RelationsManager();

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
    static RelationsManager& getInstance();
    static void libererInstance();
    void showAll() const;
    void deleteRelation(Note& n1, Note& n2);
    void deleteRelationOfNote(Note& n);
    unsigned int getRelationPosition(Note& n1, Note& n2);
    bool checkReference(Article& a) const;
    void checkReferenceInText(Note* n, const QString& s);
    bool checkRelation(Note& n);
    bool isReferenced(Note* n);
    bool isAlreadyPresent(Relation r) const;
    void CheckAllArticle(Article* a);
    void CheckAllTask(Task* t);
    void CheckAllMultimedia(Multimedia* m);
    void saveAll();
    void load();
    ///Méthode permettant de renvoyer le nom du fichier de sauvegarde des relations
    QString getFilename() const { return filename; }
    ///Méthode permettant de changer le fichier de sauvegarde des relations
    void setFilename(const QString& f) { filename=f; }
    QXmlStreamReader& loadRelation(QXmlStreamReader& xml);

    vector<Relation*>::iterator getIteratorBegin() { return relations.begin();}
    vector<Relation*>::iterator getIteratorEnd() { return relations.end();}

};



#endif // RELATION_H_INCLUDED
