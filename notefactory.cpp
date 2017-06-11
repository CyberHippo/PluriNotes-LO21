#include "fonction.h"
#include "notemanager.h"
#include "relation.h"
#include "notefactory.h"
#include "time.h"
#include "stdio.h"
#include "stdlib.h"

///Fonction qui permet de générer un nouvel id aléatoirement
unsigned int NoteFactory::getNewId() {
    ///Generates random id different than other notes
    return rand()%10000;
}

///Fonction permettant de choisir quel créateur de note on veut appeler en fonction d'un QString passé en argument
NoteFactory* NoteFactory::chooseFactory(QString& type){
    ///Si le Qstring passé en argument est "art", on crée un nouvel ArticleFactory et on le retourne
    if(type==(QString) "art") {ArticleFactory* fact = new ArticleFactory; return fact;}
    ///Si le Qstring passé en argument est "task", on crée un nouvel TaskFactory et on le retourne
    else if(type==(QString) "task") {TaskFactory* fact = new TaskFactory; return fact;}
    ///Si le Qstring passé en argument est "img", on crée un nouvel ImageFactory et on le retourne
    else if(type==(QString) "img") {ImageFactory* fact = new ImageFactory; return fact;}
    ///Si le Qstring passé en argument est "aud", on crée un nouvel AudioFactory et on le retourne
    else if(type==(QString) "aud") {AudioFactory* fact = new AudioFactory; return fact;}
    ///Si le Qstring passé en argument est "vide", on crée un nouvel VideoFactory et on le retourne
    else if(type==(QString) "vid") {VideoFactory* fact = new VideoFactory; return fact;}
    ///Sinon on lance une exception
    else {throw NotesException("Mauvais type..");}

}

///Fonction qui permet de créer un nouvel Article à partir d'un Qstring
Article* ArticleFactory::createNewNote(QString &title){
    ///On récupère un nouvel id unique
    unsigned int id = getNewId();
    ///On créée le nouvel Article et on le retourne
    Article* article = new Article(QString::number(id),title,(QString)"");
    return article;
}

///Fonction qui permet de créer un nouvel Article à partir d'un Qstring
Task* TaskFactory::createNewNote(QString &title){
    ///On récupère un nouvel id unique
    unsigned int id = getNewId();
    QDate d;
    /// on récupère la date actuelle
    d.currentDate();
    ///On créée le nouvel Article et on le retourne
    Task* task = new Task(QString::number(id),title,(QString)"",d);
    return task;
}

///Fonction qui permet de créer une nouvelle image à partir d'un Qstring
Image* ImageFactory::createNewNote(QString &title){
    ///On récupère un nouvel id unique
    unsigned int id = getNewId();
    ///On créée la nouvelle Image et on la retourne
    Image* img = new Image(QString::number(id),title,(QString)"",(QString)"");
    return img;
}

///Fonction qui permet de créer un nouvel audio à partir d'un Qstring
Audio* AudioFactory::createNewNote(QString &title){
    ///On récupère un nouvel id unique
    unsigned int id = getNewId();
    ///On créée le nouvel audio et on le retourne
    Audio* audio = new Audio(QString::number(id),title,(QString)"",(QString)"");
    return audio;
}

///Fonction qui permet de créer une nouvelle video à partir d'un Qstring
Video* VideoFactory::createNewNote(QString &title){
    ///On récupère un nouvel id unique
    unsigned int id = getNewId();
    ///On créée la nouvelele Video et on la retourne
    Video* video = new Video(QString::number(id),title,(QString)"",(QString)"");
    return video;
}
