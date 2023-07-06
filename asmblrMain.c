#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "util.h"

/* beta version for preAsmblr */
 
int main (int argc, char* argv[])
{

	if (argc < 2)
	{
		printf("Usage: %s <filename> <filename> ...\n", argv[0]);
	}
	
	 /* Processing each file name argument */
    for (int i = 1; i < argc; i++) 
    {
        FILE* file = fopen(argv[i], "r+");

        if (file == NULL) 
        {
            printf("Failed to open file: %s\n", argv[i]);
            continue; /* Move on to the next file */
        }

        mcroUnfold(file);

        
		/* for this part we use read row, for each row that is formated - tokenize
			each word that is now only seperated by 1 space. send out each token
			to 'handle data' function, according to what it returns */
        fclose(file);
    }

    return 0;
	
}
