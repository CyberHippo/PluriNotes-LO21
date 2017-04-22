#include <iostream>
#include <fstream>
#include "fonction.h"

///Méthodes de la classe Date
date::date(int j, int m, int a) : jour(j), mois(m), annee(a) {}
void date::print(){
    std:cout << jour << "/" << mois << "/" << annee << "\n";
}


///Méthodes de la classe Note
Note::Note(const string & id, const string& titre) : id(id), title(titre){}


///Methodes de la classe Article
//Constructeur:
Article::Article(const string& id, const string& titre, const string& text) : Note(id,titre),text(text){}
Article::Article(const Note& N1, const string& text) : Note(N1), text(text) {}

void Article::print(){
    std::cout << "Id de l'article: " << id << "\n";
    std::cout << "Titre de l'article: " << title << "\n";
    std::cout << "Contenu de l'article: " << text << "\n";
}


///Méthodes de la classe Task
//Constructeur
Task::Task(const string& id, const string& title, const string& act, const string& s, const date& d, const unsigned int& p) : Note(id, title), action(act), status(s), deadline(d), priority(p) {}

void Task::print(){
    std::cout << "Id de la tache : " << id << "\n";
    std::cout << "Action : " << title << "\n";
    if (priority!=0) {std::cout << "Niveau de Priorite : " << priority << "\n";}
    if (deadline.jour!=0 && deadline.mois!=0 && deadline.annee!=0) {  std::cout << "Deadline : "; deadline.print();}
    std::cout << "Statut : " << status << "\n";
}

///Méthodes de la classe Multimedia (et de ses filles)
//Constructeur
Multimedia::Multimedia(const string& id, const string& title, const string& desc, const string& imgF) : Note(id, title), description(desc), imageFilename(imgF) {}
void Image::print(){
    std::cout << "Id de l'image : " << id << "\n";
    std::cout << "Titre de l'image : " << title << "\n";
    std::cout << "Description de l'image : " << description << "\n";
    ///afficher le fichier de l'image
}

void Audio::print(){
    std::cout << "Id de l'enregistrement audio : " << id << "\n";
    std::cout << "Titre de l'enregistrement audio : " << title << "\n";
    std::cout << "Description de l'enregistrement audio : " << description << "\n";
    ///afficher l'image de l'enregistrement audio
}

void Video::print(){
    std::cout << "Id de l'enregistrement video : " << id << "\n";
    std::cout << "Titre de l'enregistrement video : " << title << "\n";
    std::cout << "Description de l'enregistrement video : " << description << "\n";
    ///afficher l'image de l'enregistrement video
}



///Méthodes de la classe NotesManager

void NotesManager::addArticle(Article* a){
	for(unsigned int i=0; i<nbArticles; i++){
		if (articles[i]->getId()==a->getId()) throw NotesException("error, creation of an already existent note");
	}
	if (nbArticles==nbMaxArticles){
		Article** newArticles= new Article*[nbMaxArticles+5];
		for(unsigned int i=0; i<nbArticles; i++) newArticles[i]=articles[i];
		Article** oldArticles=articles;
		articles=newArticles;
		nbMaxArticles+=5;
		if (oldArticles) delete[] oldArticles;
	}
	articles[nbArticles++]=a;
}

Article& NotesManager::getArticle(const string& id){
	for(unsigned int i=0; i<nbArticles; i++){
		if (articles[i]->getId()==id) return *articles[i];
	}
	throw NotesException("error, nonexistent note");

}

Article& NotesManager::getNewArticle(const string& id){
	Article* a=new Article(id,"","");
	addArticle(a);
	return *a;
}

NotesManager::NotesManager() : articles(nullptr),nbArticles(0),nbMaxArticles(0),filename("tmp.dat"){}

NotesManager::~NotesManager(){
	save();
	for(unsigned int i=0; i<nbArticles; i++) delete articles[i];
	delete[] articles;
}


NotesManager::Handler NotesManager::handler=Handler();

NotesManager & NotesManager::getInstance() {
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
	ofstream fout(filename);
	for(unsigned int i=0; i<nbArticles; i++){
		fout<<*articles[i];
	}
	fout.close();
}



void NotesManager::load(const string& f) {
	if (filename!=f) save();
	filename=f;
	ifstream fin(filename); // open file
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
		Article* a=new Article(id,title,text);
		addArticle(a);
		if (fin.peek()=='\r') fin.ignore();
		if (fin.peek()=='\n') fin.ignore();
	}
	fin.close(); // close file
}

///Surchage d'opérateurs
ostream& operator<<(ostream& f, const Article& a){
	f<<a.getId()<<"\n";
	f<<a.getTitle()<<"\n";
	f<<a.getText()<<"\n";
	return f;
}


