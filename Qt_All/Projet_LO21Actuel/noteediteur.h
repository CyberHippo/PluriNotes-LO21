#ifndef NOTEEDITEUR_H
#define NOTEEDITEUR_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>

#include "fonction.h"
#include "notemanager.h"
#include "notefactory.h"

class NoteEditeur : public QWidget {
    Q_OBJECT
    friend class NotesManager;
protected :
    QLineEdit* id;
    QLineEdit* title;
    QLineEdit* version;
    QPushButton* save;
    QPushButton* supp;

    QHBoxLayout* idLayout;
    QHBoxLayout* titleLayout;
    QHBoxLayout* versionLayout;
    QHBoxLayout* saveLayout;
    QHBoxLayout* suppLayout;

    QLabel* idLabel;
    QLabel* titleLabel;
    QLabel* versionLabel;

    QVBoxLayout* layer;

    bool isSaved;

public:
    NoteEditeur(Note* n, QWidget* parent=0);
    static NoteEditeur* chooseEditeur(Note*n, QString& type);
    const QLineEdit& getId() const {return *id;}
    QLineEdit& getTitle() const {return *title;}
    QLineEdit& getNumVersion() const {return *version;}
    virtual Note* getNote() const = 0;
    QPushButton* getSaveButton() {return save;}
    QPushButton* getSuppButton() {return supp;}
    bool getSaved() const {return isSaved;}
    void setSaved(bool s){isSaved = s;}
    virtual ~NoteEditeur(){}

signals :

public slots :
    virtual void saveNote() = 0;
    //virtual void updateNote() = 0;
private slots :
    virtual void activerSave();

};


class ArticleEditeur : public NoteEditeur {
private :
    Q_OBJECT
    Article* article;

    QTextEdit* text;
    QLabel* textLabel;
    QHBoxLayout* textLayout;
public:
    explicit ArticleEditeur(Article* a, QWidget* parent=0);
    QTextEdit& getText() const {return *text;}
    Article* getNote() const{return article;}
    ~ArticleEditeur(){}

signals :

public slots :
    void saveNote();
    //void updateNote();



};

class TaskEditeur : public NoteEditeur {
private:
    Q_OBJECT
    Task* task;
    QLineEdit* status;
    QLineEdit* deadline;
    QLineEdit* priority;
    //QWidget* action??

    QHBoxLayout* statusLayout;
    QHBoxLayout* deadlineLayout;
    QHBoxLayout* priorityLayout;

    QLabel* statusLabel;
    QLabel* deadlineLabel;
    QLabel* priorityLabel;

public:
    explicit TaskEditeur(Task* t, QWidget* parent=0);
    QLineEdit& getStatus() const { return *status;}
    QLineEdit& getDeadline() const { return *deadline;}
    QLineEdit& getPriority() const { return *priority;}
    Task* getNote() const {return task;}
    ~TaskEditeur(){}

signals :

public slots :
    void saveNote();
    //void updateNote();



};

class MultimediaEditeur: public NoteEditeur {
    Q_OBJECT
protected:
    QTextEdit* desc;
    QLineEdit* filename;

    QLabel* descLabel;
    QLabel* filenameLabel;

    QHBoxLayout* descLayout;
    QHBoxLayout* filenameLayout;

public:
    MultimediaEditeur(Multimedia *m , QWidget *parent=0);
    Multimedia* getNote() const = 0;

private slots :
    virtual void activerSave();



};

class AudioEditeur : public MultimediaEditeur{
    Q_OBJECT
protected:
    Audio* audio;
public:
    AudioEditeur(Audio* a, QWidget* parent=0);
    Audio* getNote() const{return audio;}


public slots :
    void saveNote();
    //void updateNote();

};

class ImageEditeur : public MultimediaEditeur {
    Q_OBJECT
protected:
    Image* image;
public:
    ImageEditeur(Image* img,QWidget* parent=0);
    Image* getNote() const{return image;}
    ~ImageEditeur(){}

public slots :
    void saveNote();
    //void updateNote();


};

class VideoEditeur : public MultimediaEditeur{
    Q_OBJECT
protected:
    Video* video;
public:
    VideoEditeur(Video* v, QWidget* parent=0);
    Video* getNote() const{return video;}
    ~VideoEditeur(){}

public slots :
    void saveNote();
    //void updateNote();

};




#endif // NOTEEDITEUR_H

