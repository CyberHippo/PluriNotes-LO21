#include <QApplication>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "fonctions.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    FenetrePrincipale fenetrePrincipale;
    //Fenetre fenetre;
   // FenetreAjout fenetreAjout;

    fenetrePrincipale.show();

    return app.exec();
}
