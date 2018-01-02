#ifndef H_STRUCTURES
#define H_STRUCTURES

/* DEFINITION DES CONSTANTES DU PROGRAMME */
#define TAILLE_BUFFER 1024
#define TAILLE_MOT 50
#define TAILLE_FICHIER 128

#define NB_LETTRE 4
#define NB_TOUCHE 8

#define MOT_VALIDE 0
#define MOT_VALIDE_ET_EOF 1
#define MOT_NON_VALIDE 2
#define MOT_NON_VALIDE_ET_EOF 3

#define ERREUR_ALLOCATION -1
#define ARGUMENT_INCORRECT 5
#define ERREUR 6

#define MODE_NORMAL 0
#define MODE_PREFIXE 1

/* DEFINITION DES STRUCTURES DU PROGRAMME */
typedef enum statut {
    TERMINAL,
    NON_TERMINAL
} Statut;

typedef enum visite {
    VISITE,
    NON_VISITE
} Visite;

typedef struct noeudAuxiliaire {
    struct noeudAuxiliaire * fils[NB_LETTRE];
    Statut statut;
    Visite visite;
    unsigned int hache;
    unsigned int numero;
} NoeudAuxiliaire, * ArbreAuxiliaire;

typedef struct noeudPrincipal {
    struct noeudPrincipal * touche[NB_TOUCHE];
    ArbreAuxiliaire arbreAux;
    Visite visite;
    unsigned int hache;
    unsigned int numero;
} NoeudPrincipal, * ArbrePrincipal;

#endif
