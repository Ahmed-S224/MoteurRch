  

#include "mpsh.h"

#define TAILLE_MAX 512
#define NBRE_COMMANDE 15 
#define MAX_FILE_NAME_CHARS 50

void read_cmd(int* argc,char*** argv){ 
  int i; 
  int n; 
  char* commande=(char*)malloc(TAILLE_MAX*sizeof(char)); 
  if( *argv != NULL)
    free((*argv));
  *argv=(char**)malloc(NBRE_COMMANDE*sizeof(char*)); 
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


void pwd_mpsh(){
  char pwd[256];
  
  if(getcwd(pwd, sizeof(pwd)) == NULL){
    perror("getcwd() error");
  } else {
    printf("current working directory is: %s\n", pwd);
  }
}
void chemin(){
  char pwd[256];
  
  if(getcwd(pwd, sizeof(pwd)) == NULL){
    perror("getcwd() error");
  } else {
    printf("[M P S H]:~%s $ ", pwd);
  }
}

void mkdir_mpsh(char *cmd){
  int res = 0;
  if (cmd != NULL)
  {
    res = mkdir(cmd, 0777);
    
    if(res == 0){
      printf("OK!\n");
      } else {
      perror("ERROR on mkdir");
    }
  }
}

void cd_mpsh(int arg, char * cmd){
  const char * home;
  int result = 0;
      if (arg == 1){
        printf("Argc est a la pos 1\n");

        home = getenv("HOME");
        int i = chdir(home);

        if (i<0){
          printf("Désolé on peut pas changer de repertoire !!!!\n");
        }else{
          printf("changement de repertoire\n");
          printf("home = %s\n", home);
        }
      }
      result = chdir(cmd);
      if (result == 0){
        printf("changement de repertoire\n");
       // strcpy(home,getenv("PWD"));
        //strcpy(home,argv[1]);
      }
      else
        printf("Impossible de changer de repertoire\n");
}

void ls_mpsh(int arg, char * cmd){
  if (arg > 1){
      DIR *mydir;
      struct dirent *myfile;
      struct stat mystat;

      char buf[512];
      
        mydir = opendir(cmd);
        while((myfile = readdir(mydir)) != NULL)
        {
            sprintf(buf, "%s/%s", cmd, myfile->d_name);
            stat(buf, &mystat);
            printf("%zu",mystat.st_size);
            printf(" %s\n", myfile->d_name);
        }
        closedir(mydir);
      }else{
        struct dirent **namelist;
         int n;

         n = scandir(".", &namelist, NULL, alphasort);
         if (n < 0)
             perror("scandir");
         else {
             while (n--) {
                 printf("%s\n", namelist[n]->d_name);
                 free(namelist[n]);
             }
             free(namelist);
         }
      }
      
    
}

void cat_mpsh(int arg, char * cmd){
  int i, fd, ch;  

      for (i = 1; i < arg; i++)
        {
          fd = open( cmd, O_RDONLY );
          if ( fd < 0 ) {
           perror( cmd ); 
           continue; 
         }
         while ( read( fd, &ch, 1 ) == 1 ) 
            write( STDOUT_FILENO, &ch, 1 );
          close( fd );
      }
}


void echo_mpsh(int arg, char ** cmd){
  if (arg <= 1)
      {
        puts("rien a afficher !!!!!");
      }else{
        for (int i = 1; i < arg; ++i)
        {
          printf("%s ", cmd[i]);
        }
        printf("\n");
      }
}

void history_mpsh(int arg, char ** cmd){
  if(arg<2){ //affiche la liste numérotée de l'historiques des cmds
    cat_mpsh(2, "histfichier"); //A amélioré avec chemin relatif ??
    
  }else{
    if(atoi(cmd[1])>0){ //Relance la commande numero n de la liste
      int fin =0; //fin du while si on trouve la ligne
      int cptNumChaine = 1;//Numero de la ligne récupérer dans le fichier (boucle while)
      int argc = 0; //Nombre mot dans la ligne
 
      char ** argvCmd = malloc(sizeof(char));
      char chaine[TAILLE_MAX] = "";

      FILE* histfichier = NULL;
      histfichier = fopen("histfichier", "r");

      if (histfichier != NULL){
        while (fin == 0 && (fgets(chaine, TAILLE_MAX, histfichier) != NULL)){
          if(cptNumChaine == atoi(cmd[1])){
            fin++;
          } 
          cptNumChaine++;
        }
        argc = convertionCmd(chaine, argvCmd);
      }

      if (strcmp("pwd",argvCmd[0])==0){
        pwd_mpsh();
      }
      if (strcmp("mkdir",argvCmd[0])== 0){
        mkdir_mpsh(argvCmd[1]);
      }
      if (strcmp("cat",argvCmd[0]) == 0){
        cat_mpsh(argc, argvCmd[1]);
      } 
      if (strcmp("cd",argvCmd[0])== 0){
        cd_mpsh(argc, argvCmd[1]);
      }
      if (strcmp("ls",argvCmd[0])==0){
        ls_mpsh(argc, argvCmd[1]);
      }
      if (strcmp("echo",argvCmd[0])==0){
        echo_mpsh(argc, argvCmd);
      }
      if (strcmp("history",argvCmd[0])==0){
        history_mpsh(argc, argvCmd);
      }
      fclose(histfichier);
    }else{
      //on fixe a -n le nbre de cmd a enregitrer
    }
  }
}

void umask_mpsh(){

  mode_t mask;
  umask(mask);
  printf("le masque est appliqué \n");
  return;
}

void convertion(int arg, char ** cmd, char * chaine){
  char * ctmp;
  int cptchaine = 0;
  for(int i = 0; i < arg; i++){
    ctmp = cmd[i];
    for (int j = 0; j<strlen(ctmp); j++){
      chaine[cptchaine]=ctmp[j];
      cptchaine++;
    }
    chaine[cptchaine]=' ';
    cptchaine++;
  }chaine[cptchaine]='\n';
  chaine[cptchaine+1]='\0';
}

/*
**Convertie(split) une chaine simple char *, en ligne de commande char **
**Permet de relancer les commandes depuis l'historique
**Renvoie le nbre de mot trouver dans la chaine de cmd (ex: "cat fichier" renvoie 2)
*/
int convertionCmd(char * chaineNumeroter, char ** cmd){
  int icmd=1;
  int caracActuel=0;
  int fin = 0;//fin du while
  int taille = strlen(chaineNumeroter);

  //Chaines utiles pour les comparaisons lors des splits
  char *cVide = " ";
  char *cDeuxPoint = ":\0";

  //chaine temporaire stock chaque caractere, pour les comparaisons
  char *ccpt =(char*)malloc(TAILLE_MAX*sizeof(char));

  ccpt[0]= chaineNumeroter[caracActuel];//Premiere lettre de la chaine
  ccpt[1]='\0';//Permet de comparer des caractere

  //Permet de trouver la premiere lette de la cmd, supprime la numérotation
  while(fin == 0 && caracActuel<(taille-2)){
    ccpt[0]= chaineNumeroter[caracActuel];
    if(strcmp(ccpt, cDeuxPoint) == 0){
      fin++;
    }
      caracActuel++;
  }
  
  cmd[0]=&chaineNumeroter[caracActuel];//On stock le debut du 1er mot

  //On stock les adresses des mots contenut dans chaine dans des pointeurs
  while(caracActuel<(taille-2)){ //Parcours la ligne du fichier
    while((strcmp(ccpt, cVide)!= 0) && caracActuel<(taille-2)){//Tant que l'on tombe pas sur un caractere espace ou la fin de la chaine
      caracActuel++;
      ccpt[0] = chaineNumeroter[caracActuel]; //Caractere suivant
    }
    chaineNumeroter[caracActuel] = '\0'; //On a trouver le premier mot
    caracActuel++;
    cmd[icmd] = &chaineNumeroter[caracActuel]; //On stock l'adresse
    icmd++;
    ccpt[0] = chaineNumeroter[caracActuel]; //Caractere suivant
  }

  return (icmd-1);
}
