#include "corbeille.h"
#include "corbeilleediteur.h"
#include "mainwindow.h"

/// Suppression de la note
void CorbeilleEditeur::deleteNote(){
  /// Si la liste des Notes dans la corbeille n'est pas vide, on selectionne l'item, retourne son titre
    if(!list->currentItem() == 0){
        QListWidgetItem* selectedItem = list->currentItem() ;
        QString title = selectedItem->text();
        Note* n = Corbeille::getInstance().getNoteWithTitle(title);
        /// On supprime la note dans l'instance de Corbeille
        Corbeille::getInstance().deleteNote(n);
        /// On utilise la fonction TakeItem qui sert à enlever et retourner l'élément d'un row donné dans le widget list
        list->takeItem(list->currentRow());
    }
    else{QMessageBox msgBox; msgBox.setText("Il n'y a pas de notes à supprimer"); msgBox.exec();}
}

void CorbeilleEditeur::emptyDustBin(){
    Corbeille::getInstance().emptyDustBin();
    ///On vide aussi la liste de note de l'editeur de corbeille
    list->clear();
}
///Utiliser pour griser les boutons lors de l'apparition de la fenetre. Pour les dégriser, il faut sélectionner une Note
void CorbeilleEditeur::enablePushButons(){
    supp->setEnabled(true);
    restor->setEnabled(true);
}


Note* CorbeilleEditeur::restorNote(){
    if(!list->currentItem() == 0){
      ///Si la liste n'est pas vide, on va procéder de la même manière que pour la fonction deleteNote().
        QListWidgetItem* selectedItem = list->currentItem() ;
        QString title = selectedItem->text();
        Note* n = Corbeille::getInstance().getNoteWithTitle(title);
        /// La seule différence est que l'on utilise dans ce cas la fonction RestoreNote(), de l'instance unique de Corbeille.
        Corbeille::getInstance().RestoreNote(n);
        list->takeItem(list->currentRow());
        return n;
    }
    else {QMessageBox msgBox; msgBox.setText("Il n'y a pas de notes à restaurer"); msgBox.exec();}
}
/// Actualiser le NotesManager lorsqu'une modification est effectuée dans la corbeille.
void CorbeilleEditeur::updateNotesManager(){
    MainWindow::getInstance().updateNotesManager();
}


//Constructeur
CorbeilleEditeur::CorbeilleEditeur(QWidget* parent){
    this->setWindowModality(Qt::ApplicationModal);
    list = new QListWidget();
    QListWidgetItem* item;
    for(unsigned int i=0;i<Corbeille::getInstance().getDustBinSize();i++){
        Note* n = Corbeille::getInstance().getNoteWithPosition(i);
        QString title = n->getTitle();
        item = new QListWidgetItem(title,list);
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
    QObject::connect(restor, SIGNAL(clicked()), this, SLOT(updateNotesManager()));

    scroller->setWidget(list);
    layer->addWidget(scroller);
    layer->addWidget(supp);
    layer->addWidget(empty);
    layer->addWidget(restor);

    setLayout(layer);
}
