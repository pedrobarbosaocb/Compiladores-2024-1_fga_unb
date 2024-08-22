/*
* CS4280 Fall 2014 - P2 
* Author: Loc Nguyen
* 
* $Id: symdef.h,v 1.2 2014/11/07 07:38:46 lhn7c5 Exp $
* $Source: /accounts/students/l/lhn7c5/4280/P2/RCS/symdef.h,v $
* Last modified: 
*       by $Author: lhn7c5 $
*       on $Date: 2014/11/07 07:38:46 $
* 
* $Log: symdef.h,v $
* Revision 1.2  2014/11/07 07:38:46  lhn7c5
* Done scanner.
*
* Revision 1.1  2014/11/07 06:36:51  lhn7c5
* Initial revision
*
*/

#ifndef SYMDEF_H 
#define SYMDEF_H 

char *keywords[15] = {"start", "finish", "then", "if", "repeat", "var", 
	"int", "float", "do",
	"read", "print", "void", "return", "dummy", "program"};	

char *relationalOperators[] = {"==", "<", ">", "=!=", "=>", "=<"};

// char *otherOperators[] = {":", "+", "-", "*", "/", "%"};
char otherOperators[6] = {':', '+', '-', '*', '/', '%'};

// char *delimiters[9] = {".", "(", ")", ",", "{", "}", ";", "[", "]"};
char delimiters[9] = {'.', '(', ')', ',', '{', '}', ';', '[', ']'};

char word[MAX];
int wi = 0; // index of word string

char numStr[MAX];
int ni = 0;





#endif


