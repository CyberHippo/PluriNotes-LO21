#include "archivesmanager.h"
#include "QBoxLayout"
#include "QPushButton"
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
    QPushButton* restaurerNote = new QPushButton("Restaurer");
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(listNotes);
    layout->addWidget(restaurerNote);
    multiWidget->setLayout(layout);
    this->setWidget(multiWidget);

    //Connexions au slots
    QObject::connect(restaurerNote,SIGNAL(clicked()),this,SLOT(restaurerNote()));
}

void ArchivesManagerWindow::restaurerNote(){
    if(!listNotes->currentItem() == 0){
        QListWidgetItem* selectedItem = listNotes->currentItem();
        QString title = selectedItem->text();
        Note* n = ArchivesManager::getInstance().getNoteWithTitle(title);
        ArchivesManager::getInstance().restorNote(n);
    }
    else {throw NotesException("Couldn't restor the note..");}
}

