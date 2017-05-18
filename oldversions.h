#ifndef OLDVERSIONS_H_INCLUDED
#define OLDVERSIONS_H_INCLUDED
#include <string>
#include <iostream>
#include <time.h>
#include <fstream>
#include <vector>
using namespace std;

///Classe Version Anterieures
class Note;
class OldVersions {
private:
    vector<Note*> oldNotes;
    unsigned int nbNotes;
    unsigned int nbMaxNotes;

public:
    OldVersions() : oldNotes(0),nbNotes(0),nbMaxNotes(0){}
    void addNote(Note* n);
    void printVersions();
    Note* findVersion(string title);
    ~OldVersions();
};

#endif // OLDVERSIONS_H_INCLUDED
