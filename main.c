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

    // Affichage des éléments de l'arbre
    printf("Affichage des elements de l'arbre :\n");
    afficherElements(abr);
    printf("\n");

    // Affichage des sommets de l'arbre
    printf("Affichage des sommets de l'arbre :\n");
    afficherSommets(abr);
    printf("\n");

    // Recherche d'un élément dans l'arbre
    int elementRecherche = 3;
    T_Sommet *sommetRecherche = rechercherElement(abr, elementRecherche);
    if (sommetRecherche != NULL) {
        printf("Element %d trouve dans le sommet [%d; %d]\n", elementRecherche, sommetRecherche->borneInf, sommetRecherche->borneSup);
    } else {
        printf("Element %d non trouve dans l'arbre\n", elementRecherche);
    }

    // Suppression de l'élément 5 de l'arbre
    int elementSuppression = 5;
    printf("\nSuppression de l'element %d :\n", elementSuppression);
    abr = supprimerElement(abr, elementSuppression);
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
