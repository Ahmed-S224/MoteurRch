#include "telechargement.h"


static size_t ecrire_donnee(void *contenu, size_t taille, size_t tmem, void *stream){
  return fwrite(contenu, taille, tmem, (FILE *)stream);
}


 
void telechargement(char *url, int *profondeur, int *compteur, char *fichier) {
  char *buff = malloc(sizeof(char[1024]));
  if(getcwd(buff, sizeof(char[1024])) == NULL){
    exit(EXIT_FAILURE);
  }
  printf("dir = %s\n", buff);

  char nom_fichier [30];

  sprintf(nom_fichier, "fic%d.html", *compteur);
  *compteur +=1;


  CURL *curl;
  CURLcode res;
  FILE *lien_fic;

  chdir("/tmp/");
  
  curl = curl_easy_init();

  curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

  curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);

  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, ecrire_donnee);

  lien_fic = fopen(nom_fichier, "wb");


  if(lien_fic) {
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, lien_fic);

    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    
 
    res = curl_easy_perform(curl);
    


    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(curl_easy_perform(curl)));
 
    
    
    fclose(lien_fic);
  }

  curl_easy_cleanup(curl);
  
  //strncpy(fi, nom_fichier, MAX_URL_LENGTH);

  chdir(buff);
  free(buff);
}

int main(char* argv[]){
  char* url = "www.lemonde.fr";
  char* fichier;
  int *compteur;
  int *profondeur;
  telechargement(url, profondeur, compteur, fichier);



  return 0;
}