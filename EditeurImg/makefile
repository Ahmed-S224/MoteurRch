CC=gcc 

CFLAGS= -Wall

CFLAGS_SDL =  $(CFLAGS) 

LDFLAGS_SDL = -lSDL2 -lSDL2_image

LDFLAGS_CHECK = -pthread -lcheck_pic -pthread -lrt -lm -lsubunit

SRC_COMMUN = src/minishell.c src/sdl_function.c src/affichage.c src/selection.c src/evenement.c

SRC_UNITAIRE = src/test.c src/sdl_function.c src/affichage.c src/selection.c src/evenement.c

OBJ_C = $(SRC_COMMUN:.c=.o)

OBJ_U = $(SRC_UNITAIRE:.c=.o)

EXEC =  PROJET

EXEC2 = test 

all:$(EXEC) $(EXEC2)

PROJET : $(OBJ_C) src/minishell.o
	$(CC) $(CFLAGS_SDL) -o $@ $^ $(LDFLAGS_SDL)


test : $(OBJ_U) src/test.o
	$(CC) $(CFLAGS_SDL) -o $@ $^ $(LDFLAGS_SDL) $(LDFLAGS_CHECK)

.c.o:
	$(CC) -c $< -o $@

clean:
	find . -name '*.o' -delete

mrproper: clean
	-rm -rf $(EXEC) $(EXEC2)