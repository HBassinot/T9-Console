#ifndef H_GRAPHE
#define H_GRAPHE

typedef enum {OUI, NON} Affiche;

typedef struct {
    void* etat;
    int numero;
    Affiche affiche;
} Case;

typedef struct {
    Case *table;
    int indice;
    int taille;
} Tableau;

int recupererHache(Tableau* table, void* arbre);

int hacher(Tableau* table, void* arbre);

int initialisationTable(Tableau *table, ArbrePrincipal arbre);

void initialiserTableauAux(Tableau* table, ArbreAuxiliaire arbre);

void initialiserTableau(Tableau* table, ArbrePrincipal arbre);

Affiche recupererAffiche(Tableau* table, void* arbre);

void construitFichierTrieAuxi(ArbreAuxiliaire arbre, FILE* fichier, 
			      Tableau* table, char mot[], int indice);

void construitFichierTrie(ArbrePrincipal arbre, FILE* fichier,
			  Tableau* table, char mot[], int indice);

#endif

