/*******************************************************************************
 *
 * source: [ParseTree.cpp]
 *
 ******************************************************************************/

#include <stdlib.h>
#include <stdio.h>

#include "ParseTreeNode.h"
#include "ParseTree.h"

namespace codegen {

int
ParseTree::EvalAttr_Pass0 ()
{
	root->EvalAttr_Pass0();
	return st_Success;
}//end of function EvalAttr_Pass0

int
ParseTree::EvalAttr_Pass1 ()
{
	root->EvalAttr_Pass1 ();
	return st_Success;
}//end of function EvalAttr_Pass1

int
ParseTree::Dump (FILE* fp)
{
	return root->Dump_SubTree(fp);
}//end of function Dump

int
ParseTree::Dump (int ch)
{
	char file[80];
	FILE* fp;

	sprintf(file, "debug_%02d.out", ch);
	fp = fopen(file, "w");
	Dump(fp);
	fclose(fp);

	return 0;
}//end of function Dump(ch)



}//end of namespace codegen


