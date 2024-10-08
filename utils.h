#ifndef _UTILS_H
#define _UTILS_H

#include "globals.h"

#define NEXT_NON_WHITE(string, index) \
        for (;string[(index)] && (string[(index)] == '\t' || string[(index)] == ' '); (++(index)));
#define NEXT_WHITE(string, index) \
	for (;string[(index)] && (string[(index)] != '\t' || string [(index)] != ' '); (++(index)));;

void *my_malloc(int size);

char* getSubString(char* s, int i);
bool isSubString(char* s, char* t);


#endif

