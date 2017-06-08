#ifndef NOTEEDITEUR_H
#define NOTEEDITEUR_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QDateEdit>

#include "fonction.h"
#include "notemanager.h"
#include "notefactory.h"
#include "oldversionswindow.h"

class NoteEditeur : public QWidget {
    Q_OBJECT
    friend class NotesManager;
protected :
    QLineEdit* id;
    QLineEdit* title;
    QLineEdit* version;
    QDateEdit* date_creation;
    QDateEdit* date_modif;
    QPushButton* save;
    QPushButton* oldVersions;
    QPushButton* supp;
    QPushButton* close;

    OldVersionsWindow* ovw;

    QHBoxLayout* idLayout;
    QHBoxLayout* titleLayout;
    QHBoxLayout* versionLayout;
    QHBoxLayout* datesLayout;
    QHBoxLayout* buttonLayout;

    QLabel* idLabel;
    QLabel* titleLabel;
    QLabel* versionLabel;
    QLabel* dcLabel;
    QLabel* dmLabel;

    QVBoxLayout* layer;



    bool isSaved;

public:
    NoteEditeur(Note* n, QWidget* parent=0);
    virtual void readOnly() = 0;
    virtual ~NoteEditeur(){}

signals :

public slots :
    virtual void saveNote() = 0;
    virtual void toDustbin() = 0;
    virtual void showOldVersionsWindow() = 0;
    void updateNotesManager();
    void updateArchivesManager();
    void setEmptyCentralWidget();
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
    void readOnly();
    ~ArticleEditeur(){}

signals :

public slots :
    void saveNote();
    void toDustbin();
    void showOldVersionsWindow();
    //void updateNote();

};

class TaskEditeur : public NoteEditeur {
private:
    Q_OBJECT
    Task* task;
    QTextEdit* actions;
    QLineEdit* status;
    QDateEdit* deadline;
    QLineEdit* priority;

    QHBoxLayout* actionsLayout;
    QHBoxLayout* statusLayout;
    QHBoxLayout* deadlineLayout;
    QHBoxLayout* priorityLayout;

    QLabel* actionsLabel;
    QLabel* statusLabel;
    QLabel* deadlineLabel;
    QLabel* priorityLabel;

public:
    explicit TaskEditeur(Task* t, QWidget* parent=0);
    void readOnly();
    ~TaskEditeur(){}

signals :

public slots :
    void saveNote();
    void toDustbin();
    void showOldVersionsWindow();
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
    virtual void readOnly();

private slots :
    virtual void activerSave();



};

class AudioEditeur : public MultimediaEditeur{
    Q_OBJECT
protected:
    Audio* audio;
public:
    AudioEditeur(Audio* a, QWidget* parent=0);
    //void readOnly();
    ~AudioEditeur(){}


public slots :
    void saveNote();
    void toDustbin();
    void showOldVersionsWindow();
    //void updateNote();

};

class ImageEditeur : public MultimediaEditeur {
    Q_OBJECT
protected:
    Image* image;
public:
    ImageEditeur(Image* img,QWidget* parent=0);
    //void readOnly();
    ~ImageEditeur(){}

public slots :
    void saveNote();
    void toDustbin();
    void showOldVersionsWindow();
    //void updateNote();


};

class VideoEditeur : public MultimediaEditeur{
    Q_OBJECT
protected:
    Video* video;
public:
    VideoEditeur(Video* v, QWidget* parent=0);
    //void readOnly();
    ~VideoEditeur(){}

public slots :
    void saveNote();
    void toDustbin();
    void showOldVersionsWindow();
    //void updateNote();

};




#endif // NOTEEDITEUR_H

