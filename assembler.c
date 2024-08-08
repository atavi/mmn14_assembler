#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "globals.h"
#include "utils.h"
#include "macro.h"

int main(int argc, char *argv[]){
	
	int i;

	macro_table macroTable;
	

	for(i = 1 ; i < argc ; i++) {
		macroDeploy(argv[i], macroTable);
	}
	
	return 0;
}












