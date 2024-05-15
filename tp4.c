#include <stdio.h>
#include <stdlib.h>

typedef struct T_Sommet{
    int borneInf;
    int bornreSup;
    struct T_Sommet *filsGauche;
    struct T_Sommet *filsDroit;
} T_Sommet;

typedef T_Arbre *T_Sommet;


T_Sommet *creerSommet(int element)
//ff

T_Arbre insererElement(T_Arbre abr, int element)