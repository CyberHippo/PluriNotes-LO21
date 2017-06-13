#include <QDebug>
#include <QApplication>
#include <QtWidgets>
#include <iostream>
#include <fstream>
#include <QString>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>



#include "fonction.h"
#include "notemanager.h"
#include "relation.h"
#include "notefactory.h"
#include "noteediteur.h"
#include "corbeille.h"
#include "corbeilleediteur.h"
#include "mainwindow.h"
#include "notesmanagerwindow.h"
#include "relationediteur.h"
#include "relationsmanagerwindow.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow& mw = MainWindow::getInstance();
    mw.showNotesManager();
    mw.showTaskManager();
    mw.showRelationsManagerActive();
    mw.showArchivesManager();
    mw.show();

    return app.exec();
}
