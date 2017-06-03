#include "editeurfactory.h"

EditeurFactory* EditeurFactory::chooseEditeur(QString& type) {
    if(type==(QString) "art") {ArticleEditeurFactory* fact = new ArticleEditeurFactory(); return fact;}
    else if(type==(QString) "task") {TaskEditeurFactory* fact = new TaskEditeurFactory(); return fact;}
    else if(type==(QString) "img") {ImageEditeurFactory* fact = new ImageEditeurFactory(); return fact;}
    else if(type==(QString) "aud") {AudioEditeurFactory* fact = new AudioEditeurFactory(); return fact;}
    else if(type==(QString) "vid") {VideoEditeurFactory* fact = new VideoEditeurFactory(); return fact;}
    else {throw NotesException("Mauvais type..");}
}

ArticleEditeur* ArticleEditeurFactory::createEditeur(Note* n) {
    ArticleEditeur* ae = new ArticleEditeur(dynamic_cast<Article*>(n));
    return ae;
}

TaskEditeur* TaskEditeurFactory::createEditeur(Note* n) {
    TaskEditeur* te = new TaskEditeur(dynamic_cast<Task*>(n));
    return te;
}

AudioEditeur* AudioEditeurFactory::createEditeur(Note* n) {
    AudioEditeur* ae = new AudioEditeur(dynamic_cast<Audio*>(n));
    return ae;
}

ImageEditeur* ImageEditeurFactory::createEditeur(Note* n) {
    ImageEditeur* ie = new ImageEditeur(dynamic_cast<Image*>(n));
    return ie;
}



VideoEditeur* VideoEditeurFactory::createEditeur(Note* n) {
    VideoEditeur* ve = new VideoEditeur(dynamic_cast<Video*>(n));
    return ve;
}
