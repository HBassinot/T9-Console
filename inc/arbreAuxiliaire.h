#ifndef H_ARBREAUXILIAIRE
#define H_ARBREAUXILIAIRE

int insererMotAuxiliaire(ArbreAuxiliaire * arbre, char mot[]);

int compteMotAuxiliaireProfondeur(ArbreAuxiliaire arbre, int profondeur);

int compteNoeudArbreAux(ArbreAuxiliaire arbre);

int compteNoeudAuxiliaire(ArbrePrincipal arbre);

void libererAuxiliaire(ArbreAuxiliaire *arbre);

#endif
