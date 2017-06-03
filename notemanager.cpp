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

NotesManager::NotesManager() : notes(0),nbNotes(0),nbMaxNotes(0),filename("tmp.dat"){}

NotesManager::~NotesManager(){
    //save();
    for(unsigned int i=0; i<nbNotes; i++) delete notes[i];
    notes.clear();
}

NoteEditeur* NotesManager::callEditeur(Note* n, QString type){
    EditeurFactory* ef = EditeurFactory::chooseEditeur(type);
    NoteEditeur* ne = ef->createEditeur(n);
    return ne;
    //ne->show();
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



NotesManager::Handler NotesManager::handler=Handler();

NotesManager& NotesManager::getInstance() {
  // Si le pointeur vers l'instance unique pointe vers 0
  if(!handler.instance) {
    handler.instance=new NotesManager;
  }
  // Retour par ref vers l'instance unique
  return *handler.instance;
}

void NotesManager::libererInstance() {
  // Liberation de la memoire allouee a l'instance unique
  delete handler.instance;
  // Repasse le pointeur a null/nullptr/0 pour que le prochain appel a getInstance recree bien une instance
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
    if (size_init == notes.size()) { //cela signifie que l'on a rien supprime dans le tableau
        throw NotesException("L'element a supprimer n'a pas ete trouve..\n");
    }
}
/*void NotesManager::editNote(QString id){
    QString t;
    cout << "Quel nouveau titre pour cette note?\n";
    cin >> t;
    cin.ignore();
    for (vector<Note*>::iterator it = notes.begin() ; it != notes.end(); ++it){
                if ((*it)->getId() == id){
                        (*it)->addOldVersion();
                        (*it)->setTitle(t);
                }
    }
}*/

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

/*
void NotesManager::saveNote(Note& n){
    n.save();
}*/


void NotesManager::saveAll(){

    QString fichier = "TEMP.xml";
    setFilename(fichier);

    QFile newfile(fichier);
        if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
            throw NotesException(QString("erreur sauvegarde notes : ouverture fichier xml"));
    qDebug("test");
    //newfile.open(QIODevice::WriteOnly | QIODevice::Text);
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("notes");
        for (vector<Note*>::iterator it = notes.begin() ; it != notes.end(); ++it){
                (*it)->save(stream);
        }
    stream.writeEndElement();
    stream.writeEndDocument();
    newfile.close();
}


void NotesManager::load() {
    QFile fin(filename);
    // If we can't open it, let's show an error message.
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw NotesException("Erreur ouverture fichier notes");
    }
    // QXmlStreamReader takes any QIODevice.
    QXmlStreamReader xml(&fin);
    qDebug()<<"debut fichier\n";
    // We'll parse the XML until we reach end of it.
    while(!xml.atEnd() && !xml.hasError()) {
        // Read next element.
        QXmlStreamReader::TokenType token = xml.readNext();
        // If token is just StartDocument, we'll go to next.
        if(token == QXmlStreamReader::StartDocument) continue;
        // If token is StartElement, we'll see if we can read it.
        if(token == QXmlStreamReader::StartElement) {
            // If it's named notes, we'll go to the next.
            if(xml.name() == "notes") continue;
            // If it's named article, we'll dig the information from there.
            if(xml.name() == "article") { loadArticle(xml); }
            if(xml.name() == "audio") { loadAudio(xml); }
            if(xml.name() == "image") { loadImage(xml); }
            if(xml.name() == "video") { loadVideo(xml); }
            if(xml.name() == "task") { loadTask(xml); }
        }
    }
    // Error handling.
    if(xml.hasError()) {
        throw NotesException("Erreur lecteur fichier notes, parser xml");
    }
    // Removes any device() or data from the reader * and resets its internal state to the initial state.
    xml.clear();
    qDebug()<<"fin load\n";
}

QXmlStreamReader& NotesManager::loadAudio(QXmlStreamReader& xml){
    //qDebug()<<"new audio\n";
    QString identificateur;
    QString title;
    QString description;
    QString file;
    //qDebug()<<"debut attributes\n";
    QXmlStreamAttributes attributes = xml.attributes();
    //qDebug()<<"fin attributes et debut readnext\n";
    xml.readNext();
    //We're going to loop over the things because the order might change.
    //We'll continue the loop until we hit an EndElement named article.
    //qDebug()<<"debut loop\n";
    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "audio")) {
        //qDebug()<<"dans loop\n";
        if(xml.tokenType() == QXmlStreamReader::StartElement) {
            //qDebug()<<"start element\n";
            // We've found identificateur.
            if(xml.name() == "id") {
                xml.readNext(); identificateur=xml.text().toString();
                qDebug()<<"id="<<identificateur<<"\n";
            }

            // We've found Title.
            if(xml.name() == "title") {
                xml.readNext(); title=xml.text().toString();
                qDebug()<<"description="<<title<<"\n";
            }

            // We've found description.
            if(xml.name() == "desc") {
                xml.readNext(); description=xml.text().toString();
                qDebug()<<"description="<<description<<"\n";
            }
            // We've found file
            if(xml.name() == "file") {
                xml.readNext();
                file=xml.text().toString();
                qDebug()<<"file="<<file<<"\n";
            }
        }
        // ...and next...
       xml.readNext();
    }
    qDebug()<<"ajout note "<<identificateur<<"\n";
    Image* newNote = new Image(identificateur,title,description,file);
    addNote(newNote);
    return xml;
}

QXmlStreamReader& NotesManager::loadImage(QXmlStreamReader& xml){
    //qDebug()<<"new image\n";
    QString identificateur;
    QString title;
    QString description;
    QString file;
    //qDebug()<<"debut attributes\n";
    QXmlStreamAttributes attributes = xml.attributes();
    //qDebug()<<"fin attributes et debut readnext\n";
    xml.readNext();
    //We're going to loop over the things because the order might change.
    //We'll continue the loop until we hit an EndElement named article.
    //qDebug()<<"debut loop\n";
    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "image")) {
        //qDebug()<<"dans loop\n";
        if(xml.tokenType() == QXmlStreamReader::StartElement) {
            //qDebug()<<"start element\n";
            // We've found identificateur.
            if(xml.name() == "id") {
                xml.readNext(); identificateur=xml.text().toString();
                qDebug()<<"id="<<identificateur<<"\n";
            }

            // We've found Title.
            if(xml.name() == "title") {
                xml.readNext(); title=xml.text().toString();
                qDebug()<<"description="<<title<<"\n";
            }

            // We've found description.
            if(xml.name() == "desc") {
                xml.readNext(); description=xml.text().toString();
                qDebug()<<"description="<<description<<"\n";
            }
            // We've found file
            if(xml.name() == "file") {
                xml.readNext();
                file=xml.text().toString();
                qDebug()<<"file="<<file<<"\n";
            }
        }
        // ...and next...
       xml.readNext();
    }
    qDebug()<<"ajout note "<<identificateur<<"\n";
    Audio* newNote = new Audio(identificateur,title,description,file);
    addNote(newNote);
    return xml;
}

QXmlStreamReader& NotesManager::loadVideo(QXmlStreamReader& xml){
    //qDebug()<<"new video\n";
    QString identificateur;
    QString title;
    QString description;
    QString file;
    //qDebug()<<"debut attributes\n";
    QXmlStreamAttributes attributes = xml.attributes();
    //qDebug()<<"fin attributes et debut readnext\n";
    xml.readNext();
    //We're going to loop over the things because the order might change.
    //We'll continue the loop until we hit an EndElement named article.
    //qDebug()<<"debut loop\n";
    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "video")) {
        //qDebug()<<"dans loop\n";
        if(xml.tokenType() == QXmlStreamReader::StartElement) {
            //qDebug()<<"start element\n";
            // We've found identificateur.
            if(xml.name() == "id") {
                xml.readNext(); identificateur=xml.text().toString();
                qDebug()<<"id="<<identificateur<<"\n";
            }

            // We've found Title.
            if(xml.name() == "title") {
                xml.readNext(); title=xml.text().toString();
                qDebug()<<"description="<<title<<"\n";
            }

            // We've found description.
            if(xml.name() == "desc") {
                xml.readNext(); description=xml.text().toString();
                qDebug()<<"description="<<description<<"\n";
            }
            // We've found file
            if(xml.name() == "file") {
                xml.readNext();
                file=xml.text().toString();
                qDebug()<<"file="<<file<<"\n";
            }
        }
        // ...and next...
       xml.readNext();
    }
    qDebug()<<"ajout note "<<identificateur<<"\n";
    Video* newNote = new Video(identificateur,title,description,file);
    addNote(newNote);
    return xml;
}


QXmlStreamReader& NotesManager::loadTask(QXmlStreamReader& xml){
    qDebug()<<"new Task\n";
    QString identificateur;
    QString title;
    int priority;
    QString status;
    QXmlStreamAttributes attributes = xml.attributes();
    xml.readNext();
    //We're going to loop over the things because the order might change.
    //We'll continue the loop until we hit an EndElement named article.
    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "task")) {
        //qDebug()<<"dans loop\n";
        if(xml.tokenType() == QXmlStreamReader::StartElement) {

            // We've found identificateur.
            if(xml.name() == "id") {
                xml.readNext(); identificateur=xml.text().toString();
                qDebug()<<"id="<<identificateur<<"\n";
            }

            // We've found Title.
            if(xml.name() == "title") {
                xml.readNext(); title=xml.text().toString();
                qDebug()<<"description="<<title<<"\n";
            }

            // We've found status
            if(xml.name() == "status") {
                xml.readNext();
                status=xml.text().toString();
                qDebug()<<"Status="<<status<<"\n";
            }

            // We've found priority.
            if(xml.name() == "prio") {
                xml.readNext(); priority=xml.text().toString().toInt();
                qDebug()<<"Priorite="<<priority<<"\n";
            }

        }
        // ...and next...
       xml.readNext();
    }
    qDebug()<<"ajout note "<<identificateur<<"\n";
    Task* newNote = new Task(identificateur,title,status,QDate(5,10,2017),priority);
    addNote(newNote);
    return xml;
} // il manque la date




QXmlStreamReader& NotesManager::loadArticle(QXmlStreamReader& xml){
    qDebug()<<"new article\n";
    QString identificateur;
    QString titre;
    QString text;
    QXmlStreamAttributes attributes = xml.attributes();
    xml.readNext();
    //We're going to loop over the things because the order might change.
    //We'll continue the loop until we hit an EndElement named article.
    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "article")) {
        if(xml.tokenType() == QXmlStreamReader::StartElement) {
            // We've found identificateur.
            if(xml.name() == "id") {
                xml.readNext(); identificateur=xml.text().toString();
                qDebug()<<"id="<<identificateur<<"\n";
            }

            // We've found titre.
            if(xml.name() == "title") {
                xml.readNext(); titre=xml.text().toString();
                qDebug()<<"titre="<<titre<<"\n";
            }
            // We've found text
            if(xml.name() == "text") {
                xml.readNext();
                text=xml.text().toString();
                qDebug()<<"text="<<text<<"\n";
            }
        }
        // ...and next...
        xml.readNext();
    }
    qDebug()<<"ajout note "<<identificateur<<"\n";
    Article* newArticle = new Article(identificateur,titre,text);
    addNote(newArticle);
    return xml;
}
