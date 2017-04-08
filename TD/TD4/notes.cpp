#include"notes.h"
#include <iostream>

ostream& operator << (ostream &f, const Article &a){
    f << a.getId () << endl;
    f<< a.getTitle() << endl;
    f <<a.getText() << endl;
    return f;
    }   // Pourquoi on retourne f? Cela nous permet d'effectuer des op�rations en cascade


NotesManager:: NotesManager (): articles(0),nbArticles(0),nbMaxArticles(0),filename("tmp.dat") {}
NotesManager:: ~NotesManager() {
//Lib�ration de la m�moire allou�e dynamiquement � chaque article
for (unsigned int i= 0; i< nbArticles; i++)
    {
        delete articles[i];
    }
    //Lib�ration de la m�moire allou�e dynamiquement au tableau de pointeurs "articles"
    delete []articles ;
}

Article &NotesManager :: getNewArticle(const string &id) {
    //Cr�ation de l'article avec titre et texte vide
    Article *a = new Article (ide, "","");
    //R�f�rencer l'article dans le tableau "articles" est une t�che laiss�e � la m�thode priv�e addArticle
    addArticle (a);
   return *a  //La fonction renvoie une r�f�rence vers l'article qui a �t� cr�e => vers a
   //a c'est la valeur, pas le pointeur
    }


void NotesManager::addArticle(Article *a){
//verifier que l'id n'existe pas d�j� dans le tableau (et leve une exception s'il existe)
//agrandit l'espace m�moire si n�c�ssaire pour article
//Stocke l'adresse du nouvel article dans le tableau "articles"
for(unsigned int i= 0 ; i<nbArticles;i++){
    if (articles[i]->getId() == a->getId()){
        throw NotesException ("il existe d�j� un article avec cet id..");
    }
}
//agrandit l'espace m�moire si n�cessaire pour "articles"
if (nbArticles ==nbMaxArticles) {
    //Agrandit l'espace m�moire
    nbMaxArticles+=5;
    //Alloue de la m�moire pour stocker les pointeurs vers les articles
    Article ** newArticles = new Article*[nbMaxArticles];
    //Recopie les adresses des articles depuis l'ancien tableau vers le nouveau
    for(unsigned int i=0;i<nbArticles;i++){
        newArticles[i] = articles[i];
    }
    //Lib�re l'espace m�moire allou� � l'ancien tableau
    delete[] articles;
    //Le pointeur permet d�sormais d'acc�der au nouveau tableau
    articles = newArticles;
    // Stocker l'adresse du nouvel article dans le tableau "articles"
    articles[nbArticles++]=a;

}

NotesManager ::~NotesManager() {
//Lib�ration de la m�moire allou�e dynamiquement � chaque article
for (unsigned int i=0; i< nbArticles; i++){
    delete articles[i];
}
//Lib�ration de la m�moire allou�e dynamiquement au tableau de pointeurs "articles"
delete[]articles;
}

NotesManager::NotesManager(const NotesManager &m):
    articles (nex Article*[m.nbArticles]),
    nbArticles (m.nbArticles),
    nbMaxArticles (m.nbArticles),
    filename (m.filename) {
    for(unsigned int i=0; i< nbArticles ; i++){
        articles [i] = new Article(*m.articles[i]);
    }
    }


NotesManager & NotesManager::operator=(const NotesManager & m){
    if(this!=&m){   //Contr�le de non auto-affectation

        Article** newarticles = new Article*[m.nbArticles];//Creation du tableau contenant l'adresse des articles
        for(unsigned int i=0;i<m.nbArticles;i++){
            newarticles[i] = new Article(*m.articles[i]);
        }
        for(unsigned int i=0;i<m.nbArticles;i++){
            //Supprime les anciens articles
            delete articles[i];
        }
        //supprime l'ancien tableau
        delete[] articles;
        articles = newarticles;
        nbArticles = m.nbArticles;
        nbMaxArticles = m.nbMaxArticles;
        filename = m.filename;

        return newarticles; //pas sur
    }
