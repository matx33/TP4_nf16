#include "tp4.h"
#include <stdio.h>

int main() {
    T_Arbre abr = NULL;

    // Insertion des éléments dans l'arbre
    abr = insererElement(abr, 2);
    abr = insererElement(abr, 4);
    abr = insererElement(abr, 7);
    abr = insererElement(abr, 10);
    abr = insererElement(abr, 11);
    abr = insererElement(abr, 14);
    abr = insererElement(abr, 15);
    abr = insererElement(abr, 16);

    // Affichage des sommets de l'arbre
    printf("Affichage des sommets de l'arbre :\n");
    afficherSommets(abr);
    printf("\n");

    // Affichage des éléments de l'arbre
    printf("Affichage des elements de l'arbre :\n");
    afficherElements(abr);
    printf("\n");

    // Affichage de la taille mémoire de l'arbre
    printf("Tailles mémoire de l'arbre :\n");
    tailleMemoire(abr);
    
    // Obtention et affichage de la racine de l'arbre
    T_Arbre racine = obtenirRacine(abr);
    if (racine != NULL) {
        printf("\nRacine de l'arbre: [%d; %d]\n", racine->borneInf, racine->borneSup);
    } else {
        printf("\nL'arbre est vide, pas de racine à afficher.\n");
    }

    return 0;
}
