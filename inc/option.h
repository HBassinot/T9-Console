#ifndef H_OPTION
#define H_OPTION

#define OPTION_STATISTIQUE 'n'
#define OPTION_MINIMISATION 'm'
#define OPTION_PREFIXE 'x'
#define OPTION_LEXICOGRAPHIQUE 't'
#define OPTION_GRAPHE 'b'
#define CHAINE_OPTION "nmxtb"

#define NUMERO_OPTION_STATISTIQUE 0
#define NUMERO_OPTION_MINIMISATION 1
#define NUMERO_OPTION_PREFIXE 2
#define NUMERO_OPTION_LEXICOGRAPHIQUE 3
#define NUMERO_OPTION_GRAPHE 4

#define ACTIVE 1

int executerOption(Argument argument, ArbrePrincipal* arbre);

#endif
