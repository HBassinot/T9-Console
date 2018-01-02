/******************************************************************************/
/* BASSINOT Hervé                                         Licence Maths/Infos */
/* CHATEL Grégory                                               L3.1 Groupe 1 */
/* Projet T9 arbre lexicographique                                    2009/10 */
/*                                                                            */
/******************************************************************************/
/* Fichier : arbreAuxiliaire.c                                                */
/******************************************************************************/
/* Description : Ce fichier contient toutes les fonctions utiles pour la      */
/*               manipulation des arbres auxiliaires.                         */
/*                                                                            */
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "structures.h"
#include "clavierTelephone.h"
#include "liberation.h"

/**********************************************************************
 * Fonction : creerNoeudAuxiliaire                                    *
 *                                                                    *
 * Cette fonction alloue un noeud de l'arbre auxiliaire et initialise *
 * la valeur de ses champs. Chacun de ses fils reçoit la valeur NULL  *
 * et le champ statut reçoit par défaut la valeur NON_TERMINAL.       *
 *                                                                    *
 * Argument : Aucun.                                                  *
 * Complexité : O(n) où n est la taille du tableau de fils.           *
 * Retour : Le noeud auxiliaire crée et initialisé si tout c'est bien *
 *          passé, NULL si l'appel à malloc a échoué.                 *
 *********************************************************************/

static NoeudAuxiliaire * creerNoeudAuxiliaire(void) {
    NoeudAuxiliaire* noeud;
    int i;

    if ((noeud = (NoeudAuxiliaire *) malloc(sizeof (NoeudAuxiliaire))) == NULL) {
	return NULL;
    }

    for (i = 0; i < NB_LETTRE; i++) {
	noeud->fils[i] = NULL;
    }
    noeud->statut = NON_TERMINAL;
    noeud->visite = NON_VISITE;
    return noeud;
}

/**********************************************************************
 * Fonction : insererMotIndiceAuxiliaire                              *
 *                                                                    *
 * Cette fonction insère si necessaire les maillons correspondant au  *
 * mot reçu en argument dans l'arbre reçu en argument.                *
 *                                                                    *
 * Arguments : L'arbre auxiliaire dans lequel on souhaite insérer le  *
 *             mot, le mot à inserer, l'indice de parcours du mot.    *
 * Complexité : O(n) où n est la taille du mot reçu en argument.      *
 * Retour : 0 si le mot a été inséré avec succès ou bien qu'il était  *
 *          déjà présent dans l'arbre, 1 si il y a eu un erreur       *
 *          d'allocation.                                             *
 *********************************************************************/

static int insererMotIndiceAuxiliaire(ArbreAuxiliaire * arbre, char mot[], 
				      int indice) {
    int chiffre;

    if (*arbre == NULL && (*arbre = creerNoeudAuxiliaire()) == NULL) {
	return 1;
    }

    if (mot[indice] == '\0') {
	(*arbre)->statut = TERMINAL;
	
	return 0;
    }
    
    chiffre = chiffreLettre(mot[indice]) - 1;
    return insererMotIndiceAuxiliaire(&((*arbre)->fils[chiffre]), mot,
				      indice + 1);
}

/**********************************************************************
 * Fonction : insererMotAuxiliaire                                    *
 *                                                                    *
 * Cette fonction est une surcouche de la fonction                    *
 * insererMotIndiceAuxiliaire, elle permet de rendre son appel        *
 * transparent pour l'utilisateur.                                    *
 *                                                                    *
 * Arguments : L'arbre auxiliaire dans lequel on souhaite insérer le  *
 *             mot, le mot à inserer.                                 *
 * Complexité : O(n) où n est la taille du mot car c'est la           *
 *              complexité de insererMotIndiceAuxiliaire.             *
 * Retour : Le retour de insererMotIndiceAuxiliaire.                  *
 *********************************************************************/

extern int insererMotAuxiliaire(ArbreAuxiliaire * arbre, char mot[]) {
    return insererMotIndiceAuxiliaire(arbre, mot, 0);
}

/**********************************************************************
 * Fonction : compteMotAuxiliaireProfondeurIndice                     *
 *                                                                    *
 * Cette fonction parcours l'arbre auxiliaire qu'elle reçoit en       *
 * argument jusqu'à une certaine profondeur. Pour que la présence     *
 * d'un noeud terminal entraine la reconnaissance d'un mot, ce noeud  *
 * doit être situé à la profondeur reçue en argument. C'est pour      *
 * cette raison que l'argument indice est présent. Il représente la   *
 * profondeur courante.                                               *
 *                                                                    *
 * Arguments : L'arbre auxiliaire dont on doit compter le nombre de   *
 *             mot, la profondeur à laquelle les noeuds terminaux     *
 *             doivent se trouver pour permettre la reconnaissance    *
 *             d'un mot, la profondeur courante.                      *
 * Complexité : O(n) où n est le nombre de noeud de l'arbre           *
 *              auxiliaire reçu en argument dont la profondeur est    *
 *              inférieure ou égale à la profondeur reçue en          *
 *              argument.                                             *
 * Retour : Le nombre de mot reconnu par cet arbre avec la profondeur *
 *          reçue en argument.                                        *
 *********************************************************************/

static int compteMotAuxiliaireProfondeurIndice(ArbreAuxiliaire arbre, 
					       int profondeur, int indice) {
    int nbMot = 0;
    int i;

    if (arbre == NULL) {
	return 0;
    }

    if (arbre->statut == TERMINAL && indice == profondeur) {
	return 1;
    }

    for (i = 0; i < NB_LETTRE; i++) {
	nbMot += compteMotAuxiliaireProfondeurIndice(arbre->fils[i], profondeur,
						     indice + 1);
    }

    return nbMot;
}

/**********************************************************************
 * Fonction : compteMotAuxiliaireProfondeur                           *
 *                                                                    *
 * Cette fonction est une surcouche de la fonction                    *
 * compteMotAuxiliaireProfondeurIndice. Elle a été mise en place pour *
 * simplifier l'appel de cette fonction pour l'utilisateur de ce      *
 * fichier.                                                           *
 *                                                                    *
 * Arguments : L'arbre auxiliaire dont on souhaite compter le nombre  *
 *             de mot, la profondeur à laquelle un noeud terminal     *
 *             doit se trouver pour permettre la reconnaissance d'un  *
 *             mot.                                                   *
 * Complexité : O(n) où n est le nombre de noeud de l'arbre           *
 *              auxiliaire.                                           *
 * Retour : Le nombre de mot reconnu par cet arbre.                   *
 *********************************************************************/

extern int compteMotAuxiliaireProfondeur(ArbreAuxiliaire arbre, 
					 int profondeur) {
    return compteMotAuxiliaireProfondeurIndice(arbre, profondeur, 0);
}

/**********************************************************************
 * Fonction : compteNoeudArbreAux                                     *
 *                                                                    *
 * Cette fonction compte le noeud de l'arbre auxiliaire reçu en       *
 * paramètre en employant l'algorithme suivant : si arbre n'est pas   *
 * vide ou n'a pas déja été visité, le nombre est égal à 1 + le       *
 * nombre de noeud de chacun de ses fils. Comme il est possible que   *
 * les arbres auxiliaires aient étés minimisés, il est necessaire     *
 * d'indiquer que la racine courante a été visitée au moyen du champs *
 * visite.                                                            *
 *                                                                    *
 * Argument : L'arbre auxiliaire dont on souhaite compter les noeuds. *
 * Complexité : O(n) où n est le nombre de noeud de l'arbre           *
 *              auxiliaire reçu en argument.                          *
 * Retour : Le nombre de l'arbre auxiliaire reçu en argument si       *
 *          l'arbre n'est pas vide, 0 sinon.                          *
 *********************************************************************/

extern int compteNoeudArbreAux(ArbreAuxiliaire arbre) {
    int i;
    int somme = 1;

    if (arbre == NULL || arbre->visite == VISITE) {
	return 0;
    }
    
    arbre->visite = VISITE;

    for(i = 0; i < NB_LETTRE; i++) {
	somme += compteNoeudArbreAux(arbre->fils[i]);
    }

    return somme;
}

/**********************************************************************
 * Fonction : reinitialiseVisiteAuxiliaire                            *
 *                                                                    *
 * Cette fonction réinitialise le champs visite de l'arbre auxiliaire *
 * reçu en argument.                                                  *
 *                                                                    *
 * Argument : L'arbre auxiliaire que l'on souhaite réinitialiser.     *
 * Complexité : O(n) où n est le nombre de noeud de l'arbre.          *
 * Retour : Aucun.                                                    *
 *********************************************************************/           

static void reinitialiseVisiteAuxiliaire(ArbreAuxiliaire arbre) {
    int i;

    if (arbre == NULL) {
    	return;
    }

    arbre->visite = NON_VISITE;

    for (i = 0; i < NB_LETTRE; i++) {
	reinitialiseVisiteAuxiliaire(arbre->fils[i]);
    }
}	

/**********************************************************************
 * Fonction : reinitialiseVisite                                      *
 *                                                                    *
 * Cette fonction réinitialise les champs visite de tous les arbres   *
 * auxiliaires contenus dans l'arbre principal reçu en argument.      *
 *                                                                    *
 * Argument : L'arbre principal que l'on souhaite réinitialiser.      *
 * Complexité : O(n + m) où n est le nombre de noeud de l'arbre       *
 *              principal et m est la somme des nombres de noeuds     *
 *              des arbres auxiliaires.                               *
 * Retour : Aucun.                                                    *
 *********************************************************************/

static void reinitialiseVisite(ArbrePrincipal arbre) {
    int i;

    if (arbre == NULL) {
    	return;
    }

    if (arbre->arbreAux != NULL) {
    	reinitialiseVisiteAuxiliaire(arbre->arbreAux);
    }

    for (i = 0; i < NB_TOUCHE; i++) {
    	reinitialiseVisite(arbre->touche[i]);
    }
}

/**********************************************************************
 * Fonction : compteNoeudAuxiliaireVisite                             *
 *                                                                    *
 * Cette fonction est chargée de compter le nombre de noeud           *
 * auxiliaire de l'arbre qu'elle reçoit en argument. Si l'arbre a     *
 * auparavant été minimisé, il est necessaire de marquer les noeuds   *
 * qui ont déja été visités. Pour ce faire, on utilise le champs      *
 * visite de la structure NoeudAuxiliaire. Il est necessaire de       *
 * réinitialiser ce champs à la fin du parcours de l'arbre pour       *
 * les prochains appels de fonction, pour cette raison, cette         *
 * fonction prend en argument un entier qui lui indique si le noeud   *
 * courant est la racine. Si c'est le cas, après le parcours en       *
 * profondeur, on appelle la fonction reinitialiseVisite qui          *
 * réinitialise les champs visite des arbres auxiliaires.             *
 *                                                                    *
 * Arguments : L'arbre principal dont on souhaite compter le nombre   *
 *             de noeuds auxiliaires auxquels on peut accéder, un     *
 *             entier indiquant si on est à la racine de l'arbre.     *
 * Complexité : O(n + m) où n est le nombre de noeud de l'arbre       *
 *              principal et m est la somme des nombres de noeuds     *
 *              des arbres auxiliaires.                               *
 * Retour : Le nombre de noeuds auxiliaire accessibles depuis la      *
 *          racine reçue en argument.                                 *
 *********************************************************************/

static int compteNoeudAuxiliaireVisite(ArbrePrincipal arbre, int racine) {
    int i;
    int somme = 0;

    if (arbre == NULL) {
	return 0;
    }

    if (arbre->arbreAux != NULL) {
	somme = compteNoeudArbreAux(arbre->arbreAux);
    }

    for (i = 0; i < NB_TOUCHE; i++) {
	somme += compteNoeudAuxiliaireVisite(arbre->touche[i], 1);
    }

    if (racine == 0) {
	reinitialiseVisite(arbre);
    }

    return somme;
}

/**********************************************************************
 * Fonction : compteNoeudAuxiliaire                                   *
 *                                                                    *
 * Cette fonction est une surcouche de la fonction                    *
 * compteNoeudAuxiliaireVisite. Elle permet de rendre l'appel a cette *
 * fonction transparent pour l'utilisateur. En effet cette fonction   *
 * doit prendre un booléen comme second argument pour lui indiquer si *
 * elle est à la racine ou non.                                       *
 *                                                                    *
 * Argument : La racine de l'arbre principal dont on souhaite compter *
 *            les noeuds auxilaires.                                  *
 * Complexité : O(n + m) où n est le nombre de noeud de l'arbre       *
 *              principal et m le nombre de noeud de l'arbre          *
 *              auxiliaire.                                           *
 * Retour : Le nombre de noeud, si arbre = NULL, la valeur retournée  *
 *          est 0.                                                    *
 *********************************************************************/

extern int compteNoeudAuxiliaire(ArbrePrincipal arbre) {
    return compteNoeudAuxiliaireVisite(arbre, 0);
}

/**********************************************************************
 * Fonction : libererAuxiliaire                                       *
 *                                                                    *
 * Cette fonction libère un arbre auxiliaire en employant             *
 * l'algorithme suivant : si l'arbre est vide on ne fait rien, sinon  *
 * on appel récursivement la fonction sur chacun des fils puis on     *
 * free le noeud reçu en argument et on met sa valeur à NULL.         *
 *                                                                    *
 * Argument : L'arbre auxiliaire que l'on souhaite liberer.           *
 * Complexité : O(n) où n est le nombre de noeud de l'arbre reçu en   *
 *              argument.                                             *
 * Retour : Aucun.                                                    *
 *********************************************************************/

extern void libererAuxiliaire(ArbreAuxiliaire *arbre) {
    int i;

    if (*arbre == NULL) {
	return;
    }

    for (i = 0; i < NB_LETTRE; i++) {
	libererAuxiliaire(&((*arbre)->fils[i]));	
    }

    liberer(*arbre);
    *arbre = NULL;
}
