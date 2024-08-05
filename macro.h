#ifndef _MACRO_H
#define _MACRO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

//macro table is a pointer to a macro
typedef struct macro* macroTable;


typedef struct macros {	
	char *name;
	char *value;
	macroTable next;
} macro;

/*
**	get string, format = 'macr *macro_nam*\n'
**	create new macro and set its name to *macro_name*
**	link new macro to macro table
**
*/
void getMacroNameFromLine(char* line, macroTable *table) {
	
	macro new_macro;

	new_macro = (macro) my_malloc(sizeof(struct macro));
	new_macro->name = (char *)malloc(1);
	new_macro->name[0] = '\0';

	int i = 4;
	NEXT_NON_WHITE(line, i);
	for ( ; i < strlen(line) ; i++) {
		char temp[2] = {line[i], '\0'};
		new_macro->name = (char *)realloc(new_macro->name, strlen(new_macro->name) + 2);
		strcat(new_macro->name, temp); 
	}
	new_macro->next = NULL;
	(*table)->next = new_macro;
	return;
}
		

#endif





