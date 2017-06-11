#include "oldversions.h"
#include "oldversionswindow.h"
#include "mainwindow.h"
#include <QMessageBox>

///Widget qui permet d'afficher les anciennes versions d'une note et de les restaurer.
OldVersionsWindow::OldVersionsWindow(Note* n, QWidget* parent) : note(n){
    this->setWindowModality(Qt::ApplicationModal);
    list = new QListWidget();
    QListWidgetItem* item;

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

///Fonction qui extrait un int d'un Qstring
static unsigned int extractInt(const QString &s){
    QString num;
    ///pour chaque caractère du QString, si c'est un numéro on l'ajoute à la Qstring temporaire num
    foreach(QChar c, s) {
        if (c.isDigit()) {num.append(c);}
    }
    bool ok;
    ///Conversion de la Qstring num en int
    unsigned int nb = num.toInt(&ok);
    ///Si la conversion est ok, on renvoit le int
    if (ok) {return nb;}
    ///Sinon on lance une exception
    else {throw NotesException("Erreur.. conversion Qstring->unsigned int");}
}

///Slot permettant de restaurer une note
void OldVersionsWindow::restorNote(){
    if(!list->currentItem() == 0){
        ///On récupère l'item dans la QlistWidget
        QListWidgetItem* selectedItem = list->currentItem() ;
        ///On récupère le texte de l'item séléctionné
        QString title = selectedItem->text();
        ///On extrait le numéro de version du texte
        unsigned int nb = extractInt(title);
        ///On récupère la note qui correspond à cette version
        Note* newNote = note->getVersionsAnt().getNoteWithVersionNumber(nb);
        ///On appelle la fonction de restauration de note
        note->getVersionsAnt().restorNote(newNote);
        ///On retire l'item de la liste
        list->takeItem(list->currentRow());
    }
    ///Si aucun item n'a été séléctionné, on lance un QMessageBox pour avertissement
    else {QMessageBox msgBox; msgBox.setText("Il n'y a pas de notes à restaurer"); msgBox.exec();}
}

///Slot permettant de mettre à jour l'affichage de NotesManager
void OldVersionsWindow::updateNotesManager(){
    MainWindow::getInstance().updateNotesManager();
}

///Slot permettant de fermer l'éditeur central
void OldVersionsWindow::closeEditeur(){
    ///Création d'un widget vide
    QWidget* empty = new QWidget;
    ///Ajout du Widget vide au centre de l'application
    MainWindow::getInstance().setCentralWidget(empty);
}
