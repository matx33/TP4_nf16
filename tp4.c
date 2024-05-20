#include "tp4.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#define max(a,b) ({ typeof (a) _a = (a); typeof (b) _b = (b); _a > _b ? _a : _b; })
#define min(a,b) ({ typeof (a) _a = (a); typeof (b) _b = (b); _a < _b ? _a : _b; })

T_Sommet *creerSommet(int element) {
    T_Sommet *sommet = (T_Sommet *)malloc(sizeof(T_Sommet));
    sommet->borneInf = element;
    sommet->borneSup = element;
    sommet->filsGauche = NULL;
    sommet->filsDroit = NULL;
    return sommet;
}

T_Arbre insererElement(T_Arbre abr, int element) {
    if (abr == NULL) {
        return creerSommet(element);
    }
    if (rechercherElement(abr, element) != NULL) {
        printf("L'element %d est deja present dans l'arbre.\n", element);
        return abr;
    }
    if (element >= abr->borneInf - 1 && element <= abr->borneSup + 1) {
        abr->borneInf = min(abr->borneInf, element);
        abr->borneSup = max(abr->borneSup, element);
    } else if (element < abr->borneInf - 1) {
        abr->filsGauche = insererElement(abr->filsGauche, element);
    } else if (element > abr->borneSup + 1) {
        abr->filsDroit = insererElement(abr->filsDroit, element);
    }
    return abr;
}

T_Sommet *rechercherElement(T_Arbre abr, int element) {
    if (abr == NULL) {
        return NULL;
    }
    if (element >= abr->borneInf && element <= abr->borneSup) {
        return abr;
    } else if (element > abr->borneSup) {
        return rechercherElement(abr->filsDroit, element);
    } else {
        return rechercherElement(abr->filsGauche, element);
    }
}

// Fonction pour rechercher le père d'un élément
T_Sommet* rechercherPere(T_Arbre abr, int element) {
    if (abr == NULL || (abr->filsGauche == NULL && abr->filsDroit == NULL)) {
        return NULL;
    }

    if ((abr->filsGauche && (element >= abr->filsGauche->borneInf && element <= abr->filsGauche->borneSup)) ||
        (abr->filsDroit && (element >= abr->filsDroit->borneInf && element <= abr->filsDroit->borneSup))) {
        return abr;
    }

    if (element < abr->borneInf) {
        return rechercherPere(abr->filsGauche, element);
    } else if (element > abr->borneSup) {
        return rechercherPere(abr->filsDroit, element);
    }
    return NULL;
}

void afficherSommets(T_Arbre abr) {
    if (abr == NULL) {
        return;
    }
    afficherSommets(abr->filsGauche);
    printf("[%d; %d]\n", abr->borneInf, abr->borneSup);
    afficherSommets(abr->filsDroit);
}

void afficherElements(T_Arbre abr) {
    if (abr == NULL) {
        return;
    }
    afficherElements(abr->filsGauche);
    for (int i = abr->borneInf; i <= abr->borneSup; i++) {
        printf("%d ", i);
    }
    afficherElements(abr->filsDroit);
}

T_Arbre supprimerElement(T_Arbre abr, int element) {
    if (abr == NULL) {
        return NULL;
    }
    T_Sommet *elementASupprimer = rechercherElement(abr, element);
    if (elementASupprimer == NULL) {
        printf("L'element %d n'existe pas dans l'arbre. Suppression impossible.\n", element);
        return abr;
    }
    if (element < abr->borneInf) {
        abr->filsGauche = supprimerElement(abr->filsGauche, element);
    } else if (element > abr->borneSup) {
        abr->filsDroit = supprimerElement(abr->filsDroit, element);
    } else {
        // Cas où l'élément à supprimer est trouvé dans un sommet avec borneInf == borneSup
        if (abr->borneInf == abr->borneSup) {
            T_Sommet *pere = rechercherPere(abr, element);
            if (pere != NULL) {
                // Si abr est le fils gauche de son père
                if (pere->filsGauche == abr) {
                    // Créer un nouveau sommet avec le fils droit de abr
                    T_Arbre nouveauGauche = abr->filsDroit;
                    // Faire en sorte que le fils droit de abr devienne le fils gauche du père de abr
                    pere->filsGauche = nouveauGauche;
                    // Si le nouveau fils gauche du père de abr a des fils gauches, les parcourir
                    // et ajouter le fils gauche de abr à la fin de ceux-ci
                    if (pere->filsGauche != NULL) {
                        T_Sommet *filsCourant = pere->filsGauche;
                        while (filsCourant->filsGauche != NULL) {
                            filsCourant = filsCourant->filsGauche;
                        }
                        filsCourant->filsGauche = abr->filsGauche;
                    }
                }
                // Si abr est le fils droit de son père
                else if (pere->filsDroit == abr) {
                    // Créer un nouveau sommet avec le fils gauche de abr
                    T_Arbre nouveauDroit = abr->filsGauche;
                    // Faire en sorte que le fils gauche de abr devienne le fils droit du père de abr
                    pere->filsDroit = nouveauDroit;
                    // Si le nouveau fils droit du père de abr a des fils droits, les parcourir
                    // et ajouter le fils droit de abr à la fin de ceux-ci
                    if (pere->filsDroit != NULL) {
                        T_Sommet *filsCourant = pere->filsDroit;
                        while (filsCourant->filsDroit != NULL) {
                            filsCourant = filsCourant->filsDroit;
                        }
                        filsCourant->filsDroit = abr->filsDroit;
                    }
                }
            }
            free(abr); // Libérer le nœud abr
            printf("Element %d supprime.\n", element); // Affichage d'un message indiquant la suppression réussie
            return NULL; // Retourner NULL car le nœud abr est supprimé
        }
        // Si l'élément n'est pas dans un sommet avec borneInf == borneSup
        else {
            if (element == abr->borneInf) {
                abr->borneInf++;
            } else if (element == abr->borneSup) {
                abr->borneSup--;
            } else {
                printf("Suppression de %d et separation du sommet [%d; %d]\n", element, abr->borneInf, abr->borneSup);
                // Créer un nouveau sommet pour [borneInf, element - 1]
                T_Sommet *nouveauGauche = creerSommet(abr->borneInf);
                nouveauGauche->borneSup = element - 1;
                nouveauGauche->filsGauche = abr->filsGauche;
                printf("Premier sommet genere par la separation: [%d; %d]\n", nouveauGauche->borneInf, nouveauGauche->borneSup);

                // Créer un nouveau sommet pour [element + 1, borneSup]
                T_Sommet *nouveauDroit = creerSommet(element + 1);
                nouveauDroit->borneSup = abr->borneSup;
                nouveauDroit->filsDroit = abr->filsDroit;
                printf("Second sommet genere par la separation: [%d; %d]\n", nouveauDroit->borneInf, nouveauDroit->borneSup);

                int x;
                for (x = nouveauDroit->borneInf; x <= nouveauDroit->borneSup; x++) {
                    nouveauGauche = insererElement(nouveauGauche, x);
                }

                printf("Fils gauche de abr: [%d; %d]\n", abr->filsGauche->borneInf, abr->filsGauche->borneSup);
                printf("Fils droit de abr: [%d; %d]\n", abr->filsDroit->borneInf, abr->filsDroit->borneSup);
                nouveauGauche->filsGauche = abr->filsGauche;
                nouveauDroit->filsDroit = abr->filsDroit;

                if (abr->filsGauche != NULL) {
                    for (x = abr->filsGauche->borneInf; x <= abr->filsGauche->borneSup; x++) {
                    nouveauGauche = insererElement(nouveauGauche, x);
                }}

                if (abr->filsDroit != NULL) {
                    for (x = abr->filsDroit->borneInf; x <= abr->filsDroit->borneSup; x++) {
                    nouveauGauche = insererElement(nouveauGauche, x);
                }}

                // Libérer le nœud actuel
                free(abr);

                // Retourner le nouveau sous-arbre avec les deux nouveaux sommets
                return nouveauGauche;
            }
        }
    }
    return abr;
}


unsigned int tailleMemoireIntervalles(T_Arbre abr) {
    if (abr == NULL) {
        return 0;
    }
    unsigned int tailleArbre = sizeof(T_Sommet);
    return tailleArbre + tailleMemoireIntervalles(abr->filsGauche) + tailleMemoireIntervalles(abr->filsDroit);
}

unsigned int tailleMemoireClassique(T_Arbre abr) {
    if (abr == NULL) {
        return 0;
    }
    unsigned int tailleArbre = sizeof(T_Sommet2);
    unsigned int nbElements = abr->borneSup - abr->borneInf + 1;
    return (tailleArbre * nbElements) + tailleMemoireClassique(abr->filsGauche) + tailleMemoireClassique(abr->filsDroit);
}

void tailleMemoire(T_Arbre abr) {
    unsigned int tailleIntervalles = tailleMemoireIntervalles(abr);
    unsigned int tailleClassique = tailleMemoireClassique(abr);
    printf("Taille memoire de l'arbre (version intervalles): %u octets\n", tailleIntervalles);
    printf("Taille memoire de l'arbre (version classique): %u octets\n", tailleClassique);
    printf("Nombre d'octets gagnes par la representation par intervalles: %d\n", tailleClassique - tailleIntervalles);
    double rapport = (1-((double)tailleIntervalles / tailleClassique)) * 100;
    printf("La representation par intervalles occupe %.2f%% de moins que la representation classique.\n", rapport);
}

T_Arbre obtenirRacine(T_Arbre abr) {
    return abr;
}

void insererPlusieursElements(T_Arbre *abr) {
    char buffer[256];
    printf("Entrez les elements a inserer (separes par des espaces): ");
    scanf(" %[^\n]", buffer);

    char *token = strtok(buffer, " ");
    while (token != NULL) {
        int element = atoi(token);
        *abr = insererElement(*abr, element);
        token = strtok(token + strlen(token) + 1, " ");
    }
    printf("Elements inseres.\n");
}

void supprimerPlusieursElements(T_Arbre *abr) {
    char buffer[256];
    printf("Entrez les elements a supprimer (separes par des espaces): ");
    scanf(" %[^\n]", buffer);

    char *token = strtok(buffer, " ");
    while (token != NULL) {
        int element = atoi(token);
        *abr = supprimerElement(*abr, element);
        token = strtok(token + strlen(token) + 1, " ");
    }
    printf("Elements supprimes.\n");
}


