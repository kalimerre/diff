#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 1000
#include "help.h"
#include "version.h"

/*
*
*
*
* DIFF - 3A - DW - ESGI 2013
* Cyril Valière - Maxime Grimler
* Christophe Villeger - Marc Omar Tawfik
*
* 
*
*/

int number_lines(FILE *f);
char **convertFileToTab(FILE *f);

int main(int argc, char** argv){
	if (argc < 2) {
		printf("Nombre de parametres insuffisants \n"); //Check if we got enough parameters
		return 1;
	}
	if(strcmp(argv[1], "--help") == 0) {
		help(); //load help function if "--help" is typed
		return 1;
		}
	if(strcmp(argv[1], "--version") == 0 || strcmp(argv[1], "-v") == 0) {
		version(); //load version function if "--version" or "-v" is typed
		return 0;
		}	

	
	char* src1 = argv[1]; //Get the first file in argument
	char* src2 = argv[2]; //Get the second file in argument
	
	FILE *f1 = fopen(src1, "r"); //Open the first file
	FILE *f2 = fopen(src2, "r"); //Open the second file
	
	if (f1 != NULL && f2 != NULL) //Check if f1 or f2 is NULL (not able to open)
    {
	
	//Calculate the number of lines per file
	int linesf1 = number_lines(f1);
	int linesf2 = number_lines(f2);
	
	
	//Convert the file to a tab to compare
	char** tabF1 = convertFileToTab(f1);
	char** tabF2 = convertFileToTab(f2);
	
	//Display the both files 
	printf("****************************\n");
	printf("Affichage tableau fichier 1\n");
	printf("****************************\n\n");
	int i;
	for(i=0 ; i < linesf1 ; i++)
	{
		printf("%s", tabF1[i]);
		
	}
	printf("\n\n\n****************************\n");
	printf("Affichage tableau fichier 2\n");
	printf("****************************\n\n");
		for(i=0 ; i < linesf2 ; i++)
	{
		printf("%s", tabF2[i]);
		
	}
	printf("\n\n\n***********************************\n");
	printf("Affichage nombre lignes par fichier\n");
	printf("***********************************\n\n");
	printf("f1 = %i et f2 = %i\n\n", linesf1, linesf2);
	
	//Start of the diff part
	printf("\n\n\n***************\n");
	printf("LANCEMENT DIFF\n");
	printf("***************\n\n");
	printf("Lancement de la commande diff de %s avec %s:\n\n",src1,src2);

	//define two counter of lines
	int cptr_tabF2;
	int cptr_tabF1 = 0;

	//While our lines counter is not inferior to the number of lines of first file we stay in the for
	for (cptr_tabF2=0; cptr_tabF2<linesf1; cptr_tabF2++)
	{
	
		int match = 0; //Variable used to know if we find an equal occurence in both files
		int next_line = 0; //Variable used to know how many lines there is between the match files.

		//While we don't have two lines equal in both files and while our counter is inferior to the number of lines to file 2 we stay in the while boucle.
		while (cptr_tabF1<linesf2 && match == 0)
		{
			// If strcmp function returns 0 (which means both lines are equal) we set match to 1
					if(strcmp(tabF1[cptr_tabF2], tabF2[cptr_tabF1]) == 0)
						match = 1;
			// else we increment the next line variable 
					else
						next_line++;
				
			cptr_tabF1++;
		}

		//if our variable match is equal to 1 we will treat the part to know if the line exist or not in the other file
		if (match == 1)
		{
			//Display the lines when we incremented the variable next_line
			int a = cptr_tabF1-next_line;
			for (a;a<cptr_tabF1;a++)
			{
				printf("> %s\n", tabF2[a-1]); //Means the line exist only in file 2 (we saw it with the >)
			}
            //Display the equal lines (we saw it with the =)
			printf("= %s\n", tabF1[cptr_tabF2]);



		}
		//Else if match was set to 0 it means the line exist only in file1
		else
		{
			printf("< %s\n", tabF1[cptr_tabF2]); //Means the line exist only in file 1 (we saw it with the <)
			cptr_tabF1 = cptr_tabF1-next_line; //We setup the cptr_tabF1 by removing the number of next_line to continue the diff with the other lines.
		}
	}


	//If file2 got more lines than file1 then we enter in this while to display it.
	while (cptr_tabF1 < linesf2)
    {
        printf("> %s\n", tabF2[cptr_tabF1]); //Print the new lines with the symbol > which means they only exist in file 2.
        cptr_tabF1++; //We increment our counter to display all new lines
    }

    //dellocation of malloc
    free(tabF1);
    free(tabF2);
	
	}
	
	    else
    {
        // We check which file cannot be open and display an error message
		if (f1 == NULL) {
				printf("Impossible d'ouvrir le fichier 1 \n");
				EXIT_FAILURE;
			}
		if (f2 == NULL){
				printf("Impossible d'ouvrir le fichier 2");
				EXIT_FAILURE;
			}

    }

}


char **convertFileToTab(FILE *f){
	char ligne[MAX_SIZE];
	
	int size_lines = number_lines(f); //We get back the number of lines to setup our malloc
	char** tab = (char**)malloc(size_lines*sizeof(char*)); //We declare our tab who will contain our file
	
	fseek(f, 0, SEEK_SET); //We setup the cursor to the first character of the file
		
	int i = 0;
	while(fgets(ligne,MAX_SIZE,f) != NULL){ // We read the file until it returns NULL
		tab[i] = (char*)malloc(MAX_SIZE*sizeof(char));
			if (tab[i] == NULL) //If the allocation of the memory is impossible we display an error message
				{
					printf("Allocation impossible\n");
					exit(EXIT_FAILURE);
				}	
		strcpy(tab[i], ligne); //We copy each line of the file to the tab and we increment the variable i
		i++;
	}
	
	return tab;
	
}


int number_lines(FILE *f){
	char chaine[MAX_SIZE] = "";
	int ligne_file = 0;

	if (f != NULL){
		while (fgets(chaine, MAX_SIZE, f) != NULL){ // We read the file until it returns NULL
			ligne_file++; //We increment the variable to know the number of line and return it
		}               
	return ligne_file;
	}
	
}