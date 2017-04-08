void truc1(const int& x){
std::cout<<x<<"\n";
x++;
std::cout<<x<<"\n";
}
// référence const
void truc2(int& x){
x++;
truc1(x);
x++;
}
void truc3(const int& x){
    int i =6;
truc2(i);
double y=x;
const double& z=x;
double& u=y;
 const double& t=y-3;
}

#include "fonction.h"
/*...*/
void init(point* pt, int _x, int _y, int _z) {
pt->x=_x; pt->y=_y; pt->z=_z;
}
// on fournit 4 paramètres, mais on veut que z soit a 0. Donc on initialise
 void init(point* pt, int _x, int _y) {
pt->x=_x; pt->y=_y; pt->z=0;
}
void init(point* pt, int _x) {
pt->x=_x; pt->y=0; pt->z=0;
}
void init(point* pt) {
pt->x=0; pt->y=0; pt->z=0;
}*/
void essai_init() {
point p;
init(&p); // init (&p,0,0,0)
init(&p,1); // init (&p,1,0,0)
init(&p,1,2); //init (&p,1,2,0)
init(&p,1,2,3); // init (&p,1,2,3)
}


void essai_alloc(){
int* pt_int;
double* pt_double;
/*pt_int=(int*)malloc(sizeof(int)); */
pt_int = new int ;
/*pt_double=(double*)malloc(sizeof(double)*100); */
pt_double = new double[100]  ;
/*free(pt_int); */
delete pt_int ;
/*free(pt_double); */
delete [] pt_double; //désallocation d'un tableau
}
