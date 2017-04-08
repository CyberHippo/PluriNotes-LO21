#include <iostream>

using namespace std;

void essai_comptes(){
compte tab[4]={ {"courant", 0},{"codevi", 1500 },
{"epargne", 200 }, { "cel", 300 } };
operation(tab,"courant")=100;
operation(tab,"codevi")+=100;
operation(tab,"cel")-=50;
for(int i=0; i<4; i++) cout<<tab[i].id<<" : "<<tab[i].solde<<"\n";
}
int main()
{
    essai_comptes();
    return 0;
}

int& operation (compte* c, const char* str){
    //renvoie une référence sur le solde du compte à modifier
    int i =0;
    while ( strcmp (c[i].id,str)!=0) i++;
    return c[i].solde;
}
