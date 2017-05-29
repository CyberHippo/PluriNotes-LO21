#include "FenPrincipale.h"
#include <QTextEdit>
FenPrincipale::FenPrincipale()
{
    QWidget *zoneCentrale = new QWidget; //on crée un widget zone centrale

    QLineEdit *ID = new QLineEdit;      //création des widgets a remplir
    QLineEdit *titre = new QLineEdit;
    QTextEdit *texte = new QTextEdit;

    QFormLayout *layout = new QFormLayout;          //layout de forme qui va être mis en zone centrale
    layout->addRow("ID de la note", ID);
    layout->addRow("Titre de la note", titre);
    layout->addRow("Texte", texte);
    zoneCentrale->setLayout(layout);
    setCentralWidget(zoneCentrale);
    //Barre de menus avec les diverses options
    QMenu *menuFichier = menuBar()->addMenu("&Fichier");        //création de la barre de menu
    QAction *actionQuitter = new QAction("&Quitter", this);
        menuFichier->addAction(actionQuitter);
        QAction *actionEnregistrer = new QAction("&Enregistrer", this);
            menuFichier->addAction(actionEnregistrer);

        QMenu *menuEdition = menuBar()->addMenu("&Edition");
        QAction *actionModifier = new QAction("&Modifier", this);
            menuEdition->addAction(actionModifier);
        QMenu *menuAffichage = menuBar()->addMenu("&Affichage");
        QAction *actionNotesActives = new QAction("&NotesActives", this);
            menuAffichage->addAction(actionNotesActives);

        // Gestion des signaux_slots
        connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));   //je voudrais le relier à nos méthodes
        connect(actionEnregistrer, SIGNAL(triggered()), qApp, SLOT(save()));
        connect(actionNotesActives, SIGNAL(triggered()),qApp,SLOT(quit())); //il faut rajouter des slot
}
//Pour Notes Actives, il faut lui envoyer la méthode qui affiche le listing des Notes
/*
void FenPrincipale::save()const{
        std::ofstream fout(filename.c_str());
        for(unsigned int i=0; i<nbNotes; i++){
            fout<<notes[i];
        }
        fout.close();
    }
}
*/
