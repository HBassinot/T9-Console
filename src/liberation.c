/******************************************************************************/
/* BASSINOT Hervé                                         Licence Maths/Infos */
/* CHATEL Grégory                                               L3.1 Groupe 1 */
/* Projet T9 arbre lexicographique                                    2009/10 */
/*                                                                            */
/******************************************************************************/
/* Fichier : moteur.c                                                         */
/******************************************************************************/
/* Description : Ce fichier contient toutes les fonctions utiles à la         */
/*               liberation des structures de données.                        */
/*                                                                            */
/******************************************************************************/

#include <stdlib.h>

#define TAILLE_DEFAUT 1000000

typedef enum {VIDE, OCCUPE} Etat;

typedef struct caseLiberateur {
    void* adresse;
    Etat etat;
} CaseLiberateur;

static CaseLiberateur* table = NULL;
static unsigned int tailleTable = 0;
static unsigned int nbElement = 0;

/**********************************************************************
 * Fonction : libererTable                                            *
 *                                                                    *
 * Cette fonction doit être appelée à la fin du programme pour        *
 * libérer la table de hache du module de libération.                 *
 *                                                                    *
 * Argument : Aucun.                                                  *
 * Complexité : O(1).                                                 *
 * Retour : Aucun.                                                    *
 *********************************************************************/

static void libererTable(void) {
    free(table);
}

/**********************************************************************
 * Fonction : initialiserLiberateur                                   *
 *                                                                    *
 * Cette fonction est chargée d'allouer et d'initialiser la table de  *
 * hachage du libérateur.                                             *
 *                                                                    *
 * Argument : Aucun.                                                  *
 * Complexité : O(n) où n est la valeur de la constante               *
 *              TAILLE_DEFAUT.                                        *
 * Retour : 0 si tout s'est bien passé, 1 si l'appel à malloc a       *
 *          échoué                                                    *
 *********************************************************************/

static int initialiserLiberateur(void) {
    int i;

    if ((table = (CaseLiberateur*)
	 malloc(TAILLE_DEFAUT * sizeof (CaseLiberateur))) == NULL) {
	return 1;
    }

    tailleTable = TAILLE_DEFAUT;

    for (i = 0; i < TAILLE_DEFAUT; i++) {
	table[i].etat = VIDE;
    }

    atexit(libererTable);

    return 0;
}

/**********************************************************************
 * Fonction : reinitialiserLiberateur                                 *
 *                                                                    *
 * Cette fonction est chargée de réinitialiser les champs etats des   *
 * cases de la table de hachage ainsi que de libérer les adresses qui *
 * sont contenues dans ces cases.                                     *
 *                                                                    *
 * Argument : Aucun.                                                  *
 * Complexité : O(n) où n est la taille de la table.                  *
 * Retour : Aucun.                                                    *
 *********************************************************************/

extern void reinitialiserLiberateur(void) {
    int i;

    for (i = 0; i < tailleTable; i++) {
	if(table[i].etat == OCCUPE) {
	    free(table[i].adresse);
	    table[i].etat = VIDE;
	}
    }

    nbElement = 0;
}

/**********************************************************************
 * Fonction : hacher                                                  *
 *                                                                    *
 * Cette fonction est une fonction de hachage d'adresse. Elle renvoie *
 * simplement la valeur de l'adresse modulo la valeur maximale reçue  *
 * en argument.                                                       *
 *                                                                    *
 * Arguments : L'adresse à hacher, la valeur maximale du haché.       *
 * Complexité : O(1).                                                 *
 * Retour : La valeur du haché du noeud.                              *
 *********************************************************************/

static unsigned int hacher(void* adresse, unsigned int max) {
    return ((unsigned int) adresse) % max;
}

/**********************************************************************
 * Fonction : agrandirTable                                           *
 *                                                                    *
 * Cette fonction est chargée d'agrandir la table quand celle-ci est  *
 * remplie a plus de 80% de sa capacité. Ce mécanisme permet de       *
 * garder un temps d'accès aux éléments et d'insertion faible malgré  *
 * les collisions dans la table. La taille de la table double à       *
 * chaque appel de cette fonction.                                    *
 *                                                                    *
 * Argument : Aucun.                                                  *
 * Complexité : O(n) où n est la taille de nouvelleTable.             *
 * Retour : O si tout s'est bien passé, 1 si l'appel à malloc à       *
 *          échoué.                                                   *
 *********************************************************************/

static int agrandirTable(void) {
    CaseLiberateur* nouvelleTable;
    int i;
    int j;
    unsigned int hache;
    unsigned int nouvelleTailleTable = tailleTable * 2;

    /* On alloue la nouvelle table */
    if ((nouvelleTable = (CaseLiberateur*)
	 malloc(nouvelleTailleTable * sizeof (CaseLiberateur))) == NULL) {
	return 1;
    }

    /* On initialise les champs etat des cases de la nouvelle table */
    for (i = 0; i < nouvelleTailleTable; i++) {
	nouvelleTable[i].etat = VIDE;
    }

    /* Pour chaque élément de la table de hachage du libérateur, on fait une
     * insertion dans la nouvelle table */
    for (i = 0; i < tailleTable; i++) {
	/* Si cette case ne contient pas d'élément, on passe à la prochaine 
	   case */
	if (table[i].etat == VIDE) {
	    continue; 
	}

	/* On hache puis on insère dans la nouvelle table l'élément courant de
	 * l'ancienne table */
	hache = hacher(table[i].adresse, nouvelleTailleTable);

	if (nouvelleTable[hache].etat == VIDE) {
	    nouvelleTable[hache].etat = OCCUPE;
	    nouvelleTable[hache].adresse = table[i].adresse;
	    
	    continue;
	} 
	
	for (j = (hache + 1) % nouvelleTailleTable; j != hache;
	     j = (j + 1) % nouvelleTailleTable) {
	    if (nouvelleTable[j].etat == VIDE) {
		nouvelleTable[j].etat = OCCUPE;
		nouvelleTable[j].adresse = table[i].adresse;

		break;
	    }
	}
    }

    /* On libère puis on remplace l'ancienne table par la nouvelle */

    tailleTable = nouvelleTailleTable;
    free(table);
    table = nouvelleTable;

    return 0;
}

/**********************************************************************
 * Fonction : liberer                                                 *
 *                                                                    *
 * Cette fonction fait une insertion dans la table du libérateur. Si  *
 * l'adresse reçue en argument est déjà présente dans la table, on ne *
 * fait rien. Si lorsqu'on doit ajouter l'élément, la table est       * 
 * remplie à plus de 80%, on appelle la fonction agrandirTable.       *
 *                                                                    *
 * Argument : l'adresse de la zone mémoire qu'on souhaite libérer.    *
 * Complexité : O(n) où n est la taille de la table.                  *
 * Retour : 0 si tout s'est bien passé, 1 si l'appel à la fonction    *
 *          agrandirTable a renvoyé 1, 2 si la table est pleine (ce   *
 *          retour ne devrait jamais être rencontré mais il est       *
 *          necéssaire qu'il soit présent pour éviter un warning à la *
 *          compilation).                                             *
 *********************************************************************/

extern int liberer(void* adresse) {
    unsigned int hache;
    int i;

    /* Si l'adresse de la table vaut NULL, alors il faut la creer. On appelle
     * donc la fonction initialiserLiberateur */
    if (table == NULL) {
	initialiserLiberateur();
    }

    /* Si la table est remplie a plus de 80%, on l'agrandie */
    if (nbElement > (tailleTable * 8) / 10) {
	if (agrandirTable() == 1) {
	    return 1;
	}
    }

    /* On insère l'élément reçu en argument de la fonction */
    hache = hacher(adresse, tailleTable);

    if (table[hache].etat == VIDE) {
	table[hache].adresse = adresse;
	table[hache].etat = OCCUPE;
	nbElement++;

	return 0;
    } else if (table[hache].etat == OCCUPE && table[hache].adresse == adresse) {
	return 0;
    }

    for (i = (hache + 1) % tailleTable; i != hache; i = (i + 1) % tailleTable) {
	if (table[i].etat == VIDE) {
	    table[i].adresse = adresse;
	    table[i].etat = OCCUPE;
	    nbElement++;

	    return 0;
	} else if (table[i].etat == OCCUPE && table[i].adresse == adresse) {
	    return 0;
	}
    }

    return 2;
}
