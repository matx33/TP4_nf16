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
    if (element + 1 < abr->borneInf){
        T_sommet *nouveauSommet = creerSommet(element);
        abr->filsGauche = nouveauSommet;
    }
    if (abr->borneSup + 1 < element){
        T_sommet *nouveauSommet = creerSommet(element);
        abr->filsDroit = nouveauSommet;
    }
    else{
        abr->borneInf = min(abr->borneInf, element);
        abr->borneSup = max(abr->borneSup, element);
    }
}

T_Arbre insererElement(T_Arbre abr, int element){
    if (abr == NULL){
        return creerSommet(element);
    }
    if (element + 1 < abr->borneInf){
        T_sommet *nouveauSommet = creerSommet(element);
        abr->filsGauche = nouveauSommet;
    }
    if (abr->borneSup + 1 < element){
        T_sommet *nouveauSommet = creerSommet(element);
        abr->filsDroit = nouveauSommet;
    }
    else{
        abr->borneInf = min(abr->borneInf, element);
        abr->borneSup = max(abr->borneSup, element);
    }
}

