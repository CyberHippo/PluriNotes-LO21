#include "mainwindow.h"
#include "relationediteur.h"
#include <QKeySequence>
#include <QApplication>
#include <QMessageBox>

MainWindow::MWHandler MainWindow::mw_handler=MWHandler();

MainWindow& MainWindow::getInstance() {
  // Si le pointeur vers l'instance unique pointe vers 0
  if(!mw_handler.instance) {
    mw_handler.instance=new MainWindow;
  }
  // Retour par ref vers l'instance unique
  return *mw_handler.instance;
}

void MainWindow::libererInstance() {
  // Liberation de la memoire allouee a l'instance unique
  delete mw_handler.instance;
  // Repasse le pointeur a null/nullptr/0 pour que le prochain appel a getInstance recree bien une instance
  mw_handler.instance=0;
}


MainWindow::MainWindow () {
    setWindowTitle("PluriNotes");
    setWindowState(Qt::WindowMaximized);
    centralArea = new QWidget;
    setCentralWidget(centralArea);
    centralLayout = new QGridLayout;
    centralArea->setLayout(centralLayout);

    QMenu* pluriNotes = new QMenu;
    pluriNotes = menuBar()->addMenu("&PluriNotes");

    QMenu* managers = new QMenu;
    managers = menuBar()->addMenu("&Managers");

    QMenu* menuNotesManager = new QMenu;
    menuNotesManager = managers->addMenu("&NotesManager");

    QMenu* menuNote = new QMenu;
    menuNote = menuBar()->addMenu("&Note");
    QMenu* createNotes = menuNote->addMenu("&Nouveau");

    QMenu* menuEdition = new QMenu;
    menuEdition = menuBar()->addMenu("&Edition");

    QMenu* menuRelationsManager = new QMenu;
    menuRelationsManager = managers->addMenu("&RelationsManager");

    QMenu* menuArchivesManager = managers->addMenu("&ArchivesManager");

    QMenu* menuDustbin = new QMenu;
    menuDustbin = menuBar()->addMenu("&Corbeille");

    //Dans menu PluriNotes
    QAction* save = new QAction("Save", this);
    pluriNotes->addAction(save);
    QAction* load = new QAction("Load", this);
    pluriNotes->addAction(load);
    QAction* close = new QAction("Close App", this);
    pluriNotes->addAction(close);

    //Dans menu NotesManager
    QAction* showNotesManager = new QAction("Afficher", this);
    menuNotesManager->addAction(showNotesManager);
    QAction* updateNotesManager =  new QAction("Mise à jour", this);
    menuNotesManager->addAction(updateNotesManager);


    //Dans menu Note->Nouveau
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

    //Dans menu Edition
    QAction* undo = new QAction("&Annuler", this);
    menuEdition->addAction(undo);
    QAction* redo = new QAction("&Retablir", this);
    menuEdition->addAction(redo);

    //Dans menu RelationsManager
    QAction* openRelationsEditor = new QAction("&Editer", this);
    menuRelationsManager->addAction(openRelationsEditor);
    QAction* openRelationsManager = new QAction("&Afficher", this);
    menuRelationsManager->addAction(openRelationsManager);

    //Dans menu ArchivesManager
    QAction* showArchivesManager = new QAction("&Afficher", this);
    menuArchivesManager->addAction(showArchivesManager);

    //Dans le menu Corbeille
    QAction* showDustbin = new QAction("&Afficher la corbeille", this);
    menuDustbin->addAction(showDustbin);

    //Raccourci clavier pour quitter
    //QAction* quit = new QAction("&Quitter", this);
    //quit->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));



    // Connexions SIGNAL/SLOTS
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



void MainWindow::showEditeur(NoteEditeur* ne) {
    mainEditeur = ne;
    setCentralWidget(ne);
    ne->adjustSize();
    ne->show();
}


void MainWindow::showNotesManager(){
    dockNotesManager = new NotesManagerWindow(tr("Notes Actives"), this);
    dockNotesManager->setAllowedAreas(Qt::LeftDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea, dockNotesManager);
}

void MainWindow::showRelationsManagerActive(){
    dockRelationsManager = new relationsmanagerwindow(tr("Relations Actives"), this);
    dockRelationsManager->setAllowedAreas(Qt::RightDockWidgetArea);
    addDockWidget(Qt::RightDockWidgetArea, dockRelationsManager);
}

void MainWindow::showRelationsAscendDescend(Note* n){
    dockAscendDescend = new AscendAndDescendWindow(n, tr("Ascendants & Descendants"), this);
    dockAscendDescend->setAllowedAreas(Qt::RightDockWidgetArea);
    addDockWidget(Qt::RightDockWidgetArea, dockAscendDescend);
}

void MainWindow::showArchivesManager(){
    dockArchivesManager = new ArchivesManagerWindow(tr("Notes Archivées"), this);
    dockArchivesManager->setAllowedAreas(Qt::LeftDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea, dockArchivesManager);
}




void MainWindow::updateNotesManager(){
    dockNotesManager->close();
    showNotesManager();
}


void MainWindow::QuitWithoutSaving(){
    QMessageBox msgBox;
    msgBox.setText("Voulez vous quitter sans sauvegarder?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    int rep = msgBox.exec();
    if (rep == QMessageBox::Save) {
          NotesManager& nm = NotesManager::getInstance();
          nm.setFilename("TEMP.xml");
          nm.saveAll();
          qApp->quit();
          nm.libererInstance();
          MainWindow::libererInstance();
          Corbeille::libererInstance();
    }
    else if (rep == QMessageBox::Discard){
        qApp->quit();
        NotesManager::libererInstance();
        MainWindow::libererInstance();
        Corbeille::libererInstance();
    }
    else if (rep == QMessageBox::Cancel){return;}
    else { throw NotesException("Erreur..");}
}

void MainWindow::LoadData(){
    NotesManager& nm = NotesManager::getInstance();
    nm.setFilename("TEMP.xml");
    nm.load();
}

void MainWindow::QuitApplication(){
    NotesManager& nm = NotesManager::getInstance();
    nm.setFilename("TEMP.xml");
    nm.saveAll();
    qApp->quit();
    nm.libererInstance();
    MainWindow::libererInstance();
    Corbeille::libererInstance();
}

void MainWindow::newArticle(){
    QString type = (QString) "art";
    QString title = (QString)"";
    Note* n = NotesManager::getInstance().getNewNote(title, type);
    NoteEditeur* ne = NotesManager::getInstance().callEditeur(n, type);
    showEditeur(ne);
}

void MainWindow::newTask(){
    QString type = (QString) "task";
    QString title = (QString)"";
    Note* n = NotesManager::getInstance().getNewNote(title, type);
    NoteEditeur* ne = NotesManager::getInstance().callEditeur(n, type);
    showEditeur(ne);
}

void MainWindow::newAudio(){
    QString type = (QString) "aud";
    QString title = (QString)"";
    Note* n = NotesManager::getInstance().getNewNote(title, type);
    NoteEditeur* ne = NotesManager::getInstance().callEditeur(n, type);
    showEditeur(ne);
}

void MainWindow::newImage(){
    QString type = (QString) "img";
    QString title = (QString)"";
    Note* n = NotesManager::getInstance().getNewNote(title, type);
    NoteEditeur* ne = NotesManager::getInstance().callEditeur(n, type);
    showEditeur(ne);
}

void MainWindow::newVideo(){
    QString type = (QString) "vid";
    QString title = (QString)"";
    Note* n = NotesManager::getInstance().getNewNote(title, type);
    NoteEditeur* ne = NotesManager::getInstance().callEditeur(n, type);
    showEditeur(ne);
}

void MainWindow::showDustbin(){
    myDustbin = new CorbeilleEditeur(this);
    myDustbin->show();
}

void MainWindow::showRelationsManager(){
    RelationEditeur* re = new RelationEditeur;
    mainRelationEditor = re;
    setCentralWidget(re);
    re->adjustSize();
    re->show();
}
