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
protected :
    QLineEdit *id;
    QLineEdit *title;
    QPushButton *save;
    QPushButton *supp;
    QHBoxLayout *layout;
    QHBoxLayout *idLayout;
    QHBoxLayout *titleLayout;
    QHBoxLayout *buttonLayout;
    bool isSaved;

public:
    NoteEditeur(Note* n, QWidget* parent=0);
    const QLineEdit& getId() const {return *id;}
    QLineEdit& getTitle() const {return *title;}
    virtual Note* getNote() const = 0;
    QPushButton* getSaveButton() {return save;}
    QPushButton* getSuppButton() {return supp;}
    bool getSaved() const {return isSaved;}
    void setSaved(bool s){isSaved = s;}

signals :

public slots :
    virtual void saveNote() = 0;
    virtual void updateNote() = 0;
};


class ArticleEditeur : public NoteEditeur {
private :
    Q_OBJECT
    Article* article;
    QTextEdit *text;
public:
    explicit ArticleEditeur(Note* a, QWidget* parent=0);
    QTextEdit& getText() const {return *text;}
    Article* getNote() const;

signals :

public slots :
    void saveNote();
    void updateNote();

private slots :
    void activerSave();


};

/*class TaskEditeur : public NoteEditeur {
private:
    Q_OBJECT
    Task* task;
    QLineEdit *status;
    QLineEdit *deadline;
    QLineEdit *priority;
    //QWidget *action??
public:
    explicit TaskEditeur(Note* t, QWidget* parent=0);
    QLineEdit& getStatus() const { return *status;}
    QLineEdit& getDeadline() const { return *deadline;}
    QLineEdit& getPriority() const { return *priority;}
    Task* getNote() const;

signals :

public slots :
    void saveNote();
    void updateNote();

private slots :
    void activerSave();


};*/


#endif // NOTEEDITEUR_H

