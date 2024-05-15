#ifndef TP4_H
#define TP4_H

typedef struct T_Sommet T_Sommet;
typedef T_Sommet* T_Arbre;

struct T_Sommet {
    int borneInf;
    int borneSup;
    T_Arbre filsGauche;
    T_Arbre filsDroit;
};

T_Arbre creerSommet(int element);
T_Arbre insererElement(T_Arbre abr, int element);
T_Sommet *rechercherElement(T_Arbre abr, int element);

#endif /* TP4_H */

