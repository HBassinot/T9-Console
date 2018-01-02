/******************************************************************************/
/* BASSINOT Hervé                                         Licence Maths/Infos */
/* CHATEL Grégory                                               L3.1 Groupe 1 */
/* Projet T9 arbre lexicographique                                    2009/10 */
/*                                                                            */
/******************************************************************************/
/* Fichier : recherchePrefixe.c                                               */
/******************************************************************************/
/* Description : Ce fichier contient toutes les fonctions qui recherchent un  */
/*               mot dans l'arbre en mode prefixe. Avec un arbre minimisé ou  */
/*               non.                                                         */
/*                                                                            */
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h"
#include "saisi.h"
#include "arbrePrincipal.h"
#include "clavierTelephone.h"
#include "affichage.h"

/**********************************************************************
 * Fonction : parcourirArbreAuxiliaire                                *
 *                                                                    *
 * Cette fonction est chargée de parcourir l'arbre auxiliaire reçu en *
 * argument pour en afficher les mots. Les numéros de touche sont     *
 * dans un premier temps recherchés dans le tableau mot puis,         *
 * lorsqu'on a lu tous les numéros du préfixe, on cherche les numéros *
 * de touche dans le tableau suffixeAjoute dans lequel on a stocké    *
 * les numéros de touches que l'on a ajouté au préfixe entré par      *
 * l'utilisateur. On arrete de descendre dans l'arbre quand la racine *
 * courante est nulle ou bien quand la profondeur courante est        *
 * égale a la somme des tailles du mot et du suffixe ajoute. Si à     *
 * l'endroit où on s'arrête le noeud est terminal, on affiche le      *
 * contenu du buffer.                                                 *
 *                                                                    *
 * Arguments : L'arbre auxiliaire a parcourir, le tableau             *
 *             représentant la suite de chiffre entrée par            *
 *             l'utilisateur, le suffixe (suite de numéro de touche)  *
 *             que l'on a ajouté au mot entré par l'utilisateur pour  *
 *             atteindre cet arbre auxiliaire, le buffer dans lequel  *
 *             on va stocker les caractères à afficher lors du        *
 *             parcours de l'arbre auxiliaire, la taille du mot entré *
 *             par l'utilisateur, la taille du suffixe ajoute,        *
 *             l'indice représentant la profondeur courante dans      *
 *             l'arbre auxiliaire.                                    *
 * Complexité : O(n) où n est le nmbre de noeud de l'arbre            *
 *              auxiliaire.                                           *
 * Retour : Aucun.                                                    *
 *********************************************************************/

static void parcourirArbreAuxiliaire(ArbreAuxiliaire arbre, char mot[], 
				     char suffixeAjoute[], 
				     char bufferResultat[], int tailleMot,
				     int tailleSuffixeAjoute, int indice) {
    int i;
    int numeroTouche;

    if (arbre == NULL) {
	return;
    }

    if (indice == tailleMot + tailleSuffixeAjoute) {
	if (arbre->statut == TERMINAL) {
	    afficherMot(bufferResultat, tailleMot + tailleSuffixeAjoute);
	}
	return;
    }  

    if (indice >= tailleMot) {
	numeroTouche = suffixeAjoute[indice - tailleMot];
    } else {
	numeroTouche = mot[indice];
    }

    for (i = 0; i < NB_LETTRE; i++) {
	bufferResultat[indice] = alphabetTouche(numeroTouche, i + 1);
	parcourirArbreAuxiliaire(arbre->fils[i], mot, suffixeAjoute,
				 bufferResultat, tailleMot, tailleSuffixeAjoute,
				 indice + 1);
    }
}

/**********************************************************************
 * Fonction : parcourirArbreRec                                       *
 *                                                                    *
 * Cette fonction est chargée de parcourir la totalité de l'arbre     *
 * reçu en argument en mémorisant les branches empruntées au fur et à *
 * mesure de la descente. Les numéros des branches empruntées sont    *
 * stockés dans le tableau suffixe ajouté pour permettre à la         *
 * fonction parcourirArbreAuxiliaire de savoir quelles lettres        *
 * afficher. Chaque fois qu'un noeud terminal est rencontré, cette    *
 * fonction appelle parcourirArbreAuxiliaire pour en afficher le      *
 * contenu.                                                           *
 *                                                                    *
 * Arguments : L'arbre a parcourir, le mot entré par l'utilisateur,   *
 *             le tableau dans lequel on stocke les branches          *
 *             empruntées, le buffer qui va servir à afficher le      *
 *             résultat, l'indice représentant la profondeur          *
 *             courante, la taille du mot entré par l'utilisateur.    *
 * Complexité : O(n + m) où n est le nombre de noeud de l'arbre       *
 *              principal reçu en argument et m est la somme des      *
 *              nombres de noeuds des arbres auxiliaires auxquels on  *
 *              peut accéder depuis l'arbre reçu en argument.         *
 * Retour : Aucun.                                                    *
 *********************************************************************/

static void parcourirArbreRec(ArbrePrincipal arbre, char mot[], 
			      char suffixeAjoute[], char bufferResultat[],
			      int indice, int tailleMot) {
    int i;

    if (arbre == NULL) {
	return;
    }

    if (arbre->arbreAux != NULL) {
	parcourirArbreAuxiliaire(arbre->arbreAux, mot, suffixeAjoute, 
				 bufferResultat, tailleMot, indice, 0);
    }

    for (i = 0; i < NB_TOUCHE; i++) {
	suffixeAjoute[indice] = i + 2; 
	parcourirArbreRec(arbre->touche[i], mot, suffixeAjoute, bufferResultat,
			  indice + 1, tailleMot);
    }
}

/**********************************************************************
 * Fonction : parcourirArbre                                          *
 *                                                                    *
 * Cette fonction est chargée d'allouer les buffers qui vont être     *
 * utilisés lors du parcours de l'arbre en profondeur. Pour éviter    *
 * d'utiliser la fonction réalloc, on fait un parcours en profondeur  *
 * de l'arbre reçu en argument afin d'en connaitre la hauteur et par  *
 * conséquent, la taille maximum du suffixe qu'on pourra ajouter au   *
 * mot entré par l'utilisateur.                                       *
 *                                                                    *
 * Arguments : L'arbre principal à parcourir,le mot entré par         *
 *             l'utilisateur, la taille du mot entré par              *
 *             l'utilisateur.                                         *
 * Complexité : O(n + m) où n est le nombre de noeud de l'arbre       *
 *              principal reçu en argument et m est la somme des      *
 *              nombres de noeuds des arbres auxiliaires auxquels on  *
 *              peut accéder depuis l'arbre reçu en argument.         *
 * Retour : 0 si tout s'est bien passé, ERREUR_ALLOCATION si un       *
 *          malloc a échoué.                                          *
 *********************************************************************/

static int parcourirArbre(ArbrePrincipal arbre, char mot[], int tailleMot) {
    int tailleSuffixeAjoute;
    char* bufferResultat;
    char* suffixeAjoute;

    tailleSuffixeAjoute = hauteurArbrePrincipal(arbre);

    if ((bufferResultat = (char*) malloc((tailleSuffixeAjoute + tailleMot) *
					 sizeof (char))) == NULL) {
	return ERREUR_ALLOCATION;
    }

    if ((suffixeAjoute = (char*) malloc((tailleSuffixeAjoute + 1) * 
					sizeof (char))) == NULL) {
	return ERREUR_ALLOCATION;
    }

    parcourirArbreRec(arbre, mot, suffixeAjoute, bufferResultat, 0, tailleMot);
    free(bufferResultat);
    free(suffixeAjoute);

    return 0; /* Pas de problème */
}

/**********************************************************************
 * Fonction : parcourirArbrePrincipal                                 *
 *                                                                    *
 * Cette fonction est chargée de trouver le noeud de l'arbre          *
 * principal à partir duquel on va explorer toutes les branches ainsi *
 * que tout les arbres auxiliaires accessibles.                       *
 *                                                                    *
 * Arguments : L'arbre principal à parcourir, le mot entré par        *
 *             l'utilisateur, l'indice représentant la profondeur     *
 *             courante, la taille du mot entré par l'utilisateur.    *
 * Complexité : O(n) où n est la taille du mot entré par              *
 *              l'utilisateur.                                        *
 * Retour : Un pointeur vers le noeud principal (un ArbrePrincipal    *
 *          donc) recherché.                                          *
 *********************************************************************/

static ArbrePrincipal parcourirArbrePrincipal(ArbrePrincipal arbre, char mot[],
					      int indice, int tailleMot) {
    int numeroTouche;

    if (arbre == NULL) {
	return NULL;
    }

    if (indice == tailleMot) {
	return arbre;
    }

    numeroTouche = mot[indice] - 2;

    return parcourirArbrePrincipal(arbre->touche[numeroTouche], mot, indice + 1,
				   tailleMot);
}

/**********************************************************************
 * Fonction : rechercherPrefixe                                       *
 *                                                                    *
 * Cette fonction permet à l'utilisateur de rechercher dans l'arbre   *
 * du projet tout les mots qui ont en commun une chaîne de chiffres   *
 * qu'il saisit au clavier. Pour sortir de cette fonction,            *
 * l'utilisateur doit entrer le caractère 0.                          *
 *                                                                    *
 * Argument : L'arbre principal dans lequel on va rechercher les      *
 *            mots.                                                   *
 * Complexité : O(n * a) où n est le nombre de noeud des arbres       *
 *              principaux et auxiliaire et a est le nombre de mot    *
 *              saisi par l'utilisateur avant de sortir du programme. *
 * Retour : 0 si tout s'est bien passé, ERREUR_ALLOCATION si un       *
 *          appel à malloc a échoué.                                  *
 *********************************************************************/

extern int rechercherPrefixe(ArbrePrincipal arbre) {
    int tailleBuffer = TAILLE_MOT; /* La taille du buffer de lecture de mot */
    int continuer = 1;
    int tailleMot;
    ArbrePrincipal racinePrefixe; /* La racine depuis laquelle on va afficher 
				   * tous les arbres auxiliaires.
				   */
    char *mot;
    
    if ((mot = (char*) malloc(sizeof (char) * TAILLE_MOT)) == NULL) {
	return ERREUR_ALLOCATION;
    }
   
    printf("Saisi OK\n");
    while (continuer) {
	/* Si le mot saisi est valide */
	if ((tailleMot = saisiMot(&mot, &tailleBuffer)) != -1) {
	    racinePrefixe = parcourirArbrePrincipal(arbre, mot, 0, tailleMot);
	    if (racinePrefixe == NULL) {
		printf("Aucun mot trouve !!\n");
	    } else {
		if (parcourirArbre(racinePrefixe, mot, tailleMot) 
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
