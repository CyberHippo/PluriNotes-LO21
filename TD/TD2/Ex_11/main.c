double& d1=36; // faux // on ne peut pas initialiser une r�f�rence avec une rvalue .
// a noter, un pointeur peut pointer vers une adresse ou rien. La r�f�rence doit obligatoirement etre initialis�e
double d2=36; // juste
double& ref=d2;//juste, on r�f�rence une lvalue
ref=4;
const double d3=36; // initialisation d'une constante est obligatoire
//une rvalue ne poss�de pas d'adresse
const double& d4=36; // On peut initialiser une r�f�rence avec une rvalue
                    // le compilateur met en place des instructions qui cr�ent une zone temporaire qui va �tre initialis�
                    //avec le r�sultat de la conversion de l'expression 36 en double.
                    // c'est cette donn�e qui est r�f�renc�e
const double& d5=d2; // on peut r�f�rencer une lvalue dont la valeur n'est pas constante.
d5=21; // Par contre on peut pas faire d5 =3 car la r�f�rence est constante
const double& d6=d3;
double& ref2=d6; // pas de conversion implicite const T& -> T&
Correction : double& ref2 = const_cast<double&> (d6);
int i=4;
double& d7=i;
const double& d8=i;// On peut initialiser une r�f�rence avec une rvalue
                    // le compilateur met en place des instructions qui cr�ent une zone temporaire qui va �tre initialis�
                    //avec le r�sultat de la conversion de l'expression 36 en double.
                    // c'est cette donn�e qui est r�f�renc�e
d8=3; // a partir d'une reference const on ne peut pas modifier la donn�e r�f�renc�e

// REPOSER QUESTION PROJET EN COURS
