#ifndef EDITEURFACTORY_H
#define EDITEURFACTORY_H

#include "fonction.h"
#include "noteediteur.h"

///Classe abstraite, Design pattern Factory, Patron de conception créationnel.
/// Le but est ici d'instancier des objets héritant d'une classe mère abstraite

class EditeurFactory{
public:
    virtual NoteEditeur* createEditeur(Note* n) = 0; //methode virtuelle pure
    static EditeurFactory* chooseEditeur(QString& type);
};

/// Création d'un editeur pour chaque type de Note: Article, tâche, image, audio et video.
class ArticleEditeurFactory : public EditeurFactory{
public:
    ArticleEditeur* createEditeur(Note* n);
};


class TaskEditeurFactory : public EditeurFactory{
public:
    TaskEditeur* createEditeur(Note* n);
};


class ImageEditeurFactory : public EditeurFactory{
public:
    ImageEditeur* createEditeur(Note* n);
};


class AudioEditeurFactory : public EditeurFactory{
public:
    AudioEditeur* createEditeur(Note* n);
};


class VideoEditeurFactory : public EditeurFactory{
public:
    VideoEditeur* createEditeur(Note* n);
};

#endif // EDITEURFACTORY_H

