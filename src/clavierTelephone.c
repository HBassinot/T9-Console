/******************************************************************************/
/* BASSINOT Hervé                                         Licence Maths/Infos */
/* CHATEL Grégory                                               L3.1 Groupe 1 */
/* Projet T9 arbre lexicographique                                    2009/10 */
/*                                                                            */
/******************************************************************************/
/* Fichier : clavierTelephone.c                                               */
/******************************************************************************/
/* Description : Ce fichier contient toutes les fonctions qui mannipulent     */
/*               le clavier du telephone.                                     */
/*                                                                            */
/******************************************************************************/

/* Definition des variables globales */
static const int touche[26] = {2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 
			       7, 7, 7, 8, 8, 8, 9, 9, 9, 9};

static const int chiffre[26] = {1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 
				2, 3, 4, 1, 2, 3, 1, 2, 3, 4};

static const char alphabet[8][4] = {{'a', 'b', 'c', '-'}, {'d', 'e', 'f', '-'}, 
				    {'g', 'h', 'i', '-'}, {'j', 'k', 'l', '-'}, 
				    {'m', 'n', 'o', '-'}, {'p', 'q', 'r', 's'}, 
				    {'t', 'u', 'v', '-'}, {'w', 'x', 'y' ,'z'}};

/**********************************************************************
 * Fonction : toucheLettre                                            *
 *                                                                    *
 * Cette fonction renvoie le numéro de la touche sur laquelle se      *
 * situe le caractère reçu en argument.                               *
 *                                                                    *
 * Argument : La lettre dont on souhaite connaitre la position sur le *
 *            clavier du téléphone.                                   *
 * Complexité : O(1).                                                 *
 * Retour : Le numéro de la touche sur laquelle la lettre se trouve.  *
 *********************************************************************/

extern int toucheLettre(char c) {
    return touche[c - 'a'];
}

/**********************************************************************
 * Fonction : chiffreLettre                                           *
 *                                                                    *
 * Cette fonction renvoie la position de la lettre sur la touche sur  *
 * laquelle elle se trouve.                                           *
 *                                                                    *
 * Argument : La lettre dont on souhaite connaitre la position sur la *
 *            touche du téléphone.                                    *
 * Retour : Le chiffre correspondant à la position de lettre sur la   *
 *          touche.                                                   *
 *********************************************************************/

extern int chiffreLettre(char c) {
    return chiffre[c - 'a'];
}

/**********************************************************************
 * Fonction : alphabetTouche                                          *
 *                                                                    *
 * Cette fonction renvoie la lettre correspondant à la touche et le   *
 * numéro correspondant à la position de la lettre sur la touche      *
 * reçus en argument.                                                 *
 *                                                                    *
 * Arguments : L'entier correspondant au numéro de la touche,         *
 *             l'entier correspondant à la position de la lettre sur  *
 *             la touche.                                             *
 * Retour : La lettre cherchée si les arguments sont valides, le      *
 *          caractère '-' sinon.                                      *
 *********************************************************************/

extern char alphabetTouche(int touche, int position) {
    return alphabet[touche - 2][position - 1];
}
