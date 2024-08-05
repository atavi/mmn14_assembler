#ifndef _UTILS_H
#define _UTILS_H

#include "globals.h"

#define NEXT_NON_WHITE(string, index) \
        for (;string[(index)] && (string[(index)] == '\t' || string[(index)] == ' '); (++(index)));

void *my_malloc(long size) {
	void *ptr = malloc(size);
	if (ptr == NULL) {
		printf("Error: Fatal - Memory allocation failed.\n");
		exit(1);
	{
	return ptr;
}


#endif

