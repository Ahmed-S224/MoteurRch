#include "mpsh.h"
#include "configuration.h"
//int SIZE = 15;

int main(){
  
  int status;
  pid_t pid;
  int argc; 
  char** argv=NULL;
  // int l;
  hachtable hachtab = (hachtable)malloc(15 * sizeof(hachtable));
  lireConfig(hachtab,".config");
  char ** tabCmd = recupValeur(hachtab);
  /*for (int i = 0; i < 15; ++i)
    {
    printf("%s\n", tabCmd[i]);
    }*/
  
  printf("Bienvenue sur mon petit shell mpsh !\n");
  printf("(Ctrl+C ou exit pour quitter...)\n\n");
  
  FILE* histfichier = NULL; 
  histfichier = fopen("histfichier", "a");
  fclose(histfichier);
  char* chaine=(char*)malloc(TAILLE_MAX*sizeof(char));
  int numeroHistory = 1;

  do{
    
    histfichier = fopen("histfichier", "a");
    if(histfichier == NULL){
      printf("La commande history n'as pas pu être lancé\n");
    }
    
    
    chemin();
    read_cmd(&argc,&argv);       
    if(strcmp(tabCmd[4],argv[0])!=0){
      
      if (strcmp(tabCmd[9],argv[0])==0){
	pwd_mpsh();
      //Gestion history
        convertion(argc, argv, chaine);
        fprintf(histfichier, "%d:", numeroHistory);
        fputs(chaine, histfichier);
        numeroHistory++;
        fclose(histfichier);
      }
      if (strcmp(tabCmd[8],argv[0])== 0){
        mkdir_mpsh(argv[1]);
	//Gestion history
        convertion(argc, argv, chaine);
        fprintf(histfichier, "%d:", numeroHistory);
        fputs(chaine, histfichier);
        numeroHistory++;
        fclose(histfichier);
      }
      if (strcmp(tabCmd[1],argv[0]) == 0){
        cat_mpsh(argc-1, argv[1]);
      //Gestion history
        convertion(argc, argv, chaine);
        fprintf(histfichier, "%d:", numeroHistory);
        fputs(chaine, histfichier);
        numeroHistory++;
        fclose(histfichier);
      } 
      if (strcmp(tabCmd[2],argv[0])== 0){
        cd_mpsh(argc, argv[1]);
	//Gestion history
        convertion(argc, argv, chaine);
        fprintf(histfichier, "%d:", numeroHistory);
        fputs(chaine, histfichier);
        numeroHistory++;
        fclose(histfichier);
      }
      if (strcmp(tabCmd[7],argv[0])==0){
        ls_mpsh(argc, argv[1]);
	//Gestion history
        convertion(argc, argv, chaine);
        fprintf(histfichier, "%d:", numeroHistory);
        fputs(chaine, histfichier);
        numeroHistory++;
        fclose(histfichier);
      }
      if (strcmp(tabCmd[3],argv[0])==0){
        echo_mpsh(argc, argv[1]);
      //Gestion history
        convertion(argc, argv, chaine);
        fprintf(histfichier, "%d:", numeroHistory);
        fputs(chaine, histfichier);
        numeroHistory++;
        fclose(histfichier);
      }
      if (strcmp(tabCmd[6],argv[0])==0){
	//Gestion history
        convertion(argc, argv, chaine);
        fprintf(histfichier, "%d:", numeroHistory);
        fputs(chaine, histfichier);
        numeroHistory++;
        fclose(histfichier);
        history_mpsh(argc, argv);
      }
      if(strcmp(tabCmd[10], argv[0]) == 0){
	umask_mpsh();
	//Gestion history
	convertion(argc, argv, chaine);
        fprintf(histfichier, "%d:", numeroHistory);
        fputs(chaine, histfichier);
        numeroHistory++;
        fclose(histfichier);
        history_mpsh(argc, argv);
      }
      
      if ((pid=fork())==0){
	execvp(argv[0],argv);
        execvp(argv[1],argv);
      }
      if(strcmp("&",argv[argc-1])!=0)
	waitpid(pid,&status,0); 
    }
  }while (argc == 0 || strcmp(tabCmd[4],argv[0]) != 0); 
  
  remove("histfichier");
  printf("BYE BYE !\n");
}	




