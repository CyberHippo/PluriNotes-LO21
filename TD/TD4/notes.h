// Fichier notes.h


#include <string>
#include <iostream>

using namespace std;

class NotesException{
public:
    NotesException(const string& message):info(message){}
    string getInfo() const {return info;}
private:
    string info;
};


class Article{
private:
    string id;
    string titre;
    string texte;
public:
    //Constructeurs : param�tres const string & :
    //R�f�rence :
    // - Evite une recopie de l'objet de type string en m�moire (passage
    // const :
    // - Prot�ge l'objet en argument des modifications
    // - Permet la conversion implicite const char* vers string
    // - la classe string poss�de un constructeur que prend en param�tre (const char *)
    // - une r�f�rence non const de type string doit etre initialis�e avec un string
    // - ce n'est pas le cas pour une r�f�rence const
    // string & a = // string attendu
    // const string & b = "ceciestunconstcharetoile"
    // permet la conversion implicite

    Article(const string& i, const string& ti, const string& te) : id(i),titre(ti), texte(te){};
    //Accesseurs en lecture (getters)
    const string& getId();
    const string& getTexte();
    const string& getTitre();
    //Accesseurs en �criture �crture (setters)
    void setTitre(const string & t) {titre = t;}
    void setTexte(const string & t) {texte = t;}
};

class NotesManager {
    private:
    Article** articles;
    unsigned int nbArticles;
    unsigned int nbMaxArticles;
    void addArticle(Article* a);
    string filename;
public:
    NotesManager();
    //La classe NotesManager est responsable du cycle de vie des objets Articles (composition)
    //Le destructeur par d�faut g�n�r� par le compilateur ne prend pas en charge la lib�ration de la m�moire allou�e dynamiquement. Il faut donc d�finir un destructeur
    ~NotesManager();
    // Le constructeur de reopie/op�rateur d'affectation g�n�r�s par d�faut recopie la valeur de chaque attribut
    // 'articles' �tant un pointeur , on aboutirait � une situation o� 2 objets Notes Managers partagent le m�me tableau d'articles. Or , la relation,
    //d�finie entre NotesManager et Article est une composition. Un et un seul NotesManafer est responsable du cycle de vie d'un
    // Article. Un article ne peut donc pas �tre partag� entre plusieurs Notes Manager. Il faut donc d�finir le constructeur de
    //copie et l'op�rateur d'affectation.
    NotesManager(const NotesManager & m);
    NotesManager & operato =(const NotesManager &m);
    Article& getNewArticle(const string& id);
    Article& getArticle(const string& id);
};

 /*Question 2) :En l'absence de d�claration, le compilateur g�n�re une version par d�faut du destructeur, constructeur par recopie et op�rateur d'affectation
L'op�rateur d'affectation par d�faut r�alise l'op�ration d'affectation champ par champ
Le destructeur par d�faut r�alise, pour chaque objet de la classe, un appel � son destructeur
 Les versions g�n�r�es par d�faut conviennent donc pour la classe Article */
 /* Question 3): Un constructeur est toujours appel� � la cr�ation d'une nouvelle instance d'une classe. */
 // Si on d�clare un constructeur avec param�tres, le compilateur ne va pas g�n�rer un constructeur sans param�tres
// A la d�finition d'un tableau d'objets, le constructeur sans param est appel� pour instancier chaque objet de ce tabkeau
// Un tel constructeur n'existe pas pour Article. Il n'est donc pas possible de d�finir un tableau de ce type

// un pointeur n'a pas besoin d'�tre initialis�. Il est donc possible de cr�er des tableaux de pointeurs d'objets Article => cette structure pourra �tre utilis�e dans NotesManager


// Fichier notes.cpp

class Tag {
private:
    string name;
    const Article *article;
public:
    Tag (const string &n, const Article &a): name(n), article (&a) {}
    const string &getName() const{return name;}
    const string &getArticle() const {return *article;}
    //Dans le cas d'une duplication, on obtiendra Tag destination qui aura m�me nom que le Tag source et pointera sur le m�me
    // Article.
    //Cependant, la relation d�finie entre Tag et Article est une agr�gation. Un Article peut donc �tre partag� par diff�rents Tag.
    // Pas besoin de red�finir l'op�rateur d'affectation ou le constructeur par recopie.
