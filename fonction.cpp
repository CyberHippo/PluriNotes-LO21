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
Article::Article(const Note& N1, const string& text) : Note(N1), text(text) {}
Article::~Article() {}

void Article::print() const{
    std::cout << "Id de l'article: " << id << "\n";
    std::cout << "Titre de l'article: " << title << "\n";
    std::cout << "Contenu de l'article: " << text << "\n";
}


///Méthodes de la classe Task
//Constructeur & destructeur
Task::Task(const string& id, const string& title, const string& act, const string& s, const date& d, const unsigned int& p) : Note(id, title), action(act), status(s), deadline(d), priority(p) {}
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

void Audio::print() const{
    std::cout << "Id de l'enregistrement audio : " << id << "\n";
    std::cout << "Titre de l'enregistrement audio : " << title << "\n";
    std::cout << "Description de l'enregistrement audio : " << description << "\n";
    ///afficher l'image de l'enregistrement audio
}

void Video::print() const{
    std::cout << "Id de l'enregistrement video : " << id << "\n";
    std::cout << "Titre de l'enregistrement video : " << title << "\n";
    std::cout << "Description de l'enregistrement video : " << description << "\n";
    ///afficher l'image de l'enregistrement video
}



///Méthodes de la classe NotesManager
void NotesManager::addNote(Note* n){
    notes.push_back(n);
}

///La reste devient superflu ?
/*
void NotesManager::addNote(Note* n){
	for(unsigned int i=0; i<nbNotes; i++){
		if (notes[i]->getId()==n->getId()) throw NotesException("error, creation of an already existent note");
	}
	if (nbNotes==nbMaxNotes){
		Note** newNotes= new Note*[nbMaxNotes+5];
		for(unsigned int i=0; i<nbNotes; i++) newNotes[i]=notes[i];
		Note** oldNotes=notes;
		notes=newNotes;
		nbMaxNotes+=5;
		if (oldNotes) delete[] oldNotes;
	}
	notes[nbNotes++]=n;
}

Note& NotesManager::getNote(const string& id){
	for(unsigned int i=0; i<nbNotes; i++){
		if (notes[i]->getId()==id) return *notes[i];
	}
	throw NotesException("error, nonexistent note");

}

Article& NotesManager::getArticle(const string& id){
	for(unsigned int i=0; i<nbNotes; i++){
		if (notes[i]->getId()==id) return dynamic_cast<Article> (*notes[i]);
	}
	throw NotesException("error, nonexistent note");

}

Article& NotesManager::getNewArticle(const string& id){
	Article* a=new Article(id,"","");
	addNote(a);
	return *a;
} // On ne peut pas instancier de note car c'est une classe abstraite
*/
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


///Surchage d'opérateurs
ostream& operator<<(ostream& f, const Article& a){
	f<<a.getId()<<"\n";
	f<<a.getTitle()<<"\n";
	f<<a.getText()<<"\n";
	return f;
}


