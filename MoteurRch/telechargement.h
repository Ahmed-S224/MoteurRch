#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <curl/curl.h>



static size_t ecrire_donnee(void *, size_t taille, size_t tmem, void *);

void telechargement(char *, int *, int *, char *);