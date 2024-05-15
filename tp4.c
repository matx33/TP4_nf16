#include <stdio.h>
#include <stdlib.h>
//1, 2, 3, 4 
//5, 6, 7


typedef struct T_Sommet{
    int borneInf;
    int bornreSup;
    struct T_Sommet *filsGauche;
    struct T_Sommet *filsDroit;
} T_Sommet;

typedef T_Sommet* T_Arbre;


T_Sommet *creerSommet(int element){
    T_sommet *sommet = (T_Sommet *)malloc(sizeof(T_Sommet));
    sommet->borneInf = element;
    sommet->borneSup = element;
    sommet->filsGauche = NULL;
    sommet->filsDroit = NULL;
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


