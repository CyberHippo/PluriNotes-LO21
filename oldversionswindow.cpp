#include "oldversions.h"
#include "oldversionswindow.h"
#include "mainwindow.h"
#include <QMessageBox>


OldVersionsWindow::OldVersionsWindow(Note* n, QWidget* parent) : note(n){
    list = new QListWidget();
    QListWidgetItem* item;
    /*for(unsigned int i = 0; i < n->getNumberOfVersions(); i++){
        QString title = n->toStringVersionNumber();
        item = new QListWidgetItem(title,list); // on ajoute l'item à la liste
    }*/
    vector<Note*> vect = n->getVersionsAnt().getOldNotes();
    for(unsigned int i = 0; i < vect.size(); i++){
        QString title = vect[i]->toStringVersionNumber();
        item = new QListWidgetItem(title,list);
    }
    scroller = new QScrollArea();
    layer = new QVBoxLayout();
    restor = new QPushButton("Restaurer");


    scroller->setWidget(list);
    layer->addWidget(scroller);
    layer->addWidget(restor);

    setLayout(layer);

    QObject::connect(restor, SIGNAL(clicked()), this, SLOT (restorNote()));
    QObject::connect(restor, SIGNAL(clicked()), this, SLOT (updateNotesManager()));
    QObject::connect(restor, SIGNAL(clicked()), this, SLOT (closeEditeur()));
    QObject::connect(restor, SIGNAL(clicked()), this, SLOT (close()));
}

static unsigned int extractInt(const QString &s){
    QString num;
    foreach(QChar c, s) {
        if (c.isDigit()) {num.append(c);}
    }
    bool ok;
    unsigned int nb = num.toInt(&ok);
    if (ok) {return nb;}
    else {throw NotesException("Erreur.. conversion Qstring->unsigned int");}
}

void OldVersionsWindow::restorNote(){
    if(!list->currentItem() == 0){
        QListWidgetItem* selectedItem = list->currentItem() ;
        QString title = selectedItem->text();
        unsigned int nb = extractInt(title);
        Note* newNote = note->getVersionsAnt().getNoteWithVersionNumber(nb);
        note->getVersionsAnt().restorNote(newNote);
        list->takeItem(list->currentRow());
    }
    else {throw NotesException("Couldn't restor the note..");}
}


void OldVersionsWindow::updateNotesManager(){
    MainWindow::getInstance().updateNotesManager();
}

void OldVersionsWindow::closeEditeur(){
    QWidget* empty = new QWidget;
    MainWindow::getInstance().setCentralWidget(empty);
}
