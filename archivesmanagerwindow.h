#ifndef ARCHIVESMANAGERWINDOW_H
#define ARCHIVESMANAGERWINDOW_H
#include <QDockWidget>
#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include "notesmanagerwindow.h"
/// Création de la fenêtre contenant l'ArchiveManager. Hérite de QDockWidget. Nous avons décidé de représenter ce Manager sous la forme d'un Dock
class ArchivesManagerWindow : public QDockWidget {
    Q_OBJECT
private:
    QListWidget* listNotes;
    QPushButton* restor;
    QPushButton* show;
public:
  ///Constructeur de la classe. La fenêtre contient un titre et un argument par défaut (QWidget * parent).
    ArchivesManagerWindow(QString title, QWidget* parent = 0);
    ///Retourne la liste des notes
    QListWidget* getListNotes(){return listNotes;}
    /// Permet de clear la liste
    void clear(){listNotes->clear();}
signals :
    public slots :
    ///Slot public pour afficher une Note
       void afficherNote();
       ///Slot public pour restaurer une Note
       void restaurerNote();
       ///Slot public pour mettre à jour le Manager
       void updateNotesManager();
};

#endif // ARCHIVESMANAGERWINDOW_H
