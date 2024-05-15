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


typedef struct T_Sommet{
    int borneInf;
    int borneSup;
    struct T_Sommet *filsGauche;
    struct T_Sommet *filsDroit;
} T_Sommet;

typedef T_Sommet* T_Arbre;


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
            else {
                // L'élément à supprimer est à l'intérieur de l'intervalle
                // Créer un nouveau nœud pour les valeurs supérieures à l'élément
                T_Sommet *nouveauSommet = creerSommet(element + 1);
                nouveauSommet->filsDroit = abr->filsDroit;
                abr->filsDroit = nouveauSommet;
                abr->borneSup = element - 1;
                return abr;
            }
        }
    }
    return abr;
}


// Calcule la taille en octets occupée par l'ABR
size_t tailleABR(T_Arbre abr) {
    if (abr == NULL) {
        return 0;
    }
    // Taille du sommet
    size_t tailleSommet = sizeof(T_Sommet);
    // Taille des sous-arbres gauche et droit
    size_t tailleGauche = tailleABR(abr->filsGauche);
    size_t tailleDroit = tailleABR(abr->filsDroit);
    // Taille totale de l'ABR
    return tailleSommet + tailleGauche + tailleDroit;
}

// Calcule la taille en octets qu'aurait occupé un ABR dans la représentation classique
size_t tailleABRClassique(T_Arbre abr) {
    if (abr == NULL) {
        return 0;
    }
    // Taille d'un élément individuel de l'ensemble (par exemple, un entier)
    size_t tailleElement = sizeof(int);
    // Taille des sous-arbres gauche et droit
    size_t tailleGauche = tailleABRClassique(abr->filsGauche);
    size_t tailleDroit = tailleABRClassique(abr->filsDroit);
    // Taille totale de l'ABR dans la représentation classique
    return tailleElement + tailleGauche + tailleDroit;
}

void tailleMemoire(T_Arbre abr) {
    size_t tailleABRIntervalle = tailleABR(abr);
    size_t tailleABRClass = tailleABRClassique(abr);

    printf("Taille de l'ABR par intervalles: %zu octets\n", tailleABRIntervalle);
    printf("Taille de l'ABR dans la représentation classique: %zu octets\n", tailleABRClass);
    printf("Nombre d'octets gagnés par la représentation par intervalles: %zu octets\n", tailleABRClass - tailleABRIntervalle);
}


