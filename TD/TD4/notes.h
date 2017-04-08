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
    //Constructeurs : paramètres const string & :
    //Référence :
    // - Evite une recopie de l'objet de type string en mémoire (passage
    // const :
    // - Protège l'objet en argument des modifications
    // - Permet la conversion implicite const char* vers string
    // - la classe string possède un constructeur que prend en paramètre (const char *)
    // - une référence non const de type string doit etre initialisée avec un string
    // - ce n'est pas le cas pour une référence const
    // string & a = // string attendu
    // const string & b = "ceciestunconstcharetoile"
    // permet la conversion implicite

    Article(const string& i, const string& ti, const string& te) : id(i),titre(ti), texte(te){};
    //Accesseurs en lecture (getters)
    const string& getId();
    const string& getTexte();
    const string& getTitre();
    //Accesseurs en écriture écrture (setters)
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
    //Le destructeur par défaut généré par le compilateur ne prend pas en charge la libération de la mémoire allouée dynamiquement. Il faut donc définir un destructeur
    ~NotesManager();
    // Le constructeur de reopie/opérateur d'affectation générés par défaut recopie la valeur de chaque attribut
    // 'articles' étant un pointeur , on aboutirait à une situation où 2 objets Notes Managers partagent le même tableau d'articles. Or , la relation,
    //définie entre NotesManager et Article est une composition. Un et un seul NotesManafer est responsable du cycle de vie d'un
    // Article. Un article ne peut donc pas être partagé entre plusieurs Notes Manager. Il faut donc définir le constructeur de
    //copie et l'opérateur d'affectation.
    NotesManager(const NotesManager & m);
    NotesManager & operato =(const NotesManager &m);
    Article& getNewArticle(const string& id);
    Article& getArticle(const string& id);
};

 /*Question 2) :En l'absence de déclaration, le compilateur génère une version par défaut du destructeur, constructeur par recopie et opérateur d'affectation
L'opérateur d'affectation par défaut réalise l'opération d'affectation champ par champ
Le destructeur par défaut réalise, pour chaque objet de la classe, un appel à son destructeur
 Les versions générées par défaut conviennent donc pour la classe Article */
 /* Question 3): Un constructeur est toujours appelé à la création d'une nouvelle instance d'une classe. */
 // Si on déclare un constructeur avec paramètres, le compilateur ne va pas générer un constructeur sans paramètres
// A la définition d'un tableau d'objets, le constructeur sans param est appelé pour instancier chaque objet de ce tabkeau
// Un tel constructeur n'existe pas pour Article. Il n'est donc pas possible de définir un tableau de ce type

// un pointeur n'a pas besoin d'être initialisé. Il est donc possible de créer des tableaux de pointeurs d'objets Article => cette structure pourra être utilisée dans NotesManager


// Fichier notes.cpp

class Tag {
private:
    string name;
    const Article *article;
public:
    Tag (const string &n, const Article &a): name(n), article (&a) {}
    const string &getName() const{return name;}
    const string &getArticle() const {return *article;}
    //Dans le cas d'une duplication, on obtiendra Tag destination qui aura même nom que le Tag source et pointera sur le même
    // Article.
    //Cependant, la relation définie entre Tag et Article est une agrégation. Un Article peut donc être partagé par différents Tag.
    // Pas besoin de redéfinir l'opérateur d'affectation ou le constructeur par recopie.
