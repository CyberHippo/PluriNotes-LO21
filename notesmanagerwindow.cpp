#include "notesmanagerwindow.h"
#include "notemanager.h"
#include "QBoxLayout"
#include "QPushButton"
#include "fonction.h"
#include "noteediteur.h"
#include "mainwindow.h"
#include "QObject"

///Constructeur du widget NotesManagerWindow
NotesManagerWindow::NotesManagerWindow(QString title, QWidget* parent) : QDockWidget(title, parent){
    listNotes = new QListWidget();
    QListWidgetItem* item;
    NotesManager& nm = NotesManager::getInstance();
    for(vector<Note*>::iterator it = nm.getIteratorBegin(); it != nm.getIteratorEnd(); ++it){
        item = new QListWidgetItem((*it)->getTitle(),listNotes);
    }
    QWidget* multiWidget = new QWidget();
    QPushButton* afficherNote = new QPushButton("Afficher la note");
    QPushButton* afficherRelations = new QPushButton("Afficher les relations");
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(listNotes);
    layout->addWidget(afficherNote);
    layout->addWidget(afficherRelations);
    multiWidget->setLayout(layout);
    this->setWidget(multiWidget);

    //Connexions au slots
    QObject::connect(afficherNote,SIGNAL(clicked()),this,SLOT(afficherNote()));
    QObject::connect(afficherRelations,SIGNAL(clicked()),this,SLOT(afficherAscendDescend()));
}

///Slot permettant d'afficher une note
void NotesManagerWindow::afficherNote(){
    if(!listNotes->currentItem() == 0){
        ///On récupère l'élément courrant
        QListWidgetItem* selectedItem = listNotes->currentItem();
        ///Puis son titre
        QString title = selectedItem->text();
        ///On récupère un pointeur sur une note ayant le même titre
        Note* n = NotesManager::getInstance().getNoteWithTitle(title);
        ///On appelle le bon editeur en fonction du type de note
        NoteEditeur* ne = NotesManager::getInstance().callEditeur(n,n->getClassName());
        MainWindow::getInstance().setEditeur(ne);
        ne = MainWindow::getInstance().getEditeur();
        MainWindow::getInstance().showEditeur(ne);
    }
    ///Sinon on lance une exception disant qu'il n'y a pas de notes à afficher
    else {QMessageBox msgBox; msgBox.setText("Il n'y a pas de notes à afficher"); msgBox.exec();}
}

///Slot permettant d'afficher le widget de descendants et d'ascendants pour une note
void NotesManagerWindow::afficherAscendDescend(){
    if(!listNotes->currentItem() == 0){
        ///on réucupère l'item courant
        QListWidgetItem* selectedItem = listNotes->currentItem();
        ///on récupère son titre
        QString title = selectedItem->text();
        ///on récupère un pointeur vers une note ayant ce titre
        Note* n = NotesManager::getInstance().getNoteWithTitle(title);
        ///Affichage du widget
        MainWindow::getInstance().showRelationsAscendDescend(n);
       }
    ///Sinon on lance une exception
    else {QMessageBox msgBox; msgBox.setText("Il n'y a pas d'ascendants ou de descendants à afficher"); msgBox.exec();}
}

///Constructeur du widget TaskManagerWindow permettant d'afficher toutes les taches
TaskManagerWindow::TaskManagerWindow(QString title, QWidget* parent) : QDockWidget(title, parent){
    listTask = new QListWidget();
    QListWidgetItem* item;
    NotesManager& nm = NotesManager::getInstance();
    for(vector<Note*>::iterator it = nm.getIteratorBegin(); it != nm.getIteratorEnd(); ++it){
        if((*it)->getClassName() == "task"){
            Task* t = dynamic_cast<Task*>(*it);
            unsigned int p = t->getPriority();
            QString title = t->getTitle();
            QString showedText = QString::number(p) + ":" + title;
            item = new QListWidgetItem(showedText,listTask);
        }
    }
    QWidget* multiWidget = new QWidget;
    QPushButton* showTask = new QPushButton("Afficher la tâche");
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(listTask);
    layout->addWidget(showTask);
    multiWidget->setLayout(layout);
    this->setWidget(multiWidget);

    //Connexions au slots
    QObject::connect(showTask,SIGNAL(clicked()),this,SLOT(afficherTache()));
}


///Slot permettant d'afficher une tache
void TaskManagerWindow::afficherTache(){
    ///on récupère la tache grâce à son titre puis on appelle un éditeur en fonction de son type, en l'occurence un editer de tache
    if(!listTask->currentItem() == 0){
        QListWidgetItem* selectedItem = listTask->currentItem();
        QString title = selectedItem->text();
        QStringList list1 = title.split(':');
        qDebug() << title;
        Note* t = NotesManager::getInstance().getNoteWithTitle(list1[1]);
        NoteEditeur* ne = NotesManager::getInstance().callEditeur(t,t->getClassName());
        MainWindow::getInstance().setEditeur(ne);
        ne = MainWindow::getInstance().getEditeur();
        MainWindow::getInstance().showEditeur(ne);
    }
    ///sinon on lance une exception
    else {QMessageBox msgBox; msgBox.setText("Il n'y a pas de tâches actives à afficher"); msgBox.exec();}
}
