/*
* CS4280 Fall 2014 - P2 
* Author: Loc Nguyen
* 
* $Id: token.h,v 1.5 2014/11/12 20:05:39 lhn7c5 Exp $
* $Source: /accounts/students/l/lhn7c5/4280/P2/RCS/token.h,v $
* Last modified: 
*       by $Author: lhn7c5 $
*       on $Date: 2014/11/12 20:05:39 $
* 
* $Log: token.h,v $
* Revision 1.5  2014/11/12 20:05:39  lhn7c5
*  Parse tree with a linked-list of tokens per node.
*
* Revision 1.4  2014/11/10 04:50:58  lhn7c5
* Done P2.
*
* Revision 1.3  2014/11/08 20:03:56  lhn7c5
* Done parser.
*
* Revision 1.2  2014/11/07 07:37:16  lhn7c5
* Done scanner.
*
* Revision 1.1  2014/11/06 21:54:38  lhn7c5
* Initial revision
*
*/

#ifndef TOKEN_H 
#define TOKEN_H 

#define MAX 9 // max length of each word string, not including '\0'
#define LIMIT 200 // max number of word strings in an input file

extern int lineNum;

typedef enum {
	// Identifier: begin with a letter, and continue with any number
	// of letters. No ID is longer than MAX
	IDtk, 

	// Keywords (start finish then if repeat var int float do 
	// read print void return dummy program) 
	STARTtk, FINISHtk, THENtk, IFtk, REPEATtk, VARtk, INTtk, FLOATtk, 
	DOtk, READtk, PRINTtk, VOIDtk, RETURNtk, DUMMYtk, PROGRAMtk, 

	// Number: sequence of decimal digits, no sign, no longer than MAX digits
	NUMBERtk, 

	// Relational Operators (==  <  >  =!=    =>  =<)
	EQUALtk, GREATERtk, LESStk, DIFFtk, GREATEREQtk, LESSEQtk, 

	// Other operators (= :  +  -  *  / %)
	ASSIGNtk, COLONtk, ADDtk, SUBTRACTtk, MULtk, DIVtk, REMAINDERtk,

	// Delimiters (. (  ) , { } ; [ ])
	DOTtk, LEFTPAtk, RIGHTPAtk, COMMAtk, LEFTBRACEtk, RIGHTBRACEtk, 
	SEMICOLONtk, LEFTBRACKETtk, RIGHTBRACKETtk, 

	NAtk, // N/A token 
	EOFtk

} TokenType;


struct tokenTag {
	char str[MAX];
	TokenType tokenType;
	int lineNum;

	struct tokenTag *next; // linked-list, used for parse tree
};
typedef struct tokenTag Token;

extern int numToken;
extern Token *tokens; // list of all tokens (array of numToken) 


#endif
