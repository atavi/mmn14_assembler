#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "globals.h"
#include "macro.h"

int main(int argc, char *argv[]){

	char *fileName;
	fileName = argv[1];
	bool macrFlag = FALSE;
	
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

	macro_ptr lastMacro;
	
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
		if (macrFlag) {
			if (memcmp(curr_line_info.data, "endmacr", 7) != 0) {
				/*macro data line
				//write curr_line to macro.value
				*/
				continue;
			}
			/*if here -> last line of macro definition
			*/
			macrFlag = FALSE;
			continue;
		}
		if (memcmp(curr_line_info.data, "macr", 4) == 0) {
			/*line starts with 'macr' - macro decleration
			//copy macro name to macro table
			*/
			lastMacro = getMacroNameFromLine(curr_line_info.data);
			/*lastMacro points to lastMacro->next			
			*/
			macrFlag = TRUE;
			continue;
		}
		/*
		if (lookupMacro(curr_line, filename.mt)) {
			//write macro.value to afterMacro
			//continue
		}*/
		/*if here -> curr_line has no macro relevance
		*/
		fputs(curr_line_info.data, afterMacro);
	}

	fclose(fp);
	fclose(afterMacro);

	return 0;
}
