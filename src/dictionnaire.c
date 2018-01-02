/******************************************************************************/
/* BASSINOT Hervé                                         Licence Maths/Infos */
/* CHATEL Grégory                                               L3.1 Groupe 1 */
/* Projet T9 arbre lexicographique                                    2009/10 */
/*                                                                            */
/******************************************************************************/
/* Fichier : dictionnaire.c                                                   */
/******************************************************************************/
/* Description : Ce fichier contient toutes les fonctions necessaires         */
/*               à l'initialisation du dictionnaire.                          */
/*                                                                            */
/******************************************************************************/

#include <stdio.h>

#include "structures.h"
#include "dictionnaire.h"

/**********************************************************************
 * Fonction : ouvrirDictionnaire                                      *
 *                                                                    *
 * Cette fonction ouvre le fichier correspondant au dictionnaire et   *
 * initialise les champs de la structure Dictionnaire.                *
 *                                                                    *
 * Arguments : Le dictionnaire a initialiser, le nom du fichier.      *
 * Complexité : O(1).                                                 *
 * Retour : 0 si tout s'est bien passé, ERREUR_DICO si le fichier n'a *
 *          pas pu être ouvert.                                       *
 *********************************************************************/

extern int ouvrirDictionnaire(Dictionnaire *dico, char* nom) {
    dico->fichier = fopen(nom, "r+");
    if (dico->fichier == NULL) {
	return ERREUR_DICO;
    }

    dico->curseur = TAILLE_BUFFER;
    dico->nbcaractere = TAILLE_BUFFER;
    dico->taillemot = TAILLE_MOT;
    return 0;
}

/**********************************************************************
 * Fonction : fermerDictionnaire                                      *
 *                                                                    *
 * Cette fonction fait un fclose sur le fichier du dictionnaire.      *
 *                                                                    *
 * Argument : Le dictionnaire dont on souhaite fermer le fichier.     *
 * Complexité : O(1).                                                 *
 * Retour : Aucun.                                                    *
 *********************************************************************/

extern void fermerDictionnaire(Dictionnaire *dico) {
    fclose(dico->fichier);
}
