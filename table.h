#ifndef _TABLE_H
#define _TABLE_H

/* table.h implements dynamically allocated linked list as Symbol Table for assembler.
**
** table format:
** 	SYMBOL NAME | SYMBOL TYPE | VALUE 
*/

/* define table as pointer to a row */
typedef struct row* table;

/* define single row in table */
typedef struct row {
	table next; 
	char *symbol;		//symbol name: "ADD", "LIST", ...
	symbolType type;	//see symbolType enum below
} 

typedef enum symbolType {
	CODE,
	DATA
{

#endif
