#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED


#include <string>
#include <iostream>
#include <time.h>
#include <fstream>
#include <vector>
using namespace std;

///Classe Date (classe utilis� comme une simple structure, on fait expr�s de m�tre les atributs publiques)
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
    string action; //text qui d�finie les actions de la tache
    unsigned int priority;
    date deadline;
    string status;
    Task(const Task& t); //on met le constructeur de recopie en priv�e pour que le gestion des Taches (cr�ation et destruction soit g�r� par le NoteManager
    Task& operator=(const Task& t); //on met le operateur d'affection en priv�e pour les m�me raisons

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

///Classe Multim�dia (classe abstraite)
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
    void print() const = 0; //m�thode virtuelle pure
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
    vector<Note*> notes;
    unsigned int nbNotes;
    unsigned int nbMaxNotes;

    string filename;

    NotesManager();
    NotesManager(const NotesManager& n);     /// constructeur de recopie
    ~NotesManager(); ///destructeur

    ///surcharge de =
    NotesManager& operator=(const NotesManager&);

    ///static NotesManager *instance;
    struct Handler{
        NotesManager* instance;
        Handler() : instance(0){}
        ~Handler(){if(instance) delete instance; instance = 0;}
    };
    static Handler handler;

public:
    void addNote(Note* n);
    Note& getNewNote(const string& id);
    Article& getNewArticle(const string& id);
    Note& getNote(const string& id);
    Article& getArticle(const string& id);
    void showNote (const Note& note) const;
    void load(const string& f);
	void save() const;
    static NotesManager& getInstance();
    static void libererInstance();
    void showAll() const;

    ///D�j� inclus dans "vector"
    /*
    /// Class Iterator
    class Iterator{
        friend class NotesManager;
        Note** currentN;
        int nbRemain;
        Iterator(Note** n, int nb): currentN(n), nbRemain(nb){}
      public:
        bool isDone()const {return nbRemain == 0;}
        Note& current() const{ return **currentN;}
        void next(){
            if(isDone()){throw NotesException("ERROR : fin de la collection");}
            currentN++;
            nbRemain--;
        }

    };
    Iterator getIterator() const{
        return Iterator(notes, nbNotes);
    }

    /// Class ConstIterator
    class ConstIterator{
    private:
        friend class NotesManager;
        Note** currentN;
        int nbRemain;
        ConstIterator(Note** n, int nb): currentN(n), nbRemain(nb){}
      public:
        bool isDone()const {return nbRemain == 0;}
        const Note& current() const{ return **currentN;}
        void next(){
            if(isDone())
                throw NotesException("ERROR : fin de la collection");
            currentN++;
            nbRemain--;
        }

    };
    ConstIterator getConstIterator() const{ return ConstIterator(notes, nbNotes);}
    */

/// Class SearchIterator
/*    class SearchIterator{
    private:
        friend class NotesManager;
        Note** currentN;
        int nbRemain;
        string toFind;
        SearchIterator(Note** n, int nb, string tf): currentN(n), nbRemain(nb), toFind(tf){
            while(nbRemain > 0 && (**currentN).getText().find(toFind) == string::npos){
                currentN++;
                nbRemain--;
            }
        }
      public:
        bool isDone()const {return nbRemain == 0;}
        const Note& current() const{ return **currentN;}
        void next(){
            if(isDone())
                throw NotesException("ERROR : fin de la collection");
            currentN++;
            nbRemain--;
            while(nbRemain > 0 && (**currentN).getText().find(toFind) == string::npos){
                currentN++;
                nbRemain--;
            }
        }

    };
    SearchIterator getSearchIterator(string tf) const{
        return SearchIterator(notes, nbNotes, tf);
    }

    /// Class iterator
    class iterator{
        friend class NotesManager;
        Note** currentN;

        iterator(Note** n): currentN(n){}

      public:
        bool operator!=(iterator it) const {return currentN != it.currentN;}
        Note& operator*() const {return **currentN;}
        iterator& operator++() {currentN++; return *this;}

    };
    iterator begin() const{ return iterator(notes); }
    iterator end() const{return iterator(notes + nbNotes);}*/

};

///Surchage d'op�rateurs
ostream& operator<<(ostream& f, const Note& n);




#endif // FONCTION_H_INCLUDED
