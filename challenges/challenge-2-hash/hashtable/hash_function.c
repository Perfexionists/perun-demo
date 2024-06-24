/**
  hash_function.c
  Riešenie IJC-DU2, príklad b), 23.4.2017
  Autor: Matúš Liščinský, FIT
  Login: xlisci02
  Preložené: gcc 5.4.0 (merlin)
  Hashovacia funkcia
**/

#include "private_hash_table.h"
#include "hash_table.h"
#include <string.h>
#include <stdlib.h>

#ifndef max 
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

unsigned int student_hash_function(const char *str) 
{
    unsigned int h=0; 
    const unsigned char *p; 
    for(p=(const unsigned char*)str; *p!='\0'; p++) 
        h = 65599*h + *p; 
    return h; 
}

unsigned int djb_hash_function(const char *str) 
{

    unsigned int hash = 5381;
    unsigned int i = 0;
    unsigned length = strlen(str);
    for (i = 0; i < length; str++, i++)
        hash = ((hash << 5) + hash) + (*str);
    return hash;

}

/*
* Hash funkcia
* Rozptylovacia funkcia pre retazce podla literatury
*/
unsigned int java_hash_function(const char *str) 
{
     unsigned int hash = 0;
     unsigned length = strlen(str);
     unsigned skip = max(1, length);
     for (unsigned i = 0; i < length; i += skip)
         hash = str[i] + (37 * hash);
     return hash;
}
