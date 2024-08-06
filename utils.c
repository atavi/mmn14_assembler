#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "globals.h"

void* my_malloc(int size) {
	void* ptr = malloc(size);
	if (ptr == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		exit(1);
	}
	return ptr;
}

char* getSubString(char* s, int i) {
	return s + i;
}
/*
bool isSubString(char* s, char* t) {

	if (strlen(s) < strlen(t)) return FALSE;
	
	int i, j;	

	for (i = 0 ; i < strlen(s) - strlen(t) ; i++) {
		if(strncmp(s + i, t, strlen(t)) == 0) return TRUE;
	}
	
	return FALSE;
}*/
