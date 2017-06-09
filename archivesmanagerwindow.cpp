#include "archivesmanager.h"
#include "QBoxLayout"
#include "fonction.h"
#include "noteediteur.h"
#include "mainwindow.h"
#include "QObject"
#include "archivesmanagerwindow.h"

ArchivesManagerWindow::ArchivesManagerWindow(QString title, QWidget* parent) : QDockWidget(title, parent){
///Allocation dynamique d'une liste de type QListWidget
    listNotes = new QListWidget();
    /// Création d'un pointeur sur un item de la liste
    QListWidgetItem* item;
    /// On récupère l'instance (ou on la crée) de ArchivesManager
    ArchivesManager& am = ArchivesManager::getInstance();
    /// On parcourt séquentiellement le vector de Note
    for(vector<Note*>::iterator it = am.getIteratorBegin(); it != am.getIteratorEnd(); ++it){
///On crée un item de la liste, et on l'associe à listNotes
        item = new QListWidgetItem((*it)->getTitle(),listNotes);
    }
    QWidget* multiWidget = new QWidget();
    show = new QPushButton("Afficher");
    restor = new QPushButton("Restaurer");
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(listNotes);
    layout->addWidget(restor);
    layout->addWidget(show);
    multiWidget->setLayout(layout);
    this->setWidget(multiWidget);

    ///Connexions au slots
    QObject::connect(show,SIGNAL(clicked()),this,SLOT(afficherNote()));
    QObject::connect(restor,SIGNAL(clicked()),this,SLOT(restaurerNote()));
    QObject::connect(restor,SIGNAL(clicked()),this,SLOT(updateNotesManager()));
}

void ArchivesManagerWindow::afficherNote(){
  /// Si la liste des notes n'est pas vide, on cherche la note correspondante
    if(!listNotes->currentItem() == 0){
        QListWidgetItem* selectedItem = listNotes->currentItem();
        QString title = selectedItem->text();
        Note* n = ArchivesManager::getInstance().getNoteWithTitle(title);
        NoteEditeur* ne = NotesManager::getInstance().callEditeur(n,n->getClassName());
        MainWindow::getInstance().setEditeur(ne);
        ne = MainWindow::getInstance().getEditeur();
        ne->readOnly();
        MainWindow::getInstance().showEditeur(ne);
    }
    else {QMessageBox msgBox; msgBox.setText("Il n'y a pas de notes à afficher"); msgBox.exec();}
}

void ArchivesManagerWindow::restaurerNote(){
    if(!listNotes->currentItem() == 0){
        QListWidgetItem* selectedItem = listNotes->currentItem();
        QString title = selectedItem->text();
        Note* n = ArchivesManager::getInstance().getNoteWithTitle(title);
        ArchivesManager::getInstance().restorNote(n);
        listNotes->takeItem(listNotes->currentRow());
    }
    else {QMessageBox msgBox; msgBox.setText("Il n'y a pas de notes à restaurer"); msgBox.exec();}
}

void ArchivesManagerWindow::updateNotesManager(){
    MainWindow::getInstance().updateNotesManager();
}
