#ifndef TP4_H
#define TP4_H

typedef struct T_Sommet T_Sommet;
typedef struct T_Sommet2 T_Sommet2;
typedef T_Sommet* T_Arbre;

struct T_Sommet {
    int borneInf;
    int borneSup;
    T_Arbre filsGauche;
    T_Arbre filsDroit;
};

struct T_Sommet2 {
    int element;
    T_Arbre filsGauche;
    T_Arbre filsDroit;
};

T_Arbre creerSommet(int element);
T_Arbre insererElement(T_Arbre abr, int element);
T_Sommet *rechercherElement(T_Arbre abr, int element);
void afficherSommets(T_Arbre abr);
void afficherElements(T_Arbre abr);
T_Arbre supprimerElement(T_Arbre abr, int element);
unsigned int tailleMemoireIntervalles(T_Arbre abr);
unsigned int tailleMemoireClassique(T_Arbre abr);
void tailleMemoire(T_Arbre abr);

#endif /* TP4_H */
