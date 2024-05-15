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

typedef struct T_Arbre {
    T_Sommet *racine;
} T_Arbre;
// ou 
typedef T_Sommet* T_Arbre;


T_Sommet *creerSommet(int element)
//ff

T_Arbre insererElement(T_Arbre abr, int element)