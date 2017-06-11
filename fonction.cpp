#include <iostream>
#include <fstream>
#include "fonction.h"

///Constructeur de la classe date
date::date(int j, int m, int a) : jour(j), mois(m), annee(a) {}

/// Affiche la date sous le format Jour/Mois/Annee
void date::print() const{
    qDebug() << jour << "/" << mois << "/" << annee << "\n";
}
///Destructeur
Note::~Note() {}

///Fonction qui transforme le numéro de version d'une note en un Qstring de la forme "Version#numversion"
QString Note::toStringVersionNumber(){
    QString version = "Version#" + QString::number(numVersion);
    return version;
}


///Methodes de la classe Article

///Constructeur de la classe Article pour la création d'un article à partir d'un ArticleFactory
Article::Article(const QString& id, const QString& titre, const QString& text) : Note(id,titre),text(text){}

///Constructeur de la classe Article pour la création d'un article lors de son ajout dans NotesManager pendant l'appel de la fonction load
Article::Article(const QString& id, const QString& titre, const QDate& cr, const QDate& lm, const QString& text) : Note(id,titre,cr,lm), text(text){}


/// Design Pattern Factory Method, utilisé pour qu'un objet Article ait la responsabilité en obtenant une duplication dynamique de l'objet passé en argument
Article* Article::clone() const { return new Article(*this);}

///Destructeur de la classe Article
Article::~Article() {}

///Fonction permettant d'afficher un Article sur le flux console (pas visible dans l'application)
void Article::print() const{
    qDebug() << "Id de l'article: " << id << "\n";
    qDebug() << "Titre de l'article: " << title << "\n";
    qDebug() << "Contenu de l'article: " << text << "\n";
}


///Methodes de la classe Task


///Constructeur de la classe Task pour la création d'un article à partir d'un ArticleFactory
Task::Task(const QString& id, const QString& title, const QString& s, const QDate& d, const unsigned int& p) : Note(id, title),  priority(p), deadline(d), status(s)  {}

///Constructeur de la classe Task pour la création d'un article lors de son ajout dans NotesManager pendant l'appel de la fonction load
Task::Task(const QString& id, const QString& title, const QDate& cr, const QDate& lm, const QString& s, const QDate& d, const unsigned int& p) : Note(id, title, cr, lm), priority(p), deadline(d), status(s) {}

///Fonction de clonage d'un tache
Task* Task::clone() const { return new Task(*this);}

///Destructeur de la classe Task
Task::~Task(){}

///Fonction retournant la Qstring contenant les actions d'une Task
QString Task::getActions() const{ return actions;}

///Fonction permettant d'ajouter une action aux actions d'une tâche.
void Task::addAction(const QString& s){
    QString temp = getActions();
    ///On ajoute l'action passée en paramètre à la Qstring contenant déjà les autres actions
    setAction(temp+" - "+s);
}

///Fonction permettant d'afficher une note sur la sortie console (pas visible dans l'application)
void Task::print() const{
    qDebug() << "Id de la tache : " << id << "\n";
    qDebug() << "Action : " << title << "\n";
    if (priority!=0) {qDebug() << "Niveau de Priorite : " << priority << "\n";}
    if (deadline.isValid()) {  qDebug() << "Deadline : "; deadline.toString();}
    qDebug() << "Statut : " << status << "\n";
    getActions();
}

///Methodes de la classe Multimedia (et de ses filles)

///Constructeur de la classe Multimédia
Multimedia::Multimedia(const QString& id, const QString& title, const QString& desc, const QString& imgF) : Note(id, title), description(desc), imageFilename(imgF) {}

///Constructeur de la classe Task pour la création d'un article lors de son ajout dans NotesManager pendant l'appel de la fonction load
Multimedia::Multimedia(const QString& id, const QString& title, const QDate& cr, const QDate& lm, const QString& desc, const QString& imgF) : Note(id, title,cr,lm), description(desc), imageFilename(imgF) {}

///Destructeur de la classe multimédia
Multimedia::~Multimedia(){}

///Destructeur de la classe Image
Image::~Image(){}

///Destructeur de la classe Audio
Audio::~Audio(){}

///Destructeur de la classe Video
Video::~Video(){}


///Méthode print() redéfinie pour s'adapter à la classe Image, sortie sur la console et pas dans l'application
void Image::print() const{
    qDebug() << "Id de l'image : " << id << "\n";
    qDebug() << "Titre de l'image : " << title << "\n";
    qDebug() << "Description de l'image : " << description << "\n";
    ///afficher le fichier de l'image
}

///Méthode clone() utilisée pour le clonage d'une image
Image* Image::clone() const {return new Image(*this);}

/// Méthode print() redéfinie pour s'adapter à la classe Audio, sortie sur la console et pas dans l'application
void Audio::print() const{
    qDebug() << "Id de l'enregistrement audio : " << id << "\n";
    qDebug() << "Titre de l'enregistrement audio : " << title << "\n";
    qDebug() << "Description de l'enregistrement audio : " << description << "\n";
    ///afficher l'image de l'enregistrement audio
}

///Méthode clone() utilisée pour le clonage d'un audio
Audio* Audio::clone() const {return new Audio(*this);}

/// Méthode print() redéfinie pour s'adapter à la classe Video, sortie sur la console et pas dans l'application
void Video::print() const{
    qDebug() << "Id de l'enregistrement video : " << id << "\n";
    qDebug() << "Titre de l'enregistrement video : " << title << "\n";
    qDebug() << "Description de l'enregistrement video : " << description << "\n";
    ///afficher l'image de l'enregistrement video
}

///Méthode clone() utilisée pour le clonage d'une video
Video* Video::clone() const {return new Video(*this);}

///Opérateur de comparaison entre deux notes
bool operator==(const Note& n1, const Note& n2){
    ///Si leurs Ids sont égaux alors les notes sont identiques car les Ids sotn uniques
    return n1.getId() == n2.getId();
}

/// Save Article enregistre tout les attributs définissant un Article
QXmlStreamWriter& Article::save(QXmlStreamWriter& stream) const {
        ///on indique le début d'un élément article
        stream.writeStartElement("article");
        ///On écrit son id dans le flux
        stream.writeTextElement("id",getId());
        ///On écrit sa date de création dans le flux en la convertissant en Qstring au format dd-MM-yyyy
        stream.writeTextElement("creation",getDateCreation().toString("dd-MM-yyyy"));
        ///On écrit sa date de dernière modification dans le flux en la convertissant en Qstring au format dd-MM-yyyy
        stream.writeTextElement("lastmodif",getDateLastModif().toString("dd-MM-yyyy"));
        ///On écrit le titre dans le flux
        stream.writeTextElement("title",getTitle());
        ///On écrit le texte dans le flux
        stream.writeTextElement("text",getText());
        ///on indique la fin de l'écriture de l'élément dans le flux
        stream.writeEndElement();
        return stream;
}

QXmlStreamWriter& Audio::save(QXmlStreamWriter& stream) const {
        ///on indique le début d'un élément audio
        stream.writeStartElement("audio");
        ///On écrit son id dans le flux
        stream.writeTextElement("id",getId());
        ///On écrit sa date de création dans le flux en la convertissant en Qstring au format dd-MM-yyyy
        stream.writeTextElement("creation",getDateCreation().toString("dd-MM-yyyy"));
        ///On écrit sa date de dernière modification dans le flux en la convertissant en Qstring au format dd-MM-yyyy
        stream.writeTextElement("lastmodif",getDateLastModif().toString("dd-MM-yyyy"));
        ///On écrit le titre dans le flux
        stream.writeTextElement("title",getTitle());
        ///On écrit la description dans le flux
        stream.writeTextElement("desc",getDescription());
        ///On écrit le nom du fichier dans le flux
        stream.writeTextElement("file", getImageFilename ());
        ///on indique la fin de l'écriture de l'élément dans le flux
        stream.writeEndElement();
        return stream;
}

QXmlStreamWriter& Image::save(QXmlStreamWriter& stream) const {
        ///on indique le début d'un élément image
        stream.writeStartElement("image");
        ///On écrit son id dans le flux
        stream.writeTextElement("id",getId());
        ///On écrit sa date de création dans le flux en la convertissant en Qstring au format dd-MM-yyyy
        stream.writeTextElement("creation",getDateCreation().toString("dd-MM-yyyy"));
        ///On écrit sa date de dernière modification dans le flux en la convertissant en Qstring au format dd-MM-yyyy
        stream.writeTextElement("lastmodif",getDateLastModif().toString("dd-MM-yyyy"));
        ///On écrit le titre dans le flux
        stream.writeTextElement("title",getTitle());
        ///On écrit la description dans le flux
        stream.writeTextElement("desc",getDescription());
        ///On écrit le nom du fichier dans le flux
        stream.writeTextElement("file", getImageFilename ());
        ///on indique la fin de l'écriture de l'élément dans le flux
        stream.writeEndElement();
        return stream;
}

QXmlStreamWriter& Video::save(QXmlStreamWriter& stream) const {
        ///on indique le début d'un élément video
        stream.writeStartElement("video");
        ///On écrit son id dans le flux
        stream.writeTextElement("id",getId());
        ///On écrit sa date de création dans le flux en la convertissant en Qstring au format dd-MM-yyyy
        stream.writeTextElement("creation",getDateCreation().toString("dd-MM-yyyy"));
        ///On écrit sa date de dernière modification dans le flux en la convertissant en Qstring au format dd-MM-yyyy
        stream.writeTextElement("lastmodif",getDateLastModif().toString("dd-MM-yyyy"));
        ///On écrit le titre dans le flux
        stream.writeTextElement("title",getTitle());
        ///On écrit la description dans le flux
        stream.writeTextElement("desc",getDescription());
        ///On écrit le nom du fichier dans le flux
        stream.writeTextElement("file", getImageFilename ());
        ///on indique la fin de l'écriture de l'élément dans le flux
        stream.writeEndElement();
        return stream;
}

QXmlStreamWriter& Task::save(QXmlStreamWriter& stream) const {
        ///on indique le début d'un élément task
        stream.writeStartElement("task");
        ///On écrit son id dans le flux
        stream.writeTextElement("id",getId());
        ///On écrit sa date de création dans le flux en la convertissant en Qstring au format dd-MM-yyyy
        stream.writeTextElement("creation",getDateCreation().toString("dd-MM-yyyy"));
        ///On écrit sa date de dernière modification dans le flux en la convertissant en Qstring au format dd-MM-yyyy
        stream.writeTextElement("lastmodif",getDateLastModif().toString("dd-MM-yyyy"));
        ///On écrit le titre dans le flux
        stream.writeTextElement("title",getTitle());
        ///On écrit les actions dans le flux
        stream.writeTextElement("actions",getActions());
        ///On écrit la priorité de la tache dans le flux en la convertissant en Qstring
        stream.writeTextElement("prio", QString::number(getPriority()));
        ///On écrit la deadline dans le flux en la convertissant en Qstring au format dd-MM-yyyy
        stream.writeTextElement("deadline", getDeadline().toString("dd-MM-yyyy"));
        ///On écrit le status de la tache dans le flux
        stream.writeTextElement("status", getStatus());
        ///on indique la fin de l'écriture de l'élément dans le flux
        stream.writeEndElement();
        return stream;
}
