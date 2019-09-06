#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>

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
  sqlite3_close(db);
  return 0;
}

