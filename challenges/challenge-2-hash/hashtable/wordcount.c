/**
  wordcount.c
  Riešenie IJC-DU2, príklad b), 23.4.2017
  Autor: Matúš Liščinský, FIT
  Login: xlisci02
  Preložené: gcc 5.4.0 (merlin)
  Pocitanie slov v subore 
**/

#include "hash_table.h"
#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 127
/*
* Pri vybere velkosti tabulky som sa rozdhodol pre cislo 12289 kedze  
* podla dokumentu: good hash table primes viz. http://planetmath.org/sites/default/files/texpdf/33327.pdf 
* pri tomto cisle dochadza k relativne malej chybovosti a spracovanie aj objemnejsich
* textov program zvladal v slusnom case 
*/
#define SIZE_OF_TABLE 12289 

/*
* Funkcia print_tab sluzi na:
* Vypis zaznamu tabulky
*/
void print_tab(char * key, unsigned data)
{
	printf("%s\t%u\n",key,data);	
}

/*
* Funkcia main
*/
int main (int argc, char ** argv)
{
	if (argc != 3) {
		printf("usage: ./wordcount [student|java|djb] <INPUT>\n");
		exit(1);
	}

	unsigned int (*hfunc) (const char*);
	if (strcmp(argv[1], "djb") == 0) {
		printf("Selected: djb hash function\n");
		hfunc = djb_hash_function;
	} else if (strcmp(argv[1], "java") == 0) {
		printf("Selected: java hash function\n");
		hfunc = java_hash_function;
	} else {
		printf("Selected: student hash function\n");
		hfunc = student_hash_function;
	}
	
	htab_t * tab = htab_init(SIZE_OF_TABLE, hfunc);

	if(tab==NULL)
	{
		fprintf(stderr,"Error while creating a hash table\n");
		return 1;
	}	

	char str[MAX] = {0};
	int c;

	FILE * fp = fopen(argv[2],"r");
	while((c = get_word(str,MAX,fp))!=EOF || strcmp(str,"")!=0)
	{
		if(htab_lookup_add(tab,str)==NULL)
		{
			htab_free(tab); 
			fprintf(stderr,"Error while loading the table\n");
			return 1;
		}
		if(c==EOF)
			break;
	}
	
	if(overfull_war)
		fprintf(stderr,"[WARNING] some words were truncated\n");

	if (false) {
		// You can uncomment this for debugging
		htab_foreach(tab,&print_tab);
	}
	htab_free(tab); 

	return 0;
}
