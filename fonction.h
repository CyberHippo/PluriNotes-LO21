#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED


#include <string>
#include <iostream>
#include <time.h>
using namespace std;

struct date {
 int jour;
 int mois;
 int annee;
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
    Note(const string& id, const string& titre);
    virtual string getId() const { return id; }
	virtual string getTitle() const { return title; }
	virtual void setTitle(const string& t) {title=t;}
	virtual void print() = 0; //fonction virtuelle pure
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
    void print();
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

///Surchage d'op�rateurs
ostream& operator<<(ostream& f, const Article& a);




#endif // FONCTION_H_INCLUDED
