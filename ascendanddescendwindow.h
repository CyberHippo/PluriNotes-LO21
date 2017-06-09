#ifndef ASCENDANDDESCENDWINDOW_H
#define ASCENDANDDESCENDWINDOW_H

#include <QDockWidget>
#include <QWidget>
#include <QListWidget>

#include "fonction.h"

///Fenêtre d'affichage des relations
class AscendAndDescendWindow : public QDockWidget {
   Q_OBJECT
private:
    QListWidget* listRelations;
public:
    AscendAndDescendWindow(Note* n, QString title, QWidget* parent = 0);
signals :
    public slots :
};

#endif // ASCENDANDDESCENDWINDOW_H
