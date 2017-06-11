#include <iostream>
#include <QSet>
#include <QList>
#include <QString>
#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include "relation.h"
#include "notemanager.h"
#include "mainwindow.h"

RelationsManager::RelationsManager(){}

///Le destructeur de RelationsManager supprime chaque relation contenue dans le vecteur relations puis libère la mémoire du vecteur avec clear().
RelationsManager::~RelationsManager(){
    for(unsigned int i=0; i<relations.size(); i++){ delete relations[i];}
    relations.clear();
}

///Cette fonction permet d'afficher un couple sur la sortie console. (non visible dans l'application)
void Couple::print() const{
    qDebug() << "[ " << getFirst().getId();
    qDebug() << " - ";
    qDebug() << getSecond().getId();
    qDebug() << " ]" << "\n";
}

///Cette fonction permet d'afficher tous les couples présents dans une relation sur la sortie console.
void Relation::getCouples() const{
    for (vector<Couple>::const_iterator it = couples.begin() ; it != couples.end(); ++it){
        it->print();
        qDebug() << "\n";
    }
}

///Cette fonction permet d'ajouter un couple composé de la note a et de la note b au vecteur de couples d'une relation.
void Relation::addRelation(Note& a, Note& b){
    Couple* c = new Couple(a,b);
    couples.push_back(*c);
}

///Cette fonction permet d'ajouter une couple supplémentaire au vecteur de couples d'une relation.
void Relation::addRelation(Couple& c){
    couples.push_back(c);
}

///Cette fonction permet d'ajouter une relation non orientée, c'est à dire un couple de a vers b et un couple de b vers a. Ces deux couples seront ajoutés au vecteurs de couples de la relation.
void Relation::addRelationNonOrientee(Note& a, Note& b){
    Couple* c1 = new Couple(a,b);
    couples.push_back(*c1);
    Couple* c2 = new Couple(b,a);
    couples.push_back(*c2);
}

///Cette fonction permet d'ajouter une relation non orientée à partir d'un couple passé en argument. La fonction récupère le premier et le second champ du couple et crée un autre couple du second vers le premier. La couple passé en arguement ainsi que le nouveau couple sont ensuite ajoutés au vecteur de couple de la relation.
void Relation::addRelationNonOrientee(Couple& c){
    couples.push_back(c);
    Couple* c2 = new Couple(c.getSecond(),c.getFirst());
    couples.push_back(*c2);
}

///Cette fonction permet d'afficher les ascendants d'une note passée en argument. La fonction itère tous les couples du vecteur de couples et affiche tout ceux dont le champ second correspond à la note.
void Relation::showAscendants(Note& n) const {
    for (vector<Couple>::const_iterator it = couples.begin() ; it != couples.end(); ++it){
        if(it->getSecond() == n){
           it->print();
            qDebug() << "\n";
        }
    }
}


///Cette fonction permet d'afficher les ascendants d'une note passée en argument. La fonction itère tous les couples du vecteur de couples et affiche tout ceux dont le champ first correspond à la note.
void Relation::showDescendants(Note& n) const{
    for (vector<Couple>::const_iterator it = couples.begin() ; it != couples.end(); ++it){
        if(it->getFirst() == n){
           it->print();
           qDebug() << "\n";
        }
    }
}

///Cette fonction permet d'ajouter une relation au vecteur de relations de RelationsManager.
void RelationsManager::addRelation(Relation* r){
    relations.push_back(r);
}

//attention le \r de \ref n'est pas pris en compte il faudra peut être changer en \\ref..
///Cette fonction vérifie les références faites à une autre note dans le texte d'un article. La référence doit être de la forme "\ref{id}".
bool RelationsManager::checkReference(Article& a) const{
    ///Instance de NotesManager
    NotesManager& nm = NotesManager::getInstance();
    ///Instance de RelationsManager
    RelationsManager& rm = RelationsManager::getInstance();
    ///Parcours de toutes les notes de notesManager.
    for (vector<Note*>::iterator it = nm.getIteratorBegin() ; it != nm.getIteratorEnd(); ++it){
        ///Pour chaque note on crée un Qstring personnalisé de la forme "\ref{id}".
        QString temp = "\ref{" + (*it)->getId() + "}";
            ///On parcourt le texte de l'article avec la fonction indexOf
            if (a.getText().indexOf(temp) != -1){
                    ///Si le Qstring créée est dans le texte, on crée le couple de l'article vers la note dont on a créé la Qstring personnalisée
                    Couple* c = new Couple(a,*(*it));
                    Relation* r = new Relation;
                    r->addRelation(*c);
                    rm.addRelation(r);
                    return true;
            }
            ///Sinon on ne fait rien
            else{qDebug() << "Pas présent dans " << (*it)->getId() << "\n";}
    }
    return false;
}

///Fonction qui vérifie si une note est référencée
bool RelationsManager::isReferenced(Note* n){
    ///Bool pour dire si la note est référencée ou pas
    bool check = false;
    NotesManager& nm = NotesManager::getInstance();
    ///Création de la string spécifique
    QString ref = "ref{" + n->getId() + "}";
    for (vector<Note*>::iterator it = nm.getIteratorBegin() ; it != nm.getIteratorEnd(); ++it){
        ///On vérifie s'il y a une référence pour un article, s'il contient la string alors le bool passe à true
        if ((*it)->getClassName() == (QString)"art"){
            Article* a = dynamic_cast<Article*>(*it);
            if (a->getTitle().contains(ref)){check = true; return check;}
            if (a->getText().contains(ref)){check = true; return check;}
        }
        ///On vérifie s'il y a une référence vers une tâche, si elle contient la string alors le bool passe à true
        else if ((*it)->getClassName() == (QString)"task"){
            Task* t = dynamic_cast<Task*>(*it);
            if (t->getTitle().contains(ref)){check = true; return check;}
            if (t->getActions().contains(ref)){check = true; return check;}
        }
        ///On vérifie s'il y a une référence vers un multimédia, s'il contient la string alors le bool passe à true
        else {
            Multimedia* m = dynamic_cast<Multimedia*>(*it);
            if (m->getTitle().contains(ref)){check = true; return check;}
            if(m->getDescription().contains(ref)){check = true; return check;}
        }
    }
    ///Retrourne le bool check
    return check;
}

///Renvoie une référence sur l'instance unique du RelationsManager
RelationsManager& RelationsManager::getInstance() {
    ///Si l'instance n'existe pas, on en crée une
    if(!handler3.instance) {
    handler3.instance = new RelationsManager;
  }
  /// Retour par ref vers l'instance unique
  return *handler3.instance;
}

///Libère la mémoire de l'instance de RelationsManager
void RelationsManager::libererInstance() {
  /// Libération de la mémoire allouée à l'instance unique
  delete handler3.instance;
  /// Repasse le pointeur à null/nullptr/0 pour que le prochain appel à getInstance recrée bien une instance
  handler3.instance=0;
}

///Déclaration du handler static
RelationsManager::Handler3 RelationsManager::handler3=Handler3();

///Fonction permettant de vérifier s'il existe un couple parmis toutes les relations dont la note passée en argument serait le champ first ou second.
bool RelationsManager::checkRelation(Note& n) {
    ///Iteration des relations du RelationsManager
    for (vector<Relation*>::iterator it1 = getIteratorBegin() ; it1 != getIteratorEnd(); ++it1){
        ///Iterations des couples de chaque relation
        for (vector<Couple>::iterator it2 = (*it1)->getIteratorBegin() ; it2 != (*it1)->getIteratorEnd(); ++it2){
            ///Si la note est le champ first ou second alors il y a une relation, retourne vrai
            if(it2->getFirst() == n || it2->getSecond() == n){
               return true;
            }
        }
    }
    ///Sinon, on a fini d'itérer, on retourne faux.
    return false;
}

///Fonction permettant de supprimer une relation de RelationsManager
void RelationsManager::deleteRelation(Note& n1, Note& n2){
    ///on récupère la position de la relation dans RelationsManager
    unsigned int i=getRelationPosition(n1,n2);
    ///Suppression de la relation avec la fonction erase.
    relations.erase(getIteratorBegin()+i);
    ///Mise à jour de la fenêtre des relations
    MainWindow::getInstance().updateRelationManager();
}

///Cette fonction permet de retourner la position d'une relation dans RelationsManager
unsigned int RelationsManager::getRelationPosition(Note& n1, Note& n2){
    ///Iteration sur les relations de RelationsManager
    for(unsigned int i=0;i<relations.size();i++){
        ///si la note n1 correspond à first du champ couple et n2 correspond à second du champ couple alors on retourne la position.
        if(relations[i]->couples[0].getFirst() == n1 && relations[i]->couples[0].getSecond() == n2){return i;}
    }
    ///Sinon on lance une exception disant que la note n'a pas été trouvée.
    throw NotesException("La relation n'a pas ete trouvee..");
}

void RelationsManager::deleteRelationOfNote(Note& n){
    for(unsigned int i=0;i<relations.size();i++){
        ///si la note n correspond à first ou second du champ couple alors on supprime le couple de la relation.
        if(relations[i]->couples[0].getFirst() == n){deleteRelation(n, relations[i]->couples[0].getSecond());}
        if(relations[i]->couples[0].getSecond() == n){deleteRelation(relations[i]->couples[0].getFirst(), n);}
    }
}

bool RelationsManager::isAlreadyPresent(Relation r) const{
    for(unsigned int i=0;i<relations.size();i++){
        ///si la note n1 correspond à first du champ couple et n2 correspond à second du champ couple alors on retourne la position.
        if(relations[i]->couples[0].getFirst() == r.couples[0].getFirst() && relations[i]->couples[0].getSecond() == r.couples[0].getSecond()){return true;}
    }
    return false;
}


void RelationsManager::checkReferenceInText(Note* n, const QString& s){
    ///Instance de NotesManager
    NotesManager& nm = NotesManager::getInstance();
    ///Parcours de toutes les notes de notesManager.
    for (vector<Note*>::iterator it = nm.getIteratorBegin() ; it != nm.getIteratorEnd(); ++it){
        ///Pour chaque note on crée un Qstring personnalisé de la forme "ref{id}".
        QString temp = "ref{" + (*it)->getId() + "}";
            ///On parcourt le texte de l'article avec la fonction indexOf
            if (s.indexOf(temp) != -1){
                    ///Si le Qstring créée est dans le texte, on crée le couple de la note vers la note dont on a créé la Qstring personnalisée
                    Couple* c = new Couple(*n,*(*it));
                    Reference* r = new Reference;
                    ///on ajoute la relation au vecteur
                    r->addRelation(*c);
                    if(!isAlreadyPresent(*r)){addRelation(r);}
                    qDebug() << "Présent dans " << (*it)->getId() << "relation ajotuée\n";
            }
            ///Sinon on ne fait rien
            else{qDebug() << "Pas présent dans " << (*it)->getId() << "\n";}
    }
}




void RelationsManager::CheckAllTask(Task* t){
    checkReferenceInText(t,t->getTitle());
    checkReferenceInText(t,t->getActions());
}


void RelationsManager::CheckAllArticle(Article* a){
    checkReferenceInText(a,a->getTitle());
    checkReferenceInText(a,a->getText());
}

void RelationsManager::CheckAllMultimedia(Multimedia* m){
    checkReferenceInText(m,m->getTitle());
    checkReferenceInText(m,m->getDescription());
    checkReferenceInText(m,m->getImageFilename());
}
