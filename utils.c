#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

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

bool isSubString(char* s, char* t) {
	if (strstr(s, t) != NULL) return TRUE;
	return FALSE;
}
