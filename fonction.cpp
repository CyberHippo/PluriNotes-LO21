#include <iostream>
#include <fstream>
#include "fonction.h"

/// Affiche la date sous le format Jour/Mois/Annee
date::date(int j, int m, int a) : jour(j), mois(m), annee(a) {}
void date::print() const{
    qDebug() << jour << "/" << mois << "/" << annee << "\n";
}
///Destructeur
Note::~Note() {}

QString Note::toStringVersionNumber(){
    QString version = "Version#" + QString::number(numVersion);
    return version;
}


///Methodes de la classe Article
//Constructeur & destructeur:
Article::Article(const QString& id, const QString& titre, const QString& text) : Note(id,titre),text(text){}
Article::Article(const QString& id, const QString& titre, const QDate& cr, const QDate& lm, const QString& text) : Note(id,titre,cr,lm), text(text){}

//Article::Article(const Note& N1, const QString& text) : Note(N1), text(text) {}

/// Design Pattern Factory Method, utilisé pour qu'un objet Article ait la responsabilité en obtenant une duplication dynamique de l'objet passé en argument
Article* Article::clone() const { return new Article(*this);}
Article::~Article() {}

void Article::print() const{
    qDebug() << "Id de l'article: " << id << "\n";
    qDebug() << "Titre de l'article: " << title << "\n";
    qDebug() << "Contenu de l'article: " << text << "\n";
}


///Methodes de la classe Task
//Constructeur & destructeur
Task::Task(const QString& id, const QString& title, const QString& s, const QDate& d, const unsigned int& p) : Note(id, title),  priority(p), deadline(d), status(s)  {}
Task::Task(const QString& id, const QString& title, const QDate& cr, const QDate& lm, const QString& s, const QDate& d, const unsigned int& p) : Note(id, title, cr, lm), priority(p), deadline(d), status(s) {}

//Task::Task(const QString& id, const QString& title, const QString& s, const date& d, const unsigned int& p) : Note(id, title), actions(0), priority(p), deadline(d), status(s)  {}

Task* Task::clone() const { return new Task(*this);}
Task::~Task(){}
/*void Task::getActions() const{
   for (vector<Action>::const_iterator it = actions.begin() ; it != actions.end(); ++it){
        it->print();
        qDebug() << "\n";
    }
}*/

QString Task::getActions() const{ return actions;}

/*void Task::addAction(const QString& s){
    Action* a = new Action;
    a->setText(s);
    actions.push_back(*a);
}*/

void Task::addAction(const QString& s){
    QString temp = getActions();
    setAction(temp+" - "+s);
}

void Task::print() const{
    qDebug() << "Id de la tache : " << id << "\n";
    qDebug() << "Action : " << title << "\n";
    if (priority!=0) {qDebug() << "Niveau de Priorite : " << priority << "\n";}
    if (deadline.isValid()) {  qDebug() << "Deadline : "; deadline.toString();}
    //if (deadline.jour!=0 && deadline.mois!=0 && deadline.annee!=0) {  qDebug() << "Deadline : "; deadline.print();}
    qDebug() << "Statut : " << status << "\n";
    getActions();
}

///Methodes de la classe Multimedia (et de ses filles)
//Constructeur & destructeur
Multimedia::Multimedia(const QString& id, const QString& title, const QString& desc, const QString& imgF) : Note(id, title), description(desc), imageFilename(imgF) {}
/// Surcharge du constructeur: ce constructeur sera utilisé dans la fonction load
Multimedia::Multimedia(const QString& id, const QString& title, const QDate& cr, const QDate& lm, const QString& desc, const QString& imgF) : Note(id, title,cr,lm), description(desc), imageFilename(imgF) {}
Multimedia::~Multimedia(){}
Image::~Image(){}
Audio::~Audio(){}
Video::~Video(){}
 /// Méthode redéfinie pour s'adapter à la classe Image
void Image::print() const{
    qDebug() << "Id de l'image : " << id << "\n";
    qDebug() << "Titre de l'image : " << title << "\n";
    qDebug() << "Description de l'image : " << description << "\n";
    ///afficher le fichier de l'image
}
Image* Image::clone() const {return new Image(*this);}
/// Méthode redéfinie pour s'adapter à la classe Audio
void Audio::print() const{
    qDebug() << "Id de l'enregistrement audio : " << id << "\n";
    qDebug() << "Titre de l'enregistrement audio : " << title << "\n";
    qDebug() << "Description de l'enregistrement audio : " << description << "\n";
    ///afficher l'image de l'enregistrement audio
}
Audio* Audio::clone() const {return new Audio(*this);}
/// Méthode redéfinie pour s'adapter à la classe Video
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

/// Save Article enregistre tout les attributs définissant un Article
QXmlStreamWriter& Article::save(QXmlStreamWriter& stream) const {
        stream.writeStartElement("article");
        stream.writeTextElement("id",getId());
        stream.writeTextElement("creation",getDateCreation().toString("dd-MM-yyyy"));
        stream.writeTextElement("lastmodif",getDateLastModif().toString("dd-MM-yyyy"));
        stream.writeTextElement("title",getTitle());
        stream.writeTextElement("text",getText());
        stream.writeEndElement();
        return stream;
}

QXmlStreamWriter& Audio::save(QXmlStreamWriter& stream) const {
        stream.writeStartElement("audio");
        stream.writeTextElement("id",getId());
        stream.writeTextElement("creation",getDateCreation().toString("dd-MM-yyyy"));
        stream.writeTextElement("lastmodif",getDateLastModif().toString("dd-MM-yyyy"));
        stream.writeTextElement("title",getTitle());
        stream.writeTextElement("desc",getDescription());
        stream.writeTextElement("file", getImageFilename ());
        stream.writeEndElement();
        return stream;
}

QXmlStreamWriter& Image::save(QXmlStreamWriter& stream) const {
        stream.writeStartElement("image");
        stream.writeTextElement("id",getId());
        stream.writeTextElement("creation",getDateCreation().toString("dd-MM-yyyy"));
        stream.writeTextElement("lastmodif",getDateLastModif().toString("dd-MM-yyyy"));
        stream.writeTextElement("title",getTitle());
        stream.writeTextElement("desc",getDescription());
        stream.writeTextElement("file", getImageFilename ());
        stream.writeEndElement();
        return stream;
}

QXmlStreamWriter& Video::save(QXmlStreamWriter& stream) const {
        stream.writeStartElement("video");
        stream.writeTextElement("id",getId());
        stream.writeTextElement("creation",getDateCreation().toString("dd-MM-yyyy"));
        stream.writeTextElement("lastmodif",getDateLastModif().toString("dd-MM-yyyy"));
        stream.writeTextElement("title",getTitle());
        stream.writeTextElement("desc",getDescription());
        stream.writeTextElement("file", getImageFilename ());
        stream.writeEndElement();
        return stream;
}

QXmlStreamWriter& Task::save(QXmlStreamWriter& stream) const {
        stream.writeStartElement("task");
        stream.writeTextElement("id",getId());
        stream.writeTextElement("creation",getDateCreation().toString("dd-MM-yyyy"));
        stream.writeTextElement("lastmodif",getDateLastModif().toString("dd-MM-yyyy"));
        stream.writeTextElement("title",getTitle());
        stream.writeTextElement("actions",getActions());
        stream.writeTextElement("prio", QString::number(getPriority()));
        stream.writeTextElement("deadline", getDeadline().toString("dd-MM-yyyy"));
        stream.writeTextElement("status", getStatus());
        stream.writeEndElement();
        return stream;
}
