#include <curl/curl.h>
#include <python2.7/Python.h>
#include "parser.h"



void parser_liens(char *nom_fic, char *url, int *taille, char ***resultat ){

	PyObject *pNom, *res, *mod, *methode, *arg, *tabObj;

	int taille_liste = 0;

	Py_Initialize();
	PyThreadState *state = Py_NewInterpreter();
	PyRun_SimpleString("import sys;" " sys.path.append('.')");
	PyRun_SimpleString("print('hello from python')");

	pNom = Py_None;
	pNom = PyString_FromString("parser");

	mod = Py_None;
	if((mod = PyImport_Import(pNom)) == NULL){
		printf("Module non existant\n");
		return;
	}

	printf("Module bien telecharger !!!\n");


	char *fonction = "parser_liens";
	methode = Py_None;
	methode = PyObject_GetAttrString(mod, fonction);
	arg = Py_None;

	if((arg = Py_BuildValue("zz", nom_fic, url)) == NULL){

		printf("Valeur nulle");
	}
	printf("je suiisss ici\n");

	res = Py_None;
	if((res = PyEval_CallObject(methode, arg)) == NULL){
		printf("Valeur nulle");
	}

	puts("taille de la liste de Python");
	/*taille_liste = PyList_Size(res);
	printf("%d\n",taille_liste );

	if(taille_liste == 0){
		printf("Liste vide");
		return;
	}else{
		tabObj = Py_None;
		*taille = taille_liste;
	
		if((*resultat = malloc( sizeof(char *) * (*taille))) != NULL){
			
		

		for(int i = 0; i< *taille; i++){
			tabObj = PyList_GetItem(res,i);
			char *obj = PyString_AsString(tabObj);
			printf("lalala\n");
			printf("lien %d => %s\n", i, obj );
			(*resultat)[i] = (char *) malloc(sizeof(char) * strlen(obj)+1);
			strcpy((*resultat)[i],obj);
		}
		}
	}*/

	
}

