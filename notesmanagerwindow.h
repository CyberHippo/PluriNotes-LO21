#ifndef NOTESMANAGERWINDOW_H
#define NOTESMANAGERWINDOW_H
#include <QDockWidget>
#include <QWidget>
#include <QListWidget>

class NotesManagerWindow : public QDockWidget {
    Q_OBJECT
private:
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



#endif // NOTESMANAGERWINDOW_H

