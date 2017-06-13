#ifndef NOTEMANAGER_H
#define NOTEMANAGER_H


#include "fonction.h"
#include "noteediteur.h"
#include "QList"

class NoteEditeur;
///Class Notes Manager
class NotesManager
{
private:
    vector<Note*> notes;
    mutable QString filename;

    NotesManager();
    NotesManager(const NotesManager& n);
    ///destructeur
    ~NotesManager();

    ///surcharge de l'opérateur =
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
    NoteEditeur* callEditeur(Note* n, QString type);
    Note& getNote(QString id);
    Note* getNoteWithTitle(QString title);
    Note* getNoteWithId(QString id);
    void showNote (const Note& note) const;
    /// load notes depuis le fichier filename
    void load();
    void saveNote(Note& n);
    static NotesManager& getInstance();
    static void libererInstance();
    void showAll() const;
    void deleteNote(QString id);
    void deleteNote(Note* n);
    void showOldNotes(QString id);
    void restaurerNote(QString id, QString title);
    QString getFilename() const { return filename; }
    void setFilename(const QString& f) { filename=f; }

    ///LOAD

    ///Fonction spécifique pour le chargement d'un article depuis un flux XML
    QXmlStreamReader& loadArticle(QXmlStreamReader& xml);
    ///Fonction spécifique pour le chargement d'un audio depuis un flux XML
    QXmlStreamReader& loadAudio(QXmlStreamReader& xml);
    ///Fonction spécifique pour le chargement d'une video depuis un flux XML
    QXmlStreamReader& loadVideo(QXmlStreamReader& xml);
    ///Fonction spécifique pour le chargement d'une image depuis un flux XML
    QXmlStreamReader& loadImage(QXmlStreamReader& xml);
    ///Fonction spécifique pour le chargement d'une tache depuis un flux XML
    QXmlStreamReader& loadTask(QXmlStreamReader& xml);

    ///fonction qui permet de sauvegarder toutes les notes du vecteur de notes dans le fichier filename
    void saveAll();

      /// Class SearchIterator
      class SearchIterator{
      /// La classe search iterator ne fonctionne que pour les Articles car ce sont les seuls qui ont un corps de text.
        private:
            QString toFind;
        public:
            SearchIterator(QString tf): toFind(tf){}
            Article* SearchTextArticle(const QString& s){
                ///Apple d'une instance de notesmanager
                NotesManager& nm = NotesManager::getInstance();
                ///itération des notes du vecteur de notes de notesmanager
                for (vector<Note*>::iterator it = nm.notes.begin() ; it != nm.notes.end(); ++it){
                    ///Si c'est un article
                    if((*it)->getClassName() == "art"){
                        ///alors on regarde si le Qstring toFind est présent dans son corps de texte
                        if (dynamic_cast<Article*>((*it))->getText().indexOf(s) != -1){
                                ///Si oui, on renvoie un pointeur vers cet article
                                return dynamic_cast<Article*>(*it);
                        }
                    }
                }
            }
        };

        SearchIterator getSearchIterator(QString tf) const{
            return SearchIterator(tf);
        }

        ///Fonctions pour les iterators
        vector<Note*>::iterator getIteratorBegin() { return notes.begin();}
        vector<Note*>::iterator getIteratorEnd() { return notes.end();}
};


#endif // NOTEMANAGER_H
