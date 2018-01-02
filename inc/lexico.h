#ifndef H_LEXICO
#define H_LEXICO

/* Definition de la structure de l'Arbre Ternaire de Recherche */
typedef struct _ATR
{
    struct _ATR *gauche;
    struct _ATR *milieu;
    struct _ATR *droit;
    char c;
}Noeud, *ATR;

ATR initATR(void);

void libereATR(ATR *arbre);

void ajouteMotATR(ATR *arbre, char* mot);

void afficheATR(ATR arbre, char mot[], int pos, FILE* flux);

void construitFichierOutAux(ArbreAuxiliaire arbre, ATR *ternaire, 
			    char *mot, char *resultat, int indice);

void construitFichierOut(ArbrePrincipal arbre, ATR *ternaire, 
			 char* mot, char *resultat, int indice);

#endif
