#ifndef ARCHIVESMANAGERWINDOW_H
#define ARCHIVESMANAGERWINDOW_H
#include <QDockWidget>
#include <QWidget>
#include <QListWidget>
#include "notesmanagerwindow.h"

/// Création de la fenêtre contenant l'ArchiveManager. Hérite de QDockWidget, car nous avons décidé de représenter ce Manager sous la forme d'un Dock
class ArchivesManagerWindow : public QDockWidget {
    Q_OBJECT
private:
    QListWidget* listNotes;   /// Liste contenant les notes
public:
    ArchivesManagerWindow(QString title, QWidget* parent = 0); ///Constructeur de la classe. La fenêtre contient un titre et un argument par défaut (QWidget * parent).
signals :
    public slots :
       void restaurerNote();  ///Slot public pour restaurer une Note
};

#endif // ARCHIVESMANAGERWINDOW_H
