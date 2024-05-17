#include "tp4.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

// Macro pour déterminer le maximum et le minimum entre deux valeurs (utilisees pour les bornes des intervalles)
#define max(a,b) \
    ({ typeof (a) _a = (a); \
        typeof (b) _b = (b); \
        _a > _b ? _a : _b; })

#define min(a,b) \
    ({ typeof (a) _a = (a); \
        typeof (b) _b = (b); \
        _a < _b ? _a : _b; })


T_Sommet *creerSommet(int element){
    T_Sommet *sommet = (T_Sommet *)malloc(sizeof(T_Sommet));
    sommet->borneInf = element;
    sommet->borneSup = element;
    sommet->filsGauche = NULL;
    sommet->filsDroit = NULL;

    return sommet;
}

T_Arbre insererElement(T_Arbre abr, int element){
    if (abr == NULL){
        return creerSommet(element);
    }
    // Si l'élément peut être fusionné avec le sommet actuel
    if (element >= abr->borneInf - 1 && element <= abr->borneSup + 1){
        abr->borneInf = min(abr->borneInf, element);
        abr->borneSup = max(abr->borneSup, element);
    }
    // Si l'élément doit être inséré à gauche
    else if (element < abr->borneInf - 1){
        abr->filsGauche = insererElement(abr->filsGauche, element);
    }
    // Si l'élément doit être inséré à droite
    else if (element > abr->borneSup + 1){
        abr->filsDroit = insererElement(abr->filsDroit, element);
    }
    // Si l'élément ne peut pas être inséré à gauche ou à droite
    else {
        T_Sommet *nouveauSommet = creerSommet(element);
        if (element < abr->borneInf) {
            abr->filsGauche = nouveauSommet;
        } 
        else {
            abr->filsDroit = nouveauSommet;
        }
    }
    return abr;
}

T_Sommet *rechercherElement(T_Arbre abr, int element){
    if (abr == NULL){
        return NULL;
    }
    if (element >= abr->borneInf && element <= abr->borneSup){
        return abr;
    }
    else if (element > abr->borneSup + 1){
        return rechercherElement(abr->filsDroit, element);
    }
    else{
        return rechercherElement(abr->filsGauche, element);
    }
}

void afficherSommets(T_Arbre abr){
    if (abr == NULL){
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
    printf("%d ", abr->borneInf);
    // Si l'intervalle n'est pas un singleton, affiche les éléments entre borneInf et borneSup inclus
    if (abr->borneInf != abr->borneSup) {
        for (int i = abr->borneInf + 1; i <= abr->borneSup; i++) {
            printf("%d ", i);
        }
    }
    afficherElements(abr->filsDroit);
}


T_Arbre supprimerElement(T_Arbre abr, int element) {
    if (abr == NULL) {
        return NULL;
    }

    if (element < abr->borneInf) {
        abr->filsGauche = supprimerElement(abr->filsGauche, element);
    } 
    else if (element > abr->borneSup) {
        abr->filsDroit = supprimerElement(abr->filsDroit, element);
    } 
    else {
        // Cas où l'élément est dans l'intervalle du nœud actuel
        if (abr->borneInf == abr->borneSup) {
            // Si l'intervalle est un singleton
            if (abr->borneInf == element) {
                // Suppression du nœud actuel
                T_Sommet *nouvelleRacine = NULL;
                if (abr->filsGauche == NULL) {
                    nouvelleRacine = abr->filsDroit;
                } 
                else if (abr->filsDroit == NULL) {
                    nouvelleRacine = abr->filsGauche;
                } 
                else {
                    // Trouver le nœud le plus à droite dans le sous-arbre gauche
                    T_Sommet *noeudMax = abr->filsGauche;
                    while (noeudMax->filsDroit != NULL) {
                        noeudMax = noeudMax->filsDroit;
                    }
                    // Échanger les bornes de l'ancienne racine avec le nœud max
                    int temp = abr->borneInf;
                    abr->borneInf = noeudMax->borneInf;
                    noeudMax->borneInf = temp;
                    // Supprimer le nœud max
                    abr->filsGauche = supprimerElement(abr->filsGauche, noeudMax->borneInf);
                    return abr;
                }
                // Libérer la mémoire de l'ancienne racine
                free(abr);
                return nouvelleRacine;
            }
        } 
        else {
            // Si l'intervalle n'est pas un singleton
            if (abr->borneInf == element) {
                abr->borneInf++;
            } 
            else if (abr->borneSup == element) {
                abr->borneSup--;
            }
            // Essayer de fusionner les intervalles avec le fils de gauche
            if (abr->filsGauche != NULL && abr->filsGauche->borneSup == element - 1) {
                abr->borneInf = abr->filsGauche->borneInf;
                abr->filsGauche = supprimerElement(abr->filsGauche, abr->borneSup + 1);
            }
            // Essayer de fusionner les intervalles avec le fils de droite
            else if (abr->filsDroit != NULL && abr->filsDroit->borneInf == element + 1) {
                abr->borneSup = abr->filsDroit->borneSup;
                abr->filsDroit = supprimerElement(abr->filsDroit, abr->borneInf - 1);
            }
        }
    }
    return abr;
}

unsigned int tailleMemoireIntervalles(T_Arbre abr) {
    if (abr == NULL) {
        return 0;
    }

    // Taille d'un sommet de la version intervalles
    unsigned int tailleArbre = sizeof(T_Sommet); 

    // Parcours récursif de l'arbre pour calculer la taille totale
    return tailleArbre + tailleMemoireIntervalles(abr->filsGauche) + tailleMemoireIntervalles(abr->filsDroit);
}

unsigned int tailleMemoireClassique(T_Arbre abr) {
    if (abr == NULL) {
        return 0;
    }

    // Taille d'un sommet de la version classique
    unsigned int tailleArbre = sizeof(T_Sommet2); 
    unsigned int tailleTotale = 0;

    // Parcours récursif de l'arbre pour calculer la taille totale
    tailleTotale += tailleMemoireClassique(abr->filsGauche);
    
    if (abr->borneInf != abr->borneSup) {
        tailleTotale += (abr->borneSup - abr->borneInf + 1) * tailleArbre;
    } else {
        tailleTotale += tailleArbre;
    }
    
    tailleTotale += tailleMemoireClassique(abr->filsDroit);
    
    return tailleTotale;
}

void tailleMemoire(T_Arbre abr) {
    unsigned int tailleSommet = sizeof(T_Sommet);
    unsigned int tailleSommet2 = sizeof(T_Sommet2);
    unsigned int tailleIntervalles = tailleMemoireIntervalles(abr);
    unsigned int tailleClassique = tailleMemoireClassique(abr);

    printf("Taille en octets d'un sommet pour la version intervalles: %u\n", tailleSommet);
    printf("Taille en octets d'un sommet classique: %u\n", tailleSommet2);
    printf("Taille en octets occupee par l'ABR dans la representation par intervalles: %u\n", tailleIntervalles);
    printf("Taille en octets qu'aurait occupee un ABR dans la representation classique: %u\n", tailleClassique);
    printf("Nombre d'octets gagnes par la representation par intervalles: %d\n", tailleClassique - tailleIntervalles);
    
    double rapport = (1-((double)tailleIntervalles / tailleClassique)) * 100;
    printf("La representation par intervalles occupe %.2f%% de moins que la representation classique.\n", rapport);
}

T_Arbre obtenirRacine(T_Arbre abr) {
    return abr;
}



