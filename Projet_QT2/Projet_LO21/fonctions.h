#ifndef FONCTIONS_H
#define FONCTIONS_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>

// Idee: -mettre un attribut qui pointe vers une fenetre. mettre une méthode dans la classe que l'on va connect et qui va ouvrir cette nouvelle fenetre + créer via constructeur
class FenetrePrincipale : public QWidget
{
    Q_OBJECT
public:
    FenetrePrincipale();
public slots:
    void ouverture();
    void disp();
private:
    QPushButton *m_boutonProprietes;
    QPushButton *m_boutonVersFenetreAjout;
    QHBoxLayout *layout;
};
/*
class Fenetre : public QWidget
{
    Q_OBJECT
    public:
    Fenetre();

    public slots:
    void ouvrirFichiers();
    void supprimerFichiers();
    void display();

    private:

    QPushButton *m_boutonOuvertureNote;
    QPushButton *m_boutonSupprimerNote;
    QHBoxLayout *layout;
};

class FenetreAjout : public QWidget
{
    Q_OBJECT
public:
    FenetreAjout();
public slots:
    void ouvertureToutesNotes();

};*/

#endif // FONCTIONS_H*/
