#ifndef _MACRO_H
#define _MACRO_H

#include "globals.h"

typedef enum macro_line_status {DEFAULT, DEFINITION, ENDMACRO} macro_line_status ;

typedef struct macro {	
	char *name;
	char *value;
	struct macro *next;
} macro, *macro_ptr, *macro_table;

void macroDeploy(char* filName, macro_table* table);

/*
** initiate new empty macro
*/
macro_ptr newMacro();
macro_ptr newMacroWithName(char* name);

void addMacroToTable(macro_table* table, macro_ptr new_head);
/*
** gets macro_table and macro_name
** checks if macro exists in table
** if new macro, 
** 	create new macro and link to macro table
**	return new macro pointer
** else
**	return pointer to corresponding macro in table
*/

void freeMacroTable(macro_table table);

char* getMacroNameFromLine(char* line);

/*
** iterate through table, compering name to current_macro->name
** returns pointer to macro in table, if exists, or NULL if not
*/
macro_ptr macroLookup(macro_table table, char* name);

macro_line_status getMacroLineStatus(char* line);

void writeLineToMacro(char* line, macro_ptr mcr);

void writeMacroToFile(macro_ptr mcr, FILE* file);
	
#endif





