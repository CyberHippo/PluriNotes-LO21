#include "mainwindow.h"
#include "relationediteur.h"
#include <QKeySequence>
#include <QApplication>
#include <QMessageBox>

MainWindow::MWHandler MainWindow::mw_handler=MWHandler();

MainWindow& MainWindow::getInstance() {
  /// Si le pointeur vers l'instance unique pointe vers 0
  if(!mw_handler.instance) {
    mw_handler.instance=new MainWindow;
  }
  /// Retour par ref vers l'instance unique
  return *mw_handler.instance;
}


///Slot permettant de libérer l'instance unique de mainwindow
void MainWindow::libererInstance() {
  /// Liberation de la memoire allouee a l'instance unique
  delete mw_handler.instance;
  /// Repasse le pointeur a null/nullptr/0 pour que le prochain appel a getInstance recree bien une instance
  mw_handler.instance=0;
}

///Constructeur principal de la Main Window.
MainWindow::MainWindow () {
    setWindowTitle("PluriNotes");
    setWindowState(Qt::WindowMaximized);
    centralArea = new QWidget;
    setCentralWidget(centralArea);
    centralLayout = new QGridLayout;
    centralArea->setLayout(centralLayout);

    ///Création du menu PluriNotes
    QMenu* pluriNotes = new QMenu;
    pluriNotes = menuBar()->addMenu("&PluriNotes");

    ///Création du menu Manager
    QMenu* managers = new QMenu;
    managers = menuBar()->addMenu("&Managers");

    ///Création du menu NotesManager
    QMenu* menuNotesManager = new QMenu;
    menuNotesManager = managers->addMenu("&NotesManager");

    ///Création du menu Nouveau
    QMenu* menuNote = new QMenu;
    menuNote = menuBar()->addMenu("&Note");
    QMenu* createNotes = menuNote->addMenu("&Nouveau");

    ///Création du menu Edition
    QMenu* menuEdition = new QMenu;
    menuEdition = menuBar()->addMenu("&Edition");

    ///Création du menu RelationsManager
    QMenu* menuRelationsManager = new QMenu;
    menuRelationsManager = managers->addMenu("&RelationsManager");

    QMenu* menuArchivesManager = managers->addMenu("&ArchivesManager");

    QMenu* menuDustbin = new QMenu;
    menuDustbin = menuBar()->addMenu("&Corbeille");


    ///Ajout d'une action de sauvegarde dans le menu PluriNotes
    QAction* save = new QAction("Save", this);
    pluriNotes->addAction(save);
    ///Ajout d'une action de chargement dans le menu PluriNotes
    QAction* load = new QAction("Load", this);
    pluriNotes->addAction(load);
    ///Ajout d'une action de fermeture d'application dans le menu PluriNotes
    QAction* close = new QAction("Close App", this);
    pluriNotes->addAction(close);

    ///Dans menu NotesManager
    QAction* showNotesManager = new QAction("Afficher", this);
    menuNotesManager->addAction(showNotesManager);
    QAction* updateNotesManager =  new QAction("Mise à jour", this);
    menuNotesManager->addAction(updateNotesManager);


    ///Dans menu Note->Nouveau
    QAction* newArticle = new QAction("Article", this);
    createNotes->addAction(newArticle);
    QAction* newTask = new QAction("Tache", this);
    createNotes->addAction(newTask);
    QAction* newAudio = new QAction("Audio", this);
    createNotes->addAction(newAudio);
    QAction* newImage = new QAction("Image", this);
    createNotes->addAction(newImage);
    QAction* newVideo = new QAction("Video", this);
    createNotes->addAction(newVideo);

    ///Dans menu Edition
    QAction* undo = new QAction("&Annuler", this);
    menuEdition->addAction(undo);
    QAction* redo = new QAction("&Retablir", this);
    menuEdition->addAction(redo);

    ///Dans menu RelationsManager
    QAction* openRelationsEditor = new QAction("&Editer", this);
    menuRelationsManager->addAction(openRelationsEditor);
    QAction* openRelationsManager = new QAction("&Afficher", this);
    menuRelationsManager->addAction(openRelationsManager);

    ///Dans menu ArchivesManager
    QAction* showArchivesManager = new QAction("&Afficher", this);
    menuArchivesManager->addAction(showArchivesManager);

    ///Dans le menu Corbeille
    QAction* showDustbin = new QAction("&Afficher la corbeille", this);
    menuDustbin->addAction(showDustbin);


    /// Connexions SIGNAL/SLOTS
    QObject::connect(close, SIGNAL(triggered()), this, SLOT(QuitWithoutSaving()));
    QObject::connect(newArticle, SIGNAL(triggered()), this, SLOT(newArticle()));
    QObject::connect(newTask, SIGNAL(triggered()), this, SLOT(newTask()));
    QObject::connect(newAudio, SIGNAL(triggered()), this, SLOT(newAudio()));
    QObject::connect(newImage, SIGNAL(triggered()), this, SLOT(newImage()));
    QObject::connect(newVideo, SIGNAL(triggered()), this, SLOT(newVideo()));
    QObject::connect(openRelationsEditor, SIGNAL(triggered()), this, SLOT(showRelationsManager()));
    QObject::connect(showDustbin, SIGNAL(triggered()), this, SLOT(showDustbin()));
    QObject::connect(showNotesManager, SIGNAL(triggered()), this, SLOT(showNotesManager()));
    QObject::connect(updateNotesManager, SIGNAL(triggered()), this, SLOT(updateNotesManager()));
    QObject::connect(save, SIGNAL(triggered()), this, SLOT(QuitApplication()));
    QObject::connect(showArchivesManager, SIGNAL(triggered()), this, SLOT(showArchivesManager()));
    QObject::connect(load, SIGNAL(triggered()), this, SLOT(LoadData()));
    QObject::connect(openRelationsManager, SIGNAL(triggered()), this, SLOT(showRelationsManagerActive()));

}


///fonction permettant de faire apparaitre un editeur
void MainWindow::showEditeur(NoteEditeur* ne) {
    mainEditeur = ne;
    setCentralWidget(ne);
    ne->adjustSize();
    ne->show();
}


/// Les Notes actives apparaîtront dans un dock indépendant de la fenêtre
void MainWindow::showNotesManager(){
    dockNotesManager = new NotesManagerWindow(tr("Notes Actives"), this);
    dockNotesManager->setAllowedAreas(Qt::LeftDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea, dockNotesManager);
}


///Slot permettant d'afficher le widget de relations actives sur la partie droite de l'appli
void MainWindow::showRelationsManagerActive(){
    dockRelationsManager = new relationsmanagerwindow(tr("Relations Actives"), this);
    dockRelationsManager->setAllowedAreas(Qt::RightDockWidgetArea);
    addDockWidget(Qt::RightDockWidgetArea, dockRelationsManager);
}


///Slot permettant d'afficher le widget de notes ascendantes et descendantes sur la partie droite de l'appli
void MainWindow::showRelationsAscendDescend(Note* n){
    dockAscendDescend = new AscendAndDescendWindow(n, tr("Ascendants & Descendants"), this);
    dockAscendDescend->setAllowedAreas(Qt::RightDockWidgetArea);
    addDockWidget(Qt::RightDockWidgetArea, dockAscendDescend);
}


///Slot permettant d'afficher le widget des notes archivées dans la partie gauche de l'application
void MainWindow::showArchivesManager(){
    dockArchivesManager = new ArchivesManagerWindow(tr("Notes Archivées"), this);
    dockArchivesManager->setAllowedAreas(Qt::LeftDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea, dockArchivesManager);
}


///Slot permettant d'afficher le manager de taches
void MainWindow::showTaskManager(){
    dockTaskManager = new TaskManagerWindow(tr("Tâches prioritaires"), this);
    dockTaskManager->setAllowedAreas(Qt::LeftDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea, dockTaskManager);
}


///Slot permettant de mettre à jour notesmanager
void MainWindow::updateNotesManager(){
    dockNotesManager->clear();
    QListWidgetItem* item;
    NotesManager& nm = NotesManager::getInstance();
    for(vector<Note*>::iterator it = nm.getIteratorBegin(); it != nm.getIteratorEnd(); ++it){
        item= new QListWidgetItem((*it)->getTitle(),dockNotesManager->getListNotes());
    }
}

///Slot permettant de mettre à jour relationsmanager
void MainWindow::updateRelationManager(){
    dockRelationsManager->clear();
    QListWidgetItem* item;
    QString temp;
    RelationsManager& rm = RelationsManager::getInstance();
    for(vector<Relation*>::iterator it1 = rm.getIteratorBegin(); it1 != rm.getIteratorEnd(); ++it1){
        for (vector<Couple>::iterator it2 = (*it1)->getIteratorBegin() ; it2 != (*it1)->getIteratorEnd(); ++it2){
            temp = (*it2).getFirst().getId() + " -> " + (*it2).getSecond().getId();
            item = new QListWidgetItem(temp,dockRelationsManager->getListRelations());
        }
    }
}

///Slot permettant de mettre à jour le manager d'archives
void MainWindow::updateArchivesManager(){
    dockArchivesManager->clear();
    QListWidgetItem* item;
    ArchivesManager& am = ArchivesManager::getInstance();
    for(vector<Note*>::iterator it = am.getIteratorBegin(); it != am.getIteratorEnd(); ++it){
        item= new QListWidgetItem((*it)->getTitle(),dockArchivesManager->getListNotes());
    }
}

///Slot permettant de mettre à jour le manager de taches
void MainWindow::updateTaskManager(){
    dockTaskManager->clear();
    QListWidgetItem* item;
    NotesManager& nm = NotesManager::getInstance();
    for(vector<Note*>::iterator it = nm.getIteratorBegin(); it != nm.getIteratorEnd(); ++it){
        if((*it)->getClassName() == "task"){
            Task* t = dynamic_cast<Task*>(*it);
            unsigned int p = t->getPriority();
            QString title = t->getTitle();
            QString showedText = QString::number(p) + ":" + title;
            item = new QListWidgetItem(showedText,dockTaskManager->getListTask());
        }
    }
}

///Slot permettant de fermer l'application sans sauvegarder
void MainWindow::QuitWithoutSaving(){
    QMessageBox msgBox;
    ///Message pour que l'utilateur soit sûr de la fermeture
    msgBox.setText("Voulez vous quitter sans sauvegarder?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    int rep = msgBox.exec();
    ///Si il a choisi de sauvegarder alors on sauvegarde toutes les notes et les relations
    if (rep == QMessageBox::Save) {
          NotesManager& nm = NotesManager::getInstance();
          nm.setFilename("TEMP.xml");
          nm.saveAll();
          RelationsManager& rm = RelationsManager::getInstance();
          rm.setFilename("TEMP2.xml");
          rm.saveAll();
          qApp->quit();
          nm.libererInstance();
          MainWindow::libererInstance();
          Corbeille::libererInstance();
    }
    ///S'il a choisi de ne pas sauvegarder, on libère proprement la mémoire des singletons
    else if (rep == QMessageBox::Discard){
        qApp->quit();
        NotesManager::libererInstance();
        MainWindow::libererInstance();
        Corbeille::libererInstance();
    }
    ///Sinon on annule
    else if (rep == QMessageBox::Cancel){return;}
    else { throw NotesException("Erreur..");}
}

///Slot permettant de charger en mémoire les notes et les relations contenues dans les fichiers TEMP.xml et TEMP2.xml dans l'application
void MainWindow::LoadData(){
    NotesManager& nm = NotesManager::getInstance();
    nm.setFilename("TEMP.xml");
    nm.load();
    RelationsManager& rm = RelationsManager::getInstance();
    rm.setFilename("TEMP2.xml");
    rm.load();
    MainWindow::updateRelationManager();
    MainWindow::updateNotesManager();
}

///Slot permettant de quitter l'application
void MainWindow::QuitApplication(){
    QMessageBox msgBox;
    ///Messae pour mettre en arde l'utilisateur
    msgBox.setText("Est vous sur de sauvegarder ? "
                   "\nLes notes archivées et les notes de la corbeille seront effacées."
                    "\nSi vous voulez les sauvegarder, il faut d'abord les restaurer.");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    int rep = msgBox.exec();
    ///Si l'utilisateur est ok et cliquer sur save alors on sauvegarde tout et on quitte l'appli
    if (rep == QMessageBox::Save) {
        NotesManager& nm = NotesManager::getInstance();
        nm.setFilename("TEMP.xml");
        nm.saveAll();
        RelationsManager& rm = RelationsManager::getInstance();
        rm.setFilename("TEMP2.xml");
        rm.saveAll();
        qApp->quit();
        nm.libererInstance();
        MainWindow::libererInstance();
        Corbeille::libererInstance();
    }
    else if (rep == QMessageBox::Cancel){return;}
    else { throw NotesException("Erreur..");}
}

///slot permettant d'appeler un factory d'un nouvel article
void MainWindow::newArticle(){
    QString type = (QString) "art";
    QString title = (QString)"";
    Note* n = NotesManager::getInstance().getNewNote(title, type);
    NoteEditeur* ne = NotesManager::getInstance().callEditeur(n, type);
    showEditeur(ne);
}

///slot permettant d'appeler un factory d'une nouvelle tache
void MainWindow::newTask(){
    QString type = (QString) "task";
    QString title = (QString)"";
    Note* n = NotesManager::getInstance().getNewNote(title, type);
    NoteEditeur* ne = NotesManager::getInstance().callEditeur(n, type);
    showEditeur(ne);
}

///slot permettant d'appeler un factory d'un nouvel audio
void MainWindow::newAudio(){
    QString type = (QString) "aud";
    QString title = (QString)"";
    Note* n = NotesManager::getInstance().getNewNote(title, type);
    NoteEditeur* ne = NotesManager::getInstance().callEditeur(n, type);
    showEditeur(ne);
}

///slot permettant d'appeler un factory d'une nouvelle image
void MainWindow::newImage(){
    QString type = (QString) "img";
    QString title = (QString)"";
    Note* n = NotesManager::getInstance().getNewNote(title, type);
    NoteEditeur* ne = NotesManager::getInstance().callEditeur(n, type);
    showEditeur(ne);
}

///slot permettant d'appeler un factory d'une nouvelle video
void MainWindow::newVideo(){
    QString type = (QString) "vid";
    QString title = (QString)"";
    Note* n = NotesManager::getInstance().getNewNote(title, type);
    NoteEditeur* ne = NotesManager::getInstance().callEditeur(n, type);
    showEditeur(ne);
}

///Slot permettant d'afficher la corbeille
void MainWindow::showDustbin(){
    myDustbin = new CorbeilleEditeur(this);
    myDustbin->show();
}

///fonction pour afficher RelationsManager
void MainWindow::showRelationsManager(){
    ///Création d'une nouvelle instance de RelationEditeur
    RelationEditeur* re = new RelationEditeur;
    mainRelationEditor = re;
    ///On place la widget dans la partie centrale de l'application
    setCentralWidget(re);
    re->adjustSize();
    re->show();
}
