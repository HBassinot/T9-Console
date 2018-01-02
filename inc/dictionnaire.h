#ifndef H_DICTIONNAIRE
#define H_DICTIONANIRE

#define ERREUR_DICO 1

typedef struct dictionnaire {
    FILE* fichier;
    char nom[TAILLE_FICHIER];
    char buffer[TAILLE_BUFFER];
    int curseur;
    int nbcaractere;
    int taillemot;
} Dictionnaire;

int ouvrirDictionnaire(Dictionnaire *dico, char* nom);

void fermerDictionnaire(Dictionnaire *dico);

#endif
