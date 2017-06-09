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
void NotesManager::addNote(Note* n){
    notes.push_back(n);
}

///Constructeur de la classe NotesManager
NotesManager::NotesManager() : notes(0),nbNotes(0),nbMaxNotes(0),filename("tmp.dat"){}

NotesManager::~NotesManager(){
    for(unsigned int i=0; i<nbNotes; i++) delete notes[i];
    notes.clear();
}

NoteEditeur* NotesManager::callEditeur(Note* n, QString type){
    EditeurFactory* ef = EditeurFactory::chooseEditeur(type);
    NoteEditeur* ne = ef->createEditeur(n);
    return ne;
}

Note* NotesManager::getNewNote(QString& title,QString& type){
    NoteFactory* nf = NoteFactory::chooseFactory(type);
    Note* n = nf->createNewNote(title);
    this->addNote(n);
    return n;
}

Note& NotesManager::getNote(QString id){
    for (unsigned int i=0; i<notes.size(); i++){
        if (id == notes[i]->getId()) return *notes[i];
    }
    throw NotesException ("Note non trouvee..");
}

Note* NotesManager::getNoteWithTitle(QString title){
    for(unsigned int i=0; i<notes.size(); i++){
        if(notes[i]->getTitle()== title){ return notes[i];}
    }
    throw NotesException("La note n'a pas ete trouvee..");
}

Note* NotesManager::getNoteWithId(QString id){
    for(unsigned int i=0; i<notes.size(); i++){
        if(notes[i]->getId()== id){ return notes[i];}
    }
    throw NotesException("La note n'a pas ete trouvee..");
}



NotesManager::Handler NotesManager::handler=Handler();

NotesManager& NotesManager::getInstance() {
  /// Si le pointeur vers l'instance unique pointe vers 0
  if(!handler.instance) {
    handler.instance=new NotesManager;
  }
  /// Retour par ref vers l'instance unique
  return *handler.instance;
}

void NotesManager::libererInstance() {
  /// Liberation de la memoire allouee a l'instance unique
  delete handler.instance;
  /// Repasse le pointeur a null/nullptr/0 pour que le prochain appel a getInstance recree bien une instance
  handler.instance=0;
}





void NotesManager::showAll() const {
    for (vector<Note*>::const_iterator it = notes.begin() ; it != notes.end(); ++it){
        (*it)->print();
    }
}

void NotesManager::deleteNote(QString id){
    int size_init = notes.size();
    for (unsigned int i=0; i<notes.size(); i++){
        if (notes[i]->getId() == id) {notes.erase(notes.begin()+i);}
    }
    if (size_init == notes.size()) { ///cela signifie que l'on a rien supprime dans le tableau
        throw NotesException("L'element a supprimer n'a pas ete trouve..\n");
    }
}


void NotesManager::showOldNotes(QString id){
    bool found = false;
    for (vector<Note*>::iterator it = notes.begin() ; it != notes.end(); ++it){
                if ((*it)->getId() == id){
                        found = true;
                        (*it)->printOldVersion();
                }
    }
    if (found == false){throw NotesException("Note non trouvee.. \n");}
}

void NotesManager::restaurerNote(QString id, QString title){
    bool found = false;
    OldVersions va;
    Note* tmp(0);
    for (vector<Note*>::iterator it = notes.begin() ; it != notes.end(); ++it){
                if ((*it)->getId() == id){
                        found = true;
                        va = (*it)->getVersionsAnt();
                        tmp = va.findVersion(title);
                        if (tmp != 0){
                            *it = tmp->clone();
                            (*it)->setVersionsAnt(va);
                        }
                }
    }
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

QXmlStreamReader& NotesManager::loadAudio(QXmlStreamReader& xml){
    QString identificateur;
    QString temp;
    QDate creation;
    QDate lastmodif;
    QString title;
    QString description;
    QString file;

    QXmlStreamAttributes attributes = xml.attributes();
    ///qDebug()<<"fin attributes et debut readnext\n";
    xml.readNext();
    ///We're going to loop over the things because the order might change.
    ///We'll continue the loop until we hit an EndElement named article.

    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "audio")) {

        if(xml.tokenType() == QXmlStreamReader::StartElement) {

            /// On a trouvé le champ identificateur.
            if(xml.name() == "id") {
                xml.readNext(); identificateur=xml.text().toString();
                qDebug()<<"id="<<identificateur<<"\n";
            }

            /// On a trouvé le champ Title.
            if(xml.name() == "title") {
                xml.readNext(); title=xml.text().toString();
                qDebug()<<"description="<<title<<"\n";
            }

            /// On a trouvé le champ Creation.
            if(xml.name() == "creation") {
                xml.readNext();     temp = xml.text().toString();
                creation = QDate::fromString(temp,"dd-MM-yyyy");
                qDebug()<<"creation="<<creation<<"\n";
            }

            /// On a trouvé le champ lastmodif.
            if(xml.name() == "lastmodif") {
                xml.readNext();     temp = xml.text().toString();
                lastmodif = QDate::fromString(temp,"dd-MM-yyyy");
                qDebug()<<"Lastmodif="<<lastmodif<<"\n";
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
                qDebug()<<"file="<<file<<"\n";
            }
        }
        /// ...and next...
       xml.readNext();
    }
    qDebug()<<"ajout note "<<identificateur<<"\n";
    Image* newNote = new Image(identificateur,title,creation,lastmodif,description,file);
    addNote(newNote);
    return xml;
}

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
                qDebug()<<"id="<<identificateur<<"\n";
            }

            /// On a trouvé le champ Title.
            if(xml.name() == "title") {
                xml.readNext(); title=xml.text().toString();
                qDebug()<<"description="<<title<<"\n";
            }

            /// On a trouvé le champ Creation.
            if(xml.name() == "creation") {
                xml.readNext();     temp = xml.text().toString();
                creation = QDate::fromString(temp,"dd-MM-yyyy");
                qDebug()<<"creation="<<creation<<"\n";
            }

            /// On a trouvé le champ lastmodif.
            if(xml.name() == "lastmodif") {
                xml.readNext();     temp = xml.text().toString();
                lastmodif = QDate::fromString(temp,"dd-MM-yyyy");
                qDebug()<<"Lastmodif="<<lastmodif<<"\n";
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
                qDebug()<<"file="<<file<<"\n";
            }
        }
        /// ...and next...
       xml.readNext();
    }
    qDebug()<<"ajout note "<<identificateur<<"\n";
    Audio* newNote = new Audio(identificateur,title,creation,lastmodif,description,file);
    addNote(newNote);
    return xml;
}

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
        ///qDebug()<<"dans loop\n";
        if(xml.tokenType() == QXmlStreamReader::StartElement) {

            /// On a trouvé le champ identificateur.
            if(xml.name() == "id") {
                xml.readNext(); identificateur=xml.text().toString();
                qDebug()<<"id="<<identificateur<<"\n";
            }

            /// On a trouvé le champ Title.
            if(xml.name() == "title") {
                xml.readNext(); title=xml.text().toString();
                qDebug()<<"description="<<title<<"\n";
            }

            /// On a trouvé le champ Creation.
            if(xml.name() == "creation") {
                xml.readNext();     temp = xml.text().toString();
                creation = QDate::fromString(temp,"dd-MM-yyyy");
                qDebug()<<"creation="<<creation<<"\n";
            }

            /// On a trouvé le champ lastmodif.
            if(xml.name() == "lastmodif") {
                xml.readNext();     temp = xml.text().toString();
                ///On transforme le champ en une date au format "dd-MM-yyyy"
                lastmodif = QDate::fromString(temp,"dd-MM-yyyy");
                qDebug()<<"Lastmodif="<<lastmodif<<"\n";
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
                qDebug()<<"file="<<file<<"\n";
            }
        }
        /// On lit la suite du flux xml
       xml.readNext();
    }
    qDebug()<<"ajout note "<<identificateur<<"\n";
    ///Creation d'une nouvelle video
    Video* newNote = new Video(identificateur,title,creation,lastmodif,description,file);
    ///Ajout de la note fraîchement créée
    addNote(newNote);
    return xml;
}


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
                qDebug()<<"id="<<identificateur<<"\n";
            }

            /// On a trouvé le champ Title.
            if(xml.name() == "title") {
                xml.readNext(); title=xml.text().toString();
                qDebug()<<"description="<<title<<"\n";
            }

            /// On a trouvé le champ Creation.
            if(xml.name() == "creation") {
                xml.readNext();     temp = xml.text().toString();
                creation = QDate::fromString(temp,"dd-MM-yyyy");
                qDebug()<<"creation="<<creation<<"\n";
            }

            /// On a trouvé le champ actions.
            if(xml.name() == "actions") {
                xml.readNext(); actions=xml.text().toString();
                qDebug()<<"actions="<<actions<<"\n";
            }

            /// On a trouvé le champ deadline.
            if(xml.name() == "deadline") {
                xml.readNext();     temp = xml.text().toString();
                deadline = QDate::fromString(temp,"dd-MM-yyyy");
                qDebug()<<"Deadline="<<deadline<<"\n";
            }

            /// On a trouvé le champ lastmodif.
            if(xml.name() == "lastmodif") {
                xml.readNext();     temp = xml.text().toString();
                lastmodif = QDate::fromString(temp,"dd-MM-yyyy");
                qDebug()<<"Lastmodif="<<lastmodif<<"\n";
            }

            /// On a trouvé le champ status
            if(xml.name() == "status") {
                xml.readNext();
                status=xml.text().toString();
                qDebug()<<"Status="<<status<<"\n";
            }

            /// On a trouvé le champ priority.
            if(xml.name() == "prio") {
                xml.readNext(); priority=xml.text().toString().toInt();
                qDebug()<<"Priorite="<<priority<<"\n";
            }

        }
        /// ...and next...
       xml.readNext();
    }
    qDebug()<<"ajout note "<<identificateur<<"\n";
    Task* newNote = new Task(identificateur,title,creation,lastmodif,status,QDate(15,06,2017),priority);
    if(actions != "\0") newNote->setAction(actions);
    addNote(newNote);
    return xml;
}




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
                qDebug()<<"id="<<identificateur<<"\n";
            }

            /// On a trouvé le champ titre.
            if(xml.name() == "title") {
                xml.readNext(); titre=xml.text().toString();
                qDebug()<<"titre="<<titre<<"\n";
            }

            /// On a trouvé le champ Creation.
            if(xml.name() == "creation") {
                xml.readNext();     temp = xml.text().toString();
                creation = QDate::fromString(temp,"dd-MM-yyyy");
                qDebug()<<"creation="<<creation<<"\n";
            }

            /// On a trouvé le champ lastmodif.
            if(xml.name() == "lastmodif") {
                xml.readNext();     temp = xml.text().toString();
                lastmodif = QDate::fromString(temp,"dd-MM-yyyy");
                qDebug()<<"Lastmodif="<<lastmodif<<"\n";
            }

            /// On a trouvé le champ text
            if(xml.name() == "text") {
                xml.readNext();
                text=xml.text().toString();
                qDebug()<<"text="<<text<<"\n";
            }
        }
        /// ...and next...
        xml.readNext();
    }
    qDebug()<<"ajout note "<<identificateur<<"\n";
    Article* newArticle = new Article(identificateur,titre,creation,lastmodif,text);
    addNote(newArticle);
    return xml;
}
