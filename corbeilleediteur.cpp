#include "corbeille.h"
#include "corbeilleediteur.h"
#include "mainwindow.h"

//Definition des slots de corbeille editeur
void CorbeilleEditeur::deleteNote(){ /// Suppression de la note
    if(!list->currentItem() == 0){ /// Si la liste des Notes dans la corbeille n'est pas vide
        QListWidgetItem* selectedItem = list->currentItem() ;
        QString title = selectedItem->text();
        Note* n = Corbeille::getInstance().getNoteWithTitle(title);     /// On selectionne l'item, retourne son titre
        Corbeille::getInstance().deleteNote(n);      /// On supprime la note dans l'instance de Corbeille
        list->takeItem(list->currentRow());/// TakeItem sert à enlever et retourner l'élément d'un row donné dans le widget list
    }
}

void CorbeilleEditeur::emptyDustBin(){
    Corbeille::getInstance().emptyDustBin();
    list->clear(); //On vide aussi la liste de note de l'editeur de corbeille
}

void CorbeilleEditeur::enablePushButons(){   ///Utiliser pour griser les boutons lors de l'apparition de la fenetre. Pour les dégriser, il faut sélectionner une Note
    supp->setEnabled(true);
    restor->setEnabled(true);
}


Note* CorbeilleEditeur::restorNote(){
    if(!list->currentItem() == 0){ ///Si la liste n'est pas vide, on va procéder de la même manière que pour la fonction deleteNote().
        QListWidgetItem* selectedItem = list->currentItem() ;
        QString title = selectedItem->text();
        Note* n = Corbeille::getInstance().getNoteWithTitle(title);
        Corbeille::getInstance().RestoreNote(n); /// La seule différence est que l'on utilise dans ce cas la fonction RestoreNote(), de l'instance unique de Corbeille.
        list->takeItem(list->currentRow());
        return n;
    }
    else {throw NotesException("Couldn't restor the note..");}
}

void CorbeilleEditeur::updateNotesManager(){ /// Actualiser le NotesManager lorsqu'une modification est effectuée dans la corbeille.
    MainWindow::getInstance().updateNotesManager();
}


//Constructeur
CorbeilleEditeur::CorbeilleEditeur(QWidget* parent){
    list = new QListWidget();     /// Création d'une liste
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

    /// Connection des Signaux/Slots
    QObject::connect(empty, SIGNAL(clicked()), this, SLOT(emptyDustBin()));
    QObject::connect(supp, SIGNAL(clicked()), this, SLOT(deleteNote()));
    QObject::connect(list, SIGNAL(itemSelectionChanged()), this, SLOT(enablePushButons()));
    QObject::connect(restor, SIGNAL(clicked()), this, SLOT (restorNote()));
    QObject::connect(restor, SIGNAL(clicked()), this, SLOT(updateNotesManager()));

    scroller->setWidget(list);
    layer->addWidget(scroller);
    layer->addWidget(supp);
    layer->addWidget(empty);
    layer->addWidget(restor);

    setLayout(layer);
}
