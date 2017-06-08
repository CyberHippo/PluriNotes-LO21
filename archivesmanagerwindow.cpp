#include "archivesmanager.h"
#include "QBoxLayout"
#include "fonction.h"
#include "noteediteur.h"
#include "mainwindow.h"
#include "QObject"
#include "archivesmanagerwindow.h"

ArchivesManagerWindow::ArchivesManagerWindow(QString title, QWidget* parent) : QDockWidget(title, parent){
    listNotes = new QListWidget();
    QListWidgetItem* item;
    ArchivesManager& am = ArchivesManager::getInstance();
    for(vector<Note*>::iterator it = am.getIteratorBegin(); it != am.getIteratorEnd(); ++it){
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

    //Connexions au slots
    QObject::connect(show,SIGNAL(clicked()),this,SLOT(afficherNote()));
    QObject::connect(restor,SIGNAL(clicked()),this,SLOT(restaurerNote()));
    QObject::connect(restor,SIGNAL(clicked()),this,SLOT(updateNotesManager()));
}

void ArchivesManagerWindow::afficherNote(){
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
    else {throw NotesException("Couldn't show the note..");}
}

void ArchivesManagerWindow::restaurerNote(){
    if(!listNotes->currentItem() == 0){
        QListWidgetItem* selectedItem = listNotes->currentItem();
        QString title = selectedItem->text();
        Note* n = ArchivesManager::getInstance().getNoteWithTitle(title);
        ArchivesManager::getInstance().restorNote(n);
        listNotes->takeItem(listNotes->currentRow());
    }
    else {throw NotesException("Couldn't restor the note..");}
}

void ArchivesManagerWindow::updateNotesManager(){
    MainWindow::getInstance().updateNotesManager();
}
