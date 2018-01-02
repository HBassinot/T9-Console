/******************************************************************************/
/* BASSINOT Hervé                                         Licence Maths/Infos */
/* CHATEL Grégory                                               L3.1 Groupe 1 */
/* Projet T9 arbre lexicographique                                    2009/10 */
/*                                                                            */
/******************************************************************************/
/* Fichier : listeNoeud.c                                                     */
/******************************************************************************/
/* Description : Ce fichier contient toutes les fonctions qui mannipulent     */
/*               les listes du programme.                                     */
/*                                                                            */
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "structures.h"
#include "listeNoeud.h"

/**********************************************************************
 * Fonction : creerMaillon                                            *
 *                                                                    *
 * Cette fonction alloue dynamiquement un maillon de liste chainée.   *
 * Elle initialise ensuite les champs du maillon crée s'il n'y a pas  *
 * eu d'erreur d'allocation.                                          *
 *                                                                    *
 * Argument : Le noeud principal qui va être contenu dans le maillon  *
 *            crée.                                                   *
 * Complexité : O(1).                                                 *
 * Retour : Le maillon crée et initialisé s'il n'y a pas eu d'erreur  *
 *          d'allocation, NULL sinon.                                 *
 *********************************************************************/

extern MaillonNoeudPrincipal* creerMaillon(NoeudPrincipal* noeud) {
    MaillonNoeudPrincipal* maillon;

    if ((maillon = (MaillonNoeudPrincipal*) malloc(sizeof  (MaillonNoeudPrincipal)))
	== NULL) {
	return NULL;
    }

    maillon->noeud = noeud;
    maillon->suivant = NULL;
    return maillon;
}

/**********************************************************************
 * Fonction : insererMaillon                                          *
 *                                                                    *
 * Cette fonction insère le maillon qu'elle reçoit en argument en     *
 * tête de la liste qu'elle reçoit en argument. Le maillon reçu ne    *
 * doit pas être NULL.                                                *
 *                                                                    *
 * Arguments : La liste dans laquelle on souhaite insérer le maillon, *
 *             le maillon à insérer.                                  *
 * Complexité : O(1).                                                 *
 * Retour : Aucun.                                                    *
 *********************************************************************/

extern void insererMaillon(ListeNoeudPrincipal* liste, 
			   MaillonNoeudPrincipal* maillon) {
    maillon->suivant = *liste;
    *liste = maillon;
}

/**********************************************************************
 * Fonction : extraireMaillon                                         *
 *                                                                    *
 * Cette fonction extrait un maillon en tête de liste. Le champs      *
 * suivant du maillon extrait est mit à NULL. Le maillon extrait est  *
 * ensuite renvoyé.                                                   *
 *                                                                    *
 * Argument : la liste depuis laquelle le maillon doit être extrait.  *
 * Complexité : O(1).                                                 *
 * Retour : Le maillon extrait si la liste était non vide, NULL       *
 *          sinon.                                                    *
 *********************************************************************/

extern MaillonNoeudPrincipal* extraireMaillon(ListeNoeudPrincipal* liste) {
    MaillonNoeudPrincipal* tmp = *liste;

    if (tmp == NULL) {
	return NULL;
    }
    *liste = (*liste)->suivant;
    tmp->suivant = NULL;
    
    return tmp;
}

/**********************************************************************
 * Fonction : libererMaillon                                          *
 *                                                                    *
 * Cette fonction libère un maillon. Si le maillon reçu est NULL, la  *
 * fonction ne fait rien.                                             *
 *                                                                    *
 * Argument : Le maillon à liberer.                                   *
 * Complexité : O(1).                                                 *
 * Retour : Aucun.                                                    *
 *********************************************************************/

extern void libererMaillon(MaillonNoeudPrincipal* maillon) {
    if (maillon == NULL) {
	return;
    }
    free(maillon);
}
