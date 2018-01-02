/******************************************************************************/
/* BASSINOT Hervé                                         Licence Maths/Infos */
/* CHATEL Grégory                                               L3.1 Groupe 1 */
/* Projet T9 arbre lexicographique                                    2009/10 */
/*                                                                            */
/******************************************************************************/
/* Fichier : hachage.c                                                        */
/******************************************************************************/
/* Description : Ce fichier contient toutes les fonctions qui mannipulent     */
/*               les tables de hachages.                                      */
/*                                                                            */
/******************************************************************************/

#include <stdlib.h>

#include "structures.h"
#include "hachage.h"

/**********************************************************************
 * Fonction : creerTable                                              *
 *                                                                    *
 * Cette fonction est chargée d'allouer ainsi que d'initialiser la    *
 * table de hachage qu'elle reçoit en argument. La table reçue en     *
 * argument devra être crée d'avance, seul le champs tableau de la    *
 * structure est alloué. Cette fonction alloue le tableau puis        *
 * initialise la valeur des champs etat de ce tableau ainsi que les   *
 * champs tailleTable et comparer de la structure Table.              *
 *                                                                    *
 * Arguments : La table à creer, la taille de la table (cette taille  *
 *             est définitive et doit donc être calculée par avance), *
 *             un pointeur sur la fonction qui servira à tester si    *
 *             deux noeuds peuvent être fusionnés.                    *
 * Complexité : O(n) où n est la valeur de la variable tailleTable.   *
 * Retour : 0 si tout s'est bien passé, 1 si malloc à échoué.         *
 *********************************************************************/

extern int creerTable(Table* table, unsigned int tailleTable, 
		      int (*comparer)(void*, void*)) {
    unsigned int i;

    if ((table->tableau = (CaseTable*) 
	 malloc(tailleTable * sizeof (CaseTable))) == NULL) {
	return 1 ;
    }

    for (i = 0; i < tailleTable; i++) {
	table->tableau[i].etat = VIDE;
    }

    table->tailleTable = tailleTable;
    table->comparer = comparer;
    
    return 0;
}

/**********************************************************************
 * Fonction : insererElement                                          *
 *                                                                    *
 * Cette fonction est chargée d'insérer des éléments dans la table de *
 * hachage. La table de hachage reçue en argument ne doit pas         *
 * contenir de doublon, par conséquent, si un élément possédant la    *
 * même valeur de haché que celui reçu en argument est trouvé dans la *
 * table, on les compare en utilisant la fonction contenu dans la     *
 * structure Table.                                                   *
 *                                                                    *
 * Arguments : La table dans laquelle on souhaite insérer l'élément,  *
 *             la valeur du haché de l'élément à inserer dans la      *
 *             table, l'élément à inserer.                            *
 * Compléxité : O(n) dans le pire des cas si la table est pleine.     *
 * Retour : L'élément inséré si aucun élément compatible n'était      *
 *          présent, l'élément compatible dans le cas contraire.      *
 *********************************************************************/

extern void* insererElement(Table* table, unsigned int hache, void* adresse) {
    unsigned int i;

    if (table->tableau[hache].etat == VIDE) {
	table->tableau[hache].adresse = adresse;
	table->tableau[hache].etat = OCCUPE;
	table->tableau[hache].hache = hache;

	return adresse; /* insertion effectuée */
    } else if (table->comparer(adresse, table->tableau[hache].adresse) == 0) {
	return table->tableau[hache].adresse; /* élément déja présent */
    }

    for (i = (hache + 1) % table->tailleTable; i != hache; 
	 i = (i + 1) % table->tailleTable) {
	if (table->tableau[i].etat == VIDE) {
	    table->tableau[i].adresse = adresse;
	    table->tableau[i].etat = OCCUPE;
	    table->tableau[i].hache = hache;

	    return adresse; /* insertion effectuée */
	} else if (table->tableau[i].hache == hache &&
		   table->comparer(adresse, table->tableau[i].adresse) == 0) {
	    return table->tableau[i].adresse; /* élément déja présent */
	}
    }
    
    return NULL; /* table pleine */
}

/**********************************************************************
 * Fonction : libererTable                                            *
 *                                                                    *
 * Cette fonction est chargée de libérer le champs tableau de la      *
 * table reçue en argument.                                           *
 *                                                                    *
 * Argument : La table dont on souhaite libérer le champs tableau.    *
 * Complexité : O(1).                                                 *
 * Retour : Aucun.                                                    *
 *********************************************************************/

extern void libererTable(Table* table) {
    free(table->tableau);
}
