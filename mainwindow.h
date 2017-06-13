#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QWidget"
#include <QFileDialog>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QListView>
#include <QFormLayout>
#include <QMdiSubWindow>
#include <QMdiArea>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QFontComboBox>
#include <QMessageBox>
#include <QScrollArea>
#include <QItemSelectionModel>
#include <QKeySequence>
#include <QDockWidget>


#include"fonction.h"
#include "corbeille.h"
#include "corbeilleediteur.h"
#include"noteediteur.h"
#include"notefactory.h"
#include "notemanager.h"
#include "oldversions.h"
#include "relation.h"
#include "notesmanagerwindow.h"
#include "archivesmanager.h"
#include "archivesmanagerwindow.h"
#include "relationediteur.h"
#include "relationsmanagerwindow.h"
#include "ascendanddescendwindow.h"

/// Fenêtre principale de l'application. {singleton}
class MainWindow : public QMainWindow {
    Q_OBJECT
private:

    QWidget* centralArea;
    QGridLayout* centralLayout;
    NoteEditeur* mainEditeur;
    RelationEditeur* mainRelationEditor;
    CorbeilleEditeur *myDustbin;
    QWidget* pageEdition;
    QVBoxLayout* layerEdition;
    NotesManagerWindow* dockNotesManager;
    TaskManagerWindow* dockTaskManager;
    relationsmanagerwindow* dockRelationsManager;
    ArchivesManagerWindow* dockArchivesManager;
    AscendAndDescendWindow* dockAscendDescend;

    ///Constructeur
    MainWindow();
    ///La structure Handler permet de gérer les appels de l'instance unique du singleton ainsi que sa destruction
    struct MWHandler{
        MainWindow* instance;
        MWHandler() : instance(0){}
        ~MWHandler(){if(instance) delete instance; instance = 0;}
    };
    static MWHandler mw_handler;

public:
    ///Fonction permettant de récupérer une référence sur l'instance unique de MainWindow
    static MainWindow& getInstance();
    ///fonction permettant de libérer l'instance unique de MainWindow
    static void libererInstance();
    void showEditeur(NoteEditeur* ne);
    ///Fonction renvoyant l'attribut mainEditeur
    NoteEditeur* getEditeur(){return mainEditeur;}
    ///fonction permettant de changer le mainEditeur en un editeur passé en argument
    void setEditeur(NoteEditeur* ne){mainEditeur = ne;}

signals :
    public slots :
       void showNotesManager();
       void showArchivesManager();
       void showTaskManager();
       void updateNotesManager();
       void updateRelationManager();
       void updateArchivesManager();
       void updateTaskManager();
       void newArticle();
       void newTask();
       void newAudio();
       void newImage();
       void newVideo();
       void showDustbin();
       void QuitApplication();
       void LoadData();
       void QuitWithoutSaving();
       void showRelationsManager();
       void showRelationsManagerActive();
       void showRelationsAscendDescend(Note *n);
};



#endif // MAINWINDOW_H
