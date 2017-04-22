#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED


#include <string>
#include <iostream>
#include <time.h>
#include <fstream>
using namespace std;

///Classe Date (classe utilisé comme une simple structure, on fait exprès de mêtre les atributs publiques)
class date {
public:
 date(int j = 0, int m = 0, int a = 0);
 int jour;
 int mois;
 int annee;
 void print() const;
};

///Class NotesException
class NotesException{
private:
	string info;
public:
	NotesException(const string& message):info(message){}
	string getInfo() const { return info; }
};

///Class Note
class Note { //class abstraite
protected:
    string id;
	string title;
	date creation;
	date last_modif;

public:
    Note(const string& id, const string& titre) : id(id), title(titre) {}
    virtual ~Note();
    virtual string getId() const { return id; }
	virtual string getTitle() const { return title; }
	virtual void setTitle(const string& t) {title=t;}
	virtual void print() const = 0; //fonction virtuelle pure
};

///Class Article
class Article : public Note {
private:
	string text;
    Article(const Article & a);
    Article & operator=(const Article & a);
public:
	Article(const string& id, const string& titre, const string& text);
	Article(const Note& N1, const string& text);
	//Accesseurs:
	string getText() const { return text; }
    void setText(const string& t) {text=t;}
    void print() const;
    ~Article();
};

///Class Task
class Task : public Note {
private:
    string action; //text qui définie les actions de la tache
    unsigned int priority;
    date deadline;
    string status;
    Task(const Task& t); //on met le constructeur de recopie en privée pour que le gestion des Taches (création et destruction soit géré par le NoteManager
    Task& operator=(const Task& t); //on met le operateur d'affection en privée pour les même raisons

public:
    Task(const string& id, const string& title, const string& act, const string& s, const date& d, const unsigned int& p=0);
    string getAction() const {return action;}
    unsigned int getPriority() const {return priority;}
    date getDeadline() const {return deadline;}
    string getStatus() const {return status;}
    void setAction(const string& act) {action = act;}
    void setPriority(const unsigned int& p) {priority = p;}
    void setDeadline(const date& d) {deadline = d;}
    void setStatus(const string& s) {status = s;}
    void print() const;
    ~Task();
};

///Classe Multimédia (classe abstraite)
class Multimedia : public Note {
protected:
    string description;
    string imageFilename; //Pour l'instant je mets juste un nom de fichier
    Multimedia(const Multimedia& m);
    Multimedia& operator=(const Multimedia& m);

public:
    Multimedia(const string& id, const string& title, const string& desc, const string& imgF);
    string getDescription() const {return description;}
    string getImageFilename() const {return imageFilename;}
    void setDescription(const string& desc) {description = desc;}
    void setImageFilename(const string& imgF) {imageFilename = imgF;}
    void print() const = 0; //méthode virtuelle pure
    virtual ~Multimedia();
};

///Classe Image
class Image : public Multimedia {
public:
    Image(const string& id, const string& title, const string& desc, const string& imgF) : Multimedia(id,title,desc,imgF){}
    void print() const;
    ~Image();

};

///Classe Audio
class Audio : public Multimedia {
public:
    Audio(const string& id, const string& title, const string& desc, const string& imgF) : Multimedia(id,title,desc,imgF){}
    void print() const;
    ~Audio();
};

///Classe Video
class Video : public Multimedia {
public:
    Video(const string& id, const string& title, const string& desc, const string& imgF) : Multimedia(id,title,desc,imgF){}
    void print() const;
    ~Video();
};

///Class Notes Manager
class NotesManager
{
private:
    Article** articles;
    unsigned int nbArticles;
    unsigned int nbMaxArticles;
    void addArticle(Article* a);
    string filename;

    NotesManager();
    NotesManager(const NotesManager& n);     /// constructeur de recopie
    ~NotesManager(); ///destructeur

    ///surcharge de =
    NotesManager& operator=(const NotesManager&);

    ///static NotesManager *instance;
    struct Handler{
        NotesManager* instance;
        Handler() : instance(nullptr){}
        ~Handler(){if(instance) delete instance; instance = nullptr;}
    };
    static Handler handler;

public:
    Article& getNewArticle(const string& id);
    Article& getArticle(const string& id);
    void load(const string& f);
	void save() const;
    static NotesManager& getInstance();
    static void libererInstance();

    /// Class Iterator
    class Iterator{
        friend class NotesManager;
        Article** currentA;
        int nbRemain;
        Iterator(Article**a, int nb): currentA(a), nbRemain(nb){}
      public:
        bool isDone()const {return nbRemain == 0;}
        Article& current() const{ return **currentA;}
        void next(){
            if(isDone()){throw NotesException("ERROR : fin de la collection");}
            currentA++;
            nbRemain--;
        }

    };
    Iterator getIterator() const{
        return Iterator(articles, nbArticles);
    }

    /// Class ConstIterator
    class ConstIterator{
    private:
        friend class NotesManager;
        Article** currentA;
        int nbRemain;
        ConstIterator(Article**a, int nb): currentA(a), nbRemain(nb){}
      public:
        bool isDone()const {return nbRemain == 0;}
        const Article& current() const{ return **currentA;}
        void next(){
            if(isDone())
                throw NotesException("ERROR : fin de la collection");
            currentA++;
            nbRemain--;
        }

    };
    ConstIterator getConstIterator() const{ return ConstIterator(articles, nbArticles);}


/// Class SearchIterator
    class SearchIterator{
    private:
        friend class NotesManager;
        Article** currentA;
        int nbRemain;
        string toFind;
        SearchIterator(Article**a, int nb, string tf): currentA(a), nbRemain(nb), toFind(tf){
            while(nbRemain > 0 && (**currentA).getText().find(toFind) == string::npos){
                currentA++;
                nbRemain--;
            }
        }
      public:
        bool isDone()const {return nbRemain == 0;}
        const Article& current() const{ return **currentA;}
        void next(){
            if(isDone())
                throw NotesException("ERROR : fin de la collection");
            currentA++;
            nbRemain--;
            while(nbRemain > 0 && (**currentA).getText().find(toFind) == string::npos){
                currentA++;
                nbRemain--;
            }
        }

    };
    SearchIterator getSearchIterator(string tf) const{
        return SearchIterator(articles, nbArticles, tf);
    }

    /// Class iterator
    class iterator{
        friend class NotesManager;
        Article** currentA;

        iterator(Article**a): currentA(a){}

      public:
        bool operator!=(iterator it) const {return currentA != it.currentA;}
        Article& operator*() const {return **currentA;}
        iterator& operator++() {currentA++; return *this;}

    };
    iterator begin() const{ return iterator(articles); }
    iterator end() const{return iterator(articles + nbArticles);}

};

///Surchage d'opérateurs
ostream& operator<<(ostream& f, const Article& a);




#endif // FONCTION_H_INCLUDED
