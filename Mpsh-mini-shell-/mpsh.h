 
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/wait.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h> 
#include <string.h>
#include <dirent.h>

#define TAILLE_MAX 512

void read_cmd(int* argc,char*** argv);

void pwd_mpsh();
 
void mkdir_mpsh(char * cmd);

void cat_mpsh(int arg, char * cmd);

void cd_mpsh(int arg, char * cmd);

void ls_mpsh(int arg, char * cmd);

void echo_mpsh(int arg, char ** cmd);

void history_mpsh();

void umask_mpsh();

void convertion(int arg, char ** cmd, char * chaine);

int convertionCmd(char * chaineNumeroter, char ** cmd);

void chemin();
