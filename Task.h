#ifndef TASK_H_INCLUDED
#define TASK_H_INCLUDED
#include <string>

/*class Note{};
class Date;

class Task : public Note
{
public:
    const int getPriority()const {return priority;}; // Nous avons d�fini la priorit� sur une �chelle de 1 � 10.
                                                        //Quand l'utilisateur va cr�er la Task,il renseigne le degr� de priorit�
    void setPriority();
    std::string getStatus() const;
    void setStatus();
    timestamp();
    Date& getDeadline();
private:
    int priority;
    std::string status;
    Date& deadline;

};*/

class Date
{
private:
int M,J,A; //mois, jour ,annee

public:
Date(int j, int m, int a);
~Date(){};
void afficherDate();
const int getM()const {return M;};
const int getJ()const{return J;}
const int getA()const {return A;};
void setM(int mois){M=mois;};
void setJ(int jour){J=jour;};
void setA(int annee){A=annee;};
};

class TaskException{ // Classe TaskException pour g�rer les exceptions de t�che
public:
	TaskException(const std::string& message):info(message){}
	std::string getInfo() const { return info; }
private:
	std::string info;
};
#endif // TASK_H_INCLUDED
