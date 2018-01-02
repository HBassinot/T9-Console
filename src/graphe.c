/******************************************************************************/
/* BASSINOT Hervé                                         Licence Maths/Infos */
/* CHATEL Grégory                                               L3.1 Groupe 1 */
/* Projet T9 arbre lexicographique                                    2009/10 */
/*                                                                            */
/******************************************************************************/
/* Fichier : graphe.c                                                         */
/******************************************************************************/
/* Description : Ce fichier contient toutes les fonctions qui mannipulent     */
/*               l'option B du programme.                                     */
/*                                                                            */
/******************************************************************************/

#include <stdlib.h>
#include <stdio.h>

#include "structures.h"
#include "arbrePrincipal.h"
#include "arbreAuxiliaire.h"
#include "graphe.h"
#include "clavierTelephone.h"

/**********************************************************************
 * Fonction : recupererAffiche                                        *
 *                                                                    *
 * Cette fonction indique si le noeud du graphe à déjà été affiché.   *
 * Si la reponse est NON on la fait passer à OUI pour indiquer que    *
 * maintenant ce noeud à été affiché et on renvoi NON.                *
 *                                                                    *
 * Arguments : la table de hachage contenant les noeuds du graphe et  *
 *             le noeud dont on souhaite savoir si il a déjà été      *
 *             affiché.                                               *
 * Complexité : O(n) où n est la taille de la table de hachage.       *
 * Retour : OUI si le noeud à déjà été affiché NON sinon.             *
 *********************************************************************/

Affiche recupererAffiche(Tableau* table, void* arbre) {
    int num = (int) arbre % table->taille;
 
    do {
	if (table->table[num].etat == arbre) {
	    if(table->table[num].affiche == NON) {
		table->table[num].affiche = OUI;
		return NON;
	    }
	    else {
		return OUI;
	    }
	}
	num = (num + 1) % table->taille;
    } while (table->table[num-1].etat != arbre);

    return NON;
}

/**********************************************************************
 * Fonction : recupererHache                                          *
 *                                                                    *
 * Cette fonction indique le numero du noeud dans le graphe           *
 *                                                                    *
 * Arguments : la table de hachage contenant les noeuds du graphe et  *
 *             le noeud dont on souhaite savoir son numero dans le    *
 *             graphe.                                                *
 * Complexité : O(n) où n est la taille de la table de hachage.       *
 * Retour : le numero correspondant au noeud passé en argument ou -1  *
 *          si le noeud n'est pas présent dans la table.              *
 *********************************************************************/

int recupererHache(Tableau* table, void* arbre) {
    int i = (int) arbre % table->taille;
    int numero = -1;
    do {
	if (table->table[i].etat == arbre) {
	    numero = table->table[i].numero;
	    return numero;
	}
	i = (i + 1) % table->taille;
    } while (numero == -1);

    return numero;
}

/**********************************************************************
 * Fonction : hacher                                                  *
 *                                                                    *
 * Cette fonction hache le noeud et renvoi l'indice où il faut le     *
 * stocker dans la table de hachage.                                  *
 * Arguments : la table de hachage contenant les noeuds du graphe et  *
 *             dans laquelle on doit stocker le noeud et le noeud     *
 *             dont on souhaite connaitre son indice dans la table.   *
 * Complexité : O(n) où n est la taille de la table de hachage.       *
 * Retour : l'indice dans la table de hachage du noeud passé en       *
 *          argument. Ou -1 si le noeud est deja dans la table.       *
 *********************************************************************/

int hacher(Tableau* table, void* arbre) {
    int num = (int) arbre % table->taille;

    do {
	if (table->table[num].etat == NULL) {
	    return num;
	}
	if (table->table[num].etat == arbre) {
	    return -1;
	}
	num = (num+1)%table->taille;
    } while (table->table[num-1].etat != arbre);

    return num;
}

/**********************************************************************
 * Fonction : initialisationTable                                     *
 *                                                                    *
 * Cette fonction initialise la table de hachage ainsi que tous les   *
 * champs de la structure.                                            *
 * Arguments : la table de hachage et l'arbre principal pour          *
 *             connaitre la taille à allouer à la table contenant les *
 *             noeuds.                                                *
 * Complexité : O(n) où n est la taille de la table de hachage.       *
 * Retour : 0 si tous cest bien passé ERREUR_ALLOCATION si            *
 *          l'allocation de la table à echoué.                        *
 *********************************************************************/

int initialisationTable(Tableau *table, ArbrePrincipal arbre) {
    int i;

    table->indice = 0;
    table->taille = (compteNoeudPrincipal(arbre) + 
		     compteNoeudAuxiliaire(arbre)) * 2;
    table->table = (Case*) malloc(sizeof (Case) * table->taille);

    if (table->table == NULL) {
	return ERREUR_ALLOCATION;
    }

    for (i = 0; i < table->taille; i++) {
	table->table[i].etat = NULL;
	table->table[i].affiche = NON;
    }

    return 0;
}

/**********************************************************************
 * Fonction : initialiserTableauAux                                   *
 *                                                                    *
 * Cette fonction ajoute à la table de hachage tous les noeuds        *
 * auxiliaires de l'arbre auxiliaire transmis en parametre.           *
 *                                                                    *
 * Arguments : la table de hachage et l'arbre auxiliaire pour         *
 *             inserer tous ses noeuds dans la table.                 *
 * Complexité : O(n * m) où n est la taille de la table de hachage    *
 *              et m le nombre total de noeud auxiliaire dans l'arbre *
 *              auxiliaire.                                           *
 * Retour : rien.                                                     *
 *********************************************************************/

void initialiserTableauAux(Tableau* table, ArbreAuxiliaire arbre) {
    int i;
    int num;

    if (arbre == NULL) {
	return;
    }

    num = hacher(table, arbre);
    /* Si num = -1 alors le noeud a deja été inseré dans la table */
    if (num != -1) {
	table->table[num].etat = arbre;
	table->table[num].numero = table->indice;
	table->indice++;
    }

    for (i = 0; i < NB_LETTRE; i++) {
	initialiserTableauAux(table, arbre->fils[i]);
    }
}

/**********************************************************************
 * Fonction : initialiserTableau                                      *
 *                                                                    *
 * Cette fonction ajoute à la table de hachage tous les noeuds        *
 * principaux de l'arbre principal transmis en parametre.             *
 *                                                                    *
 * Arguments : la table de hachage et l'arbre principal pour          *
 *             inserer tous ses noeuds dans la table.                 *
 * Complexité : O(n * m) où n est la complexité du hachage et m le    *
 * nombre total de noeuds dans l'arbre principal.                     *
 * Retour : rien.                                                     *
 *********************************************************************/

void initialiserTableau(Tableau* table, ArbrePrincipal arbre) {
    int i;
    int num;

    if (arbre == NULL) {
	return;
    }

    num = hacher(table, arbre);
    if (num != -1) {
	table->table[num].etat = arbre;
	table->table[num].numero = table->indice;
	(table->indice)++;
    }

    if (arbre->arbreAux != NULL) {
	initialiserTableauAux(table, arbre->arbreAux); 
    }

    for (i = 0; i < NB_TOUCHE; i++) {
	initialiserTableau(table, arbre->touche[i]);
    }
}

/**********************************************************************
 * Fonction : construitFichierTrieAuxi                                *
 *                                                                    *
 * Cette fonction parcours l'arbre auxiliaire transmis en argument    *
 * pour construire le fichier .trieout representant l'arbre sous      *
 * forme de graphe.                                                   *
 *                                                                    *
 * Arguments : la table de hachage contenant tous les noeuds, l'arbre *
 *             auxiliaire pour lequel on veux enregistrer tous ses    *
 *             noeuds, le fichier dans lequel ecrire, une chaine de   *
 *             caractères contenant les lettres à afficher et un      *
 *             indice pour se situer dans la chaine de caracteres.    *
 * Complexité : O(n * m) où n est la complexité du hachage et m le    *
 *              nombre total de noeud dans l'arbre.                   *
 * Retour : rien.                                                     *
 *********************************************************************/

void construitFichierTrieAuxi(ArbreAuxiliaire arbre, FILE* fichier, Tableau* table, 
		 char mot[], int indice) {
    int i;
  
    if (arbre == NULL) {
	return;
    }

    if(recupererAffiche(table, arbre) == OUI) {
	return;
    }

    if (arbre->statut == TERMINAL) {
	fprintf(fichier, "%d,1 : ",  recupererHache(table, arbre));
    } else {
	fprintf(fichier, "%d,0 : ",  recupererHache(table, arbre));
    }
   
    for (i = 0; i < NB_LETTRE; i++) {
	if (arbre->fils[i] != NULL) {
	    fprintf(fichier, "(%c,%d) ", 
		    alphabetTouche(mot[indice] + 2, 
				   i + 1), recupererHache(table, arbre->fils[i]));
	}
    }
    fprintf(fichier, "\n");

    for (i = 0; i < NB_LETTRE; i++) {
	construitFichierTrieAuxi(arbre->fils[i], fichier, table, mot, indice + 1);
    }
}

/**********************************************************************
 * Fonction : construitFichierTrie                                    *
 *                                                                    *
 * Cette fonction parcours l'arbre principal transmis en argument     *
 * pour construire le fichier .trieout representant l'arbre sous      *
 * forme de graphe.                                                   *
 * Arguments : la table de hachage contenant tous les noeuds, l'arbre *
 *             principal pour lequel on souhaite enregistrer tous ses *
 *             noeuds principaux et auxiliaires, le fichier dans      *
 *             lequel ecrire, une chaine de caractères mot contenant  *
 *             les lettres à afficher et un indice pour se situer     *
 *             dans la chaine de caracteres.                          * 
 * Complexité : O(n * m) où n est la complexité du hachage et m le    *
 * nombre total de noeud dans l'arbre.                                *
 * Retour : rien.                                                     *
 *********************************************************************/

void construitFichierTrie(ArbrePrincipal arbre, FILE* fichier, Tableau* table, 
			  char mot[], int indice) {
    int i;
   
    if (arbre == NULL) {
	return;
    }
  
    if(recupererAffiche(table, arbre) == OUI) {
	return;
    }

    if (arbre->arbreAux != NULL) {
	fprintf(fichier, "%d,1 : ", recupererHache(table, arbre));
	fprintf(fichier, "(A,%d) ", recupererHache(table, arbre->arbreAux));
    } else {
	fprintf(fichier, "%d,0 : ", recupererHache(table, arbre));
    }
   
    for (i = 0; i < NB_TOUCHE; i++) {
	if (arbre->touche[i] != NULL) {
	    fprintf(fichier, "(%d,%d) ", i + 2, 
		    recupererHache(table, arbre->touche[i]));
	}
    }
    fprintf(fichier, "\n");

    /* On regarde si il ya un noeud auxiliaire avant d'aller voir les fils */
    construitFichierTrieAuxi(arbre->arbreAux, fichier, table, mot, 0);

    for (i = 0; i < NB_TOUCHE; i++) {
	mot[indice] = i; 
	construitFichierTrie(arbre->touche[i], fichier, table, mot, indice + 1);
    }
}
