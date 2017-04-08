#include <stdio.h>
#include <stdlib.h>
int fact1 (int nbre);
int main()
{
    int nombre = 0;
    printf("Rentrer un nombre:\n");
    scanf("%d", &nombre);
    printf("Voici le factorielle de %d : %d", nombre, fact1(nombre));
    return 0;
}


int fact1 (int nbre)
{
    int resultat=1, i;

    for (i=1; i<= nbre ;i++)
    {
        resultat = fact1(i-1)*nbre;
    }

    return (resultat);
}
