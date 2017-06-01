#include <QDebug>
#include <QApplication>
#include <QtWidgets>
#include "fenetres.h"
#include <iostream>
#include <fstream>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

   Principale fenetre;
    fenetre.show();
            QFile file(":/default.txt");
            file.open(QIODevice::ReadOnly);

            TreeModel model(file.readAll());

            file.close();

            QTreeView view;
            view.setModel(&model);
            view.setWindowTitle(QObject::tr("Simple Tree Model"));
            view.show();
    return app.exec();
}
