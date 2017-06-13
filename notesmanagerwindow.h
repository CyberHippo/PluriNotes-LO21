#ifndef NOTESMANAGERWINDOW_H
#define NOTESMANAGERWINDOW_H
#include <QDockWidget>
#include <QWidget>
#include <QListWidget>

///Widget dockable dans lequel seront affichées toutes les notes de notesmanager
class NotesManagerWindow : public QDockWidget {
    Q_OBJECT
protected:
    QListWidget* listNotes;
public:
    NotesManagerWindow(QString title, QWidget* parent = 0);
    QListWidget* getListNotes(){return listNotes;}
    void clear(){listNotes->clear();}
signals :
    public slots :
       void afficherNote();
       void afficherAscendDescend();
};



///Widget dockable dans lequel seront affichées toutes les taches de notesmanager
class TaskManagerWindow : public QDockWidget {
    Q_OBJECT
protected:
    QListWidget* listTask;
public:
    TaskManagerWindow(QString title, QWidget* parent = 0);
    virtual QListWidget* getListTask(){return listTask;}
    virtual void clear(){listTask->clear();}
signals :
    public slots :
        void afficherTache();
};

#endif // NOTESMANAGERWINDOW_H

