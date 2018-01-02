CC = gcc
DEBUG=yes
ifeq ($(DEBUG), yes)
	CFLAGS = -Wall -ansi -pedantic -g
else
	CFLAGS = -Wall -ansi -pedantic -Werror -O3
endif
ARCHIVE_DIR = projetT9
ARCHIVE = projetT9.tar.gz
SRC = src
INC = inc
OBJ = obj
CORPUS = corpus
DOC = doc
INC_FLAG = -I./inc
EXEC=T9
SRCS = $(SRC)/arbreAuxiliaire.c $(SRC)/arbrePrincipal.c \
	$(SRC)/clavierTelephone.c $(SRC)/lecture.c $(SRC)/saisi.c \
	$(SRC)/argument.c $(SRC)/t9.c $(SRC)/lexico.c $(SRC)/listeNoeud.c \
	$(SRC)/fusion.c	$(SRC)/option.c $(SRC)/rechercheNormale.c \
	$(SRC)/recherchePrefixe.c $(SRC)/affichage.c $(SRC)/hachage.c \
	$(SRC)/minimisation.c $(SRC)/graphe.c $(SRC)/liberation.c

all: $(EXEC)

T9 : $(OBJ)/t9.o $(OBJ)/arbreAuxiliaire.o $(OBJ)/arbrePrincipal.o \
	$(OBJ)/clavierTelephone.o $(OBJ)/lecture.o $(OBJ)/saisi.o \
	$(OBJ)/lexico.o $(OBJ)/listeNoeud.o $(OBJ)/fusion.o \
	$(OBJ)/argument.o $(OBJ)/dictionnaire.o $(OBJ)/option.o \
	$(OBJ)/rechercheNormale.o $(OBJ)/recherchePrefixe.o $(OBJ)/affichage.o \
	$(OBJ)/hachage.o $(OBJ)/minimisation.o $(OBJ)/graphe.o \
	$(OBJ)/liberation.o

	@echo "executable $@"
	@$(CC) $^ -o $@

# Règle de compilation générique des objets
$(OBJ)/%.o : $(SRC)/%.c
	@echo "module $@"
	@$(CC) $(CFLAGS) $(INC_FLAG) -c $< -o $@

depend:
	makedepend -- $(CFLAGS) $(INC_FLAG) -- $(SRCS)

# Nettoyage
clean :
	@rm -rf $(OBJ)/*.o *~ $(SRC)/*~ $(INC)/*~ $(CORPUS)/*~ makefile.bak

mrproper: clean
	@rm -f $(EXEC)

archive : clean
	@rm -rf $(ARCHIVE_DIR)
	@mkdir $(ARCHIVE_DIR)
	@mkdir $(ARCHIVE_DIR)/$(SRC)
	@mkdir $(ARCHIVE_DIR)/$(INC)
	@mkdir $(ARCHIVE_DIR)/$(OBJ)
	@mkdir $(ARCHIVE_DIR)/$(CORPUS)
	@mkdir $(ARCHIVE_DIR)/$(DOC)
	@ln makefile $(ARCHIVE_DIR)
	@ln $(SRC)/* $(ARCHIVE_DIR)/$(SRC)
	@ln $(INC)/* $(ARCHIVE_DIR)/$(INC)
	@ln $(OBJ)/* $(ARCHIVE_DIR)/$(OBJ)
	@ln $(CORPUS)/* $(ARCHIVE_DIR)/$(CORPUS)
	@ln $(DOC)/* $(ARCHIVE_DIR)/$(DOC)
	@tar -cvzf $(ARCHIVE) $(ARCHIVE_DIR)
	@rm -rf $(ARCHIVE_DIR)

# DO NOT DELETE

src/arbreAuxiliaire.o: /usr/include/stdio.h /usr/include/features.h
src/arbreAuxiliaire.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
src/arbreAuxiliaire.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
src/arbreAuxiliaire.o: /usr/include/bits/types.h
src/arbreAuxiliaire.o: /usr/include/bits/typesizes.h /usr/include/libio.h
src/arbreAuxiliaire.o: /usr/include/_G_config.h /usr/include/wchar.h
src/arbreAuxiliaire.o: /usr/include/bits/stdio_lim.h
src/arbreAuxiliaire.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
src/arbreAuxiliaire.o: /usr/include/sys/types.h /usr/include/time.h
src/arbreAuxiliaire.o: /usr/include/endian.h /usr/include/bits/endian.h
src/arbreAuxiliaire.o: /usr/include/bits/byteswap.h /usr/include/sys/select.h
src/arbreAuxiliaire.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
src/arbreAuxiliaire.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
src/arbreAuxiliaire.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
src/arbreAuxiliaire.o: ./inc/structures.h ./inc/clavierTelephone.h
src/arbreAuxiliaire.o: ./inc/liberation.h
src/arbrePrincipal.o: /usr/include/stdio.h /usr/include/features.h
src/arbrePrincipal.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
src/arbrePrincipal.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
src/arbrePrincipal.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
src/arbrePrincipal.o: /usr/include/libio.h /usr/include/_G_config.h
src/arbrePrincipal.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
src/arbrePrincipal.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
src/arbrePrincipal.o: /usr/include/sys/types.h /usr/include/time.h
src/arbrePrincipal.o: /usr/include/endian.h /usr/include/bits/endian.h
src/arbrePrincipal.o: /usr/include/bits/byteswap.h /usr/include/sys/select.h
src/arbrePrincipal.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
src/arbrePrincipal.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
src/arbrePrincipal.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
src/arbrePrincipal.o: /usr/include/string.h ./inc/structures.h
src/arbrePrincipal.o: ./inc/clavierTelephone.h ./inc/arbreAuxiliaire.h
src/arbrePrincipal.o: ./inc/liberation.h
src/lecture.o: /usr/include/stdio.h /usr/include/features.h
src/lecture.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
src/lecture.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
src/lecture.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
src/lecture.o: /usr/include/libio.h /usr/include/_G_config.h
src/lecture.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
src/lecture.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
src/lecture.o: /usr/include/sys/types.h /usr/include/time.h
src/lecture.o: /usr/include/endian.h /usr/include/bits/endian.h
src/lecture.o: /usr/include/bits/byteswap.h /usr/include/sys/select.h
src/lecture.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
src/lecture.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
src/lecture.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
src/lecture.o: /usr/include/string.h /usr/include/ctype.h ./inc/structures.h
src/lecture.o: ./inc/dictionnaire.h ./inc/arbrePrincipal.h ./inc/affichage.h
src/saisi.o: /usr/include/stdio.h /usr/include/features.h
src/saisi.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
src/saisi.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
src/saisi.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
src/saisi.o: /usr/include/libio.h /usr/include/_G_config.h
src/saisi.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
src/saisi.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
src/saisi.o: /usr/include/sys/types.h /usr/include/time.h
src/saisi.o: /usr/include/endian.h /usr/include/bits/endian.h
src/saisi.o: /usr/include/bits/byteswap.h /usr/include/sys/select.h
src/saisi.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
src/saisi.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
src/saisi.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
src/saisi.o: /usr/include/string.h
src/argument.o: /usr/include/stdlib.h /usr/include/features.h
src/argument.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
src/argument.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
src/argument.o: /usr/include/sys/types.h /usr/include/bits/types.h
src/argument.o: /usr/include/bits/typesizes.h /usr/include/time.h
src/argument.o: /usr/include/endian.h /usr/include/bits/endian.h
src/argument.o: /usr/include/bits/byteswap.h /usr/include/sys/select.h
src/argument.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
src/argument.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
src/argument.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
src/argument.o: /usr/include/getopt.h ./inc/structures.h ./inc/argument.h
src/argument.o: ./inc/option.h
src/t9.o: /usr/include/stdio.h /usr/include/features.h
src/t9.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
src/t9.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
src/t9.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
src/t9.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
src/t9.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
src/t9.o: /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
src/t9.o: /usr/include/endian.h /usr/include/bits/endian.h
src/t9.o: /usr/include/bits/byteswap.h /usr/include/sys/select.h
src/t9.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
src/t9.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
src/t9.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
src/t9.o: /usr/include/string.h ./inc/structures.h ./inc/dictionnaire.h
src/t9.o: ./inc/argument.h ./inc/arbrePrincipal.h ./inc/lecture.h
src/t9.o: ./inc/option.h ./inc/saisi.h ./inc/recherchePrefixe.h
src/t9.o: ./inc/rechercheNormale.h ./inc/affichage.h
src/lexico.o: /usr/include/stdio.h /usr/include/features.h
src/lexico.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
src/lexico.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
src/lexico.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
src/lexico.o: /usr/include/libio.h /usr/include/_G_config.h
src/lexico.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
src/lexico.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
src/lexico.o: /usr/include/sys/types.h /usr/include/time.h
src/lexico.o: /usr/include/endian.h /usr/include/bits/endian.h
src/lexico.o: /usr/include/bits/byteswap.h /usr/include/sys/select.h
src/lexico.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
src/lexico.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
src/lexico.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
src/lexico.o: /usr/include/string.h ./inc/structures.h ./inc/lexico.h
src/lexico.o: ./inc/clavierTelephone.h ./inc/affichage.h
src/listeNoeud.o: /usr/include/stdio.h /usr/include/features.h
src/listeNoeud.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
src/listeNoeud.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
src/listeNoeud.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
src/listeNoeud.o: /usr/include/libio.h /usr/include/_G_config.h
src/listeNoeud.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
src/listeNoeud.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
src/listeNoeud.o: /usr/include/sys/types.h /usr/include/time.h
src/listeNoeud.o: /usr/include/endian.h /usr/include/bits/endian.h
src/listeNoeud.o: /usr/include/bits/byteswap.h /usr/include/sys/select.h
src/listeNoeud.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
src/listeNoeud.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
src/listeNoeud.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
src/listeNoeud.o: ./inc/structures.h ./inc/listeNoeud.h
src/fusion.o: /usr/include/stdlib.h /usr/include/features.h
src/fusion.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
src/fusion.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
src/fusion.o: /usr/include/sys/types.h /usr/include/bits/types.h
src/fusion.o: /usr/include/bits/typesizes.h /usr/include/time.h
src/fusion.o: /usr/include/endian.h /usr/include/bits/endian.h
src/fusion.o: /usr/include/bits/byteswap.h /usr/include/sys/select.h
src/fusion.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
src/fusion.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
src/fusion.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
src/fusion.o: ./inc/structures.h ./inc/listeNoeud.h ./inc/arbrePrincipal.h
src/fusion.o: ./inc/arbreAuxiliaire.h
src/option.o: /usr/include/stdio.h /usr/include/features.h
src/option.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
src/option.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
src/option.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
src/option.o: /usr/include/libio.h /usr/include/_G_config.h
src/option.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
src/option.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
src/option.o: /usr/include/sys/types.h /usr/include/time.h
src/option.o: /usr/include/endian.h /usr/include/bits/endian.h
src/option.o: /usr/include/bits/byteswap.h /usr/include/sys/select.h
src/option.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
src/option.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
src/option.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
src/option.o: ./inc/structures.h ./inc/hachage.h ./inc/argument.h
src/option.o: ./inc/arbreAuxiliaire.h ./inc/arbrePrincipal.h ./inc/lexico.h
src/option.o: ./inc/option.h ./inc/fusion.h ./inc/minimisation.h
src/option.o: ./inc/clavierTelephone.h ./inc/affichage.h ./inc/graphe.h
src/rechercheNormale.o: /usr/include/stdio.h /usr/include/features.h
src/rechercheNormale.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
src/rechercheNormale.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
src/rechercheNormale.o: /usr/include/bits/types.h
src/rechercheNormale.o: /usr/include/bits/typesizes.h /usr/include/libio.h
src/rechercheNormale.o: /usr/include/_G_config.h /usr/include/wchar.h
src/rechercheNormale.o: /usr/include/bits/stdio_lim.h
src/rechercheNormale.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
src/rechercheNormale.o: /usr/include/sys/types.h /usr/include/time.h
src/rechercheNormale.o: /usr/include/endian.h /usr/include/bits/endian.h
src/rechercheNormale.o: /usr/include/bits/byteswap.h
src/rechercheNormale.o: /usr/include/sys/select.h /usr/include/bits/select.h
src/rechercheNormale.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
src/rechercheNormale.o: /usr/include/sys/sysmacros.h
src/rechercheNormale.o: /usr/include/bits/pthreadtypes.h
src/rechercheNormale.o: /usr/include/alloca.h /usr/include/string.h
src/rechercheNormale.o: ./inc/structures.h ./inc/saisi.h
src/rechercheNormale.o: ./inc/arbrePrincipal.h ./inc/arbreAuxiliaire.h
src/rechercheNormale.o: ./inc/clavierTelephone.h ./inc/rechercheNormale.h
src/rechercheNormale.o: ./inc/affichage.h
src/recherchePrefixe.o: /usr/include/stdio.h /usr/include/features.h
src/recherchePrefixe.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
src/recherchePrefixe.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
src/recherchePrefixe.o: /usr/include/bits/types.h
src/recherchePrefixe.o: /usr/include/bits/typesizes.h /usr/include/libio.h
src/recherchePrefixe.o: /usr/include/_G_config.h /usr/include/wchar.h
src/recherchePrefixe.o: /usr/include/bits/stdio_lim.h
src/recherchePrefixe.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
src/recherchePrefixe.o: /usr/include/sys/types.h /usr/include/time.h
src/recherchePrefixe.o: /usr/include/endian.h /usr/include/bits/endian.h
src/recherchePrefixe.o: /usr/include/bits/byteswap.h
src/recherchePrefixe.o: /usr/include/sys/select.h /usr/include/bits/select.h
src/recherchePrefixe.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
src/recherchePrefixe.o: /usr/include/sys/sysmacros.h
src/recherchePrefixe.o: /usr/include/bits/pthreadtypes.h
src/recherchePrefixe.o: /usr/include/alloca.h /usr/include/string.h
src/recherchePrefixe.o: ./inc/structures.h ./inc/saisi.h
src/recherchePrefixe.o: ./inc/arbrePrincipal.h ./inc/clavierTelephone.h
src/recherchePrefixe.o: ./inc/affichage.h
src/affichage.o: /usr/include/stdio.h /usr/include/features.h
src/affichage.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
src/affichage.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
src/affichage.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
src/affichage.o: /usr/include/libio.h /usr/include/_G_config.h
src/affichage.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
src/affichage.o: /usr/include/bits/sys_errlist.h
src/hachage.o: /usr/include/stdlib.h /usr/include/features.h
src/hachage.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
src/hachage.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
src/hachage.o: /usr/include/sys/types.h /usr/include/bits/types.h
src/hachage.o: /usr/include/bits/typesizes.h /usr/include/time.h
src/hachage.o: /usr/include/endian.h /usr/include/bits/endian.h
src/hachage.o: /usr/include/bits/byteswap.h /usr/include/sys/select.h
src/hachage.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
src/hachage.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
src/hachage.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
src/hachage.o: ./inc/structures.h ./inc/hachage.h
src/minimisation.o: /usr/include/stdlib.h /usr/include/features.h
src/minimisation.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
src/minimisation.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
src/minimisation.o: /usr/include/sys/types.h /usr/include/bits/types.h
src/minimisation.o: /usr/include/bits/typesizes.h /usr/include/time.h
src/minimisation.o: /usr/include/endian.h /usr/include/bits/endian.h
src/minimisation.o: /usr/include/bits/byteswap.h /usr/include/sys/select.h
src/minimisation.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
src/minimisation.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
src/minimisation.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
src/minimisation.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
src/minimisation.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
src/minimisation.o: /usr/include/bits/posix2_lim.h /usr/include/stdio.h
src/minimisation.o: /usr/include/libio.h /usr/include/_G_config.h
src/minimisation.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
src/minimisation.o: /usr/include/bits/sys_errlist.h ./inc/structures.h
src/minimisation.o: ./inc/arbrePrincipal.h ./inc/arbreAuxiliaire.h
src/minimisation.o: ./inc/hachage.h ./inc/liberation.h
src/graphe.o: /usr/include/stdlib.h /usr/include/features.h
src/graphe.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
src/graphe.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
src/graphe.o: /usr/include/sys/types.h /usr/include/bits/types.h
src/graphe.o: /usr/include/bits/typesizes.h /usr/include/time.h
src/graphe.o: /usr/include/endian.h /usr/include/bits/endian.h
src/graphe.o: /usr/include/bits/byteswap.h /usr/include/sys/select.h
src/graphe.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
src/graphe.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
src/graphe.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
src/graphe.o: /usr/include/stdio.h /usr/include/libio.h
src/graphe.o: /usr/include/_G_config.h /usr/include/wchar.h
src/graphe.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
src/graphe.o: ./inc/structures.h ./inc/arbrePrincipal.h
src/graphe.o: ./inc/arbreAuxiliaire.h ./inc/graphe.h ./inc/clavierTelephone.h
src/liberation.o: /usr/include/stdlib.h /usr/include/features.h
src/liberation.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
src/liberation.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
src/liberation.o: /usr/include/sys/types.h /usr/include/bits/types.h
src/liberation.o: /usr/include/bits/typesizes.h /usr/include/time.h
src/liberation.o: /usr/include/endian.h /usr/include/bits/endian.h
src/liberation.o: /usr/include/bits/byteswap.h /usr/include/sys/select.h
src/liberation.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
src/liberation.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
src/liberation.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
