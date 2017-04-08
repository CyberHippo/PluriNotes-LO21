double* pt1=4096; //FAUX /* On essaye d'associer*/  // Peu importe le type, il est pas courant de mettre l'adresse.Il faut donc lui montrer ce qu'on veut faire. Le compilateur refuse de faire une conversion implicite de type int vers le pointeur. Int -> T* interdite
Correction: double* pt1 = reinterpret_cast <double*> (4096);
double* pt2=(double*)4096;  //JUSTE/* on cree un objet de valeur   4096, de plus, on caste le type de 4096 pour le transformer en double* */
void* pt3=pt1; // JUSTE /* on cr�e un pointeur de type non d�fini qui pointe vers l'objet pt1 */
Correction: Une adresse stock�e dans n'importe quelle type de pointeur peut �tre stock�e dans void*: T* ->void* autoris�e
pt1=pt3; // FAUX /* pt3 peut contenir l'adresse de n'importe quoi, mais elle ne peut pas correspondre uniquement � l'adresse d'un double */
pt1=(double*)pt3; // JUSTE/* on caste le type de pt3 (qui est non d�fini) pour que cela devienne du type double* car pt1 est de type double*/
double d1=36;// JUSTE /* on affecte la valeur 36 � la variable d1 de type double */
const double d2=36;// JUSTE /* on affecte la valeur 36 � la variable constante d2 de type double */
double* pt4=&d1; // JUSTE/* on cr�e un pointeur pt4 de type double qui pointe sur l'objet d1 */
const double* pt5=&d1; // FAUX/*
CORRECTION: /* On ne peut pas modifier la valeur de d& via pt5!!! mais on peut l'afficher (but du const). Mais le pointeur est r�affectable)   */ // conversion implicite T* -> const T*
*pt4=2.1;
*pt5=2.1; // a partir d'un pointeur const on ne peut pas modifier la valeur point�e
pt4=&d2; // conversion implcicite const T* -> T* INTERDITE
CORRECTION : pt4=const_cast <double*>(&d2);
pt5=&d2; // Pointeur const r�affectable
double* const pt6=&d1; // pointeur constant
// Attention, diff�rence entre pointeur constant et pointeur const
pt6=&d1;// non r�affectable ,ne peut pas pointer sur autre chose, mais la valeur point�e peut �tre modifi�e
*pt6=2.78;// JUSTE
double* const pt6b=&d2; // conversion implicite const T* -> T*
const double* const pt7=&d1; // pointeur const et constant
pt7=&d1; // non r�affectable
*pt7=2.78; // on ne peut pas affecter la valeur point�e
double const* pt8=&d1; // pointeur const �quivalent � const double* pt8 = &d1
pt8=&d2; // pointeur const reaffectable
pt8=&d1;// pointeur const reaffectable
*pt8=3.14; // on ne peut pas affecter la valeur point�e
