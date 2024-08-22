/*
* CS4280 Fall 2014 - P2 
* Author: Loc Nguyen
* 
* $Id: main.c,v 1.5 2014/11/12 18:17:34 lhn7c5 Exp $
* $Source: /accounts/students/l/lhn7c5/4280/P2/RCS/main.c,v $
* Last modified: 
*       by $Author: lhn7c5 $
*       on $Date: 2014/11/12 18:17:34 $
* 
* $Log: main.c,v $
* Revision 1.5  2014/11/12 18:17:34  lhn7c5
* Parse tree with a linked-list of tokens per node.
*
* Revision 1.4  2014/11/09 18:33:27  lhn7c5
* Done parser and parse tree.
*
* Revision 1.3  2014/11/08 20:03:42  lhn7c5
* Done parser.
*
* Revision 1.2  2014/11/07 07:35:46  lhn7c5
* Done scanner.
*
* Revision 1.1  2014/11/06 21:53:39  lhn7c5
* Initial revision
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "token.h"
#include "scanner.h"
#include "parser.h"

int main(int argc, char *argv[])
{
	// printf("---BEGIN main()--- \n");
	FILE *filePtr;
	/*---------Begin process cmd-line args and Redirection--------*/

	switch (argc) {
		case 1: // No parameters, use stdin
			// printf("NO argument provided\n");
			filePtr = stdin;
			break;

		case 2: // One parameter, use .lan file supplied	
			if ( (filePtr = fopen(strcat(argv[1], ".lan"), "r")) == NULL ) {
				printf("Cannot open input file %s.\n", argv[1]);
				printf("Syntax: testScanner [file] (.lan is implicit)\n");
				exit(1);
			}
			break;

		default:
			printf("Syntax: testScanner [file] (.lan is implicit)\n");
			exit(0);
	}

	/*---------End process cmd-line args and Redirection----------*/

	/*---------Begin check if file empty-----------*/

	fseek(filePtr, 0, SEEK_END);
	if (ftell(filePtr) == 0) {
		printf("File is empty.\n");
		exit(1);
	} else {
		rewind(filePtr);
	}

	/*---------/End check if file empty-------------*/

	/*---------Begin check for invalid characters and max length-------------*/
	
	char c;
	int numLine = 1;

	int charCount = 0;
	char tempStr[MAX]; // ! Remember: C doesn't do array out-of-bound checking! 
	int i;

	int isValid = 1; // true 
	while ((c = fgetc(filePtr)) != EOF) {
		if (c == '\n')
			numLine++;

		// Exclude comment line starting with '//'
		if (c == '/') {
			if (fgetc(filePtr) == '/') {
				while ((c = fgetc(filePtr)) != '\n') {
					//printf("%c", c);
				}
				numLine++;
			}			
		}

		// printf("%c", c); 

		if (isalnum(c)) {
			//printf("%c is letter or a number \n", c);
			tempStr[charCount] = c; // array out-of-bound checking not happen here
			charCount++;
			if (charCount > MAX) {
				printf("Word '%s' on line number %d is too long. \n", tempStr, numLine);
				exit(1);	
			}
		} else if (isspace(c) || isExAcceptableChar(c)) { 
			//printf("%c is space is extra acceptable character \n", c);
			charCount = 0;
		} else {
			printf("Invalid character '%c' at line %d. \n", c, numLine);
			isValid = 0; // false
		}

	}

	if (isValid == 0) { 
		printf("Something wrong with the input file. \n");
		exit(1);
	}

	/*---------/End check for invalid characters and max length-------------*/
	

	// At this time, the file is good. Now let scanner.c do the work
	
	displaySourceFile(filePtr);


	/*---------Begin Scanner-------------*/

	printf("%10s \t Line number \t %s\n\n", "Token instance", "Token type");
	numToken = 0; // extern var
	//Token *tokens = (Token *) malloc(numToken * sizeof(Token));	
	tokens = (Token *) malloc(numToken * sizeof(Token)); // extern var	
	do {
		numToken++;
		tokens = (Token *)realloc(tokens, numToken * sizeof(Token));
		tokens[numToken - 1] = scanner(filePtr);

		printToken(tokens[numToken - 1]);

	} while (tokens[numToken - 1].tokenType != EOFtk);

	/*---------/End Scanner-------------*/


	displaySourceFile(filePtr);


	/*---------Begin Parser-------------*/
	
	parser(filePtr);

	/*---------/End Parser--------------*/


	fclose(filePtr);
	// printf("\n---/END main()--- \n");
	return 0;
}

