#ifndef EDITEURFACTORY_H
#define EDITEURFACTORY_H

#include "fonction.h"
#include "noteediteur.h"

/// Le but est ici d'instancier des objets héritant d'une classe mère abstraite.
class EditeurFactory{
public:
    virtual NoteEditeur* createEditeur(Note* n) = 0;
    static EditeurFactory* chooseEditeur(QString& type);
};
/// Création d'un editeur pour chaque les Articles
class ArticleEditeurFactory : public EditeurFactory{
public:
    ArticleEditeur* createEditeur(Note* n);
};

/// Création d'un editeur pour chaque les Taches

class TaskEditeurFactory : public EditeurFactory{
public:
    TaskEditeur* createEditeur(Note* n);
};

/// Création d'un editeur pour chaque les Images

class ImageEditeurFactory : public EditeurFactory{
public:
    ImageEditeur* createEditeur(Note* n);
};

/// Création d'un editeur pour chaque les Audio

class AudioEditeurFactory : public EditeurFactory{
public:
    AudioEditeur* createEditeur(Note* n);
};

/// Création d'un editeur pour chaque les Vidéos

class VideoEditeurFactory : public EditeurFactory{
public:
    VideoEditeur* createEditeur(Note* n);
};

#endif // EDITEURFACTORY_H
