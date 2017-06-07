#ifndef ARCHIVESMANAGERWINDOW_H
#define ARCHIVESMANAGERWINDOW_H
#include <QDockWidget>
#include <QWidget>
#include <QListWidget>
#include "notesmanagerwindow.h"

class ArchivesManagerWindow : public QDockWidget {
    Q_OBJECT
private:
    QListWidget* listNotes;
public:
    ArchivesManagerWindow(QString title, QWidget* parent = 0);
    QListWidget* getListNotes(){return listNotes;}
    void clear(){listNotes->clear();}
signals :
    public slots :
       void restaurerNote();
       void updateNotesManager();
};

#endif // ARCHIVESMANAGERWINDOW_H
