void raz(personne& p)
{
    p.age = 0;
    p.nom[0] = '\0'; //strcpy(p.nom,""); c'est suffisant de mettre \0 dans la première case du tableau
}
void affiche_struct (const personne& p)
{
    std::cout <<p.nom << ":" <<p.age<< "an(s) \n";
}
void affiche_tab(const personne * tab)
{
    for ((int i=0; i<n ; i++) affiche_struct(tab[i]); // Le C++ accepte la déclaration de la var i directement dans le for
}
void init_struct(personne& p, const char* n, int a )
{
    p.age = a; strcpy (p.nom,n);
}
void copy_struct (personne& p1, const personne& p2);
    //p1.age =p2.age; strcpy(p1.nom, p2.nom)
    p1=p2;
void copy_tab (personne* tab1, const personne* tab2, int n)
{
    for ( int i=0; i<n ; i++) tab1[i]=tab2[i];
}
