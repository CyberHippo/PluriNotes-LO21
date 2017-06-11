#include <iostream>
#include <fstream>
#include <QFile>
#include <QTextCodec>
#include <QtXml/QtXml>
#include <QMessageBox>

#include "fonction.h"
#include "notemanager.h"
#include "notefactory.h"
#include "noteediteur.h"
#include "editeurfactory.h"

///Methodes de la classe NotesManager

///Méthode qui permet d'ajouter une note au vecteur de notes "notes" de NotesManager
void NotesManager::addNote(Note* n){
    notes.push_back(n);
}

///Constructeur de la classe NotesManager
NotesManager::NotesManager() : notes(0),filename("TEMP.xml"){}

///Destructeur de la classe NotesManager
NotesManager::~NotesManager(){
    ///Pour chaque note contenue dans le vecteur de notes, on supprime cette note
    for(unsigned int i=0; i<notes.size(); i++) delete notes[i];
    ///On libère le vecteur "notes"
    notes.clear();
}

///Fonction qui permet d'appeler un éditeur de note
NoteEditeur* NotesManager::callEditeur(Note* n, QString type){
    ///On choisit quel type d'éditeur appeler en fonction du type passé en argument
    EditeurFactory* ef = EditeurFactory::chooseEditeur(type);
    ///On crée un édtieur du bon type par rapport à la note passée en argument
    NoteEditeur* ne = ef->createEditeur(n);
    ///on renvoie cette éditeur
    return ne;
}

///Fonction qui permet de retourner une nouvelle note
Note* NotesManager::getNewNote(QString& title,QString& type){
    ///On choisit le bon type de factory à appeler en fonction du type passé en argument
    NoteFactory* nf = NoteFactory::chooseFactory(type);
    ///On crée une note du bon type à partir du titre passé en argument
    Note* n = nf->createNewNote(title);
    ///On ajoute cette note au vecteur de notes de NotesManager
    this->addNote(n);
    ///On retourne cette note
    return n;
}

///fonction qui permet de retourner une note à partir d'un id
Note& NotesManager::getNote(QString id){
    ///on itère les notes du vecteur de notes
    for (unsigned int i=0; i<notes.size(); i++){
        ///Si l'id de la note correspond à l'id passé en argument, on renvoie la note
        if (id == notes[i]->getId()) return *notes[i];
    }
    ///sinon on lance une exception
    throw NotesException ("Note non trouvee..");
}

///fonction qui permet de retourner une note à partir d'un titre
Note* NotesManager::getNoteWithTitle(QString title){
    ///on itère les notes du vecteur de notes
    for(unsigned int i=0; i<notes.size(); i++){
        ///Si le titre de la note correspond au titre passé en argument, on renvoie la note
        if(notes[i]->getTitle()== title){ return notes[i];}
    }
    ///sinon on lance une exception
    throw NotesException("La note n'a pas ete trouvee..");
}

///fonction qui permet de retourner une note à partir d'un id
Note* NotesManager::getNoteWithId(QString id){
    ///on itère les notes du vecteur de notes
    for(unsigned int i=0; i<notes.size(); i++){
        ///Si l'id de la note correspond à l'id passé en argument, on renvoie la note
        if(notes[i]->getId()== id){ return notes[i];}
    }
    ///sinon on lance une exception
    throw NotesException("La note n'a pas ete trouvee..");
}

///Handler de NotesManager
NotesManager::Handler NotesManager::handler=Handler();

///Fonction permettant de renvoyer une référence sur l'instance unique de NotesManager
NotesManager& NotesManager::getInstance() {
  /// Si le pointeur vers l'instance unique pointe vers 0
  if(!handler.instance) {
    handler.instance=new NotesManager;
  }
  /// Retour par ref vers l'instance unique
  return *handler.instance;
}

///Fonction qui permet de libérer la mémoire de l'instance unique de NotesManager
void NotesManager::libererInstance() {
  /// Liberation de la memoire allouee a l'instance unique
  delete handler.instance;
  /// Repasse le pointeur a null/nullptr/0 pour que le prochain appel a getInstance recree bien une instance
  handler.instance=0;
}

///fonction qui permet d'afficher toutes les notes du vecteur de notesmanager sur la sortie console
void NotesManager::showAll() const {
    ///On itère les notes du vecteur notes
    for (vector<Note*>::const_iterator it = notes.begin() ; it != notes.end(); ++it){
        ///appel de la méthode print() pour chaque note
        (*it)->print();
    }
}

///Méthode qui permet de supprimer une notes de notesManager à partir d'un id
void NotesManager::deleteNote(QString id){
    ///Initialisation d'un int à la taille du vecteur notes
    int size_init = notes.size();
    ///itérations sur les notes du vecteur
    for (unsigned int i=0; i<notes.size(); i++){
        ///Si l'id de la note correspond à l'id passé en argument, on efface la note grâce à la fonction erase()
        if (notes[i]->getId() == id) {notes.erase(notes.begin()+i);}
    }
    ///Sinon cela signifie que l'on a rien supprime dans le tableau
    if (size_init == notes.size()) {
        ///Et on lance une exception
        throw NotesException("L'element a supprimer n'a pas ete trouve..\n");
    }
}

///Méthode permettant d'afficher toutes les anciennes versions d'une note
void NotesManager::showOldNotes(QString id){
    bool found = false;
    ///On itère sur les notes de notesmanager
    for (vector<Note*>::iterator it = notes.begin() ; it != notes.end(); ++it){
        ///Si l'id de la note correspond à l'id passé en argument, on affiche les anciennes version de cette note
                if ((*it)->getId() == id){
                        found = true;
                        (*it)->printOldVersion();
                }
    }
    ///Sinon, la note n'a pas été trouvée, on lance une exception
    if (found == false){throw NotesException("Note non trouvee.. \n");}
}

///Méthode permettant de restaurer une note
void NotesManager::restaurerNote(QString id, QString title){
    ///Variables temporaires
    bool found = false;
    OldVersions va;
    Note* tmp(0);
    ///on itère les les notes de notesManager
    for (vector<Note*>::iterator it = notes.begin() ; it != notes.end(); ++it){
        ///Si l'id de la note correspond à l'id passé en argument
                if ((*it)->getId() == id){
                        found = true;
                        ///On récupère les anciennes version de la note
                        va = (*it)->getVersionsAnt();
                        ///On récupère l'ancienne version que l'on veut grâce au titre passé en argument et on la stocke dans tmp
                        tmp = va.findVersion(title);
                        ///Si tmp n'est pas vide, on crée un clone de la note
                        if (tmp != 0){
                            *it = tmp->clone();
                            ///et on change la version de la note en l'ancienne version que l'on vient de récupérer
                            (*it)->setVersionsAnt(va);
                        }
                }
    }
    ///Sinon on lance une exception
    if (found == false){throw NotesException("Note non trouvee.. \n");}
}


///Fonction permettant de sauvegarder toutes les notes contenues dans NotesManager dans un fichier XML
void NotesManager::saveAll(){
    ///Nom du fichier XML de sortie
    QString fichier = "TEMP.xml";
    setFilename(fichier);
    ///Ouverture du fichier
    QFile newfile(fichier);
        if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
            throw NotesException(QString("erreur sauvegarde notes : ouverture fichier xml"));
    ///On crée un Stream XML pour écrire dans le fichier
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    ///On commence par un attribut notes
    stream.writeStartElement("notes");
    ///On itère sur les notes de NotesManager et pour chaque note on appelle la fonction save
        for (vector<Note*>::iterator it = notes.begin() ; it != notes.end(); ++it){
                (*it)->save(stream);
        }
    stream.writeEndElement();
    stream.writeEndDocument();
    ///On ferme le fichier XML
    newfile.close();
}


///Fonction qui permet de charger les notes contenues dans un fichier XML dans notesManager
void NotesManager::load() {
    QFile fin(filename);
    /// Si on ne peut pas ouvrir le fichier, on lance une erreur.
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw NotesException("Erreur ouverture fichier notes");
    }
    ///Création d'un flux XML
    QXmlStreamReader xml(&fin);

    /// On va parser le XML jusqu'à la fin.
    while(!xml.atEnd() && !xml.hasError()) {
        /// on lit le prochain élément
        QXmlStreamReader::TokenType token = xml.readNext();
        /// Si le Token est StartDocument, on avance.
        if(token == QXmlStreamReader::StartDocument) continue;
        /// If token is StartElement, we'll see if we can read it.
        if(token == QXmlStreamReader::StartElement) {
            ///Notes est le début du document, on peux continuer
            if(xml.name() == "notes") continue;
            ///Pour chaque type de notes, on appelle une fonction load spécifique
            if(xml.name() == "article") { loadArticle(xml); }
            if(xml.name() == "audio") { loadAudio(xml); }
            if(xml.name() == "image") { loadImage(xml); }
            if(xml.name() == "video") { loadVideo(xml); }
            if(xml.name() == "task") { loadTask(xml); }
        }
    }
    /// Erreur de manipulation
    if(xml.hasError()) {
        throw NotesException("Erreur lecteur fichier notes, parser xml");
    }
    /// Removes any device() or data from the reader * and resets its internal state to the initial state.
    xml.clear();
}

///Fonction spécifique pour charger un audio depuis un fichier XMl
QXmlStreamReader& NotesManager::loadAudio(QXmlStreamReader& xml){
    QString identificateur;
    QString temp;
    QDate creation;
    QDate lastmodif;
    QString title;
    QString description;
    QString file;

    QXmlStreamAttributes attributes = xml.attributes();
    xml.readNext();
    ///We're going to loop over the things because the order might change.
    ///We'll continue the loop until we hit an EndElement named audio.

    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "audio")) {

        if(xml.tokenType() == QXmlStreamReader::StartElement) {

            /// On a trouvé le champ identificateur.
            if(xml.name() == "id") {
                xml.readNext(); identificateur=xml.text().toString();
                //qDebug()<<"id="<<identificateur<<"\n";
            }

            /// On a trouvé le champ Title.
            if(xml.name() == "title") {
                xml.readNext(); title=xml.text().toString();
                //qDebug()<<"description="<<title<<"\n";
            }

            /// On a trouvé le champ Creation.
            if(xml.name() == "creation") {
                xml.readNext();     temp = xml.text().toString();
                ///Conversion d'une Qstring en QDate depuis le format dd-MM-yyyy
                creation = QDate::fromString(temp,"dd-MM-yyyy");
                //qDebug()<<"creation="<<creation<<"\n";
            }

            /// On a trouvé le champ lastmodif.
            if(xml.name() == "lastmodif") {
                xml.readNext();     temp = xml.text().toString();
                ///Conversion d'une Qstring en QDate depuis le format dd-MM-yyyy
                lastmodif = QDate::fromString(temp,"dd-MM-yyyy");
                //qDebug()<<"Lastmodif="<<lastmodif<<"\n";
            }

            /// On a trouvé le champ description.
            if(xml.name() == "desc") {
                xml.readNext(); description=xml.text().toString();
                //qDebug()<<"description="<<description<<"\n";
            }
            /// On a trouvé le champ file
            if(xml.name() == "file") {
                xml.readNext();
                file=xml.text().toString();
                //qDebug()<<"file="<<file<<"\n";
            }
        }
        /// ...and next...
       xml.readNext();
    }

    ///Création du nouvel audio avec le constructeur surchargé et ajout dans le vecteur de notesManager
    Audio* newNote = new Audio(identificateur,title,creation,lastmodif,description,file);
    addNote(newNote);
    return xml;
}

///Fonction spécifique pour charger une image depuis un fichier XMl
QXmlStreamReader& NotesManager::loadImage(QXmlStreamReader& xml){

    QString identificateur;
    QString title;
    QString temp;
    QDate creation;
    QDate lastmodif;
    QString description;
    QString file;

    QXmlStreamAttributes attributes = xml.attributes();

    xml.readNext();
    ///We're going to loop over the things because the order might change.
    ///We'll continue the loop until we hit an EndElement named article.

    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "image")) {

        if(xml.tokenType() == QXmlStreamReader::StartElement) {

            /// On a trouvé le champ identificateur.
            if(xml.name() == "id") {
                xml.readNext(); identificateur=xml.text().toString();
                //qDebug()<<"id="<<identificateur<<"\n";
            }

            /// On a trouvé le champ Title.
            if(xml.name() == "title") {
                xml.readNext(); title=xml.text().toString();
                //qDebug()<<"description="<<title<<"\n";
            }

            /// On a trouvé le champ Creation.
            if(xml.name() == "creation") {
                xml.readNext();     temp = xml.text().toString();
                ///Conversion d'une Qstring en QDate depuis le format dd-MM-yyyy
                creation = QDate::fromString(temp,"dd-MM-yyyy");
                //qDebug()<<"creation="<<creation<<"\n";
            }

            /// On a trouvé le champ lastmodif.
            if(xml.name() == "lastmodif") {
                xml.readNext();     temp = xml.text().toString();
                ///Conversion d'une Qstring en QDate depuis le format dd-MM-yyyy
                lastmodif = QDate::fromString(temp,"dd-MM-yyyy");
                //qDebug()<<"Lastmodif="<<lastmodif<<"\n";
            }

            /// On a trouvé le champ description.
            if(xml.name() == "desc") {
                xml.readNext(); description=xml.text().toString();
                //qDebug()<<"description="<<description<<"\n";
            }
            /// On a trouvé le champ file
            if(xml.name() == "file") {
                xml.readNext();
                file=xml.text().toString();
                //qDebug()<<"file="<<file<<"\n";
            }
        }
        /// ...and next...
       xml.readNext();
    }

    ///Création de la nouvelle image avec le constructeur surchargé et ajout dans le vecteur de notesManager
    Image* newNote = new Image(identificateur,title,creation,lastmodif,description,file);
    addNote(newNote);
    return xml;
}


///Fonction spécifique pour charger une video depuis un fichier XMl
QXmlStreamReader& NotesManager::loadVideo(QXmlStreamReader& xml){

    QString identificateur;
    QString title;
    QString temp;
    QDate creation;
    QDate lastmodif;
    QString description;
    QString file;

    QXmlStreamAttributes attributes = xml.attributes();

    xml.readNext();
    ///We're going to loop over the things because the order might change.
    ///We'll continue the loop until we hit an EndElement named article.

    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "video")) {

        if(xml.tokenType() == QXmlStreamReader::StartElement) {

            /// On a trouvé le champ identificateur.
            if(xml.name() == "id") {
                xml.readNext(); identificateur=xml.text().toString();
                //qDebug()<<"id="<<identificateur<<"\n";
            }

            /// On a trouvé le champ Title.
            if(xml.name() == "title") {
                xml.readNext(); title=xml.text().toString();
                //qDebug()<<"description="<<title<<"\n";
            }

            /// On a trouvé le champ Creation.
            if(xml.name() == "creation") {
                xml.readNext();     temp = xml.text().toString();
                ///Conversion d'une Qstring en QDate depuis le format dd-MM-yyyy
                creation = QDate::fromString(temp,"dd-MM-yyyy");
                //qDebug()<<"creation="<<creation<<"\n";
            }

            /// On a trouvé le champ lastmodif.
            if(xml.name() == "lastmodif") {
                xml.readNext();     temp = xml.text().toString();
                ///On transforme le champ en une date au format "dd-MM-yyyy"
                lastmodif = QDate::fromString(temp,"dd-MM-yyyy");
                //qDebug()<<"Lastmodif="<<lastmodif<<"\n";
            }

            /// On a trouvé le champ description.
            if(xml.name() == "desc") {
                xml.readNext(); description=xml.text().toString();
                qDebug()<<"description="<<description<<"\n";
            }
            /// On a trouvé le champ file
            if(xml.name() == "file") {
                xml.readNext();
                file=xml.text().toString();
                //qDebug()<<"file="<<file<<"\n";
            }
        }
        /// On lit la suite du flux xml
       xml.readNext();
    }

    ///Création de la nouvelle video avec le constructeur surchargé et ajout dans le vecteur de notesManager
    Video* newNote = new Video(identificateur,title,creation,lastmodif,description,file);
    addNote(newNote);
    return xml;
}


///Fonction spécifique pour charger une tache depuis un fichier XMl
QXmlStreamReader& NotesManager::loadTask(QXmlStreamReader& xml){

    QString identificateur;
    QString title;
    QString temp;
    QDate creation;
    QDate lastmodif;
    int priority;
    QString status;
    QDate deadline;
    QString actions= "\0";
    QXmlStreamAttributes attributes = xml.attributes();
    xml.readNext();
    //// On va looper sur le flux parce que l'ordre des champs peut changer
    //// On continue tant qu'on atteint pas un champ EndElement
    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "task")) {

        if(xml.tokenType() == QXmlStreamReader::StartElement) {

            /// On a trouvé le champ identificateur.
            if(xml.name() == "id") {
                xml.readNext(); identificateur=xml.text().toString();
                //qDebug()<<"id="<<identificateur<<"\n";
            }

            /// On a trouvé le champ Title.
            if(xml.name() == "title") {
                xml.readNext(); title=xml.text().toString();
                //qDebug()<<"description="<<title<<"\n";
            }

            /// On a trouvé le champ Creation.
            if(xml.name() == "creation") {
                xml.readNext();     temp = xml.text().toString();
                ///Conversion d'une Qstring en QDate depuis le format dd-MM-yyyy
                creation = QDate::fromString(temp,"dd-MM-yyyy");
                //qDebug()<<"creation="<<creation<<"\n";
            }

            /// On a trouvé le champ actions.
            if(xml.name() == "actions") {
                xml.readNext(); actions=xml.text().toString();
                //qDebug()<<"actions="<<actions<<"\n";
            }

            /// On a trouvé le champ deadline.
            if(xml.name() == "deadline") {
                xml.readNext();     temp = xml.text().toString();
                ///Conversion d'une Qstring en QDate depuis le format dd-MM-yyyy
                deadline = QDate::fromString(temp,"dd-MM-yyyy");
                //qDebug()<<"Deadline="<<deadline<<"\n";
            }

            /// On a trouvé le champ lastmodif.
            if(xml.name() == "lastmodif") {
                xml.readNext();     temp = xml.text().toString();
                ///Conversion d'une Qstring en QDate depuis le format dd-MM-yyyy
                lastmodif = QDate::fromString(temp,"dd-MM-yyyy");
                //qDebug()<<"Lastmodif="<<lastmodif<<"\n";
            }

            /// On a trouvé le champ status
            if(xml.name() == "status") {
                xml.readNext();
                status=xml.text().toString();
                //qDebug()<<"Status="<<status<<"\n";
            }

            /// On a trouvé le champ priority.
            if(xml.name() == "prio") {
                ///conversion d'un Qstring en int
                xml.readNext(); priority=xml.text().toString().toInt();
                //qDebug()<<"Priorite="<<priority<<"\n";
            }

        }
        /// ...and next...
       xml.readNext();
    }

    ///Création de la nouvelle tache avec le constructeur surchargé et ajout dans le vecteur de notesManager
    Task* newNote = new Task(identificateur,title,creation,lastmodif,status,QDate(15,06,2017),priority);
    if(actions != "\0") newNote->setAction(actions);
    addNote(newNote);
    return xml;
}

///Fonction spécifique pour charger un article depuis un fichier XMl
QXmlStreamReader& NotesManager::loadArticle(QXmlStreamReader& xml){

    QString identificateur;
    QString titre;
    QString temp;
    QDate creation;
    QDate lastmodif;
    QString text;

    QXmlStreamAttributes attributes = xml.attributes();
    xml.readNext();

    ///We're going to loop over the things because the order might change.
    ///We'll continue the loop until we hit an EndElement named article.
    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "article")) {
        if(xml.tokenType() == QXmlStreamReader::StartElement) {

            /// On a trouvé le champ identificateur.
            if(xml.name() == "id") {
                xml.readNext(); identificateur=xml.text().toString();
                //qDebug()<<"id="<<identificateur<<"\n";
            }

            /// On a trouvé le champ titre.
            if(xml.name() == "title") {
                xml.readNext(); titre=xml.text().toString();
                //qDebug()<<"titre="<<titre<<"\n";
            }

            /// On a trouvé le champ Creation.
            if(xml.name() == "creation") {
                xml.readNext();     temp = xml.text().toString();
                ///Conversion d'une Qstring en QDate depuis le format dd-MM-yyyy
                creation = QDate::fromString(temp,"dd-MM-yyyy");
                //qDebug()<<"creation="<<creation<<"\n";
            }

            /// On a trouvé le champ lastmodif.
            if(xml.name() == "lastmodif") {
                xml.readNext();     temp = xml.text().toString();
                ///Conversion d'une Qstring en QDate depuis le format dd-MM-yyyy
                lastmodif = QDate::fromString(temp,"dd-MM-yyyy");
                //qDebug()<<"Lastmodif="<<lastmodif<<"\n";
            }

            /// On a trouvé le champ text
            if(xml.name() == "text") {
                xml.readNext();
                text=xml.text().toString();
                //qDebug()<<"text="<<text<<"\n";
            }
        }
        /// ...and next...
        xml.readNext();
    }

    ///Création du nouvel article avec le constructeur surchargé et ajout dans le vecteur de notesManager
    Article* newArticle = new Article(identificateur,titre,creation,lastmodif,text);
    addNote(newArticle);
    return xml;
}
