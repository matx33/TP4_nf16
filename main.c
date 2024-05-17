#include "tp4.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void afficherMenu() {
    printf("\nMenu:\n");
    printf("1. Inserer un element\n");
    printf("2. Inserer plusieurs elements\n");
    printf("3. Rechercher un element\n");
    printf("4. Supprimer un element\n");
    printf("5. Supprimer plusieurs elements\n");
    printf("6. Afficher les sommets de l'arbre\n");
    printf("7. Afficher les elements de l'arbre\n");
    printf("8. Afficher la taille memoire de l'arbre\n");
    printf("9. Afficher la racine de l'arbre\n");
    printf("10. Quitter\n");
    printf("Choisissez une option: ");
}

int main() {
    T_Arbre abr = NULL;
    int choix, element;
    T_Sommet *resultatRecherche;

    printf("Bienvenue dans le programme de gestion d'arbres binaires de recherche par intervalles.\n");

    while (1) {
        if (abr == NULL) {
            printf("\nL'arbre est vide. Veuillez inserer un premier sommet.\n");
            printf("Entrez un entier: ");
            scanf("%d", &element);
            abr = insererElement(abr, element);
        } else {
            afficherMenu();
            scanf("%d", &choix);

            switch (choix) {
                case 1:
                    printf("Entrez l'element a inserer: ");
                    scanf("%d", &element);
                    abr = insererElement(abr, element);
                    sleep(2); // Pause de 2 secondes
                    break;
                case 2:
                    insererPlusieursElements(&abr);
                    sleep(2); // Pause de 2 secondes
                    break;
                case 3:
                    printf("Entrez l'element a rechercher: ");
                    scanf("%d", &element);
                    resultatRecherche = rechercherElement(abr, element);
                    if (resultatRecherche != NULL) {
                        printf("Element trouve dans l'intervalle [%d; %d].\n", resultatRecherche->borneInf, resultatRecherche->borneSup);
                    } else {
                        printf("Element non trouve.\n");
                    }
                    sleep(2); // Pause de 2 secondes
                    break;
                case 4:
                    printf("Entrez l'element a supprimer: ");
                    scanf("%d", &element);
                    abr = supprimerElement(abr, element);
                    printf("Element supprime.\n");
                    sleep(2); // Pause de 2 secondes
                    break;
                case 5:
                    supprimerPlusieursElements(&abr);
                    sleep(2); // Pause de 2 secondes
                    break;
                case 6:
                    printf("Affichage des sommets de l'arbre:\n");
                    afficherSommets(abr);
                    sleep(2); // Pause de 2 secondes
                    break;
                case 7:
                    printf("Affichage des elements de l'arbre:\n");
                    afficherElements(abr);
                    sleep(2); // Pause de 2 secondes
                    break;
                case 8:
                    printf("Tailles memoire de l'arbre:\n");
                    tailleMemoire(abr);
                    sleep(2); // Pause de 2 secondes
                    break;
                case 9:
                    if (abr != NULL) {
                        printf("Racine de l'arbre: [%d; %d]\n", abr->borneInf, abr->borneSup);
                    } else {
                        printf("L'arbre est vide, pas de racine a afficher.\n");
                    }
                    sleep(2); // Pause de 2 secondes
                    break;
                case 10:
                    printf("Quitter le programme.\n");
                    exit(0);
                    break;
                default:
                    printf("Choix invalide. Veuillez reessayer.\n");
                    sleep(2); // Pause de 2 secondes
            }
        }
    }

    return 0;
}
