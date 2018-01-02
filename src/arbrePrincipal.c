/******************************************************************************/
/* BASSINOT Hervé                                         Licence Maths/Infos */
/* CHATEL Grégory                                               L3.1 Groupe 1 */
/* Projet T9 arbre lexicographique                                    2009/10 */
/*                                                                            */
/******************************************************************************/
/* Fichier : arbrePrincipal.c                                                 */
/******************************************************************************/
/* Description : Ce fichier contient toutes les fonctions utiles pour la      */
/*               manipulation de l'arbre principal.                           */
/*                                                                            */
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h"
#include "clavierTelephone.h"
#include "arbreAuxiliaire.h"
#include "liberation.h"

/**********************************************************************
 * Fonction : creerNoeudPrincipal                                     *
 *                                                                    *
 * Cette fonction alloue un noeud de l'arbre principal et initialise  *
 * la valeur de ses champs en utilisant des valeurs par défaut.       *
 *                                                                    *
 * Argument : Aucun.                                                  *
 * Complexité : O(n) où n est la taille du tableau de fils d'un       *
 *              noeud.                                                *
 * Retour : Le noeud alloué si tout s'est bien passé, NULL s'il y a   *
 *          eu une erreur d'allocation.                               *
 *********************************************************************/

static NoeudPrincipal* creerNoeudPrincipal(void) {
    NoeudPrincipal* noeud;
    int i;

    if ((noeud = (NoeudPrincipal*) malloc(sizeof (NoeudPrincipal))) == NULL) {
	return NULL;
    }

    for (i = 0; i < NB_TOUCHE; i++) {
	noeud->touche[i] = NULL;
    }
    noeud->arbreAux = NULL;
    noeud->visite = NON_VISITE;
    
    return noeud;
}

/**********************************************************************
 * Fonction : insererMotIndicePrincipal                               *
 *                                                                    *
 * Cette fonction insère un mot dans dans l'arbre principal. Une fois *
 * que toutes les lettres du mot on étées lues, on insère le mot dans *
 * l'arbre auxiliaire de la racine courante.                          *
 *                                                                    *
 * Arguments : L'arbre dans lequel on souhaite insérer le mot, le mot *
 *             à insérer, l'indice de parcours du mot.                *
 * Complexité : O(n) où n est la taille du mot.                       *
 * Retour : 1 pour une erreur d'allocation, 0 si tout s'est bien      *
 *          passé.                                                    *
 *********************************************************************/

static int insererMotIndicePrincipal(ArbrePrincipal * arbre, char mot[],
				     int indice) {
    int numeroTouche;

    if (*arbre == NULL && (*arbre = creerNoeudPrincipal()) == NULL) {
	return 1;
    }

    if (mot[indice] == '\0') {
	return insererMotAuxiliaire(&((*arbre)->arbreAux), mot);
    }

    numeroTouche = toucheLettre(mot[indice]) - 2;
  
    return insererMotIndicePrincipal(&((*arbre)->touche[numeroTouche]), 
				     mot, indice + 1);
}

/**********************************************************************
 * Fonction : insererMotPrincipal                                     *
 *                                                                    *
 * Cette fonction est une surcouche de la fonction                    *
 * insererMotIndicePrincipal. Elle a été mise en place pour           *
 * simplifier l'appel de cette fonction pour l'utilisateur de ce      *
 * fichier.                                                           *
 *                                                                    *
 * Arguments : L'arbre dans lequel on doit insérer le mot, le mot à   *
 *             insérer.                                               *
 * Complexité : O(n) où n est la taille du mot.                       *
 * Retour : Le retour de la fonction insererMotIndicePrincipal.       *
 *********************************************************************/

extern int insererMotPrincipal(ArbrePrincipal * arbre, char mot[]) {
    return insererMotIndicePrincipal(arbre, mot, 0);
}
/**********************************************************************
 * Fonction : libererPrincipalRec                                     *
 *                                                                    *
 * Cette fonction fait un parcours en profondeur de l'arbre principal *
 * et libère ses noeuds lors de la phase remontante de la recursion.  *
 * Le pointeur est mit à NULL après la libération. Les arbres         *
 * auxiliaires sont aussi libérés.                                    *
 *                                                                    *
 * Argument : L'arbre que l'on souhaite libérer.                      *
 * Complexité : O(n + a) où n est le nombre de noeud de l'arbre       *
 *              principal et a la somme des nombres de noeud de tous  *
 *              les arbres auxiliaires.                               *
 * Retour : Aucun.                                                    *
 *********************************************************************/

static void libererPrincipalRec(ArbrePrincipal* arbre) {
    int i;

    if (*arbre == NULL) {
	return;
    }

    libererAuxiliaire(&((*arbre)->arbreAux));
 
    for (i = 0; i < NB_TOUCHE; i++) {
	libererPrincipalRec(&((*arbre)->touche[i]));
    }
 
    liberer(*arbre);
    *arbre = NULL;
}

/**********************************************************************
 * Fonction : libererPrincipal                                        *
 *                                                                    *
 * Cette fonction est une surcouche de la fonction                    *
 * libererPrincipalRec. Elle a été mise en place pour permettre la    *
 * libération des arbres minimisés par le biais du module de          *
 * libération. Après chaque série de libération la fonction           *
 * reinitialiserLiberateur doit être appelée.                         *
 *                                                                    *
 * Argument : L'arbre que l'on souhaite libérer.                      *
 * Complexité : O(n + a) où n est le nombre de noeud de l'arbre       *
 *              principal et a la somme des nombres de noeud de tous  *
 *              les arbres auxiliaires.                               *
 * Retour : Aucun.                                                    *
 *********************************************************************/

extern void libererPrincipal(ArbrePrincipal* arbre) {
    libererPrincipalRec(arbre);
    reinitialiserLiberateur();
}

/**********************************************************************
 * Fonction : compteMotPrincipalFusionProfondeur                      *
 *                                                                    *
 * Cette fonction compte le nombre de mot reconnu par l'arbre         *
 * principal après fusion. Elle effectue un parcours en profondeur de *
 * l'arbre en mémorisant la hauteur par rapport à la racine courante. *
 * Si la racine courante possède un arbre auxiliaire, la fonction     *
 * compteMotAuxiliaireProfondeur est appelée. Cette fonction compte   *
 * le nombre de mot reconnus par l'arbre en lisant un nombre de       *
 * lettre équivalent à la profondeur reçue en argument.               *
 *                                                                    *
 * Arguments : L'arbre dont on souhaite compter le nombre de mot,     *
 *             la profondeur courante (initialement 0).               *
 * Complexité : O(n + m) où n est le nombre de noeud de l'arbre       *
 *              principal et m est la somme des nombres de noeud de   *
 *              tous les arbres auxiliaires.                          *
 * Retour : Le nombre de mot reconnu par cet arbre.                   *
 *********************************************************************/

static int compteMotPrincipalFusionProfondeur(ArbrePrincipal arbre, 
					      int profondeur) {
    int nbMot = 0;
    int i;

    if (arbre == NULL) {
	return 0;
    }

    if (arbre->arbreAux != NULL) {
	nbMot = compteMotAuxiliaireProfondeur(arbre->arbreAux, profondeur);
    }

    for (i = 0; i < NB_TOUCHE; i++) {
	nbMot += compteMotPrincipalFusionProfondeur(arbre->touche[i], 
						    profondeur + 1);
    }

    return nbMot;
}

/**********************************************************************
 * Fonction : compteMotPrincipalFusion                                *
 *                                                                    *
 * Cette fonction est une surcouche de la fonction                    *
 * compteMotPrincipalFusionProfondeur. Elle a été mise en place pour  *
 * simplifier l'appel de cette fonction pour l'utilisateur de ce      *
 * fichier.                                                           *
 *                                                                    *
 * Argument : L'arbre dont on souhaite compter le nombre de mot.      *
 * Complexité : La compléxité de la fonction                          *
 *              compteMotPrincipalFusionProfondeur.                   *
 * Retour : Le nombre de mot reconnu par cet arbre.                   *
 *********************************************************************/

extern int compteMotPrincipal(ArbrePrincipal arbre) {
    return compteMotPrincipalFusionProfondeur(arbre, 0);
}

/**********************************************************************
 * Fonction : hauteurArbrePrincipal                                   *
 *                                                                    *
 * Cette fonction fait un parcours en profondeur de l'arbre principal *
 * pour en déterminer la profondeur.                                  *
 *                                                                    *
 * Argument : L'arbre dont on souhaite calculer la hauteur.           *
 * Complexité : O(n) où n est le nombre de noeud de l'arbre.          *
 * Retour : La hauteur de l'arbre si arbre est différent de NULL, -1  *
 *          sinon.                                                    *
 *********************************************************************/

extern int hauteurArbrePrincipal(ArbrePrincipal arbre) {
    int hauteurFilsCourant;
    int maxHauteurFils = -1;
    int i;

    if (arbre == NULL) {
	return -1;
    }
    
    for (i = 0; i < NB_TOUCHE; i++) {
	hauteurFilsCourant = hauteurArbrePrincipal(arbre->touche[i]);
	if (hauteurFilsCourant > maxHauteurFils) {
	    maxHauteurFils = hauteurFilsCourant;
	}
    }
    
    return 1 + maxHauteurFils;
}

/**********************************************************************
 * Fonction : reinitialiseVisite                                      *
 *                                                                    *
 * Cette fonction est chargée de réinitialiser le champs visite de    *
 * tous les noeud de l'arbre principal reçu en argument.              *
 *                                                                    *
 * Argument : L'arbre dont on souhaite réinitialiser les champs       *
 *            visite.                                                 *
 * Complexité : O(n) où n est le nombre de noeud de l'arbre principal *
 *              reçu en argument.                                     *
 * Retour : Aucun.                                                    *
 *********************************************************************/

static void reinitialiseVisite(ArbrePrincipal arbre) {
    int i;

    if (arbre == NULL) {
    	return;
    }

    arbre->visite = NON_VISITE;

    for (i = 0; i < NB_TOUCHE; i++) {
    	reinitialiseVisite(arbre->touche[i]);
    }
}

/**********************************************************************
 * Fonction : compteNoeudPrincipalVisite                              *
 *                                                                    *
 * Cette fonction permet de compter le nombre de noeud de l'arbre     *
 * principal reçu en argument. Elle utilise le champs visite pour ne  *
 * pas compter plusieurs fois le même noeud.                          *
 *                                                                    *
 * Argument : L'arbre dont on souhaite compter le nombre de noeud.    *
 * Complexité : O(n) où n est le nombre de noeud de l'arbre           *
 *              principal.                                            *
 * Retour : Le nombre de noeud de l'arbre reçu en argument.           *
 *********************************************************************/

static int compteNoeudPrincipalVisite(ArbrePrincipal arbre) {
    int i;
    int somme = 1;

    if (arbre == NULL || arbre->visite == VISITE) {
	return 0;
    }
    
    arbre->visite = VISITE;

    for (i = 0; i < NB_TOUCHE; i++) {
	somme += compteNoeudPrincipalVisite(arbre->touche[i]);
    }

    return somme;
}

/**********************************************************************
 * Fonction : compteNoeudPrincipal                                    *
 *                                                                    *
 * Cette fonction est une surcouche à la fonction                     *
 * compteNoeudPrincipalVisite. Elle a été mise en place pour          *
 * permettre l'appel à la fonction reinitialiseVisite qui             *
 * réinitialise le champs visite de tous les noeuds de l'arbre        *
 * principal.                                                         *
 *                                                                    *
 * Argument : L'arbre dont on souhaite compter les noeuds.            *
 * Complexité : O(n) où n est le nombre de noeud de l'arbre.          *
 * Retour : Le nombre de noeud de l'arbre.                            *
 *********************************************************************/

extern int compteNoeudPrincipal(ArbrePrincipal arbre) {
    int res = compteNoeudPrincipalVisite(arbre);

    reinitialiseVisite(arbre);

    return res;
}

