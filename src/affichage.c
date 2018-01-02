/******************************************************************************/
/* BASSINOT Hervé                                         Licence Maths/Infos */
/* CHATEL Grégory                                               L3.1 Groupe 1 */
/* Projet T9 arbre lexicographique                                    2009/10 */
/*                                                                            */
/******************************************************************************/
/* Fichier : affichage.c                                                      */
/******************************************************************************/
/* Description : Ce fichier contient les fonctions chargées de l'affichage.   */
/*                                                                            */
/******************************************************************************/

#include <stdio.h>

/**********************************************************************
 * Fonction : afficherMot                                             *
 *                                                                    *
 * Cette fonction affiche un tableau de char suivi d'un retour à la   *
 * ligne.                                                             *
 *                                                                    *
 * Arguments : Le tableau de caractères à afficher, le nombre de      *
 *             caractères à afficher.                                 *
 * Complexité : O(n) où n est la valeur de taille.                    *
 * Retour : Aucun.                                                    *
 *********************************************************************/

extern void afficherMot(char mot[], int taille) {
    int i;

    for (i = 0; i < taille; i++) {
	printf("%c", mot[i]);
    }
    printf("\n");
}

/**********************************************************************
 * Fonction : afficherErreur                                          *
 *                                                                    *
 * Cette fonction est chargée d'afficher le message d'erreur qu'elle  *
 * reçoit en argument.                                                *
 *                                                                    *
 * Argument : Le message à afficher.                                  *
 * Complexité : O(1).                                                 *
 * Retour : Aucun.                                                    *
 *********************************************************************/

extern void afficherErreur(char erreur[]) {
    fprintf(stderr, "Erreur : %s\n", erreur);
}
