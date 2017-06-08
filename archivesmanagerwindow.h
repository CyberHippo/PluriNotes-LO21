#ifndef ARCHIVESMANAGERWINDOW_H
#define ARCHIVESMANAGERWINDOW_H
#include <QDockWidget>
#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include "notesmanagerwindow.h"

class ArchivesManagerWindow : public QDockWidget {
    Q_OBJECT
private:
    QListWidget* listNotes;
    QPushButton* restor;
    QPushButton* show;
public:
    ArchivesManagerWindow(QString title, QWidget* parent = 0);
    QListWidget* getListNotes(){return listNotes;}
    void clear(){listNotes->clear();}
signals :
    public slots :
       void afficherNote();
       void restaurerNote();
       void updateNotesManager();
};

#endif // ARCHIVESMANAGERWINDOW_H
