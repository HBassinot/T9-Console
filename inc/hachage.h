#ifndef H_HACHAGE
#define H_HACHAGE

typedef enum {VIDE, OCCUPE} Etat;

typedef struct caseTable {
    void* adresse;
    unsigned int hache;
    Etat etat;
} CaseTable;

typedef struct table {
    CaseTable* tableau;
    unsigned int tailleTable;
    int (*comparer)(void*, void*);
} Table;

int creerTable(Table* table, unsigned int tailleTable,
	       int (*compare)(void*, void*));

void* insererElement(Table* table, unsigned int hache, void* adresse);

void libererTable(Table* table);

#endif
