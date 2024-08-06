#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "globals.h"
#include "utils.h"
#include "macro.h"

int main(int argc, char *argv[]){

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
	macro_table mcrTable = newMacro();

	macro_ptr mcr = newMacro();
	
	/*open input file
	*/
	FILE* fp = fopen(fileName, "r");
	if (fp == NULL) {
        	printf("Cannot open file %s for reading\n", fileName);
        	return 1;
	}
	

	curr_line_info.fileName = fileName;
	curr_line_info.data = curr_line;
	for (curr_line_info.index = 1; fgets(curr_line_info.data, 100, fp) != NULL ; curr_line_info.index++) {
		if (mcrFlag) {
			if (memcmp(curr_line_info.data, "endmacr", 7) != 0) {
				/*macro data line
				//write curr_line to macro.value
				*/
				writeLineToMacro(mcr, curr_line_info.data);
				continue;
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
			mcr = getMacroFromName(mcrTable, curr_line_info.data);
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
		mcr = macroLookup(mcrTable, curr_line_info.data);
		if (mcr != NULL) {
			fputs(mcr->value, afterMacro);
			continue;
		}
		fputs(curr_line_info.data, afterMacro);
	}

	fclose(fp);
	fclose(afterMacro);

	return 0;
}
