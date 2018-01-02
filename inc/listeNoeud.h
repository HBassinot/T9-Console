#ifndef H_LISTENOEUD
#define H_LISTENOEUD

typedef struct maillonNoeudPrincipal {
    NoeudPrincipal* noeud;
    struct maillonNoeudPrincipal* suivant;
} MaillonNoeudPrincipal, *ListeNoeudPrincipal;

MaillonNoeudPrincipal* creerMaillon(NoeudPrincipal* noeud);

void insererMaillon(ListeNoeudPrincipal* liste, MaillonNoeudPrincipal* maillon);

MaillonNoeudPrincipal* extraireMaillon(ListeNoeudPrincipal* liste);

void libererMaillon(MaillonNoeudPrincipal* maillon);

#endif
