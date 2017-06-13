#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED

#include <QString>
#include <QDebug>
#include <iostream>
#include <time.h>
#include <fstream>
#include <vector>
#include "oldversions.h"
#include <QDate>
#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QMessageBox>
using namespace std;


///Class NotesException, sera utilisée pour l'interruption de l'exécution du programme suite à un événement particulier
class NotesException{
private:
    QString info;
public:
    NotesException(const QString& message):info(message){}
    QString getInfo() const { return info; }
};

///Class Note, classe mère abstraite. Les méthodes virtuelles seront définies dans les classes filles. Il est indispensable de mettre les accesseurs en virtual pour pouvoir retourner les attributs correspondants bien à chaque classe d'intérêt (Task, Article, Image etc...)
class Note {
protected:
    ///ID de la Note
    QString id;
    ///Titre de la Note
    QString title;
    ///Date de création de la Note
    QDate creation;
    ///Date de dernière modification de la Note
    QDate last_modif;
    ///Attribut de type OldVersions, servant à versionner les Notes, et intéragir avec les versions précédentes d'une Note.
    OldVersions versions_anterieurs;
    /// Indique la version de la Note
    unsigned int numVersion;

public:
    ///Constructeur de la classe Note pour la création d'un article à partir d'un ArticleFactory, à noter que Note est une classe virtuelle pure, on ne peut donc pas instancier d'objet Note.
    Note(const QString& id, const QString& titre) : id(id), title(titre), numVersion(0) {creation = QDate::currentDate(); last_modif = QDate::currentDate();}
    ///Surcharge du constructeur de la classe Note pour utlisation lors de la fonction Load, à noter que Note est une classe virtuelle pure, on ne peut donc pas instancier d'objet Note.
    Note(const QString& id, const QString& titre, const QDate& cr, const QDate& lm) : id(id), title(titre), creation(cr), last_modif(lm), numVersion(0) {}
    ///Destructeur
    virtual ~Note();
    ///Accesseur ID
    virtual QString getId() const { return id; }
    ///Accesseur Titre
    virtual QString getTitle() const { return title; }
    ///Accesseur Date_Creation
    virtual QDate getDateCreation() const { return creation; }
    ///Accesseur Date_Dernièremodif
    virtual QDate getDateLastModif() const { return last_modif; }
    ///Setteur Date Dernière modification
    virtual void setDateLastMofid(){last_modif = QDate::currentDate();}
    /// Accesseur renvoyant le numéro de version
    virtual unsigned int getNumVersion() const { return numVersion;}
    ///Setteur pour définir le numéro de la version
    virtual void setNumVersion(unsigned int nb) { numVersion == nb;}
    /// Incrément le numéro de la version.
    virtual void incrementNumVersion(){ numVersion++;}
    /// Retourne les versions antérieures de la Note
    virtual OldVersions getVersionsAnt() const {return versions_anterieurs;}
    /// Setteur Titre
    virtual void setTitle(const QString& t) {title=t;}
    /// Setteur versions antérieures
    virtual void setVersionsAnt(OldVersions va){versions_anterieurs = va;}
    /// Renvoie le nombre d'anciennes versions
    virtual unsigned int getNumberOfVersions(){return versions_anterieurs.getOldNotes().size();}
    /// Retourne un QString composé du nombre de la version.
    virtual QString toStringVersionNumber();
    ///Cela permet de stocker une note dans l'attribut versions_anterieurs de la classe Note
    virtual void addOldVersion (){ versions_anterieurs.addNote((*this).clone());}
    ///Cette fonction permets d'afficher les versions anterieurs
    virtual void printOldVersion(){ versions_anterieurs.printVersions();}
    virtual void print() const = 0;
    ///Design Pattern Factory
    virtual Note* clone() const = 0;
    ///Renvoie le nom de la classe
    virtual QString getClassName() const = 0;
    ///Méthode virtuelle pure servant à sauvegarder les attributs d'une note
    virtual QXmlStreamWriter& save(QXmlStreamWriter& stream) const = 0;
    virtual Note& getReference(){return *this;}
};

///Class Article, héritage public de Note. La Classe Article hérite donc des attributs et des méthodes de la classe Note. Un objet Article est aussi un objet de la classe Note.
class Article : public Note {
private:
    ///Attribut privé pour renseigner le texte d'un article
    QString text;

    Article & operator=(const Article & a);
    //Article(const Article & a); On l'enleve pour implementer le factory method
public:
    Article(const QString& id, const QString& titre, const QString& text);
    Article(const QString& id, const QString& titre, const QDate& cr, const QDate& lm, const QString& text);
    ///Renvoie le nom de la classe Article : "art"
    QString getClassName() const {return (QString)"art";}
    ///Renvoie le texte d'un article
    QString getText() const { return text; }
    ///Permet de changer l'attribut text d'un article en un Qstring passé en argument
    void setText(const QString& t) {text=t;}
    ///Permet d'afficher un article sur la sortie console (pas visible dans l'application)
    void print() const;
    Article* clone() const;
    ///Destructeur
    ~Article();
    ///Fonction permettant de sauvegarder tous les attributs d'un article dans un flux XML
    QXmlStreamWriter& save(QXmlStreamWriter& stream) const;
};

/*
///Class Action
class Action {
    QString text;
public:
    Action(const QString& s) : text(s) {}
    QString getClassName() const {return "Action";}
    QString getText() const {return text;}
    void setText(const QString& newText) {text = newText;}
    void print() const { qDebug() << " - " << text; }
};
*/

///Class Task, hérite de Note. La classe Task a été conçu de façon similaire à la classe Article
class Task : public Note {
private:
    /// Text définissant les actions de la tache
    QString actions;
    /// Définir la priorité de la tache.
    unsigned int priority;
    /// Définit une date de fin de la tâche
    QDate deadline;
    /// en attente, en cours ou terminée
    QString status;
    //Task(const Task& t); On l'enleve pour implementer le factory method

    ///on met le operateur d'affection en prive pour empecher recopie par affectation
    Task& operator=(const Task& t);

public:
    Task(const QString& id, const QString& title, const QString& s, const QDate& d, const unsigned int& p=0);
    Task(const QString& id, const QString& title, const QDate& cr, const QDate& lm, const QString& s, const QDate& d, const unsigned int& p=0);
    //Task(const QString& id, const QString& title, const QString& s, const date& d, const unsigned int& p=0);
    QString getActions() const;
    unsigned int getPriority() const {return priority;}
    QDate getDeadline() const {return deadline;}
    QString getStatus() const {return status;}
    void setAction(const QString& act) {actions = act;}
    void addAction(const QString& s);
    void setPriority(const unsigned int& p) {priority = p;}
    void setDeadline(const QDate& d) {deadline = d;}
    void setStatus(const QString& s) {status = s;}
    void print() const;
    Task* clone() const;
    ~Task();
    QString getClassName() const {return (QString)"task";}
    QXmlStreamWriter& save(QXmlStreamWriter& stream) const;
};




///Classe Multimedia (classe abstraite)
class Multimedia : public Note {
protected:
    QString description;
    QString imageFilename; //Pour l'instant je mets juste un nom de fichier
    Multimedia& operator=(const Multimedia& m);
    //Multimedia(const Multimedia& m);

public:
    Multimedia(const QString& id, const QString& title, const QString& desc, const QString& imgF);
    Multimedia(const QString& id, const QString& title, const QDate& cr, const QDate& lm, const QString& desc, const QString& imgF);
    QString getDescription() const {return description;}
    QString getImageFilename() const {return imageFilename;}
    void setDescription(const QString& desc) {description = desc;}
    void setImageFilename(const QString& imgF) {imageFilename = imgF;}
    ///Méthode virtuelle pure d'affichage d'un multimédia sur la sortie console
    void print() const = 0;
    Multimedia* clone() const = 0;
    ///Fonction virtuelle pure permettant de sauvegarder les attributs d'une video dans un flux XML
    virtual QXmlStreamWriter& save(QXmlStreamWriter& stream) const = 0;
    ///Destructeur virtuel
    virtual ~Multimedia();
    virtual QString getClassName() const = 0;
};

///Classe Image
class Image : public Multimedia {
public:
    ///Renvoie le nom de la classe Image : "img"
    QString getClassName() const {return (QString)"img";}
    ///Constructeur
    Image(const QString& id, const QString& title, const QString& desc, const QString& imgF) : Multimedia(id,title,desc,imgF){}
    ///Surcharge du constructeur
    Image(const QString& id, const QString& title, const QDate& cr, const QDate& lm, const QString& desc, const QString& imgF) : Multimedia(id,title,cr,lm,desc,imgF){}
    void print() const;
    Image* clone() const;
    ///Fonction permettant de sauvegarder les attributs d'une image dans un flux XML
    QXmlStreamWriter& save(QXmlStreamWriter& stream) const;
    ~Image();

};

///Classe Audio
class Audio : public Multimedia {
public:
    QString getClassName() const {return (QString)"aud";}
    Audio(const QString& id, const QString& title, const QString& desc, const QString& imgF) : Multimedia(id,title,desc,imgF){}
    Audio(const QString& id, const QString& title, const QDate& cr, const QDate& lm, const QString& desc, const QString& imgF) : Multimedia(id,title,cr,lm,desc,imgF){}
    void print() const;
    Audio* clone() const;
    ///Fonction permettant de sauvegarder les attributs d'une video dans un flux XML
    QXmlStreamWriter& save(QXmlStreamWriter& stream) const;
    ~Audio();
};

///Classe Video
class Video : public Multimedia {
public:
    ///Renvoie le nom de la classe Video : "vid"
    QString getClassName() const {return (QString)"vid";}
    ///Constructeur
    Video(const QString& id, const QString& title, const QString& desc, const QString& imgF) : Multimedia(id,title,desc,imgF){}
    ///Surcharge du constructeur
    Video(const QString& id, const QString& title, const QDate& cr, const QDate& lm, const QString& desc, const QString& imgF) : Multimedia(id,title,cr,lm,desc,imgF){}
    ///Fonction permettant d'afficher une vidéo sur la sortie console
    void print() const;
    Video* clone() const;
    ///Fonction permettant de sauvegarder les attributs d'une video dans un flux XML
    QXmlStreamWriter& save(QXmlStreamWriter& stream) const;
    ~Video();
};


///Surchage de l'operateur <<
ostream& operator<<(ostream& f, const Note& n);

///Surchage de l'operateur ==
bool operator==(const Note& n1, const Note& n2);


#endif // FONCTION_H_INCLUDED
