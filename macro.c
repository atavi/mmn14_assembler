#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "macro.h"
#include "utils.h"


/* main of macro.c: creates *.am for file */
void macrDeploy(char* fileName, macro_table table) {

	FILE *am;
	FILE *fp;
	fp = fopen(fileName, "r");
	am = fopen("%s.am", "w");

	macro_ptr curr_macro = NULL;
	macro_line_status curr_line_status;

	line_info curr_line_info;
	
	char* newFileName[strlen(fileName) + 3];
	
	/* iterated through file */
	for (curr_line_info.index = 1; fgets(curr_line_info.data, MAX_LINE_LEN, fp) != NULL ; curr_line_info.index++) {
		curr_line_status = getMacroLineStatus(curr_line_info.data);
		switch(curr_line_status) {
			case DEFINITION:	
				/* line is a new macro definition */ 
				curr_macro = newMacroWithName(curr_line_info.data + 5);
				addMacroToTable(&table, curr_macro);
			case ENDMACRO:
				curr_macro = NULL;
			case DEFAULT:
				if (curr_macro != NULL) {
					writeLineToMacro(curr_macro, curr_line_info.data);
					break;
				}
				else {
					curr_macro = macroLookup(table, curr_line_info.data);
					if (curr_macro != NULL) {
						writeMacroToFile(curr_macro, am);
						break;
					}
					fputs(curr_line_info.data, am);
					break;
				}
			case ILLEGAL_MACRO_LINE:
				printf("ILLEGAL MACRO LINE");
		}
	}

}

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
	*table = new_head;
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

void writeLineToMacro(macro_ptr mcr, char* line) {
	mcr->value = strncat(mcr->value, line, MAX_LINE_LEN);
}

macro_line_status isMacroLine(char* line) {

	if(!isSubString(line, "macr")) return DEFAULT; 

	if(memcmp(line, "macr ", 5) == 0 || memcmp(line, "macr\t", 5) == 0) return DEFINITION;

	if(memcmp(line, "endmacr\n", 8) == 0) return ENDMACRO;

	return ILLEGAL_MACRO_LINE; 
	
}























