#include <QApplication>
#include <QMessageBox>
#include "fonctions.h"
#include <QFileDialog>
#include <QHBoxLayout>

FenetrePrincipale::FenetrePrincipale(): QWidget()
{
    setFixedSize(600, 120);

    m_boutonProprietes = new QPushButton("Gestion", this);
    m_boutonProprietes->move(40, 50);
    m_boutonVersFenetreAjout = new QPushButton ("Ajout",this);
    m_boutonVersFenetreAjout-> move(40,100);
    layout = new QHBoxLayout;
        layout->addWidget(m_boutonProprietes);
        layout->addWidget(m_boutonVersFenetreAjout);
        this->setLayout(layout);
        QObject::connect(m_boutonVersFenetreAjout, SIGNAL(clicked()), this, SLOT(ouverture()));
        QObject::connect(m_boutonProprietes,SIGNAL(clicked()),this,SLOT(disp()));
       /* QObject::connect(m_boutonVersFenetreAjout, SIGNAL(clicked()), fenetreAjout, SLOT(ouvertureToutesNotes));
        QObject::connect(m_boutonProprietes,SIGNAL(clicked()),fenetre,SLOT(display()));*/
}
void FenetrePrincipale::ouverture(){
    FenetrePrincipale Fenetre;
    Fenetre.setFixedSize(600,150);

}
void FenetrePrincipale::disp(){
    FenetrePrincipale Fenetre;
    Fenetre.setFixedSize(600,150);
    Fenetre.show();
}

/*
//---------------CLASSE FENETRE: Fenetre d'ouverture des propriétés-----------//
Fenetre:: Fenetre() : QWidget()
{
    setFixedSize(600, 120);

    m_boutonOuvertureNote = new QPushButton("Ouverture", this);
    m_boutonOuvertureNote->move(40, 50);
    m_boutonSupprimerNote = new QPushButton ("Suppression",this);
    m_boutonSupprimerNote-> move(40,100);
    layout = new QHBoxLayout;
        layout->addWidget(m_boutonOuvertureNote);
        layout->addWidget(m_boutonSupprimerNote);
        this->setLayout(layout);


    QObject::connect(m_boutonOuvertureNote, SIGNAL(clicked()), this, SLOT(ouvrirFichiers()));
    QObject::connect(m_boutonSupprimerNote,SIGNAL(clicked()),this,SLOT(supprimerFichiers()));
}

void Fenetre::ouvrirFichiers()
{
        int reponse = QMessageBox::question(this, "Ouverture d'un fichier?","O", QMessageBox ::Yes | QMessageBox::No);

        if (reponse == QMessageBox::Yes)
        {
            QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Images (*.png *.gif *.jpg *.jpeg)");
               QMessageBox::information(this, "Fichier", "Vous avez sélectionné :\n" + fichier);
               // INSERER LA FONCTION D'OUVERTURE DU FICHIER
        }
        else if (reponse == QMessageBox::No)//ENREGISTREMENT DE

        {
            QString fichier = QFileDialog::getSaveFileName(this, "Enregistrer un fichier", QString(), "Images (*.png *.gif *.jpg *.jpeg)");
        }
    }
void Fenetre::supprimerFichiers() //AJOUTER LA FONCTION DE SUPPRESSION + ARCHIVAGE
{
    int reponse = QMessageBox::question(this, "Ouverture d'un fichier?","O", QMessageBox ::Yes | QMessageBox::No);

    if (reponse == QMessageBox::Yes)
    {
        QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Images (*.png *.gif *.jpg *.jpeg)");
           QMessageBox::information(this, "Fichier", "Vous avez sélectionné :\n" + fichier);
           // INSERER LA FONCTION D'OUVERTURE DU FICHIER
    }
    else if (reponse == QMessageBox::No)//ENREGISTREMENT DE L
    {
        QString fichier = QFileDialog::getSaveFileName(this, "Enregistrer un fichier", QString(), "Images (*.png *.gif *.jpg *.jpeg)");
    }
}

void Fenetre::display()//je veux creer une fonction qui crée une fenetre.
{
    Fenetre new;
    newe.show().
}
*/
