#ifndef EDITEURFACTORY_H
#define EDITEURFACTORY_H

#include "fonction.h"
#include "noteediteur.h"

class EditeurFactory{ //Classe abstraite
public:
    virtual NoteEditeur* createEditeur(Note* n) = 0; //methode virtuelle pure
    static EditeurFactory* chooseEditeur(QString& type);
};

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

