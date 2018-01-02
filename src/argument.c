/******************************************************************************/
/* BASSINOT Hervé                                         Licence Maths/Infos */
/* CHATEL Grégory                                               L3.1 Groupe 1 */
/* Projet T9 arbre lexicographique                                    2009/10 */
/*                                                                            */
/******************************************************************************/
/* Fichier : argument.c                                                       */
/******************************************************************************/
/* Description : Ce fichier contient la fonction qui traite les arguments     */
/*               transmis au programme.                                       */
/*                                                                            */
/******************************************************************************/

#include <stdlib.h>
#include <getopt.h>

#include "structures.h"
#include "argument.h"
#include "option.h"

/**********************************************************************
 * Fonction : initialiserArgument                                     *
 *                                                                    *
 * Cette fonction initialise les champs de la structure Argument. Par *
 * défaut, le tableau d'option est rempli avec le booléen 0 pour      *
 * montrer que le programme n'a pas encore reçu d'arguments. Le nom   *
 * de fichier vaut NULL car il n'a pas encore été lu.                 *
 *                                                                    *
 * Argument : La structure argument à initialiser.                    *
 * Complexité : O(n) où n est la valeur de constante NB_ARGUMENT qui  *
 *              représente le nombre d'argument maximum de la ligne   *
 *              de commande ainsi que la taille du tableau d'option.  *
 * Retour : Aucun.                                                    *
 *********************************************************************/

static void initialiserArgument(Argument* argument) {
    int i;
    for (i = 0 ; i < NB_ARGUMENT ; i++) {
	argument->options[i] = 0;
    }
    argument->nomFichier = NULL;
}

/**********************************************************************
 * Fonction : recupererArgument                                       *
 *                                                                    *
 * Cette fonction parse la ligne de commande qui a été utilisée pour  *
 * lancer le programme. Toutes les options prévues sont traitées en   *
 * utilisant la fonction getopt de getopt.h. Le tableau options de la *
 * structure Argument est remplie avec le booléen 1 dans les cases    *
 * correspondant aux options reçus par le programme. On vérifie       *
 * ensuite si le programme a bien reçu un nom de dictionnaire. Si     *
 * c'est le cas, on fait pointer le champ nomFichier de la structure  *
 * Argument sur la case du tableau argv contenant le nom de fichier.  *
 * Recupérer le nom de fichier de cette méthode permet de ne pas      *
 * avoir à se soucier de la taille maximale du nom de fichier,        *
 * d'allocation dynamique ou autre.                                   *
 *                                                                    *
 * Arguments : Le nombre d'argument de la ligne de commande,          *
 *             le tableau argv contenant les options de la ligne de   *
 *             commande, la structure Argument à remplir.             *
 * Complexité : O(n) où n est la valeur de la variable argc car il    *
 *              est possible que le programme reçoive plusieurs fois  *
 *              le même argument.                                     *
 * Retour : 0 si tout s'est bien passé, ERREUR_ARGUMENT si un         *
 *          argument non valide a été trouvé sur la ligne de commande *
 *          ou bien que le nom du fichier contenant le dictionnaire   *
 *          n'a pas pu être trouvé dans le tableau argv.              *
 *********************************************************************/

extern int recupererArgument(int argc, char **argv, Argument* argument) {
    int opt;
   
    initialiserArgument(argument);

    while ((opt = getopt(argc, argv, CHAINE_OPTION)) != -1) {
	switch (opt) {
	case OPTION_STATISTIQUE :
	    argument->options[NUMERO_OPTION_STATISTIQUE] = 1;
	    break;
	    
	case OPTION_MINIMISATION :
	    argument->options[NUMERO_OPTION_MINIMISATION] = 1;
	    break;

	case OPTION_PREFIXE :
	    argument->options[NUMERO_OPTION_PREFIXE] = 1;
	    break;
	
	case OPTION_LEXICOGRAPHIQUE :
	    argument->options[NUMERO_OPTION_LEXICOGRAPHIQUE] = 1;
	    break;

	case OPTION_GRAPHE : 
	    argument->options[NUMERO_OPTION_GRAPHE] = 1;
	    break;
	    
	case '?' :
	    return ERREUR_ARGUMENT;
	}
    }
   
    if (argc - optind > 1) {
	return ERREUR_ARGUMENT;
    } else {
	argument->nomFichier = argv[optind];
    }

    return (argument->nomFichier == NULL) ? ERREUR_ARGUMENT : 0;
}
