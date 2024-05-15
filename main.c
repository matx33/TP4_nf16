#include "tp4.h"
#include <stdio.h>

int main(){
    T_Arbre abr = NULL;
    abr = insererElement(abr, 1);
    abr = insererElement(abr, 2);
    abr = insererElement(abr, 3);
    abr = insererElement(abr, 6);
    abr = insererElement(abr, 10);
    abr = insererElement(abr, 11);
    abr = insererElement(abr, 12);
    T_Sommet *sommet = rechercherElement(abr, 10);
    afficherSommets(abr);
    printf("Sommet trouve: [%d; %d]\n", sommet->borneInf, sommet->borneSup);
    return 0;
}
