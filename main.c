#include "tp4.h"
#include <stdio.h>

int main() {
    T_Arbre abr = NULL;

    // Insertion des éléments dans l'arbre
    abr = insererElement(abr, 5);
    abr = insererElement(abr, 2);
    abr = insererElement(abr, 7);
    abr = insererElement(abr, 1);
    abr = insererElement(abr, 3);
    abr = insererElement(abr, 6);
    abr = insererElement(abr, 8);
    abr = insererElement(abr, 9);
    abr = insererElement(abr, 10);
    abr = insererElement(abr, 12);
    abr = insererElement(abr, 13);

    // Affichage des éléments de l'arbre
    printf("Affichage des elements de l'arbre :\n");
    afficherElements(abr);
    printf("\n");

    // Affichage des sommets de l'arbre
    printf("Affichage des sommets de l'arbre :\n");
    afficherSommets(abr);
    printf("\n");

    // Recherche d'un élément dans l'arbre
    T_Sommet *sommetRecherche = rechercherElement(abr, 3);
    if (sommetRecherche != NULL) {
        printf("Element %d trouve dans le sommet [%d; %d]\n", 3, sommetRecherche->borneInf, sommetRecherche->borneSup);
    } else {
        printf("Element %d non trouve dans l'arbre\n", 3);
    }

    // Suppression de l'élément 5 de l'arbre
    printf("\nSuppression de l'element %d :\n", 5);
    abr = supprimerElement(abr, 5);
    afficherSommets(abr);
    printf("\n");

    // Affichage des éléments de l'arbre
    printf("Affichage des elements de l'arbre :\n");
    afficherElements(abr);
    printf("\n");

    abr = insererElement(abr, 11);
    abr = insererElement(abr, 14);

    // Suppression de l'élément 7 de l'arbre
    printf("\nSuppression de l'element %d :\n", 7);
    abr = supprimerElement(abr, 7);
    afficherSommets(abr);
    printf("\n");

    // Affichage des éléments de l'arbre
    printf("Affichage des elements de l'arbre :\n");
    afficherElements(abr);
    printf("\n");

    // Calcul de la taille mémoire utilisée par l'arbre
    tailleMemoire(abr);

    return 0;
}
