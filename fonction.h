#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED

class NotesManager
{
    Article** articles;
    unsigned int nbArticles;
    unsigned int nbMaxArticles;
    void addArticle(Article* a);
    string filename;

    NotesManager():articles(NULL), nbArticles(0),
                   nbMaxArticles(0), filename("tmp.dat"){}

    /// constructeur de recopie
    NotesManager(const NotesManager& n);

    /// destructeur
    ~NotesManager();

    /// surcharge de =
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
            if(isDone())
                throw NotesException("ERROR : fin de la collection");
            currentA++;
            nbRemain--;
        }

    };
    Iterator getIterator() const{
        return Iterator(articles, nbArticles);
    }

    /// Class ConstIterator
    class ConstIterator{
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
    ConstIterator getConstIterator() const{
        return ConstIterator(articles, nbArticles);
    }

/// Class SearchIterator
    class SearchIterator{
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

#endif // FONCTION_H_INCLUDED
