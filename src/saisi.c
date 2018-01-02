/******************************************************************************/
/* BASSINOT Hervé                                         Licence Maths/Infos */
/* CHATEL Grégory                                               L3.1 Groupe 1 */
/* Projet T9 arbre lexicographique                                    2009/10 */
/*                                                                            */
/******************************************************************************/
/* Fichier : moteur.c                                                         */
/******************************************************************************/
/* Description : Ce fichier contient toutes les fonctions utiles à la saisi   */
/*               des mots à rechercher.                                       */
/*                                                                            */
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**********************************************************************
 * Fonction : verifieMot                                              *
 *                                                                    *
 * Cette fonction verifie que le mot saisi par l'utilisateur est      *
 * valide.                                                            *
 *                                                                    *
 * Arguments : le mot dont on souhaite savoir si il est valide ou non *
 * Complexité : O(n) où n est la taille du mot à verifier.            *
 * Retour : -1 si le mot n'est pas valide. La taille du mot sinon.    *
 *********************************************************************/

int verifieMot(char *mot) {
    int i = 0;
    
    if(strlen(mot) == 0) {
	return -1;
    }
    while (mot[i] != '\0')  {
	if ((mot[i] < '2') || (mot[i] > '9')) {
	    return -1;
	}
	mot[i] -= '0';
	i++;
    }

    return i;
}

/**********************************************************************
 * Fonction : verifieMot                                              *
 *                                                                    *
 * Cette fonction saisi le mot à chercher dans le dictionnaire. Si le *
 * mot saisi est trop long on realloue automatiquement pour augmenter *
 * sa taille.                                                         *
 *                                                                    *
 * Arguments : un pointeur sur le mot que l'on va saisir et la taille *
 *             de la chaine de caracteres.                            *
 * Complexité : O(n) où n est la taille du mot.                       *
 * Retour : -1 si le mot saisi n'est pas valide.                      *
 *          La taille du mot sinon.                                   *
 *********************************************************************/

int saisiMot(char **mot, int *taille) {
    int i = 0;

    do {
	if (i == *taille) {
	    *taille *= 2;
	    if ((*mot = realloc(*mot, *taille * sizeof (char))) == NULL) {
		return 1;
	    }
	}

	scanf("%c", &(*mot)[i]);
	i++;
    } while ((*mot)[i-1] != '\n');
    (*mot)[i-1] = '\0';
    
    /* Si le mot est correct return 0 sinon return 1 */
    return verifieMot(*mot);
}

/**********************************************************************
 * Fonction : controlSortie                                           *
 *                                                                    *
 * Cette fonction controle si l'utilisateur souhaite quittre le       *
 * programme                                                          *
 *                                                                    *
 * Arguments : la chaine de caractere à tester.                       *
 * Complexité : O(1).                                                 *
 * Retour : 0 si il faut arreter le programme, 1 sinon.               *
 *********************************************************************/

int controlSortie(char *mot) {
    if ((strlen(mot) == 1) && (mot[0] == '0')) {
	return 0;
    }
    return 1;
}

