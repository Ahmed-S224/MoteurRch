#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <curl/curl.h>
#include "telechargement.h"
#include "parser.c"


int main(){
char **resultat;
	int size = 0;
	parser_liens("fichier", "www.lemonde.fr", &size, &resultat );
	
	return 0;
}