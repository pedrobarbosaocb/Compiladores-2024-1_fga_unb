/*
* CS4280 Fall 2014 - P2 
* Author: Loc Nguyen
* 
* $Id: parser.h,v 1.4 2014/11/12 20:05:26 lhn7c5 Exp $
* $Source: /accounts/students/l/lhn7c5/4280/P2/RCS/parser.h,v $
* Last modified: 
*       by $Author: lhn7c5 $
*       on $Date: 2014/11/12 20:05:26 $
* 
* $Log: parser.h,v $
* Revision 1.4  2014/11/12 20:05:26  lhn7c5
*  Parse tree with a linked-list of tokens per node.
*
* Revision 1.3  2014/11/10 04:50:20  lhn7c5
* Done P2.
*
* Revision 1.2  2014/11/09 18:32:47  lhn7c5
* Done parser and parse tree.
*
* Revision 1.1  2014/11/08 20:05:42  lhn7c5
* Initial revision
*
*/

#ifndef PARSER_H 
#define PARSER_H 

void parser(FILE *);

// Represent non-terminal token nodes
typedef enum {
	programNode, blockNode, varNode, mvarsNode, exprNode, xNode, 
	tNode, yNode, fNode, rNode, statsNode, mStatNode, statNode, 
	inNode, outNode, ifNode, loopNode, assignNode, roNode
} NodeType;

/*------- TREE -------*/
struct nodeTag {
	NodeType nodeType;
	Token *tokenPtr; // linked-list of tokens of this node 
	struct nodeTag *child1; // usually only up to 3 children needed 
	struct nodeTag *child2;
	struct nodeTag *child3;
	struct nodeTag *child4; // but for <if> and <loop>, 4 children needed
};
typedef struct nodeTag Node;


#endif
