#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "macro.h"
#include "utils.h"
#include "globals.h"

macro_ptr newMacro() {
	macro_ptr mcr = (macro_ptr)my_malloc(sizeof(macro));
	mcr->name = (char *)my_malloc((MAX_LINE_LEN - 5) * sizeof(char));
	mcr->value = (char *)my_malloc(MAX_LINE_LEN * sizeof(char));

	mcr->name[0] = '\0';
	mcr->value[0] = '\0';
	mcr->next = NULL;
	
	return mcr;
}

macro_ptr newMacroWithName(char* name) {
	macro_ptr mcr = newMacro();
	mcr->name = (char*)my_malloc((strlen(name) + 1) * sizeof(char));
	strcpy(mcr->name, name);
	return mcr;
}

void addMacroToTable(macro_table *table, macro_ptr mcr) {
	mcr->next = table;
	table = mcr;
}

macro_ptr getMacroFromName(macro_table table, char* name) {
	macro_ptr mcr;
	mcr = macroLookup(table, name);
	if (mcr == NULL) {
		addMacroToTable(table, newMacroWithName(name));
	}

	return mcr;
}

void freeMacroTable(macro_table table) {
	macro_ptr index = table;
	macro_ptr next;

	while (index != NULL) {
		next = index->next;
		free(index->name);
		free(index->value);
		free(index);
		index = next;
	}
}

macro_ptr macroLookup(macro_table table, char* name) {
	macro_ptr index = table;

	while(index != NULL) {
		if(strcmp(index->name, name) == 0) break;
		index = index->next;
	}
	return index;
}


char* getMacroNameFromLine(char* line) {
	return getSubString(line, 5);
}
