#ifndef RELATIONSMANAGERWINDOW_H
#define RELATIONSMANAGERWINDOW_H
#include <QDockWidget>
#include <QWidget>
#include <QListWidget>

class relationsmanagerwindow : public QDockWidget {
   Q_OBJECT
private:
    QListWidget* listRelations;
public:
    relationsmanagerwindow(QString title, QWidget* parent = 0);
    QListWidget* getListRelations(){return listRelations;}
    void clear(){listRelations->clear();}
signals :
    public slots :
//void DeleteRelation();
};


#endif // RELATIONSMANAGERWINDOW_H
