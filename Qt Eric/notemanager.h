#ifndef NOTEMANAGER_H
#define NOTEMANAGER_H

#include "fonction.h"

///Class Notes Manager
class NotesManager
{
private:
    vector<Note*> notes;
    unsigned int nbNotes;
    unsigned int nbMaxNotes;
    mutable QString filename;

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
    Note* getNewNote(QString& title,QString& type);
    void callEditeur(Note* n, QString& type);
    //Article& getNewArticle(const QString& id);
    Note& getNote(const QString& id);
    //Article& getArticle(const QString& id);
    void showNote (const Note& note) const;
    //void load(); // load notes from file filename
    //void save() const; // save notes in file filename
    void saveNote(Note& n);
    static NotesManager& getInstance();
    static void libererInstance();
    void showAll() const;
    void deleteNote(QString id);
    //void deleteNote(Note* n);
    void editNote(QString id); //a developper
    void showOldNotes(QString id);
    void restaurerNote(QString id, QString title);
    QString getFilename() const { return filename; }
    void setFilename(const QString& f) { filename=f; }

/*/// Class SearchIterator
// La classe search iterator ne fonctionne que pour les Articles car ce sont les seuls qui ont un corps de text.
  class SearchIterator{
    private:
        //friend class NotesManager;
        string toFind;
    public:
        SearchIterator(string tf): toFind(tf){}
        Article* SearchTextArticle(const string& s){
            NotesManager& nm = NotesManager::getInstance();
            for (vector<Note*>::iterator it = nm.notes.begin() ; it != nm.notes.end(); ++it){
                if((*it)->getClassName() == "Article"){
                    if (dynamic_cast<Article*>((*it))->getText().find(s) != string::npos){
                            return dynamic_cast<Article*>(*it);
                    }
                }
            }
        }
    };

    SearchIterator getSearchIterator(string tf) const{
        return SearchIterator(tf);
    }

    ///Fonctions pour les iterators
    vector<Note*>::iterator getIteratorBegin() { return notes.begin();}
    vector<Note*>::iterator getIteratorEnd() { return notes.end();}*/
};


#endif // NOTEMANAGER_H

