#include "editeurfactory.h"

/// EditeurFactory est une fabrique abstraite qui, via la méthode chooseEditeur, va permettre de selectionnerl'éditeur d'intérêt
EditeurFactory* EditeurFactory::chooseEditeur(QString& type) {
    if(type==(QString) "art") {ArticleEditeurFactory* fact = new ArticleEditeurFactory(); return fact;}
    else if(type==(QString) "task") {TaskEditeurFactory* fact = new TaskEditeurFactory(); return fact;}
    else if(type==(QString) "img") {ImageEditeurFactory* fact = new ImageEditeurFactory(); return fact;}
    else if(type==(QString) "aud") {AudioEditeurFactory* fact = new AudioEditeurFactory(); return fact;}
    else if(type==(QString) "vid") {VideoEditeurFactory* fact = new VideoEditeurFactory(); return fact;}
    else {throw NotesException("Mauvais type..");}
}


/// Création de l'éditeur Article.
ArticleEditeur* ArticleEditeurFactory::createEditeur(Note* n) {
    ArticleEditeur* ae = new ArticleEditeur(dynamic_cast<Article*>(n));
    return ae;
}


/// Création de l'éditeur Tache
TaskEditeur* TaskEditeurFactory::createEditeur(Note* n) {
    TaskEditeur* te = new TaskEditeur(dynamic_cast<Task*>(n));
    return te;
}


/// Création de l'éditeur Audio.
AudioEditeur* AudioEditeurFactory::createEditeur(Note* n) {
    AudioEditeur* ae = new AudioEditeur(dynamic_cast<Audio*>(n));
    return ae;
}


/// Création de l'éditeur Image
ImageEditeur* ImageEditeurFactory::createEditeur(Note* n) {
    ImageEditeur* ie = new ImageEditeur(dynamic_cast<Image*>(n));
    return ie;
}



/// Création de l'éditeur Video
VideoEditeur* VideoEditeurFactory::createEditeur(Note* n) {
    VideoEditeur* ve = new VideoEditeur(dynamic_cast<Video*>(n));
    return ve;
}
