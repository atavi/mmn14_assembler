#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "globals.h"
#include "utils.h"
#include "macro.h"

int main(int argc, char *argv[]){

	if (argc < 2) {
		printf("-E-\ttoo few arguments.\n\tformat: \"./assembler PATH_TO_FILE\"");

	char *fileName;
	fileName = argv[1];
	bool mcrFlag = FALSE;
	
	/*allocate space for a single line
	*/
	char curr_line[100];
	line_info curr_line_info;
	
	/*destination file
	*/
	FILE *afterMacro;
	char newFileName[105];
	strcpy(newFileName, argv[1]);
	strcat(newFileName, ".am");
	afterMacro = fopen(newFileName, "w");
	macro_table mcrTable = NULL;

	macro_ptr mcr = NULL;
	
	/*open input file
	*/
	FILE* fp = fopen(fileName, "r");
	if (fp == NULL) {
        	printf("Cannot open file %s for reading\n", fileName);
        	return 1;
	}
	

	curr_line_info.fileName = fileName;
	curr_line_info.data = curr_line;


	
	printf("Main: pre for loop \n");

	for (curr_line_info.index = 1; fgets(curr_line_info.data, 100, fp) != NULL ; curr_line_info.index++) {
		if (mcrFlag) {
			if (memcmp(curr_line_info.data, "endmacr", 7) != 0) {
				/*macro data line
				//write curr_line to macro.value
				
				writeLineToMacro(mcr, curr_line_info.data);
				*/continue;
			}
			/*if here -> last line of macro definition
			*/
			mcrFlag = FALSE;
			continue;
		}
		/* line starts with 'macr' - macro decleration
		*/
		if (memcmp(curr_line_info.data, "macr", 4) == 0) {
			/* getMacroFromName returns pointer to corresponding macro in macro table
			*/
			mcr = getMacroFromName(&mcrTable, curr_line_info.data);
			/*if current line is a new macro definition, mcr->next will point to mcrTable
			*/
			if (mcr->next == mcrTable) {
				mcrTable = mcr;
			}
			mcrFlag = TRUE;
			continue;
		}
		/*
		** if here, line is either command or a call for existing macro
		*/
			
		printf("Macro lookup call\t");

		mcr = macroLookup(mcrTable, curr_line_info.data);

		printf("Macro lookup done\n");
		
		if (mcr != NULL) {
			printf("current macro not NULL");
			fputs(mcr->value, afterMacro);
			printf("\tcurrent macro->value:\t%s\n", &mcr->value);
			continue;
		}

		printf("\nif here current macro is NULL");
		fputs(curr_line_info.data, afterMacro);
	}

		
	printf("Main: survived for loop \n");

	/*
	** close all
	*/
	fclose(fp);
	fclose(afterMacro);
	freeMacroTable(mcrTable);
	
	return 0;
}












