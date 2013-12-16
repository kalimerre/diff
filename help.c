#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "help.h"
#define TAILLE_MAX 1000

/*
*
 HELP
*
*/
void help ()
{
    printf("Options available:\n");
    printf("  -v \t\t\t\t Display the version of the program \n");
	printf("  --version \t\t\t Display the version of the program \n");
    printf("  --help \t\t\t Output this help.\n");
}
/*
*
*
END OF HELP
*
*/