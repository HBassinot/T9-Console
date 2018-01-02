/******************************************************************************/
/* BASSINOT Hervé                                         Licence Maths/Infos */
/* CHATEL Grégory                                               L3.1 Groupe 1 */
/* Projet T9 arbre lexicographique                                    2009/10 */
/*                                                                            */
/******************************************************************************/
/* Fichier : minimisation.c                                                   */
/******************************************************************************/
/* Description : Ce fichier contient toutes les fonctions qui mannipulent     */
/*               la minimisation des arbres.                                  */
/*                                                                            */
/******************************************************************************/

#include <stdlib.h>
#include <limits.h>

#include <stdio.h>

#include "structures.h"
#include "arbrePrincipal.h"
#include "arbreAuxiliaire.h"
#include "hachage.h"
#include "liberation.h"

static unsigned int numeroNoeud = 0;

/**********************************************************************
 * Structure : NoeudPronfondeur                                       *
 *                                                                    *
 * Cette structure a étée crée pour être utilisée durant la           *
 * minimisation de l'arbre principal. En effet, on ne peut pas        *
 * stocker directement un pointeur sur l'arbre dans la table car la   *
 * fonction de comparaison servant à tester si deux noeuds sont ou    *
 * non fusionnables a besoin de la profondeur du noeud.               *
 *********************************************************************/

typedef struct noeudProfondeur {
    NoeudPrincipal* arbre;
    unsigned int profondeur;
} NoeudProfondeur;

/**********************************************************************
 * Fonction : initialiserNumeroNoeud                                  *
 *                                                                    *
 * Cette fonction initialise la variable globale statique numeroNoeud *
 * qui sert à attribuer un numero aux noeuds durant la minimisation.  *
 *                                                                    *
 * Argument : Aucun.                                                  *
 * Complexité : O(1).                                                 *
 * Retour : Aucun.
 *********************************************************************/

static void initialiserNumeroNoeud(void) {
    numeroNoeud = 0;
}

/**********************************************************************
 * Fonction : hacherAuxiliaire                                        *
 *                                                                    *
 * Cette fonction est une fonction de hachage. Elle associe à         *
 * l'arbre qu'elle reçoit en entrer un entier non signé. La           *
 * conception de cette fonction permet de ne faire aucun dépassement  *
 * de capacité du type unsigned int et par conséquent d'utiliser la   *
 * la totalité des informations disponibles lors du calcul du haché.  *
 * On assure cette propriété grace à l'usage de l'opérateur ou        *
 * exclusif. Une explication détaillée de cette fonction sera fournie *
 * dans le rapport du projet pour ne pas surcharger le code de        *
 * commentaires.                                                      *
 *                                                                    *
 * Arguments : Le noeud à hacher, la valeure maximale du haché (la    *
 *             taille de la table de hachage.                         *
 * Complexité : O(n) où n est la valeur de la constance NB_LETTRE.    *
 * Retour : Le haché souhaité.                                        *
 *********************************************************************/

static unsigned int hacherAuxiliaire(ArbreAuxiliaire arbre, int max) {
    unsigned int res = 922337206;
    unsigned int tmp;
    unsigned int tailleInt = sizeof (unsigned int);
    int i;
    int nbFils = 0;

    for (i = 0; i < NB_LETTRE; i++) {
	if (arbre->fils[i] != NULL) {
	    tmp = arbre->fils[i]->hache;
	    tmp = (tmp >> ((i % tailleInt) * CHAR_BIT)) | 
		(tmp << ((i % tailleInt) * CHAR_BIT));
	    res ^= tmp;
	    nbFils++;
	}
    }

    if (nbFils % 2 == 0) {
	res = (res >> ((tailleInt / 2) * CHAR_BIT)) | 
	    (res << ((tailleInt / 2) * CHAR_BIT));
    }

    res %= max;

    if (arbre->statut == TERMINAL) {
	res |= 1;
    } else {
	res &= ~1;
    }
    
    return res;
}

/**********************************************************************
 * Fonction : hacherPrincipal                                         *
 *                                                                    *
 * Le commentaire de cette fonction est identique à celle de la       *
 * fonction hacherAuxiliaire                                          *
 *********************************************************************/

static unsigned int hacherPrincipal(ArbrePrincipal arbre, int max, 
				    unsigned int profondeur) {
    unsigned int res = 922337206;
    unsigned int profondeurChiffre = 712736244;
    unsigned int tmp;
    unsigned int tailleInt = sizeof (unsigned int);
    int i;
    int nbFils = 0;

    for (i = 0; i < NB_TOUCHE; i++) {
	if (arbre->touche[i] != NULL) {
	    tmp = arbre->touche[i]->hache;
	    tmp = (tmp >> ((i % tailleInt) * CHAR_BIT)) |
		(tmp << ((i % tailleInt) * CHAR_BIT));
	    res ^= tmp;
	    nbFils++;
	}
    }

    if (arbre->arbreAux != NULL) {
	if (nbFils % 2 == 0) {
	    res ^= arbre->arbreAux->numero;
	} else {
	    res ^= (arbre->arbreAux->numero >> ((tailleInt / 2) * CHAR_BIT)) |
		(arbre->arbreAux->numero << ((tailleInt / 2) * CHAR_BIT));
	}
    }

    if (nbFils % 2 == 0) {
	res = (res >> ((tailleInt / 2) * CHAR_BIT)) |
	    (res << ((tailleInt / 2) * CHAR_BIT));
    }
    
    res ^= profondeur ^ ((profondeurChiffre << 
			  ((nbFils % tailleInt) * CHAR_BIT)) |
			 (profondeurChiffre >>
			  ((nbFils % tailleInt) * CHAR_BIT)));
    
    res %= max;
    
    if (arbre->arbreAux == NULL) {
	res |= 1;
    } else {
	res &= ~ 1;
    }

    return res;
}

/**********************************************************************
 * Fonction : comparerAuxiliaire                                      *
 *                                                                    *
 * Cette fonction est chargée de comparer les deux noeuds auxiliaires *
 * qu'elle reçoit en argument. Ces noeuds sont reçus sous forme de    *
 * pointeur génériques pour permettre la factorisation du code de la  *
 * de la table de hachage. En effet, la table de hachage utilisée     *
 * pour la minimisation ne stocke que des pointeurs génériques, les   *
 * tests d'égalité sont délégués à la fonction de comparaison reçue   *
 * en argument lors de la création de la table de hachage. Ce         *
 * mécanisme est une adaptation du concept de polymorphisme de la     *
 * programmation objet adapté au langage C. Cette fonction ne teste   *
 * pas l'égalité des noeuds mais leur compatibilité pour la           *
 * minimisation, en effet, deux noeuds ayant le même haché peuvent ne *
 * pas être fusionnable car la répartition de la fonction de hachage  *
 * n'est pas parfaite. Pour que deux noeuds soient fusionnables, il   *
 * faut qu'ils aient le même statut (terminal ou non) et que leurs    *
 * fils aient les mêmes numéros (expliqué dans le rapport).           *
 *                                                                    *
 * Arguments : Les deux noeuds à comparer.                            *
 * Complexité : O(n) où n est la valeur de la constante NB_LETTRE.    *
 * Retour : 0 si les noeuds sont compatibles, 1 s'ils ne sont pas     *
 *          compatibles.                                              *
 *********************************************************************/

int comparerAuxiliaire(void* arbre1, void* arbre2) {
    ArbreAuxiliaire arbreAux1 = (ArbreAuxiliaire) arbre1;
    ArbreAuxiliaire arbreAux2 = (ArbreAuxiliaire) arbre2;
    int i;
    
    if (arbreAux1->statut != arbreAux2->statut) {
	return 1;
    }

    for (i = 0; i < NB_LETTRE; i++) {
	if ((arbreAux1->fils[i] == NULL && arbreAux2->fils[i] != NULL) ||
	    (arbreAux1->fils[i] != NULL && arbreAux2->fils[i] == NULL) ||
	    ((arbreAux1->fils[i] != NULL && arbreAux2->fils[i] != NULL) &&
	     (arbreAux1->fils[i]->numero != arbreAux2->fils[i]->numero))) {
	    return 1;
	}
    }

    return 0;
}

/**********************************************************************
 * Fonction : comparerPrincipal                                       *
 *                                                                    *
 * L'algorithme de cette fonction est décrit dans le rapport du       *
 * projet. Comme expliqué dans le rapport, il est sans doute          *
 * nécessaire de modifier cette fonction pour faire fonctionner la    *
 * minimisation de l'arbre principal.                                 *
 *                                                                    *
 * Arguments : Les deux noeuds à comparer.                            *
 * Compléxité : O(n) où n est la valeur de la constante NB_TOUCHE.    *
 * Retour : 0 si les noeuds sont compatibles, 1 s'ils ne sont pas     *
 *          compatibles.                                              *
 *********************************************************************/

int comparerPrincipal(void* arbre1, void* arbre2) {
    NoeudProfondeur* np1 = (NoeudProfondeur*) arbre1;
    NoeudProfondeur* np2 = (NoeudProfondeur*) arbre2;
    int i;

    if ((np1->arbre->arbreAux != NULL && np2->arbre->arbreAux == NULL) ||
	(np1->arbre->arbreAux == NULL && np2->arbre->arbreAux != NULL) ||
	(np1->arbre->arbreAux != NULL && np2->arbre->arbreAux != NULL &&
	  np1->arbre->arbreAux != np2->arbre->arbreAux) ||
	np1->profondeur != np2->profondeur) {
	
	return 1;
    }
    
    for (i = 0; i < NB_TOUCHE; i++) {
	if ((np1->arbre->touche[i] != NULL && np2->arbre->touche[i] == NULL) ||
	    (np1->arbre->touche[i] == NULL && np2->arbre->touche[i] != NULL) ||
	    (np1->arbre->touche[i] != NULL && np2->arbre->touche[i] != NULL &&
	     np1->arbre->touche[i]->numero != np1->arbre->touche[i]->numero)) {

	    return 1;
	}
    }

    return 0;
}

/**********************************************************************
 * Fonction : parcourirAuxiliaireMinAux                               *
 *                                                                    *
 * Cette fonction est chargée de parcourir et minimiser l'arbre       *
 * auxiliaire qu'elle reçoit en argument. Comme décrit dans           *
 * l'algorithme de minimisation des graphes acycliques, on lance le   *
 * parcours en profondeur de l'arbre puis, lors de la phase           *
 * remontante de la récursion, on hache et on fusionne les noeuds     *
 * superflus. La fonction d'insertion dans la table de hachage        *
 * renvoie l'adresse du noeud qu'on lui a passé en argument si ce     *
 * noeud a été insérer ou bien l'adresse du noeud compatible s'il est *
 * présent dans la table. Si on a réussi à insérer le noeud dans la   *
 * table, on lui attribue un numéro (comme expliqué dans le rapport)  *
 * si un noeud compatible était déjà présent dans la table, le noeud  *
 * courant devient ce noeud.                                          *
 *                                                                    *
 * Argument : L'arbre à fusionner, la table de hachage de noeud.      *
 * Complexité : O(n * a) où n est le nombre de noeud de l'arbre       *
 *              auxiliaire reçu en argument et a la complexité de la  *
 *              fonction hacherAuxiliaire.                            *
 * Retour : Aucun.                                                    *
 *********************************************************************/

static void parcourirAuxiliaireMinAux(ArbreAuxiliaire* arbre, Table* table, 
				      unsigned int indice, 
				      unsigned int profondeurMax) {
    int i;
    ArbreAuxiliaire arbreAux;

    /* Si l'arbre est NULL, il n'y a rien a faire */
    if (*arbre == NULL /*|| indice > profondeurMax*/) {
	return;
    }

    /* Si l'arbre n'est pas NULL, on lance le parcours sur ses fils */
    for (i = 0; i < NB_LETTRE; i++) {
	parcourirAuxiliaireMinAux(&((*arbre)->fils[i]), table, 
				  indice + 1, profondeurMax);
    }

    /* Une fois que ses fils ont obtenus un haché grace à la fonction 
     * hacherAuxilaire, on calcul le haché du noeud courant.
     */
    (*arbre)->hache = hacherAuxiliaire(*arbre, table->tailleTable);
    /* Une fois ce haché calculé, on essaye d'insérer le noeud courant dans
     * la table de hachage.
     */
    arbreAux = insererElement(table, (*arbre)->hache, *arbre);

    if (*arbre == arbreAux) {
	/* Si le noeud n'était pas présent dans la table, on lui attribue un 
	 * numéro.
	 */
	(*arbre)->numero = numeroNoeud++;
    } else {
	/* Sinon on fusionne le noeud courant et le noeud de la table. */
	liberer(*arbre);
	*arbre = arbreAux;
    }
}

/**********************************************************************
 * Fonction : parcourirPrincipal                                      *
 *                                                                    *
 *
 *********************************************************************/

/* static void parcourirPrincipalMinAux(ArbrePrincipal arbre, Table* table) { */
/*     int i; */

/*     if (arbre == NULL) { */
/* 	return; */
/*     } */
    
/*     parcourirAuxiliaireMinAux(&(arbre->arbreAux), table); */

/*     for (i = 0; i < NB_TOUCHE; i++) { */
/* 	parcourirPrincipalMinAux(arbre->touche[i], table); */
/*     } */
/* } */

static void parcourirPrincipalMinAux(ArbrePrincipal arbre, Table* table, 
				     unsigned int profondeur) {
    int i;

    if (arbre == NULL) {
	return;
    }
    
    parcourirAuxiliaireMinAux(&(arbre->arbreAux), table, 0, profondeur);

    for (i = 0; i < NB_TOUCHE; i++) {
	parcourirPrincipalMinAux(arbre->touche[i], table, profondeur + 1);
    }
}

/**********************************************************************
 * Fonction : parcourirPrincipalMinPrinc                              *
 *********************************************************************/

static int parcourirPrincipalMinPrinc(ArbrePrincipal* arbre, Table* table, 
				      unsigned int profondeur) {
    NoeudProfondeur* resInsertion;
    NoeudProfondeur* temp;
    int i;

    if (*arbre == NULL) {
	return 0;
    }

    if ((temp = (NoeudProfondeur*) malloc(sizeof (NoeudProfondeur))) == NULL) {
	return 1;
    }

    for (i = 0; i < NB_TOUCHE; i++) {
	parcourirPrincipalMinPrinc(&((*arbre)->touche[i]), table, 
				   profondeur + 1);
    }

    temp->arbre = *arbre;
    temp->profondeur = profondeur;

    (*arbre)->hache = hacherPrincipal(*arbre, table->tailleTable, profondeur);
    resInsertion = insererElement(table, (*arbre)->hache, temp);

    if (*arbre == resInsertion->arbre) {
	(*arbre)->numero = numeroNoeud++;
    } else {
	liberer(*arbre);
	*arbre = resInsertion->arbre;
    }
    liberer(temp);

    return 0;
}

/**********************************************************************
 * Fonction : minimiserAuxiliaire                                     *
 *                                                                    *
 * Cette fonction est chargée de creer la table de hachage qui va     *
 * servir lors de la minimisation des arbres auxiliaires. Cette       *
 * fonction est aussi chargée d'appeller les fonctions de libération  *
 * de mémoire.                                                        *
 *                                                                    *
 * Argument : L'arbre principal dont on souhaite minimiser les arbres *
 *            auxiliaires.                                            *
 * Complexité : O(n * a) où n est le nombre de noeuds auxilaires et   *
 *              a la compléxité de la fonction de hachage de noeud    *
 *              auxiliaire.                                           *
 * Retour : 0 si tout s'est bien passé, 1 si un appel à malloc a      *
 *          échoué.                                                   *
 *********************************************************************/

extern int minimiserAuxiliaire(ArbrePrincipal arbre) {
    Table table;
    unsigned int tailleTable;

    tailleTable = (compteNoeudAuxiliaire(arbre) * 10) / 8;
    if (creerTable(&table, tailleTable, comparerAuxiliaire) == 1) {
	return 1; /* Erreur allocation */
    }

    initialiserNumeroNoeud();
    parcourirPrincipalMinAux(arbre, &table, 0);
    reinitialiserLiberateur();
    libererTable(&table);

    return 0;
}

/**********************************************************************
 * Fonction : minimiserPrincipal                                      *
 *                                                                    *
 * Le commentaire de cette fonction est identique à celui de la       *
 * fonction minimiserAuxiliaire.                                      *
 *********************************************************************/

extern int minimiserPrincipal(ArbrePrincipal* arbre) {
    Table table;
    unsigned int tailleTable;

    tailleTable = (compteNoeudPrincipal(*arbre) * 10) / 8;

    if (creerTable(&table, tailleTable, comparerPrincipal) == 1) {
	return 1;
    }

    initialiserNumeroNoeud();
    fprintf(stderr, "\n\t\tLancement du parcours de l'arbre principal\n");
    parcourirPrincipalMinPrinc(arbre, &table, 0);
    fprintf(stderr, "\t\tLiberation des noeuds superflus\n");
    reinitialiserLiberateur();
    fprintf(stderr, "\t\tLiberation de la table de hachage\n");
    libererTable(&table);

    return 0;
}
