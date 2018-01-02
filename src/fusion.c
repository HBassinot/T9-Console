/******************************************************************************/
/* BASSINOT Hervé                                         Licence Maths/Infos */
/* CHATEL Grégory                                               L3.1 Groupe 1 */
/* Projet T9 arbre lexicographique                                    2009/10 */
/*                                                                            */
/******************************************************************************/
/* Fichier : fusion.c                                                         */
/******************************************************************************/
/* Description : Ce fichier contient toutes les fonctions de fusion des       */
/*               arbres.                                                      */
/*                                                                            */
/******************************************************************************/

#include <stdlib.h>

#include "structures.h"
#include "listeNoeud.h"
#include "arbrePrincipal.h"
#include "arbreAuxiliaire.h"

/**********************************************************************
 * Fonction : fusionnerArbreAuxRec                                    *
 *                                                                    *
 * Cette fonction fusionne le contenu de l'arbre2 dans l'arbre1. Au   *
 * fur et à mesure que les fusions sont faites, cette fonction        *
 * supprime les liens du deuxième arbre2 sur ses branches qui ont     *
 * été ajoutées à l'arbre1. Ce mécanisme permet de faciliter la       *
 * libération des branches communes après fusion.                     *
 *                                                                    *
 * Arguments : Les deux arbres auxiliaires à fusionner.               *
 * Complexité : O(n) où n est la somme des nombres de noeuds des deux *
 *              arbres auxiliaires.                                   *
 * Retour : L'arbre auxiliaire contenant les deux arbres auxiliaires  *
 *          reçus en argument.                                        *
 *********************************************************************/

static ArbreAuxiliaire fusionnerArbreAuxRec(ArbreAuxiliaire arbre1, 
					    ArbreAuxiliaire arbre2) {
    int i;

    if (arbre2->statut == TERMINAL) {
	arbre1->statut = TERMINAL;
    }

    for (i = 0; i < NB_LETTRE; i++) {
	if (arbre1->fils[i] != NULL && arbre2->fils[i] != NULL) {
	    arbre1->fils[i] = fusionnerArbreAuxRec(arbre1->fils[i], 
						   arbre2->fils[i]);
	} else if (arbre1->fils[i] == NULL && arbre2->fils[i] != NULL) {
	    arbre1->fils[i] = arbre2->fils[i];
	    arbre2->fils[i] = NULL;
	}
    }

    return arbre1;
}

/**********************************************************************
 * Fonction : fusionnerArbreAuxiliaire                                *
 *                                                                    *
 * Cette fonction est chargée de fusionner tous les arbres            *
 * auxiliaires appartenant au tableau de d'ArbrePrincipal reçu en     *
 * argument. Tous les arbres auxiliaires vont être fusionnés avec     *
 * de la dernière case du tableau.                                    *
 *                                                                    *
 * Arguments : Le tableau d'ArbrePrincipal dont on souhaite fusionner *
 *             les arbres auxiliaires, la taille de ce tableau.       *
 * Complexité : O(n * m) où n est le nombre de noeud d'un arbre       *
 *              et m est la taille du tableau.                        *
 * Retour : Aucun.                                                    *
 *********************************************************************/

static void fusionnerArbreAuxiliaire(ArbrePrincipal* aFusionner, int taille) {
    int i;

    if (taille == 0 || taille == 1) {
	return;
    }

    for (i = 0; i < taille - 1; i++) {
	aFusionner[taille - 1]->arbreAux = 
	    fusionnerArbreAuxRec(aFusionner[taille - 1]->arbreAux, 
				 aFusionner[i]->arbreAux);
    }

    for (i = 0; i < taille - 1; i++) {
	libererAuxiliaire(&(aFusionner[i]->arbreAux));
	aFusionner[i]->arbreAux = aFusionner[taille - 1]->arbreAux;
    }
}

/**********************************************************************
 * Fonction : construireTableRec                                      *
 *                                                                    *
 * Cette fonction est chargée de construire la table qui va contenir  *
 * les noeuds correspondant à une hauteur. Elle parcours l'arbre en   *
 * profondeur en mémorisant la profondeur courante pour pouvoir       *
 * insérer le noeud dans la bonne table. L'algorithme de fusion est   *
 * décrit dans le rapport du projet.                                  *
 *                                                                    *
 * Arguments : Le tableau de liste de NoeudPrincipal, la racine de    *
 *             l'arbre qu'on souhaite insérer dans la table, la       *
 *             profondeur courante.                                   *
 * Complexité : O(n) où n est le nombre de noeud de la table car les  *
 *              ajouts dans les liste de noeuds se font en temps      *
 *              constant.                                             *
 * Retour : 0 si tout s'est bien passé, 1 si un appel à malloc a      *
 *          échoué.                                                   *
 *********************************************************************/

static int construireTableRec(ListeNoeudPrincipal* table, ArbrePrincipal arbre,
			      int profondeur) {
    MaillonNoeudPrincipal* maillonNoeudCourant;
    int i;
    int retour;
    
    /* Si on est arrivé a une feuille, on sort */
    if (arbre == NULL) { 
	return 0;
    }

    /* Si ce noeud est final, on l'ajoute a la liste */
    if (arbre->arbreAux != NULL) { 
	if ((maillonNoeudCourant = creerMaillon(arbre)) == NULL) {
	    return 1;
	}
	insererMaillon(&(table[profondeur]), maillonNoeudCourant);
    }

    /* On descend ensuite dans l'arbre */
    for (i = 0; i < NB_TOUCHE; i++) {
	retour = construireTableRec(table, arbre->touche[i], profondeur + 1);
	if (retour != 0) { /* Si quelque chose casse plus bas, on sort */
	    return retour;
	} 
    }

    return 0;
}

/**********************************************************************
 * Fonction : construireTable                                         *
 *                                                                    *
 * Cette fonction est chargée d'allouer le tableau de liste qui va    *
 * être utilisé dans la fonction construireTableRec. On fait un       *
 * parcours en profondeur de la table pour connaître le nombre de     * 
 * liste que va contenir le tableau (la hauteur + 1 comme expliqué    *
 * dans le code). Une fois que le tableau est alloué, on initialise   *
 * les listes à NULL et on appelle la fonction construireTableRec     *
 *                                                                    *
 * Arguments : Le tableau de noeud à construire, la taille de table   *
 *             (à remplir), l'arbre à insérer dans la table.          *
 * Complexité : O(n * m) où n est la somme des nombres de noeud des   *
 *              arbres auxiliaires et m est le nombre de noeud moyen  *
 *              des arbres auxiliaires.                               *
 * Retour : 0 si tout s'est bien passé, 2 si un appel à malloc a      *
 *          échoué, 1 si l'arbre reçu en argument est NULL.           *
 *********************************************************************/

static int construireTable(ListeNoeudPrincipal** table, int* tailleTable,
			   ArbrePrincipal arbre) {
    int i;

    if (arbre == NULL) {
	*table = NULL;
	*tailleTable = 0;

	return 1;
    }

    *tailleTable = hauteurArbrePrincipal(arbre) + 1;

    /* La taille correspond la hauteur + 1 car on souhaite stocker des noeuds à 
     * l'indice 0 ainsi qu'à l'indice correspondant à la hauteur de l'arbre.
     */

    if ((*table = (ListeNoeudPrincipal*) 
	 malloc(*tailleTable * sizeof (ListeNoeudPrincipal))) == NULL) {
	*table = NULL;
	*tailleTable = 0;

	return 2;
    }

    /* On initialise les listes de la table */

    for (i = 0; i < *tailleTable; i++) {
	(*table)[i] = NULL;
    }

    return construireTableRec(*table, arbre, 0);
}

/**********************************************************************
 * Fonction : libererTable                                            *
 *********************************************************************/

static void libererTable(ListeNoeudPrincipal* table) {
    free(table);
}

/**********************************************************************
 * Fonction : fusionner                                               *
 *********************************************************************/

/* 1 pour erreur alloc */
extern int fusionner(ArbrePrincipal arbre) {
    int i;
    int k; /* indice de parcours du tableau aFusionner */
    ArbrePrincipal* aFusionner;
    ListeNoeudPrincipal* table;
    MaillonNoeudPrincipal* tmp;
    int tailleTable;
    int retour;
    int tableVide = 0;

    if ((retour = construireTable(&table, &tailleTable, arbre)) != 0) {
	return retour;
    }
   
    if ((aFusionner = (ArbrePrincipal*) 
	 malloc(tailleTable * sizeof (NoeudPrincipal*))) == NULL) {
	return 1;
    }

    while (tableVide == 0) {
	tableVide = 1; /* On suppose que la table est vide */
	k = 0;

	for (i = 0; i < tailleTable; i++) {
	    if ((tmp = extraireMaillon(&(table[i]))) != NULL) {
		aFusionner[k++] = tmp->noeud;
		libererMaillon(tmp);
		/* Si on est entré dans ce test, la table n'était pas vide */
		tableVide = 0; 
	    }
	}
	fusionnerArbreAuxiliaire(aFusionner, k);
    }

    free(aFusionner);
    libererTable(table);

    return 0;
}
