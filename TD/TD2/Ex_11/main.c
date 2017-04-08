double& d1=36; // faux // on ne peut pas initialiser une référence avec une rvalue .
// a noter, un pointeur peut pointer vers une adresse ou rien. La référence doit obligatoirement etre initialisée
double d2=36; // juste
double& ref=d2;//juste, on référence une lvalue
ref=4;
const double d3=36; // initialisation d'une constante est obligatoire
//une rvalue ne possède pas d'adresse
const double& d4=36; // On peut initialiser une référence avec une rvalue
                    // le compilateur met en place des instructions qui créent une zone temporaire qui va être initialisé
                    //avec le résultat de la conversion de l'expression 36 en double.
                    // c'est cette donnée qui est référencée
const double& d5=d2; // on peut référencer une lvalue dont la valeur n'est pas constante.
d5=21; // Par contre on peut pas faire d5 =3 car la référence est constante
const double& d6=d3;
double& ref2=d6; // pas de conversion implicite const T& -> T&
Correction : double& ref2 = const_cast<double&> (d6);
int i=4;
double& d7=i;
const double& d8=i;// On peut initialiser une référence avec une rvalue
                    // le compilateur met en place des instructions qui créent une zone temporaire qui va être initialisé
                    //avec le résultat de la conversion de l'expression 36 en double.
                    // c'est cette donnée qui est référencée
d8=3; // a partir d'une reference const on ne peut pas modifier la donnée référencée

// REPOSER QUESTION PROJET EN COURS
