#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
  int i;
  for(i=0; i<argc; i++){
    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  printf("\n");
  return 0;
}

int main(int argc, char* argv[]){
  sqlite3 *db;
  int rc = sqlite3_open(argv[0], &db);
  if(rc){
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    return 1;
  }
  else{
    fprintf(stderr, "Opened database successfully\n");
  }
  //Create SQL statement
  const char *sql = "CREATE TABLE PROJET(" \
    "ID INT PRIMARY KEY NOT NULL," \
    "MOTS TEXT NOT NULL," \
    "URL TEXT NOT NULL," \
    "POIDS INT NOT NULL," \
    "LIENPERE TEXT NULL);";

  //Execute SQL statement 
  char *errmsg = "";
  if(sqlite3_exec(db, sql, callback, 0, &errmsg) != SQLITE_OK){
    fprintf(stderr, "SQL error: %s\n", errmsg);
    sqlite3_free(errmsg);
  }
  else{
    fprintf(stdout, "Operation done successfully\n");
  }
  sqlite3_close(db);
  return 0;
}
