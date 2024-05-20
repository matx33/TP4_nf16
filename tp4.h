#ifndef TP4_H
#define TP4_H

typedef struct T_Sommet T_Sommet;
typedef struct T_Sommet2 T_Sommet2; // Simule un sommet classique (caractérisé par un entier unique plutot que des bornes inf et sup)
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
T_Sommet* rechercherPere(T_Arbre abr, int element);
void afficherSommets(T_Arbre abr);
void afficherElements(T_Arbre abr);
void insererIntervallesDroite(T_Arbre *abr, int element, int borneSup);
T_Arbre supprimerElement(T_Arbre abr, int element);
unsigned int tailleMemoireIntervalles(T_Arbre abr);
unsigned int tailleMemoireClassique(T_Arbre abr);
void tailleMemoire(T_Arbre abr);

// Nouvelle fonction pour obtenir la racine de l'arbre
T_Arbre obtenirRacine(T_Arbre abr);

// Fonctions pour insérer et supprimer plusieurs éléments
void insererPlusieursElements(T_Arbre *abr);
void supprimerPlusieursElements(T_Arbre *abr);

#endif /* TP4_H */
