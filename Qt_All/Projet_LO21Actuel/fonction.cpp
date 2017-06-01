#include <iostream>
#include <fstream>
#include "fonction.h"

///Methodes de la classe Date
date::date(int j, int m, int a) : jour(j), mois(m), annee(a) {}
void date::print() const{
    qDebug() << jour << "/" << mois << "/" << annee << "\n";
}
///Methodes de la classe Note
Note::~Note() {}

///Methodes de la classe Article
//Constructeur & destructeur:
Article::Article(const QString& id, const QString& titre, const QString& text) : Note(id,titre),text(text){}
//Article::Article(const Note& N1, const QString& text) : Note(N1), text(text) {}
Article* Article::clone() const { return new Article(*this);}
Article::~Article() {}

void Article::print() const{
    qDebug() << "Id de l'article: " << id << "\n";
    qDebug() << "Titre de l'article: " << title << "\n";
    qDebug() << "Contenu de l'article: " << text << "\n";
}



///Methodes de la classe Task
//Constructeur & destructeur
Task::Task(const QString& id, const QString& title, const QString& s, const QDate& d, const unsigned int& p) : Note(id, title), actions(0), priority(p), deadline(d), status(s)  {}
Task* Task::clone() const { return new Task(*this);}
Task::~Task(){}
void Task::getActions() const{
    for (vector<Action>::const_iterator it = actions.begin() ; it != actions.end(); ++it){
        it->print();
        qDebug() << "\n";
    }
}

void Task::addAction(const QString& s){
    Action* a = new Action;
    a->setText(s);
    actions.push_back(*a);
}

void Task::print() const{
    qDebug() << "Id de la tache : " << id << "\n";
    qDebug() << "Action : " << title << "\n";
    if (priority!=0) {qDebug() << "Niveau de Priorite : " << priority << "\n";}
    if (deadline.isValid()) {  qDebug() << "Deadline : "; deadline.toString();}
    qDebug() << "Statut : " << status << "\n";
    getActions();
}

///Methodes de la classe Multimedia (et de ses filles)
//Constructeur & destructeur
Multimedia::Multimedia(const QString& id, const QString& title, const QString& desc, const QString& imgF) : Note(id, title), description(desc), imageFilename(imgF) {}
Multimedia::~Multimedia(){}
Image::~Image(){}
Audio::~Audio(){}
Video::~Video(){}

void Image::print() const{
    qDebug() << "Id de l'image : " << id << "\n";
    qDebug() << "Titre de l'image : " << title << "\n";
    qDebug() << "Description de l'image : " << description << "\n";
    ///afficher le fichier de l'image
}
Image* Image::clone() const {return new Image(*this);}

void Audio::print() const{
    qDebug() << "Id de l'enregistrement audio : " << id << "\n";
    qDebug() << "Titre de l'enregistrement audio : " << title << "\n";
    qDebug() << "Description de l'enregistrement audio : " << description << "\n";
    ///afficher l'image de l'enregistrement audio
}
Audio* Audio::clone() const {return new Audio(*this);}

void Video::print() const{
    qDebug() << "Id de l'enregistrement video : " << id << "\n";
    qDebug() << "Titre de l'enregistrement video : " << title << "\n";
    qDebug() << "Description de l'enregistrement video : " << description << "\n";
    ///afficher l'image de l'enregistrement video
}
Video* Video::clone() const {return new Video(*this);}




/*///Surchage d'operateurs
ostream& operator<<(ostream& f, const Article& a){
    f<<a.getId()<<"\n";
    f<<a.getTitle()<<"\n";
    f<<a.getText()<<"\n";
    return f;
}*/

bool operator==(const Note& n1, const Note& n2){
    return n1.getId() == n2.getId();
}


