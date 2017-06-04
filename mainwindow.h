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
    ArchivesManagerWindow* dockArchivesManager;


    MainWindow();
    struct MWHandler{
        MainWindow* instance;
        MWHandler() : instance(0){}
        ~MWHandler(){if(instance) delete instance; instance = 0;}
    };
    static MWHandler mw_handler;
public:
    static MainWindow& getInstance();
    static void libererInstance();
    void showEditeur(NoteEditeur* ne);
    NoteEditeur* getEditeur(){return mainEditeur;}
    void setEditeur(NoteEditeur* ne){mainEditeur = ne;}



signals :
    public slots :
       void showNotesManager();
       void showArchivesManager();
       void updateNotesManager();
       void newArticle();
       void newTask();
       void newAudio();
       void newImage();
       void newVideo();
       void showDustbin();
       void QuitApplication();
       void QuitWithoutSaving();
       void showRelationsManager();
       //NoteEditeur* getNewEditeur(Note* n, QString& type);
};



#endif // MAINWINDOW_H

