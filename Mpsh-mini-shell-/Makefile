CC=gcc -Wall

SRC_COMMUN = main.c mpsh.c configuration.c

OBJ_C = $(SRC_COMMUN:.c=.o)

EXEC =  main 

all:$(EXEC)

main : $(OBJ_C) main.o
	$(CC) -o $@ $^

config : $(OBJ_C) configuration.o
	$(CC) -o $@ $^

.c.o:
	$(CC) -c $< -o $@

clean:
	find . -name '*.o' -delete

mrproper: clean
	-rm -rf $(EXEC)