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


/* pointer to table and new macro to add
** macro is new head of list
** new_head->next points to old table,
** table points to new head
*/
void addMacroToTable(macro_table* table, macro_ptr new_head) {
	new_head->next = *table; 
	table = mcr*;
}

macro_ptr getMacroFromName(macro_table* table, char* name) {
	macro_ptr mcr;
	mcr = macroLookup(*table, name);
	if (mcr == NULL) {
		mcr = newMacroWithName(name);
		addMacroToTable(table, mcr);
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
		
	printf("Macro lookup enter\t");
	macro_ptr index = table;

	while(index != NULL) {
		if(strcmp(index->name, name) == 0) break;
		index = index->next;
	}
		
	printf("Macro lookup exit\t");

	return index;
}


char* getMacroNameFromLine(char* line) {
	return getSubString(line, 5);
}

void writeLineToMacro(macro_ptr mcr, char* line) {
	mcr->value = strncat(mcr->value, line, MAX_LINE_LEN);
}























