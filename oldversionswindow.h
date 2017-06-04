#ifndef OLDVERSIONSWINDOW_H
#define OLDVERSIONSWINDOW_H

#include <iostream>
#include <QSet>
#include <QList>
#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QScrollArea>
#include "fonction.h"

class OldVersionsWindow : public QWidget{
    Q_OBJECT
private:
    Note* note;
    QListWidget* list;
    QVBoxLayout* layer;
    QPushButton* close;
    QPushButton* restor;
    QScrollArea* scroller;
public:
    OldVersionsWindow(Note* n, QWidget* parent=0);

public slots :
    void restorNote();
};

#endif // OLDVERSIONSWINDOW_H

