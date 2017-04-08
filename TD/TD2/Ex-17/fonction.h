#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED

/*...*/
struct personne {
char nom[30];
unsigned int age;
};

void raz(personne& p);
void affiche_struct (const personne& p);
void affiche_tab(const personne * tab, int n);
void init_struct(personne & p, const char *, int a );
void copy_struct (personne& p1, const personne& p2);
void copy_tab (personne* tab1, const personne* tab2, int n);

void utilisation ()
{

}

#endif // FONCTION_H_INCLUDED
