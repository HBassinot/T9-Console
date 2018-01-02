/******************************************************************************/
/* BASSINOT Hervé                                         Licence Maths/Infos */
/* CHATEL Grégory                                               L3.1 Groupe 1 */
/* Projet T9 arbre lexicographique                                    2009/10 */
/*                                                                            */
/******************************************************************************/
/* Fichier : lecture.c                                                        */
/******************************************************************************/
/* Description : Ce fichier contient toutes les fonctions necessaires         */
/*               pour la lecture à partir du fichier dictionnaire.            */
/*                                                                            */
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "structures.h"
#include "dictionnaire.h"
#include "arbrePrincipal.h"
#include "affichage.h"

/**********************************************************************
 * Fonction : recupererMot                                            *
 *                                                                    *
 * Cette fonction permet de récuperer à chaque appel un mot du        *
 * dictionnaire contenu dans le buffer. Si le buffer est vide, la     *
 * fonction le met à jour automatiquement à partir du fichier source  *
 * et continu le traitement. On verifie à chaque fois que le mot      *
 * est valide ou non. Si le mot à recuperé est plus grand que la      *
 * chaine de caracteres mot, on effectue une reallocation.            *
 *                                                                    *
 * Arguments : le dictionnaire de mot et une chaine de caracteres     *
 *             qui va contenir le mot à recuperé.                     *
 * Complexité : O(n) où n est la taille du mot à recuperer.           *
 * Retour : ERREUR_ALLOCATION si il ya une erreur lors de la          *
 *          reallocation du mot.                                      *
 *          MOT_NON_VALIDE si le mot recuperé n'est pas valide.       *
 *          MOT_NON_VALIDE_ET_EOF si le mot est non valide et que cest*
 *          le dernier du fichier.                                    *
 *          MOT_VALIDE si le mot recuperé est valide.                 *
 *          MOT_VALIDE_ET_EOF si le mot est valide et que cest le     *
 *          dernier du fichier.                                       *
 *********************************************************************/

extern int recupererMot(Dictionnaire *dico, char** mot) {
    int i = 0;
    int test = MOT_VALIDE;
    do {
	/* Si on a pris tout le buffer on le MAJ */
	if (dico->curseur >= dico->nbcaractere) {
	    dico->curseur = 0;
	    dico->nbcaractere = fread(dico->buffer, sizeof (char), TAILLE_BUFFER,
				      dico->fichier);
	}

	/* Si le mot est trop petit on reallou */
	if (i >= dico->taillemot) {
	    dico->taillemot *= 2;
	    	   
	    if ((*mot = realloc(*mot, dico->taillemot * sizeof (char))) == NULL) {
		return ERREUR_ALLOCATION;
	    }
	    (*mot)[i] = '\0';
	}

	/* Si caractere lu non conforme */
	(*mot)[i] = dico->buffer[dico->curseur];	
	if(((islower((*mot)[i]) == 0) && ((*mot)[i] != '\n') && ((*mot)[i] != EOF))) {
	    test = MOT_NON_VALIDE;
	}

	/* Si dernier mot du dictionnaire */
	if (((*mot)[i] == EOF)||((dico->nbcaractere != TAILLE_BUFFER)&&
			     (dico->curseur == dico->nbcaractere))) {
	    (*mot)[i] = '\0';
	    if(test == MOT_NON_VALIDE) {
		return MOT_NON_VALIDE_ET_EOF;
	    }
	    else {
		return MOT_VALIDE_ET_EOF;
	    }
	}

	i++;
	(dico->curseur)++;
	
    } while (((*mot)[i-1] != '\n') && ((*mot)[i-1] != EOF));
    (*mot)[i-1] = '\0';

    return test;
}

/**********************************************************************
 * Fonction : insererDictionnaire                                     *
 *                                                                    *
 * Cette fonction permet de récuperer et d'inserer dans l'arbre tous  *
 * les mots du dictionnaire.                                          *
 *                                                                    *
 * Arguments : le dictionnaire de mot et la racine de l'arbre         *
 *             principal dans lequel on va inserer nos mots.          *
 * Complexité : O(n) où n est la taille du fichier texte à lire.      *
 * Retour : ERREUR_ALLOCATION si il ya une erreur lors de la          *
 *          l'allocation du mot ou dans les autres fonctions appelées.*
 *          0 si tous c'est bien deroulé.                             *
 *********************************************************************/

extern int insererDictionnaire(ArbrePrincipal *arbre, Dictionnaire *dico) {
    char* mot;
    int test;

    if ((mot = (char *) malloc(sizeof (char) * TAILLE_MOT)) == NULL) {
	return ERREUR_ALLOCATION;
    }

    printf("\n\nInitialisation du dictionnaire en cours ...\n");
    
    /* Tant qu'on est pas au bout du fichier */
    do {	
	test = recupererMot(dico, &mot);
	
	/* Si mot est conforme ou final */
	if ((test == MOT_VALIDE)  || (test == MOT_VALIDE_ET_EOF)) {
	    if(mot[0] != '\0') { /* On test si le mot n'est pas vide */
		insererMotPrincipal(arbre, mot);	
	    }	
	}
	/* Si mot est non conforme on ne le prend pas en compte */
	else if ((test == MOT_NON_VALIDE) || (test == MOT_NON_VALIDE_ET_EOF)) {
	    afficherErreur("Caractere non conforme !");
	}
	/* Si probleme d'allocation memoire */
	else if (test == ERREUR_ALLOCATION){
	    return ERREUR_ALLOCATION;
	}
    } while ((test != MOT_VALIDE_ET_EOF) && (test != MOT_NON_VALIDE_ET_EOF));
   
    free(mot);
    return 0;
}
