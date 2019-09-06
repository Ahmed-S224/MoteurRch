/*
 * minishell.c
 *
 *  Created on: 23 mars 2019
 *      Author: yallaboy224
 */

#include "sdl_infos.h"

void read_cmd(int* argc,char*** argv){ 
  int i; 
  int n; 
  char* commande=(char*)malloc(TAILLE_MAX*sizeof(char)); 
  if( *argv != NULL)
    free((*argv));
  *argv=(char**)malloc(3*sizeof(char*)); 
  commande=fgets (commande, TAILLE_MAX, stdin); 
  *argc=0; 
  n=1; 
  i=0; 
  while( commande[i] != '\n' )
    { 
      switch( commande[i] ) { 
        case ' ' : n=1; 
    commande[i]='\0';
    break; 
      case '&' : (*argv)[*argc]=&commande[i]; 
    (*argc)++; commande[i+1]='\0'; 
    return; 
      default :
        if( n == 1 ) { 
        n=0; 
        (*argv)[*argc]=&commande[i]; 
        (*argc)++; 
      } 
    break;
      } 
      i++; 
    }
  commande[i]='\0';
  (*argv)[*argc]=NULL;
} 

void chemin(){
  char pwd[256];
  
  if(getcwd(pwd, sizeof(pwd)) == NULL){
    perror("getcwd() error");
  } else {
    printf("[minishell]:~%s $ ", pwd);
  }
}

int main(){
  

  pid_t pid;
  int argc = 0; 
  char** argv=NULL;
  char *tabCmd[2];
  tabCmd[0] = "exit";
  tabCmd[1] = "open";
  
  SDL_Window *window = NULL;
  SDL_Renderer *renderer = NULL;

  int statut = EXIT_FAILURE;
  
  printf("(Ctrl+C ou exit pour quitter...)\n\n");
  

  do{
    
    
    chemin();
    read_cmd(&argc, &argv); 

    if(strcmp(tabCmd[0],argv[0])!=0){
      if (strcmp(tabCmd[1],argv[0])== 0 && argv[1] != NULL)
      {

        if (0 != init_and_open_window(&window, &renderer, WIDTH, HEIGTH)) {
          goto Quit;
        }
        int rst = runForever(window, renderer, argv[1]);
        

        if (rst == 0) {
          statut = EXIT_SUCCESS;
        }     
      }
      
      
      
      if ((pid=fork())==0){
        execvp(argv[0],argv);
        execvp(argv[1],argv);
      }
      if(strcmp("&",argv[argc-1])!=0)
	       waitpid(pid,&statut,0); 
      }
  }while (argc == 0 || strcmp(tabCmd[0],argv[0]) != 0); 

  Quit: clean_sdl(window, renderer);
  return statut;

  return EXIT_SUCCESS;
  

  printf("BYE BYE !\n");
}	




