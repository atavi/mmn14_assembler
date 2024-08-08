#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "macro.h"
#include "utils.h"


/* main of macro.c: creates *.am for file */
void macroDeploy(char* fileName, macro_table* table) {
	printf("HI\n");
	FILE *am;
	FILE *fp;
	char* newFileName = (char *)my_malloc(sizeof(char)*strlen(fileName) + 4); 
	sprintf(newFileName, "%s.am", fileName);

	fp = fopen(fileName, "r");
	if (fp == NULL) {
		printf("Error opening file %s\n", fileName);
		return;
	}
	am = fopen(newFileName, "w");
	if (am == NULL) {
		printf("Error opening file %s\n", newFileName);
		fclose(fp);
		return;
	}
	macro_ptr curr_macro;
	curr_macro = newMacro();
	line_info curr_line_info;
	bool mFlag = FALSE;
	char newMacroName[MAX_LINE_LEN];
	
	/* iterated through file */
	for (curr_line_info.index = 1; !feof(fp) && fgets(curr_line_info.data, MAX_LINE_LEN, fp) != NULL ; curr_line_info.index++) {		
		printf("Line number %d:\tdata: %s\t\n", curr_line_info.index, curr_line_info.data);
		if(!mFlag) {
			if (curr_macro != NULL) {
				printf("Printing line %d to file\n", curr_line_info.index);
				writeMacroToFile(curr_macro, am);
				continue;
			}	
			if(memcmp(curr_line_info.data, "macr", 4) == 0) {
				mFlag = TRUE;
				strcpy(newMacroName, getMacroNameFromLine(curr_line_info.data));	
				curr_macro = newMacroWithName(newMacroName);
				addMacroToTable(&table, curr_macro);
				continue;
			}
			curr_macro->value = strcat(curr_macro->value, curr_line_info.data);
		}
		if(memcmp(curr_line_info.data, "endmacr", 7) == 0) {
			mFlag = FALSE;
			continue;
		}
		fputs(curr_line_info.data, am);
		
		
	}

	fclose(fp);
	fclose(am);
	free(newFileName);
	free(newMacroName);

}

macro_ptr newMacro() {
	macro_ptr mcr = (macro_ptr)my_malloc(sizeof(macro));
	mcr->name = (char *)my_malloc(MAX_LINE_LEN * sizeof(char));
	mcr->value = (char *)my_malloc(MAX_LINE_LEN * sizeof(char));

	mcr->name[0] = '\0';
	mcr->value[0] = '\0';
	mcr->next = NULL;
	
	return mcr;
}

macro_ptr newMacroWithName(char *name) {
	macro_ptr mcr = newMacro();
	mcr->name = (char*)my_malloc((strlen(name) + 1) * sizeof(char));
	strcpy(mcr->name, name[5]);
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

void writeLineToMacro(char* line, macro_ptr mcr) {
	mcr->value = strncat(mcr->value, line, MAX_LINE_LEN);
}
/* assume this line checked for macro relevnce */
macro_line_status getMacroLineStatus(char* line) {
	if (!isSubString(line, "macr")) return DEFAULT;
	if (memcmp(line, "macr ", 5) == 0 || memcmp(line, "macr\t", 5)) return DEFINITION;
	return ENDMACRO;
	
}

void writeMacroToFile(macro_ptr mcr, FILE* file) {
	fputs(mcr->value, file);
}




















