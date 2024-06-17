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
	(void)argc;
	printf("hello: %s\n",argv[1]);
	// inicializacia tabulky 
	htab_t * tab = htab_init(SIZE_OF_TABLE);

	if(tab==NULL)
	{
		fprintf(stderr,"Chyba pri alokacii pamate\n");
		return 1;
	}	
	
	char str[MAX] = {0};
	int c;

	FILE * fp = fopen(argv[1],"r");
	/* nacitavanie slov a pridavanie do tabulky
	* ak narazi na EOF, testuje ci este nieco neostalo nacitane ak ano
	* prida do tabulky a vyskoci z cyklu
	*/
	printf("hello: %s\n",argv[1]);
	while((c = get_word(str,MAX,fp))!=EOF || strcmp(str,"")!=0)
	{
		if(htab_lookup_add(tab,str)==NULL)
		{
			htab_free(tab); 
			fprintf(stderr,"Chyba pri alokacii pamate pre novu polozku\n");
			return 1;
		}
		if(c==EOF)
			break;
	}
	
	if(overfull_war)
		fprintf(stderr,"[WARNING] Niektore zo slov prekrocilo limit a bolo skratene\n");

//	htab_foreach(tab,&print_tab); //vypis
	htab_free(tab); 

	return 0;
}
