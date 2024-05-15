#include <stdio.h>
#include <stdlib.h>

// Macro pour déterminer le maximum et le minimum entre deux valeurs (utilisees pour les bornes des intervalles)
#define max(a,b) \
    ({ typeof (a) _a = (a); \
        typeof (b) _b = (b); \
        _a > _b ? _a : _b; })

#define min(a,b) \
    ({ typeof (a) _a = (a); \
        typeof (b) _b = (b); \
        _a < _b ? _a : _b; })

//1, 2, 3, 4 
//5, 6, 7


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


