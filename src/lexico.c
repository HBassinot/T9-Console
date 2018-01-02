/******************************************************************************/
/* BASSINOT Hervé                                         Licence Maths/Infos */
/* CHATEL Grégory                                               L3.1 Groupe 1 */
/* Projet T9 arbre lexicographique                                    2009/10 */
/*                                                                            */
/******************************************************************************/
/* Fichier : ternaire.c                                                       */
/******************************************************************************/
/* Description : Ce fichier contient toutes les fonctions qui gerent l'arbre  */
/*               ternaire pour l'option T du programme.                       */
/*                                                                            */
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h"
#include "lexico.h"
#include "clavierTelephone.h"
#include "affichage.h"

/**********************************************************************
 * Fonction : initATR                                                 *
 *                                                                    *
 * Cette fonction permet d'initialiser l'Arbre Ternaire.              *
 *                                                                    *
 * Arguments : Aucun                                                  *
 * Complexité : O(1).                                                 *
 * Retour : l'arbre qui vien d'etre alloué et initialisé.             *
 *********************************************************************/
ATR initATR(void) {
    ATR arbre = (ATR)malloc(sizeof(Noeud));
    
    if (arbre == NULL) {
	perror("initialiseArbre");
	return NULL;
    } else {
	memset(arbre, 0, sizeof(Noeud));
    }

    return arbre;
}

/**********************************************************************
 * Fonction : libereATR                                               *
 *                                                                    *
 * Cette fonction libere l'Arbre Ternaire.                            *
 *                                                                    *
 * Arguments : l'arbre ternaire à liberer.                            *
 * Complexité : O(n) où n est le nombre de noeuds dans l'arbre.       *
 * Retour : Aucun.                                                    *
 *********************************************************************/

void libereATR(ATR *arbre) {
    if (*arbre == NULL) {
	return ;
    }

    libereATR(&((*arbre)->gauche));
    libereATR(&((*arbre)->milieu));
    libereATR(&((*arbre)->droit));

    free(*arbre);
    *arbre = NULL;
}

/**********************************************************************
 * Fonction : ajouteMotATR                                            *
 *                                                                    *
 * Cette fonction ajoute un mot transmis en argument à l'Arbre        *
 * Ternaire.                                                          *
 *                                                                    *
 * Arguments : l'arbre ternaire dans lequel on souhaite inserer le mot*
 *             Le mot à inserer dans l'arbre ternaire.                *
 * Complexité : O(n) où n est la taille du mot à inserer dans l'arbre.*
 * Retour : Aucun.                                                    *
 *********************************************************************/

void ajouteMotATR(ATR *arbre, char* mot) {
    if (*arbre == NULL) {
	*arbre = initATR();

	if (*arbre == NULL) {
	    return;
	}

	(*arbre)->c = *mot;

	if (*mot != '\0') {
	    ajouteMotATR(&((*arbre)->milieu),mot + 1);
	}
    } else if((*arbre)->c == *mot) {
	ajouteMotATR(&((*arbre)->milieu), mot + 1);
    } else if((*arbre)->c < *mot) {
	ajouteMotATR(&((*arbre)->droit), mot);
    } else if((*arbre)->c > *mot) {
	ajouteMotATR(&((*arbre)->gauche), mot);
    }
}

/**********************************************************************
 * Fonction : afficheATR                                              *
 *                                                                    *
 * Cette fonction affiche l'integralité des mots contenu dans l'ATR   *
 * sur le flux indiqué en argument.                                   *
 * Arguments : l'arbre ternaire dont on veux afficher son contenu.    *
 *             une chaine de caracteres mot servant de buffer.        *
 *             un indice pour se situer dans le buffer.               *
 *             un flux pour indiquer sur quelle sortie afficher le    *
 *             contenu.                                               *
 * Complexité : O(n) où n est le nombre de noeuds dans l'arbre.       *
 * Retour : Aucun.                                                    *
 *********************************************************************/

void afficheATR(ATR arbre, char* mot, int indice, FILE* flux)
{
    if(arbre == NULL) {
	return ;
    }
    afficheATR(arbre->gauche, mot, indice, flux);
    
    mot[indice] = arbre->c;
    if(mot[indice] == '\0')
    {
	fprintf(flux, "%s\n", mot);
    }
    
    afficheATR(arbre->milieu, mot, indice + 1, flux);
    afficheATR(arbre->droit, mot, indice, flux);
}

/**********************************************************************
 * Fonction : afficheATR                                              *
 *                                                                    *
 * Cette fonction construit le fichier de sortie en parcourant l'     *
 * arbre auxiliaire. Et en inserant tous les mots de l'arbre          *
 * auxiliaire dans l'ATR.                                             *
 *                                                                    *
 * Arguments : l'arbre ternaire dont on veux inserer tous les mots de *
 *             l'arbre auxiliaire.                                    *
 *             un indice pour se situer dans le buffer.               *
 *             l'arbre auxiliaire pour recuperer tous ses mots.       *
 *             un buffer resultat qui contient le mot à inserer dans  *
 *             l'ATR.                                                 *
 *             un buffer mot pour le parcours.                        *
 * Complexité : O(n) où n est le nombre de noeuds dans l'arbre.       *
 * Retour : Aucun.                                                    *
 *********************************************************************/

void construitFichierOutAux(ArbreAuxiliaire arbre, ATR *ternaire, char *mot, char* resultat, int indice) {
    int i;
    int touche; 
   
    if (arbre == NULL) {
	return;
    }

    touche = mot[indice];

    for (i = 0; i < NB_LETTRE; i++) {
	resultat[indice] = alphabetTouche(touche, i+1);
	construitFichierOutAux(arbre->fils[i], ternaire, mot, resultat, indice + 1);
    }
    if (arbre->statut == TERMINAL) {
	ajouteMotATR(ternaire, resultat);
	return;
    }
}

/**********************************************************************
 * Fonction : afficheATR                                              *
 *                                                                    *
 * Cette fonction construit le fichier de sortie en parcourant l'     *
 * arbre principal. Et en inserant tous les mots de l'arbre           *
 * auxiliaire dans l'ATR.                                             *
 *                                                                    *
 * Arguments : l'arbre ternaire dont on veux inserer tous les mots de *
 *             l'arbre auxiliaire.                                    *
 *             un indice pour se situer dans le buffer.               *
 *             l'arbre auxiliaire pour recuperer tous ses mots.       *
 *             un buffer resultat qui contient le mot à inserer dans  *
 *             l'ATR.                                                 *
 *             un buffer mot pour le parcours.                        *
 * Complexité : O(n) où n est le nombre de noeuds dans l'arbre.       *
 * Retour : Aucun.                                                    *
 *********************************************************************/

void construitFichierOut(ArbrePrincipal arbre, ATR *ternaire, char* mot, char* resultat, int indice) {
    int i;
   
    if (arbre == NULL) {
	return;
    }
  	    
    if (arbre->arbreAux != NULL) {
	construitFichierOutAux(arbre->arbreAux, ternaire, mot, resultat, 0);
    }

    for (i = 0; i < (NB_TOUCHE); i++) {
	mot[indice] = i+2;
	mot[indice+1] = '\0';
	construitFichierOut(arbre->touche[i], ternaire, mot, resultat, indice + 1);
    }
}
