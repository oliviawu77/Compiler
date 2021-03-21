/*******************************************************************************
 *
 * source: [codegen_arith.cpp]
 *
 ******************************************************************************/

#include <stdlib.h>
#include <stdio.h>

#include "SymbTbl.h"

#include "ParseTreeNode.h"
#include "ParseTree.h"
#include "InstructionList.h"

using namespace codegen;

#include "lexer.h"
#include "parser.h"

namespace codegen {

SymbTbl* symb_table;

int num_PT_nodes;

ParseTree* parse_tree;


}//end of namespace codegen



int
main ()
{
	FILE* fp;
	InstructionList* code;
	int num;
	symb_table = new SymbTbl;
	num_PT_nodes = 0;
	parse_tree = NULL;

	yyin = fopen ("sample.txt", "r");
	yyparse();

	parse_tree->EvalAttr_Pass0 ();
	parse_tree->EvalAttr_Pass1 ();
	code = parse_tree->Get_Code();
	parse_tree-> Dump ();

	return 0;
}//end of function main

