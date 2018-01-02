#ifndef H_ARGUMENT
#define H_ARGUMENT

#define NB_ARGUMENT 5
#define ERREUR_ARGUMENT 1

typedef struct argument{
    char options[NB_ARGUMENT]; 
    char* nomFichier;
} Argument;

int recupererArgument(int argc, char **argv, Argument* argument);

#endif
