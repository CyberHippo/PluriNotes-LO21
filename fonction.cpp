#include <iostream>
#include <fstream>
#include "fonction.h"

///Méthodes de la classe Date
date::date(int j, int m, int a) : jour(j), mois(m), annee(a) {}
void date::print() const{
    std:cout << jour << "/" << mois << "/" << annee << "\n";
}
///Methodes de la classe Note
Note::~Note() {}

///Methodes de la classe Article
//Constructeur & destructeur:
Article::Article(const string& id, const string& titre, const string& text) : Note(id,titre),text(text){}
//Article::Article(const Note& N1, const string& text) : Note(N1), text(text) {}
Article* Article::clone() const { return new Article(*this);}
Article::~Article() {}

void Article::print() const{
    std::cout << "Id de l'article: " << id << "\n";
    std::cout << "Titre de l'article: " << title << "\n";
    std::cout << "Contenu de l'article: " << text << "\n";
}


///Méthodes de la classe Task
//Constructeur & destructeur
Task::Task(const string& id, const string& title, const string& act, const string& s, const date& d, const unsigned int& p) : Note(id, title), action(act), status(s), deadline(d), priority(p) {}
Task* Task::clone() const { return new Task(*this);}
Task::~Task(){}

void Task::print() const{
    std::cout << "Id de la tache : " << id << "\n";
    std::cout << "Action : " << title << "\n";
    if (priority!=0) {std::cout << "Niveau de Priorite : " << priority << "\n";}
    if (deadline.jour!=0 && deadline.mois!=0 && deadline.annee!=0) {  std::cout << "Deadline : "; deadline.print();}
    std::cout << "Statut : " << status << "\n";
}

///Méthodes de la classe Multimedia (et de ses filles)
//Constructeur & destructeur
Multimedia::Multimedia(const string& id, const string& title, const string& desc, const string& imgF) : Note(id, title), description(desc), imageFilename(imgF) {}
Multimedia::~Multimedia(){}
Image::~Image(){}
Audio::~Audio(){}
Video::~Video(){}

void Image::print() const{
    std::cout << "Id de l'image : " << id << "\n";
    std::cout << "Titre de l'image : " << title << "\n";
    std::cout << "Description de l'image : " << description << "\n";
    ///afficher le fichier de l'image
}
Image* Image::clone() const {return new Image(*this);}

void Audio::print() const{
    std::cout << "Id de l'enregistrement audio : " << id << "\n";
    std::cout << "Titre de l'enregistrement audio : " << title << "\n";
    std::cout << "Description de l'enregistrement audio : " << description << "\n";
    ///afficher l'image de l'enregistrement audio
}
Audio* Audio::clone() const {return new Audio(*this);}

void Video::print() const{
    std::cout << "Id de l'enregistrement video : " << id << "\n";
    std::cout << "Titre de l'enregistrement video : " << title << "\n";
    std::cout << "Description de l'enregistrement video : " << description << "\n";
    ///afficher l'image de l'enregistrement video
}
Video* Video::clone() const {return new Video(*this);}


///Méthodes de la classe NotesManager
void NotesManager::addNote(Note* n){
    notes.push_back(n->clone());
}

NotesManager::NotesManager() : notes(0),nbNotes(0),nbMaxNotes(0),filename("tmp.dat"){}

NotesManager::~NotesManager(){
	save();
	for(unsigned int i=0; i<nbNotes; i++) delete notes[i];
	notes.clear();
}


NotesManager::Handler NotesManager::handler=Handler();

NotesManager& NotesManager::getInstance() {
  // Si le pointeur vers l'instance unique pointe vers 0
  if(!handler.instance) {
    handler.instance=new NotesManager;
  }
  // Retour par ref vers l'instance unique
  return *handler.instance;
}

void NotesManager::libererInstance() {
  // Libération de la mémoire allouée à l'instance unique
  delete handler.instance;
  // Repasse le pointeur à null/nullptr/0 pour que le prochain appel à getInstance recrée bien une instance
  handler.instance=0;
}

void NotesManager::save() const {
	std::ofstream fout(filename.c_str());
	for(unsigned int i=0; i<nbNotes; i++){
		fout<<notes[i];
	}
	fout.close();
}



void NotesManager::load(const string& f) {
	if (filename!=f) save();
	filename=f;
	std::ifstream fin(filename.c_str()); // open file
	if (!fin) throw NotesException("error, file does not exist");
	while(!fin.eof()&&fin.good()){
		char tmp[1000];
		fin.getline(tmp,1000); // get id on the first line
		if (fin.bad()) throw NotesException("error reading note id on file");
		string id=tmp;
		fin.getline(tmp,1000); // get title on the next line
		if (fin.bad()) throw NotesException("error reading note title on file");
		string title=tmp;
		fin.getline(tmp,1000); // get text on the next line
		if (fin.bad()) throw NotesException("error reading note text on file");
		string text=tmp;
		/*Note* n=new Note(id,title,text);
		addNote(n);*/ // On ne peut pas instancier de note car c'est une classe abstraite
		if (fin.peek()=='\r') fin.ignore();
		if (fin.peek()=='\n') fin.ignore();
	}
	fin.close(); // close file
}

//void NotesManager::showNote(const Note& note) const{
//    note.print();
//}

void NotesManager::showAll() const {

    std::cout << "|------ NOTES ------|\n\n";

    for (vector<Note*>::const_iterator it = notes.begin() ; it != notes.end(); ++it){
        (*it)->print();
        std::cout << "------------------\n";
    }
}
/// !!!! Ne pas supprimer
/*void NotesManager::deleteNote(string &id){
    int size_init = notes.size();
    for (vector<Note*>::iterator it = notes.begin() ; it != notes.end(); ++it){
            if ((*it)->getId() == id){
                Note* tmp = dynamic_cast<Note*>(*it); //On met l'élement à supprimer à la fin du vector pour pouvoir le supprimé
                *it = notes.end();//On échange l'emplacement de l'adresse de la note a supprimer avec la dernière adresse dans le tableau
                notes.end() = tmp;
                note.pop_back();
                Note* sup = tmp;
                delete sup; //On supprime la note a l'aide de son adresse car le NotesManager compose les notes, il doit donc les supprimer
            }
    }
    if (size_init == notes;size()) { //cela signifie que l'on a rien supprimé dans le tableau
        throw NotesException("L'element a supprimer n'a pas ete trouve..\n");
    }


}*/
void NotesManager::editNote(string id){
    string t;
    cout << "Quel nouveau titre pour cette note?\n";
    cin >> t;
    cin.ignore();
    for (vector<Note*>::iterator it = notes.begin() ; it != notes.end(); ++it){
                if ((*it)->getId() == id){
                        (*it)->addOldVersion();
                        (*it)->setTitle(t);
                }
    }
}

void NotesManager::showOldNotes(string id){
    for (vector<Note*>::iterator it = notes.begin() ; it != notes.end(); ++it){
                if ((*it)->getId() == id){
                        (*it)->printOldVersion();
                }
    }
}


///Surchage d'opérateurs
ostream& operator<<(ostream& f, const Article& a){
	f<<a.getId()<<"\n";
	f<<a.getTitle()<<"\n";
	f<<a.getText()<<"\n";
	return f;
}


