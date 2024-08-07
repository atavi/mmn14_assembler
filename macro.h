#ifndef _MACRO_H
#define _MACRO_H

typedef struct macro {	
	char *name;
	char *value;
	struct macro *next;
} macro, *macro_ptr, *macro_table;

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
macro_ptr getMacroFromName(macro_table* table, char* name);	

void freeMacroTable(macro_table table);

/*
** iterate through table, compering name to current_macro->name
** returns pointer to macro in table, if exists, or NULL if not
*/
macro_ptr macroLookup(macro_table table, char* name);

char* getMacroNameFromLine(char* line);

void writeLineToMacro(macro_ptr mcr, char* line);
	
#endif





