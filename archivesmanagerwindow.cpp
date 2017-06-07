#include "archivesmanager.h"
#include "QBoxLayout"
#include "QPushButton"
#include "fonction.h"
#include "noteediteur.h"
#include "mainwindow.h"
#include "QObject"
#include "archivesmanagerwindow.h"

ArchivesManagerWindow::ArchivesManagerWindow(QString title, QWidget* parent) : QDockWidget(title, parent){
    listNotes = new QListWidget();   ///Allocation dynamique d'une liste de type QListWidget
    QListWidgetItem* item;     /// Création d'un pointeur sur un item de la liste
    ArchivesManager& am = ArchivesManager::getInstance();   /// On récupère l'instance (ou on la crée) de ArchivesManager
    for(vector<Note*>::iterator it = am.getIteratorBegin(); it != am.getIteratorEnd(); ++it){ /// On parcourt séquentiellement le vector de Note
        item = new QListWidgetItem((*it)->getTitle(),listNotes);  ///On crée un item de la liste, et on l'associe à listNotes
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
    if(!listNotes->currentItem() == 0){     /// Si la liste des notes n'est pas vide
        QListWidgetItem* selectedItem = listNotes->currentItem(); /// On cherche la note correspondante
        QString title = selectedItem->text();
        Note* n = ArchivesManager::getInstance().getNoteWithTitle(title);
        ArchivesManager::getInstance().restorNote(n);
    }
    else {throw NotesException("Couldn't restor the note..");}
}

