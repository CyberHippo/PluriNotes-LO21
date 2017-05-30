#include "fonction.h"
#include "notemanager.h"
#include "relation.h"
#include "notefactory.h"
#include "time.h"
#include "stdio.h"
#include "stdlib.h"

unsigned int NoteFactory::getNewId() { //Generates random id different than other notes
    return rand()%10000;
}


NoteFactory* NoteFactory::chooseFactory(QString& type){
    if(type==(QString) "art") {ArticleFactory* fact = new ArticleFactory; return fact;}
    else if(type==(QString) "task") {TaskFactory* fact = new TaskFactory; return fact;}
    else if(type==(QString) "img") {ImageFactory* fact = new ImageFactory; return fact;}
    else if(type==(QString) "aud") {AudioFactory* fact = new AudioFactory; return fact;}
    else if(type==(QString) "vid") {VideoFactory* fact = new VideoFactory; return fact;}
    else {throw NotesException("Mauvais type..");}

}

Article* ArticleFactory::createNewNote(QString &title){
    unsigned int id = getNewId();
    Article* article = new Article(QString::number(id),title,(QString)"");
    return article;
}

Task* TaskFactory::createNewNote(QString &title){
    unsigned int id = getNewId();
    date d(15,6,2017);
    Task* task = new Task(QString::number(id),title,(QString)"",d);
    return task;
}

Image* ImageFactory::createNewNote(QString &title){
    unsigned int id = getNewId();
    Image* img = new Image(QString::number(id),title,(QString)"",(QString)"");
    return img;
}

Audio* AudioFactory::createNewNote(QString &title){
    unsigned int id = getNewId();
    Audio* audio = new Audio(QString::number(id),title,(QString)"",(QString)"");
    return audio;
}

Video* VideoFactory::createNewNote(QString &title){
    unsigned int id = getNewId();
    Video* video = new Video(QString::number(id),title,(QString)"",(QString)"");
    return video;
}
