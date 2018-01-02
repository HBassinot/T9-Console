/******************************************************************************/
/* BASSINOT Hervé                                         Licence Maths/Infos */
/* CHATEL Grégory                                               L3.1 Groupe 1 */
/* Projet T9 arbre lexicographique                                    2009/10 */
/*                                                                            */
/******************************************************************************/
/* Fichier : option.c                                                         */
/******************************************************************************/
/* Description : Ce fichier contient toutes les fonctions qui traitent        */
/*               les options du programme.                                    */
/*                                                                            */
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "structures.h"
#include "hachage.h"
#include "argument.h"
#include "arbreAuxiliaire.h"
#include "arbrePrincipal.h"
#include "lexico.h"
#include "option.h"
#include "fusion.h"
#include "minimisation.h"
#include "clavierTelephone.h"
#include "affichage.h"
#include "graphe.h"

/**********************************************************************
 * Fonction : optionB                                                 *
 *                                                                    *
 * Cette fonction réalise l'option B du programme. C'est à dire créer *
 * l'arbre sous forme d'un graphe.                                    *
 *                                                                    *
 * Arguments : l'arbre principal pour réaliser l'option ainsi que une *
 *             structure argument pour connaitre le nom du fichier    *
 *             à creer.                                               *
 * Complexité : O(n) où n est .                                       *
 * Retour : Aucun.                                                    *
 *********************************************************************/

/**********************************************************************
 **************************A completer*********************************
 *********************************************************************/

static void optionB(ArbrePrincipal arbre, Argument argument) {
    FILE* fichier;
    char nom[TAILLE_FICHIER];
    char *mot;
    Tableau table;

    /* On allou un mot de la taille du plus grand mot de l'arbre */
    if ((mot = (char *) malloc(sizeof (char) * hauteurArbrePrincipal(arbre) * 2)) == NULL) {
	afficherErreur("Allocation");
	return;
    }

    sprintf(nom, "%s.trieout", argument.nomFichier);
    fichier = fopen(nom, "w");

    if (fichier == NULL) {
	return;
    }

    if (initialisationTable(&table, arbre) == ERREUR_ALLOCATION) {
	afficherErreur("Allocation");
	return;
    }
    initialiserTableau(&table, arbre);

    construitFichierTrie(arbre, fichier, &table, mot, 0);

    /* Liberation de la memoire */
    free(table.table);
    fclose(fichier);
}

/**********************************************************************
 * Fonction : optionN                                                 *
 *                                                                    *
 * Cette fonction réalise l'option N du programme. C'est à dire       *
 * affichage des statistiques de l'arbre.                             *
 *                                                                    *
 * Arguments : l'arbre principal pour réaliser l'option.              *
 * Complexité : O(n) où n est .                                       *
 * Retour : Aucun.                                                    *
 *********************************************************************/

static void optionN(ArbrePrincipal arbre) {
    printf("\tNombre de mots dans l'arbre             : %d\n", 
	   compteMotPrincipal(arbre));
    printf("\tNombre de noeuds de l'arbre principal   : %d\n", 
	   compteNoeudPrincipal(arbre));
    printf("\tNombre de noeuds des arbres auxiliaires : %d\n", 
	   compteNoeudAuxiliaire(arbre));
}

/**********************************************************************
 * Fonction : optionM                                                 *
 *                                                                    *
 * Cette fonction réalise l'option M du programme. C'est à dire la    *
 * minimisation de l'arbre.                                           *
 *                                                                    *
 * Arguments : l'arbre principal pour réaliser l'option.              *
 * Complexité : O(n) où n est .                                       *
 * Retour : Aucun.                                                    *
 *********************************************************************/

static void optionM(ArbrePrincipal* arbre) {
    printf("\tFusion des arbres auxiliaires ... ");
    fflush(stdout);
    fusionner(*arbre);
    printf("OK\n");
    printf("\tMinimisation des arbres auxiliaires ... ");
    fflush(stdout);
    minimiserAuxiliaire(*arbre);
    printf("OK\n");
/*    printf("\tMinimisation de l'arbre principal ... "); */
/*     fflush(stdout); */
/*     minimiserPrincipal(arbre); */
/*     printf("OK\n"); */
}

/**********************************************************************
 * Fonction : optionT                                                 *
 *                                                                    *
 * Cette fonction réalise l'option T du programme. C'est à dire la    *
 * création d'un fichier contenant tous les mots du dictionnaire dans *
 * l'ordre lexicographique.                                           *
 *                                                                    *
 * Arguments : l'arbre principal pour réaliser l'option.              *
 *             un argument pour connaitre le nom du fichier à créer   *
 * Complexité : O(n) où n est .                                       *
 * Retour : Aucun.                                                    *
 *********************************************************************/

static void optionT(ArbrePrincipal arbre, Argument argument) {
    FILE* fichier;
    char nom[TAILLE_FICHIER];
    char *mot;
    char *resultat;
    ATR ternaire=NULL;
    int tailleMot = hauteurArbrePrincipal(arbre);

    /* On alloue un mot de la taille du plus grand mot de l'arbre */
    if ((mot = (char *) malloc(sizeof (char) * tailleMot * 2)) == NULL) {
	afficherErreur("Allocation");
	return;
    }
    if ((resultat = (char *) malloc(sizeof (char) * tailleMot * 2)) == NULL) {
	afficherErreur("Allocation");
	return;
    }

    sprintf(nom, "%s.dicout", argument.nomFichier);
    fichier = fopen(nom, "w");
    if(fichier == NULL) {
	return;
    }

    construitFichierOut(arbre, &ternaire, mot, resultat, 0);
    afficheATR(ternaire, mot, 0, fichier);

    /* liberation de la memoire */
    libereATR(&ternaire);
    fclose(fichier);
    free(mot);
    free(resultat);
}

/**********************************************************************
 * Fonction : executerOption                                          *
 *                                                                    *
 * Cette fonction permet d'executer toutes les eventuelles options    *
 * transmises au programme.                                           *
 *                                                                    *
 * Arguments : l'arbre principal pour réaliser l'option.              *
 *             un argument pour connaitre les options à executer.     *
 * Complexité : O(n) où n est .                                       *
 * Retour : MODE_PREFIXE si l'opton prefixe à été activée.            *
 *          MODE_NORMAL sinon.                                        *
 *********************************************************************/

extern int executerOption(Argument argument, ArbrePrincipal* arbre) {
    int mode = MODE_NORMAL;

    if (argument.options[NUMERO_OPTION_LEXICOGRAPHIQUE] == ACTIVE) {
	printf("Creation du fichier lexicographique ...\n");
	optionT(*arbre, argument);
    }

    if (argument.options[NUMERO_OPTION_MINIMISATION] == ACTIVE) {
	printf("Minimisation de l'arbre ...\n");
	optionM(arbre);
    }

    if (argument.options[NUMERO_OPTION_STATISTIQUE] == ACTIVE) {
	printf("Statistiques de l'arbre ...\n");
	optionN(*arbre);
    }

    if (argument.options[NUMERO_OPTION_GRAPHE] == ACTIVE) {
	printf("Creation du fichier graphe ...\n");
	optionB(*arbre, argument);
    }

    if (argument.options[NUMERO_OPTION_PREFIXE] == ACTIVE) {
	printf("Mode prefixe active ...\n");
	mode = MODE_PREFIXE;
    }

    return mode;
}

