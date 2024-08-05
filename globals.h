#ifndef _GLOBALS_H
#define _GLOBALS_H

/* IC: Instruction counter initial value = 100 */
#define IC_INIT_VAL = 100

#define MAX_LINE_LEN = 80

/* Boolean definition */
typedef enum booleans {TRUE = 1, FALSE = 0} bool ;

/* define registers */
typedef enum registers {R0, R1, R2, R3, R4, R5, R6, R7} reg ; 

/*
** struct to hold source line and its information 
*/
typedef struct line_info {
	
	int index;
	char* fileName;
	char *data;

} line_info;


#endif
