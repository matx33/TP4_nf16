#include "tp4.h"
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

void afficherElements(T_Arbre abr) {
    if (abr == NULL) {
        return;
    }
    afficherElements(abr->filsGauche);
    printf("%d ", abr->borneInf);
    // Si l'intervalle n'est pas un singleton, affiche les éléments entre borneInf et borneSup inclus
    if (abr->borneInf != abr->borneSup) {
        for (int i = abr->borneInf + 1; i <= abr->borneSup; i++) {
            printf("%d ", i);
        }
    }
    afficherElements(abr->filsDroit);
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


// Fonction pour calculer la taille en octets occupée par l'arbre dans la représentation par intervalles
unsigned int tailleMemoireIntervalles(T_Arbre abr) {
  if (abr == NULL) {
    return 0;
  }

  // Taille de chaque sommet dans la représentation par intervalles
  unsigned int tailleSommet = sizeof(T_Sommet);

  // Variable pour compter le nombre d'intervalles uniques
  unsigned int nbIntervalles = 1;

  // Parcourir l'arbre récursivement
  if (abr->filsGauche != NULL) {
    nbIntervalles += tailleMemoireIntervalles(abr->filsGauche);

    // Vérifier si l'intervalle du fils gauche se termine à la même borne que l'intervalle actuel
    if (abr->filsGauche->borneSup == abr->borneInf - 1) {
      nbIntervalles--; // Fusionner les intervalles adjacents
    }
  }

  if (abr->filsDroit != NULL) {
    nbIntervalles += tailleMemoireIntervalles(abr->filsDroit);

    // Vérifier si l'intervalle du fils droit commence à la même borne que l'intervalle actuel
    if (abr->filsDroit->borneInf == abr->borneSup + 1) {
      nbIntervalles--; // Fusionner les intervalles adjacents
    }
  }

  // Taille totale de l'arbre (sommet + taille des intervalles des fils)
  unsigned int tailleArbre = tailleSommet * nbIntervalles;
  return tailleArbre;
}


unsigned int tailleMemoireClassique(T_Arbre abr) {
  if (abr == NULL) {
    return 0; // Taille d'un nœud feuille (singleton)
  }

  // Taille d'un nœud interne
  unsigned int tailleSommet = sizeof(T_Sommet);

  // Taille des sous-arbres gauche et droit
  unsigned int tailleGauche = tailleMemoireClassique(abr->filsGauche);
  unsigned int tailleDroite = tailleMemoireClassique(abr->filsDroit);

  // Déterminer le nombre d'éléments représentés par le nœud actuel
  int nbElements = 1; // Compte l'élément actuel
  if (abr->filsGauche != NULL) {
    // Si le fils gauche existe, ajouter le nombre d'éléments dans son sous-arbre
    if (abr->filsGauche->borneSup == abr->borneInf - 1) {
      // Intervalle adjacent, fusionner les éléments
      nbElements += abr->filsGauche->borneSup - abr->filsGauche->borneInf + 1;
    } else {
      // Intervalles distincts, ajouter le nombre d'éléments du sous-arbre
      nbElements += tailleMemoireClassique(abr->filsGauche);
    }
  }

  if (abr->filsDroit != NULL) {
    // Si le fils droit existe, ajouter le nombre d'éléments dans son sous-arbre
    if (abr->filsDroit->borneInf == abr->borneSup + 1) {
      // Intervalle adjacent, fusionner les éléments
      nbElements += abr->filsDroit->borneSup - abr->filsDroit->borneInf + 1;
    } else {
      // Intervalles distincts, ajouter le nombre d'éléments du sous-arbre
      nbElements += tailleMemoireClassique(abr->filsDroit);
    }
  }

  // Taille totale du nœud (taille du nœud + taille des sous-arbres * nombre d'éléments)
  unsigned int tailleNoeud = tailleSommet + nbElements * sizeof(int);

  return tailleNoeud;
}



// Fonction pour afficher la taille en octets occupée par l'ABR, la taille qu'aurait occupée un ABR dans la représentation classique, et le nombre d'octets gagnés
void tailleMemoire(T_Arbre abr) {
    unsigned int tailleIntervalles = tailleMemoireIntervalles(abr);
    unsigned int tailleClassique = tailleMemoireClassique(abr);
    printf("Taille en octets occupée par l'ABR dans la représentation par intervalles: %u\n", tailleIntervalles);
    printf("Taille en octets qu'aurait occupée un ABR dans la représentation classique: %u\n", tailleClassique);
    printf("Nombre d'octets gagnés par la représentation par intervalles: %d\n", tailleClassique - tailleIntervalles);
}
