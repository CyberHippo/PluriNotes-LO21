#include "corbeille.h"
#include "corbeilleediteur.h"

//Definition des slots de corbeille editeur
void CorbeilleEditeur::deleteNote(){
    if(!list->currentItem() == 0){
        QListWidgetItem* selectedItem = list->currentItem() ;
        QString title = selectedItem->text();
        Note* n = Corbeille::getInstance().getNoteWithTitle(title);
        Corbeille::getInstance().deleteNote(n);
        list->takeItem(list->currentRow());
    }
}

void CorbeilleEditeur::emptyDustBin(){
    Corbeille::getInstance().emptyDustBin();
    list->clear(); //On vide aussi la liste de note de l'editeur de corbeille
}

void CorbeilleEditeur::enablePushButons(){
    supp->setEnabled(true);
    restor->setEnabled(true);
}


Note* CorbeilleEditeur::restorNote(){
    if(!list->currentItem() == 0){
        QListWidgetItem* selectedItem = list->currentItem() ;
        QString title = selectedItem->text();
        Note* n = Corbeille::getInstance().getNoteWithTitle(title);
        Corbeille::getInstance().RestoreNote(n);
        list->takeItem(list->currentRow());
        return n;
    }
    else {throw NotesException("Couldn't restor the note..");}
}

CorbeilleEditeur::CorbeilleEditeur(QWidget* parent){
    list = new QListWidget();
    QListWidgetItem* item;
    for(unsigned int i=0;i<Corbeille::getInstance().getDustBinSize();i++){
        Note* n = Corbeille::getInstance().getNoteWithPosition(i);
        QString title = n->getTitle();
        item = new QListWidgetItem(title,list); // on ajoute l'item à la liste
    }
    layer = new QVBoxLayout();
    scroller = new QScrollArea();

    supp = new QPushButton("Supprimer");
    empty = new QPushButton("Vider la Corbeille");
    restor = new QPushButton("Restaurer");

    supp->setEnabled(false);
    restor->setEnabled(false);

    QObject::connect(empty, SIGNAL(clicked()), this, SLOT(emptyDustBin()));
    QObject::connect(supp, SIGNAL(clicked()), this, SLOT(deleteNote()));
    QObject::connect(list, SIGNAL(itemSelectionChanged()), this, SLOT(enablePushButons()));
    QObject::connect(restor, SIGNAL(clicked()), this, SLOT (restorNote()));

    scroller->setWidget(list);
    layer->addWidget(scroller);
    layer->addWidget(supp);
    layer->addWidget(empty);
    layer->addWidget(restor);

    setLayout(layer);
}
