/*
* CS4280 Fall 2014 - P2 
* Author: Loc Nguyen
* 
* $Id: scanner.h,v 1.3 2014/11/10 04:50:40 lhn7c5 Exp $
* $Source: /accounts/students/l/lhn7c5/4280/P2/RCS/scanner.h,v $
* Last modified: 
*       by $Author: lhn7c5 $
*       on $Date: 2014/11/10 04:50:40 $
* 
* $Log: scanner.h,v $
* Revision 1.3  2014/11/10 04:50:40  lhn7c5
* Done P2.
*
* Revision 1.2  2014/11/08 20:05:28  lhn7c5
* Done parser.
*
* Revision 1.1  2014/11/07 07:36:15  lhn7c5
* Initial revision
*
*/

#ifndef SCANNER_H 
#define SCANNER_H 

int isExAcceptableChar(char);

int isDelimiter(char);
int isOtherOperators(char);
int isStartRelationalOperator(char);
int isKeyword(char *);

Token scanner(FILE *);

void printToken(Token);

TokenType getTokenTypeOfKeyword(char *);
TokenType getTokenTypeOfDelimiter(char);
TokenType getTokenTypeOfOtherOperator(char);

void displaySourceFile(FILE *);












#endif


