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


/// Slot permettant d'afficher une note
void ArchivesManagerWindow::afficherNote(){
  /// Si la liste des notes n'est pas vide, on cherche la note correspondante
    if(!listNotes->currentItem() == 0){
        ///On récupère l'item séléctionné dans la liste de notes
        QListWidgetItem* selectedItem = listNotes->currentItem();
        ///On récupère le titre (le texte) de l'item séléctionné
        QString title = selectedItem->text();
        ///On récupère un pointeur vers la note avec ce titre
        Note* n = ArchivesManager::getInstance().getNoteWithTitle(title);
        ///On appelle un editeur de note en fonction de la classe de la note récupérée
        NoteEditeur* ne = NotesManager::getInstance().callEditeur(n,n->getClassName());
        MainWindow::getInstance().setEditeur(ne);
        ne = MainWindow::getInstance().getEditeur();
        ///On ne peut pas modifier la note
        ne->readOnly();
        MainWindow::getInstance().showEditeur(ne);
    }
    ///Sinon, on lance un QMessageBox disant qu'il n'y a pas de notes à afficher
    else {QMessageBox msgBox; msgBox.setText("Il n'y a pas de notes à afficher"); msgBox.exec();}
}


///Slot permettant de restaurer une note
void ArchivesManagerWindow::restaurerNote(){
    if(!listNotes->currentItem() == 0){
        ///On récupère l'item séléctionné dans la liste de notes
        QListWidgetItem* selectedItem = listNotes->currentItem();
        ///On récupère le titre (le texte) de l'item séléctionné
        QString title = selectedItem->text();
        ///On récupère un pointeur vers la note avec ce titre
        Note* n = ArchivesManager::getInstance().getNoteWithTitle(title);
        ///On restaure la note
        ArchivesManager::getInstance().restorNote(n);
        ///On retire la note de la liste des notes archivées
        listNotes->takeItem(listNotes->currentRow());
    }
    ///Sinon, on lance un QMessageBox disant qu'il n'y a pas de notes à restaurer
    else {QMessageBox msgBox; msgBox.setText("Il n'y a pas de notes à restaurer"); msgBox.exec();}
}

///Slot permettant de mettre à jour le NotesManager
void ArchivesManagerWindow::updateNotesManager(){
    MainWindow::getInstance().updateNotesManager();
}
