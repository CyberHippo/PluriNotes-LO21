#include "mainwindow.h"
#include <QKeySequence>
#include <QApplication> // if needed


MainWindow::MainWindow () {
    setWindowTitle("PluriNotes");
    setWindowState(Qt::WindowMaximized);
    centralArea = new QWidget;
    setCentralWidget(centralArea);
    centralLayout = new QGridLayout;
    centralArea->setLayout(centralLayout);

    QMenu* menuNotesManager = new QMenu;
    menuNotesManager = menuBar()->addMenu("&NotesManager");

    QMenu* menuNote = new QMenu;
    menuNote = menuBar()->addMenu("&Note");
    QMenu* createNotes = menuNote->addMenu("&Nouveau");

    QMenu* menuEdition = new QMenu;
    menuEdition = menuBar()->addMenu("&Edition");

    QMenu* menuDustbin = new QMenu;
    menuDustbin = menuBar()->addMenu("&Corbeille");

    //Dans menu NotesManager
    QAction* showNotesManager = new QAction("Afficher", this);
    menuNotesManager->addAction(showNotesManager);


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


    //Dans le menu Corbeille
    QAction* showDustbin = new QAction("&Afficher la corbeille", this);
    menuDustbin->addAction(showDustbin);

    //Raccourci clavier pour quitter
    //QAction* quit = new QAction("&Quitter", this);
    //quit->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));

    //Dans menu NotesManager
    QAction* QuitApplication = new QAction("Quitter", this);
    menuNotesManager->addAction(QuitApplication);


    // Connexions SIGNAL/SLOTS
    QObject::connect(newArticle, SIGNAL(triggered()), this, SLOT(newArticle()));
    QObject::connect(newTask, SIGNAL(triggered()), this, SLOT(newTask()));
    QObject::connect(newAudio, SIGNAL(triggered()), this, SLOT(newAudio()));
    QObject::connect(newImage, SIGNAL(triggered()), this, SLOT(newImage()));
    QObject::connect(newVideo, SIGNAL(triggered()), this, SLOT(newVideo()));
    QObject::connect(showDustbin, SIGNAL(triggered()), this, SLOT(showDustbin()));
    QObject::connect(showNotesManager, SIGNAL(triggered()), this, SLOT(showNotesManager()));
    QObject::connect(QuitApplication, SIGNAL(triggered()), this, SLOT(QuitApplication()));
    //QObject::connect(quit, SIGNAL(triggered()), this, SLOT(close()));

}

void MainWindow::showEditeur(NoteEditeur* ne) {
    mainEditeur = ne;
    setCentralWidget(ne);
    ne->adjustSize();
    ne->show();
}


void MainWindow::showNotesManager(){
    dockNotesManager = new NotesManagerWindow(tr("Notes Manager"), this);
    dockNotesManager->setAllowedAreas(Qt::LeftDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea, dockNotesManager);
}


void MainWindow::QuitApplication(){
    NotesManager& nm = NotesManager::getInstance();
    nm.setFilename("TEMP.xml");
    nm.saveAll();
    //app.quit();
    qApp->quit();
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
    myDustbin = new CorbeilleEditeur;
    myDustbin->show();
}
