#include "notesmanagerwindow.h"
#include "notemanager.h"
#include "QBoxLayout"
#include "QPushButton"
#include "fonction.h"
#include "noteediteur.h"
#include "mainwindow.h"
#include "QObject"


NotesManagerWindow::NotesManagerWindow(QString title, QWidget* parent) : QDockWidget(title, parent){
    listNotes = new QListWidget();
    QListWidgetItem* item;
    NotesManager& nm = NotesManager::getInstance();
    for(vector<Note*>::iterator it = nm.getIteratorBegin(); it != nm.getIteratorEnd(); ++it){
        item= new QListWidgetItem((*it)->getTitle(),listNotes);
    }
    QWidget* multiWidget = new QWidget();
    QPushButton* afficherNote = new QPushButton("Afficher");
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(listNotes);
    layout->addWidget(afficherNote);
    multiWidget->setLayout(layout);
    this->setWidget(multiWidget);

    //Connexions au slots
    QObject::connect(afficherNote,SIGNAL(clicked()),this,SLOT(afficherNote(this->listNotes)));
}

void NotesManagerWindow::afficherNote(QListWidget* list){
    if(!list->currentItem() == 0){
        QListWidgetItem* selectedItem = list->currentItem();
        QString title = selectedItem->text();
        Note* n = NotesManager::getInstance().getNoteWithTitle(title);
        NoteEditeur* ne = NotesManager::getInstance().callEditeur(n,n->getClassName());
        ne->show();
    }
    else {throw NotesException("Couldn't show the note..");}
}
