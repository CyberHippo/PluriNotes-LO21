#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED
class Tableau Priority
{
    Priority* tab;
    int nbPriority;  /* le destructeur de nbPriority sera appelé à la fin  */
    public:
    Tableau (Priority int n):
        nbPriority (n)
        {
            tab = new Priority[n];
        }
        void setPriority (int i, int v ) {tab[i].setValue(v)}
        int getPriority (int i) const {return tab[i].getvalue ();}
        void libererTableauDynamique (){delete{};}
        ~TableauPriority() {delete []tab;} /* un destructeur ne détruit pas l'objet: il est toujours actif en mémoire après l'exécution du destructeur*/
});/* le destructeur est exécuté en fin de fonction */
/* delete []tab a pour but d'éliminer les objets, appel automatique du destructeur */
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
