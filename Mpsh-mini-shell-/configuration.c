#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "configuration.h"
int SIZE =15;



struct tableconfig* dummyitem;


int hachCode(int indice){
  return indice % SIZE;
}

 tableconfig * cherche(hachtable hachtab,int indice, char* cl){
  // renvoi hachcode
  int hi = hachCode(indice);
  while(hachtab[hi] !=NULL){
    if(strcmp(hachtab[hi]->cle,cl)==0)
      return hachtab[hi];
    //aller au suivant
    ++hi;
    hi = hi%SIZE;
  }
  return NULL;
}
void insert(hachtable hachtab,int indice,char* c, char *data){
   tableconfig * item = (tableconfig *)malloc(sizeof(tableconfig));
  
  if(item==NULL){
  
  perror("erreur malloc item");
  }
  else{
    item->cle = malloc(strlen(c)*sizeof(char));
    item->valeur = malloc(strlen(data)*sizeof(char));
    if(item->cle ==NULL) perror("erreur malloc itm->valeur");
    else{
      strcpy(item->cle, c);
      strcpy(item->valeur, data);
      item->indice = indice;
      //recup hachcode
      int hi = hachCode(indice);
      while(hachtab[hi]!=NULL && strcmp(hachtab[hi]->cle,c) !=0){
	++hi;
	hi= hi%SIZE;
      }
      hachtab[hi] = item;
    }
    
  }
  
}

 tableconfig * supprime(hachtable  hachtab,  tableconfig *item){
  int indice = item->indice;
  char* c = item->cle;

  //hachcode
  int hi = hachCode(indice);
  //move in array until empty
  while(hachtab[hi] !=NULL){
    if(strcmp(hachtab[hi]->cle,c) ==0){
      struct tableconfig * temp = hachtab[hi];
      hachtab[hi] = dummyitem;
      return temp;
    } ++hi;
    hi = hi%SIZE;
    
  }
  return NULL;
}

void affiche(hachtable  hachtab){
  int i=0;
  for(i=0;i<SIZE;i++){
    if(hachtab[i] !=NULL)
      printf("%s->%s\n",hachtab[i]->cle, hachtab[i]->valeur);
      else printf("~~\n");
    
  }
}

void modifie(hachtable hachtab, char *v,int indice,char * cle){
	int hi = hachCode(indice);
        while(hachtab[hi]!=NULL ){
		if(strcmp(hachtab[hi]->cle,cle)==0){
	 		hachtab[hi]->valeur = v;
			return ;

		}
		++hi;
		hi= hi%SIZE;

	}
}
  
void  lireConfig(hachtable hachtab, char * filename){
   FILE *f;
   f=fopen(filename,"r");
  

   if(f==NULL || hachtab ==NULL)
    perror("fopen r ou malloc");
 	else{
	 int i =0;
    int taille=1024;
    char *s;
    char buf[taille];
    //char *res;
 
     while((s=fgets(buf,taille,f))!=NULL){
	char * token = strtok(buf,":");
     char *t1 =strtok(NULL,":");
     t1 = strtok(t1,"\n");
     
	insert(hachtab,i,token,t1);
	 i++;
	}

    }
//fclose(f);
 //return hachtab;


}
 int sizeHachtab(hachtable hachtab){
  int i = hachCode(0);
  int s=0;
 
    while(hachtab[i]!=NULL){
   if(strcmp(hachtab[i]->cle ,"-1")!=0)
       s =s+1;
   i=i+1;
   i = hachCode(i);
}
 return s;
}
char ** recupValeur(hachtable hachtab){
  int s = sizeHachtab(hachtab);
   char ** res = malloc(s*sizeof(hachtab));
 if(res==NULL) return NULL;
   int i =0;
 int hi = hachCode(0);
 
  while(hachtab[i]!=NULL){
   if(strcmp(hachtab[i]->cle ,"-1")!=0)
       res[i]=hachtab[i]->valeur;
   i=i+1;
  hi = hi+1;
   hi= hachCode(hi);
}
 return res;
}
void afficheValeur(char **valeur,int t){
   int i;
printf("[");
 for(i=0;i< t; i++)
  printf("%s,",valeur[i]);
printf("]\n");




}
void detruireHachtab(hachtable hachtab){
 int hi = hachCode(0);
 while(hachtab[hi]!=NULL){
 	free(hachtab[hi]->cle);
 	++hi;
 	hi = hachCode(hi);
 } free(hachtab);
}

void remplace(hachtable hachtab){
  detruireHachtab(hachtab);
  lireConfig(hachtab,".config");
}
/*int main(void){
  
 hachtable hachtab= lireConfig(".config");
  affiche(hachtab);
  
 char ** valeur = recupValeur(hachtab);

 printf("%s\n", valeur[1]);
  char controle[] ={'C','N','F','B','K','S','W','R'};
			printf("%c",controle[0]);
      afficheValeur(valeur, 12);
 
    return 0;
}
 */