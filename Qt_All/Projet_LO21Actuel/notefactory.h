#ifndef NOTEFACTORY_H
#define NOTEFACTORY_H

#include "fonction.h"
#include "notemanager.h"

class NoteFactory
{
private:
    friend class NotesManager;
public:
    static unsigned int getNewId();
    virtual Note* createNewNote(QString& title)=0;
    static NoteFactory* chooseFactory(QString& type);
    ~NoteFactory();
};

class ArticleFactory : public NoteFactory {
public:
    Article* createNewNote(QString& title);
    ~ArticleFactory();
};

class TaskFactory : public NoteFactory {
public:
    Task* createNewNote(QString& title);
    ~TaskFactory();
};

class AudioFactory : public NoteFactory {
public:
    Audio* createNewNote(QString& title);
    ~AudioFactory();
};

class ImageFactory : public NoteFactory {
public:
    Image* createNewNote(QString& title);
    ~ImageFactory();
};

class VideoFactory : public NoteFactory {
public:
    Video* createNewNote(QString& title);
    ~VideoFactory();
};
#endif // NOTEFACTORY_H

