/******************************************************************************/
/* BASSINOT Hervé                                         Licence Maths/Infos */
/* CHATEL Grégory                                               L3.1 Groupe 1 */
/* Projet T9 arbre lexicographique                                    2009/10 */
/*                                                                            */
/******************************************************************************/
/* Fichier : t9.c                                                             */
/******************************************************************************/
/* Description : Ce fichier contient la focntion main() du programme.         */
/*                                                                            */
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h"
#include "dictionnaire.h"
#include "argument.h"
#include "arbrePrincipal.h"
#include "lecture.h"
#include "option.h"
#include "saisi.h"
#include "recherchePrefixe.h"
#include "rechercheNormale.h"
#include "affichage.h"

/* Fonction principale du programme */
int main(int argc, char** argv) {
    Dictionnaire dico;
    ArbrePrincipal arbre = NULL;
    Argument argument;

    /* On recupere tous les arguments envoyés au programme */
    if (recupererArgument(argc, argv, &argument) == ERREUR_ARGUMENT) {
	afficherErreur("Argument transmis incorrect.");
	return 1;
    }
    
    /* On ouvre le dictionnaire */
    if (ouvrirDictionnaire(&dico, argument.nomFichier) == ERREUR_DICO) {
	afficherErreur("Nom de fichier invalide.");
	return 1;
    }

    /* On insere tous les mots du dictionnaire dans l'arbre */
    if (insererDictionnaire(&arbre, &dico) == ERREUR_ALLOCATION) {
	afficherErreur("Probleme d'allocation memoire.");
	return 1;
    }
  
    /* Suivant le mode de recherche(normal ou prefixe) */
    if (executerOption(argument, &arbre) == MODE_NORMAL) {
	rechercherNormal(arbre);
    } else {
	rechercherPrefixe(arbre);
    }

    /* Liberation de la memoire */
    fermerDictionnaire(&dico);
    libererPrincipal(&arbre);

    return 0;
}
