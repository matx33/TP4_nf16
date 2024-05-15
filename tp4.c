#include <stdio.h>
#include <stdlib.h>

typedef struct T_Sommet{
    int borneInf;
    int bornreSup;
    struct T_Sommet *filsGauche;
    struct T_Sommet *filsDroit;
} T_Sommet;

typedef T_Arbre *T_Sommet;

// test 2