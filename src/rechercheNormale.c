/******************************************************************************/
/* BASSINOT Hervé                                         Licence Maths/Infos */
/* CHATEL Grégory                                               L3.1 Groupe 1 */
/* Projet T9 arbre lexicographique                                    2009/10 */
/*                                                                            */
/******************************************************************************/
/* Fichier : rechercheNormale.c                                               */
/******************************************************************************/
/* Description : Ce fichier contient toutes les fonctions qui recherchent un  */
/*               mot dans l'arbre en mode normal. Avec un arbre Minimisé ou   */
/*               ou non.                                                      */
/*                                                                            */
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h"
#include "saisi.h"
#include "arbrePrincipal.h"
#include "arbreAuxiliaire.h"
#include "clavierTelephone.h"
#include "rechercheNormale.h"
#include "affichage.h"

/**********************************************************************
 * Fonction : parcourirArbreAuxiliaire                                *
 *                                                                    *
 * Cette fonction est chargée de parcourir un arbre auxiliaire pour   *
 * afficher les mots correspondant au mot entré par l'utilisateur.    *
 * Cette fonction ne descend pas plus bas dans l'arbre que la taille  *
 * du mot entré par l'utilisateur. Pour qu'un mot soit afficher, il   *
 * necessaire que le noeud de l'arbre auxiliaire correspondant à sa   *
 * dernière lettre soit situé à une distance égale à la taille du mot *
 * de la racine et que ce noeud soit terminal. Cette méthode          *
 * d'affichage permet d'écrire une unique fonction, que les arbres    *
 * soit minimisés ou non.                                             *
 *                                                                    *
 * Arguments : L'arbre auxiliaire à parcourir, le mot entré par       *
 *             l'utilisateur, le buffer dans lequel les lettres       *
 *             correspondant aux branches parcourues vont être        *
 *             recopiées, l'indice représentant la profondeur par     *
 *             rapport à la racine, la taille du mot entré par        *
 *             l'utilisateur.                                         *
 * Compléxité : O(n) où n est le nombre de noeuds accessibles depuis  *
 *              la racine reçues en argument situés à une distance    *
 *              (en arêtes) de tailleMot maximum.                     *
 * Retour : Aucun.                                                    *
 *********************************************************************/

static void parcourirArbreAuxiliaireIndice(ArbreAuxiliaire arbre, char mot[],
					   char res[], int indice, 
					   int tailleMot) {
    int i;
    int numeroTouche; /* numéro de la touche du téléphone correspondant à la 
		       * branche qui va être explorée.
		       */

    if (arbre == NULL) {
	return;
    }

    if (indice == tailleMot) {
	if (arbre->statut == TERMINAL) {
	    afficherMot(res, indice);
	}
	return;
    }
  
    numeroTouche = mot[indice];
    for (i = 0; i < NB_LETTRE; i++) {
	res[indice] = alphabetTouche(numeroTouche, i + 1);
	parcourirArbreAuxiliaireIndice(arbre->fils[i], mot, res, indice + 1, 
				       tailleMot);
    }
}

/**********************************************************************
 * Fonction : parcourirArbreAuxiliaire                                *
 *                                                                    *
 * Cette fonction est une surcouche de la fonction                    *
 * parcourirArbreAuxiliaireIndice. Elle sert à allouer le buffer qui  *
 * va être utilisé pour afficher les mots trouvés dans l'arbre        *
 * auxiliaire.                                                        *
 *                                                                    *
 * Arguments : L'arbre auxiliaire à parcourir, le mot entré par       *
 *             l'utilisateur, la taille du mot entré par              *
 *             l'utilisateur.                                         *
 * Complexité : La même complexité que la fonction                    *
 *              parcourirArbreAuxiliaireIndice                        *
 * Retour : 0 si tout s'est bien passé, ERREUR_ALLOCATION si l'appel  *
 *          à malloc a échoué.                                        *
 *********************************************************************/

static int parcourirArbreAuxiliaire(ArbreAuxiliaire arbre, char mot[], 
				    int tailleMot) {
    char* res;

    if ((res = (char*) malloc(sizeof (char) * tailleMot)) == NULL) {
	return ERREUR_ALLOCATION; 
    }
    parcourirArbreAuxiliaireIndice(arbre, mot, res, 0, tailleMot);
    free(res);

    return 0; /* A remplacer avec un define pour PAS_DE_PROBLEME */
}

/**********************************************************************
 * Fonction : parcourArbrePrincipal                                   *
 *                                                                    *
 * Cette fonction est chargée de trouver l'arbre auxiliaire dans      *
 * lequel on va trouver les mots correspondant à la chaine entrée par *
 * l'utilisateur.                                                     *
 *                                                                    *
 * Arguments : L'arbre principal dans lequel on va chercher l'arbre   *
 *             auxiliaire, le mot entré par l'utilisateur,  l'indice  *
 *             représentant la profondeur par rapport à la racine,    *
 *             la taille du mot entré par l'utilisateur.              *
 * Complexité : O(n) où n est la taille du mot entré par              *
 *              l'utilisateur.                                        *
 * Retour : L'arbre auxiliaire correspondant s'il a pu être trouvé,   *
 *          NULL sinon.                                               *
 *********************************************************************/

static ArbreAuxiliaire parcourirArbrePrincipal(ArbrePrincipal arbre, char mot[],
					       int indice, int tailleMot) {
    int numeroTouche = mot[indice] - 2;

    if (arbre == NULL) {
	return NULL;
    }

    if (indice == tailleMot) {
	return arbre->arbreAux;
    }

    return parcourirArbrePrincipal(arbre->touche[numeroTouche], mot, 
				   indice + 1, tailleMot);
}

/**********************************************************************
 * Fonction : rechercherNormal                                        *
 *                                                                    *
 * Cette fonction permet à l'utilisateur de rechercher dans l'arbre   *
 * du projet tout les mots correspondant à une chaîne de chiffres     *
 * qu'il saisit au clavier. Pour sortir de cette fonction,            *
 * l'utilisateur doit entrer le caractère 0.                          *
 *                                                                    *
 * Argument : L'arbre principal dans lequel on va rechercher les      *
 *             mots.                                                  *
 * Complexité : O(n * a) où n est le nombre de noeud des arbres       *
 *              principaux et auxiliaire et a est le nombre de mot    *
 *              saisi par l'utilisateur avant de sortir du programme. *
 * Retour : 0 si tout s'est bien passé, ERREUR_ALLOCATION si un       *
 *          appel à malloc a échoué.                                  *
 *********************************************************************/

extern int rechercherNormal(ArbrePrincipal arbre) {
    ArbreAuxiliaire auxi;
    int tailleBuffer = TAILLE_MOT;
    int continuer = 1;
    int tailleMot;
    char *mot;
    
    if ((mot = (char *) malloc(sizeof (char) * tailleBuffer)) == NULL) {
	return ERREUR_ALLOCATION;
    }
    
    printf("Saisi OK\n");
    while (continuer != 0) {
	/* Si le mot saisie est valide */
	if ((tailleMot = saisiMot(&mot, &tailleBuffer)) != -1) {
	    auxi = parcourirArbrePrincipal(arbre, mot, 0, tailleMot);
	    if (auxi == NULL) {
		printf("Aucun mot trouve !!\n");
	    } else {
		if (parcourirArbreAuxiliaire(auxi, mot, tailleMot) 
		    == ERREUR_ALLOCATION) {
		    return ERREUR_ALLOCATION;
		}
	    }
        } else if ((continuer = controlSortie(mot)) == 1) {
	    printf("Mot non valide !!\n");
        } else {
	    printf("FIN DU PROGRAMME\n");
        }
    }
    free(mot);
    return 0;
}
