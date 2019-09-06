#include <stdio.h>

int main(void){
	char * test = system("python3 parser.py");
	printf(test);
}