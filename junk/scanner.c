/*
* CS4280 Fall 2014 - P2 
* Author: Loc Nguyen
* 
* $Id: scanner.c,v 1.5 2014/11/10 06:12:43 lhn7c5 Exp $
* $Source: /accounts/students/l/lhn7c5/4280/P2/RCS/scanner.c,v $
* Last modified: 
*       by $Author: lhn7c5 $
*       on $Date: 2014/11/10 06:12:43 $
* 
* $Log: scanner.c,v $
* Revision 1.5  2014/11/10 06:12:43  lhn7c5
* Add more specific output for each token type.
*
* Revision 1.4  2014/11/10 04:50:31  lhn7c5
* Done P2.
*
* Revision 1.3  2014/11/08 20:06:05  lhn7c5
* Done parser.
*
* Revision 1.2  2014/11/07 07:36:03  lhn7c5
* Done scanner.
*
* Revision 1.1  2014/11/06 21:55:19  lhn7c5
* Initial revision
*
*/

#include <stdio.h>
#include <stdlib.h>

#include "token.h"
#include "scanner.h"
#include "symdef.h"

int numToken = 0; // define extern var declared from token.h
int lineNum = 1; /// silimilar, extern var from token.h
Token *tokens = NULL; // define extern var

Token scanner(FILE *filePtr) {

	//printf("\n*** in scanner.c ***\n");

	Token token;
	char ch;

	while ((ch = fgetc(filePtr)) != EOF) {
		if (ch == '\n') 
			lineNum++;


		// Ignore comment starting with // to the end of line
		if (ch == '/') {
			if (fgetc(filePtr) == '/') {
				while ((ch = fgetc(filePtr)) != '\n') {}
				lineNum++;
			} else 
				fseek(filePtr, -1, SEEK_CUR);
		}

		if (isalpha(ch)) {
			word[wi++] = ch;
			while (isalpha(ch = fgetc(filePtr))) {
				word[wi++] = ch;
			}
			word[wi] = '\0';
			wi = 0;

			strcpy(token.str, word);
			if (isKeyword(word)) {
				token.tokenType = getTokenTypeOfKeyword(word);	
			} else {
				token.tokenType = IDtk;
			}
			token.lineNum = lineNum;

			fseek(filePtr, -1, SEEK_CUR);
			//printToken(token);
			return token;
		}

		else if (isdigit(ch)) {
			numStr[ni++] = ch;
			while (isdigit(ch = fgetc(filePtr))) {
				numStr[ni++] = ch;
			}
			numStr[ni] = '\0';
			ni = 0;

			strcpy(token.str, numStr);
			token.tokenType = NUMBERtk;
			token.lineNum = lineNum;

			fseek(filePtr, -1, SEEK_CUR);
			//printToken(token);
			return token;

		}
	
		else if (ispunct(ch)) {
			if (isDelimiter(ch)) {
				token.tokenType = getTokenTypeOfDelimiter(ch);
				token.lineNum = lineNum;

				char str[2];
				str[0] = ch;
				str[1] = '\0';
				strcpy(token.str, str);	

				//printToken(token);
				return token;
			}
			else if (isOtherOperators(ch)) {
				token.tokenType = getTokenTypeOfOtherOperator(ch);
				token.lineNum = lineNum;

				char str[2];
				str[0] = ch;
				str[1] = '\0';
				strcpy(token.str, str);

				//printToken(token);
				return token;
			}
			else if (isStartRelationalOperator(ch)) {
				if (ch == '<' || ch == '>') {
					token.lineNum = lineNum;
					if (ch == '<') {
						token.tokenType = LESStk;
						strcpy(token.str, "<");
					} else {
						token.tokenType = GREATERtk;
						strcpy(token.str, ">");
					}
					//printToken(token);
					return token;
				}
				else if (ch == '=') {
					if ((ch = fgetc(filePtr)) == '=' || ch == '>' || ch == '<') {
						token.lineNum = lineNum;
						if (ch == '=') {
							token.tokenType = EQUALtk;
							strcpy(token.str, "==");
						} else if (ch == '>') {
							token.tokenType = GREATEREQtk;
							strcpy(token.str, "=>");
						} else {
							token.tokenType = LESSEQtk;
							strcpy(token.str, "=<");
						}

						//printToken(token);
						return token;

					} else if (ch == '!') {
						if ((ch = fgetc(filePtr)) == '=') {
							token.lineNum = lineNum;
							token.tokenType = DIFFtk;
							strcpy(token.str, "=!=");

							//printToken(token);
							return token;
						} else 
							fseek(filePtr, -1, SEEK_CUR);
					} else 
						fseek(filePtr, -1, SEEK_CUR);
				}
			}
		} // end if ispunct

	} // end while
	
	// rewind(filePtr);

	//printf("\n*** in scanner.c ***\n");
	
	token.tokenType = EOFtk;
	return token;
}

/*----------Check a char----------*/
int isKeyword(char *str) {
	int i;
	int result = 0; // false
	for (i = 0; i < 15; i++) {
		if (!strcasecmp(keywords[i], str))
			result = 1;
	}
	return result;

}

int isDelimiter(char c) {
	 int i;
	 int result = 0; // false
	 for (i = 0; i < 9; i++) {
		if (delimiters[i] == c) 
		result = 1;
	 }
	 return result;
}

int isOtherOperators(char c) {
	 int i;
	 int result = 0; // false
	 for (i = 0; i < 6; i++) {
		if (otherOperators[i] == c) 
			result = 1;
	 }
	 return result;
 }

int isStartRelationalOperator(char c) {
	int i;
	int result = 0; // false
	if (c == '=' || c == '<' || c == '>') {
		result = 1;
	}
	return result;	
}

/*----------/Check a char----------*/

TokenType getTokenTypeOfKeyword(char *word) {

	if (strcasecmp(word, "start") == 0) return STARTtk; 
	if (strcasecmp(word, "finish") == 0) return FINISHtk; 
	if (strcasecmp(word, "then") == 0) return THENtk; 
	if (strcasecmp(word, "repeat") == 0) return REPEATtk; 
	if (strcasecmp(word, "var") == 0) return VARtk; 
	if (strcasecmp(word, "int") == 0) return INTtk; 
	if (strcasecmp(word, "float") == 0) return FLOATtk; 
	if (strcasecmp(word, "do") == 0) { return DOtk; }
	if (strcasecmp(word, "read") == 0) return READtk; 
	if (strcasecmp(word, "print") == 0) return PRINTtk; 
	if (strcasecmp(word, "void") == 0) return VOIDtk; 
	if (strcasecmp(word, "return") == 0) return RETURNtk; 
	if (strcasecmp(word, "dummy") ==0) return DUMMYtk; 
	if (strcasecmp(word, "program") == 0) return PROGRAMtk; 
}

TokenType getTokenTypeOfDelimiter(char ch) {
	if (ch == '.') return DOTtk;
	if (ch == '(') return LEFTPAtk;
	if (ch == ')') return RIGHTPAtk;
	if (ch == ',') return COMMAtk;
	if (ch == '{') return LEFTBRACEtk;
	if (ch == '}') return RIGHTBRACEtk;
	if (ch == ';') return SEMICOLONtk;
	if (ch == '[') return LEFTBRACKETtk;
	if (ch == ']') return RIGHTBRACKETtk;
}

TokenType getTokenTypeOfOtherOperator(char ch) {
	if (ch == '=') return ASSIGNtk;
	if (ch == ':') return COLONtk;
	if (ch == '+') return ADDtk;
	if (ch == '-') return SUBTRACTtk;
	if (ch == '*') return MULtk;
	if (ch == '/') return DIVtk;
	if (ch == '%') return REMAINDERtk;
}

// Besides English letters, and digits, these are extra acceptable characters
int isExAcceptableChar(char c) {
	if (c == '.' || c == '(' || c == ')' || c == ',' || c =='{' || c == '}' ||
		c == ';' || c == '[' || c == ']' || 
		c == ':' || c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || 
		c == '=' || c == '<' || c == '>' || c == '!' 
		/* || c == '#' */ ) {

		return 1;
	} else 
		return 0;
}

char *getTokenTypeStr(Token token, char *str) {
	switch (token.tokenType) {
		case IDtk: strcpy(str, "IDENTIFER"); break;
		case NUMBERtk: strcpy(str, "NUMBER"); break;

		case STARTtk: 	strcpy(str, "start [KEYWORD]"); break; 
		case FINISHtk: 	strcpy(str, "finish [KEYWORD]"); break;
		case THENtk: 	strcpy(str, "then [KEYWORD]"); break;
		case IFtk: 		strcpy(str, "if [KEYWORD]"); break;
		case REPEATtk: 	strcpy(str, "repeat [KEYWORD]"); break; 
		case VARtk: 	strcpy(str, "var [KEYWORD]"); break; 
		case INTtk: 	strcpy(str, "int [KEYWORD]"); break; 
		case FLOATtk: 	strcpy(str, "float [KEYWORD]"); break; 
		case DOtk: 		strcpy(str, "do [KEYWORD]"); break;
		case READtk: 	strcpy(str, "read [KEYWORD]"); break; 
		case PRINTtk: 	strcpy(str, "print [KEYWORD]"); break; 
		case VOIDtk: 	strcpy(str, "void [KEYWORD]"); break; 
		case RETURNtk: 	strcpy(str, "return [KEYWORD]"); break; 
		case DUMMYtk: 	strcpy(str, "dummy [KEYWORD]"); break; 
		case PROGRAMtk:	strcpy(str, "program [KEYWORD]"); break;

		case DOTtk: 	strcpy(str, "dot [DELIMITER]"); break; 
		case LEFTPAtk: 	strcpy(str, "left-parenthesis [DELIMITER]"); break; 
		case RIGHTPAtk: strcpy(str, "right-parenthesis [DELIMITER]"); break; 
		case COMMAtk: 	strcpy(str, "comma [DELIMITER]"); break; 
		case LEFTBRACEtk: 		strcpy(str, "left-brace [DELIMITER]"); break; 
		case RIGHTBRACEtk: 		strcpy(str, "right-brace [DELIMITER]"); break;
		case LEFTBRACKETtk:		strcpy(str, "left-bracket [DELIMITER]"); break;
		case RIGHTBRACKETtk:	strcpy(str, "right-bracket [DELIMITER]"); break;
		case SEMICOLONtk: 		strcpy(str, "semi-colon [DELIMITER]"); break; 

		case ASSIGNtk:		strcpy(str, "assign [OTHER OPERATOR]"); break;
		case COLONtk:		strcpy(str, "colon [OTHER OPERATOR]"); break;
		case ADDtk:			strcpy(str, "add [OTHER OPERATOR]"); break;
		case SUBTRACTtk:	strcpy(str, "subtractk [OTHER OPERATOR]"); break;
		case MULtk: 		strcpy(str, "multiply [OTHER OPERATOR]"); break;
		case DIVtk: 		strcpy(str, "division [OTHER OPERATOR]"); break;
		case REMAINDERtk:	strcpy(str, "remainder [OTHER OPERATOR]"); break;

		case EQUALtk: 		strcpy(str, "equal [RELATIONAL OPERATOR]"); break;
		case GREATERtk:		strcpy(str, "greater [RELATIONAL OPERATOR]"); break;
		case LESStk:		strcpy(str, "less than [RELATIONAL OPERATOR]"); break;
		case DIFFtk:		strcpy(str, "different [RELATIONAL OPERATOR]"); break;
		case GREATEREQtk:	strcpy(str, "greater or equal [RELATIONAL OPERATOR]"); break; 
		case LESSEQtk: 		strcpy(str, "less than or equal [RELATIONAL OPERATOR]"); break;


		default: strcpy(str, "UNKNOWN");
	}
	return str;
}

void printToken(Token token) {
	if (token.tokenType == EOFtk) {
		printf("***** EOFtk ***** \n\n");
		return;
	}

	char tokenTypestr[2 * MAX];
	printf("%10s \t line #%d \t %s \n", 
		token.str, token.lineNum, getTokenTypeStr(token, tokenTypestr));
}

void displaySourceFile(FILE *filePtr) {
	rewind(filePtr);
	printf("\n-----Source file starts here-----\n\n");

	char ch;
	while ((ch = fgetc(filePtr)) != EOF) {
		printf("%c", ch);
	}
	rewind(filePtr);

	printf("\n-----/Source file ends here------\n\n");
}

