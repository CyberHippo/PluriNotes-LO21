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

class MainWindow : public QMainWindow {
    Q_OBJECT
private:
    QWidget* centralArea;
    QGridLayout* centralLayout;
    NoteEditeur* mainEditeur;
    CorbeilleEditeur *myDustbin;
    QWidget* pageEdition;
    QVBoxLayout* layerEdition;
    QDockWidget* dockNotesManager;
public:
    MainWindow();
    void showEditeur(NoteEditeur* ne);


signals :
    private slots :
       void showNotesManager();
       void newArticle();
       void newTask();
       void newAudio();
       void newImage();
       void newVideo();
       void showDustbin();
       //NoteEditeur* getNewEditeur(Note* n, QString& type);
};



#endif // MAINWINDOW_H

