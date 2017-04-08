#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED
class Tableau Priority
{
    Priority* tab;
    int nbPriority;  /* le destructeur de nbPriority sera appel� � la fin  */
    public:
    Tableau (Priority int n):
        nbPriority (n)
        {
            tab = new Priority[n];
        }
        void setPriority (int i, int v ) {tab[i].setValue(v)}
        int getPriority (int i) const {return tab[i].getvalue ();}
        void libererTableauDynamique (){delete{};}
        ~TableauPriority() {delete []tab;} /* un destructeur ne d�truit pas l'objet: il est toujours actif en m�moire apr�s l'ex�cution du destructeur*/
});/* le destructeur est ex�cut� en fin de fonction */
/* delete []tab a pour but d'�liminer les objets, appel automatique du destructeur */
class Priority {
int valeur;
public:
Priority():valeur (0){}
Priority(): valeur(V){}

int getValue () const{
return valeur;
}
void setvalue (int v) {valeur = v;}

#endif // FONCTIONS_H_INCLUDED
