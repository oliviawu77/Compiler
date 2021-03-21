/*******************************************************************************
 *
 * source: [ParseTree.h]
 *
 ******************************************************************************/

#ifndef ParseTree_h

#define ParseTree_h

#include <stdio.h>

#include "ParseTreeNode.h"



namespace codegen {

class ParseTree {
	//
	// fields of a parse tree
	//
	ParseTreeNode*		root;

public:
	//
	// status flags
	//
	static const int	st_Success=0;
	static const int	st_Fail=-1;
	static const int	st_NA=-1;

	//
	// constructor and destructor
	//
	ParseTree (ParseTreeNode* r) {root=r;}
	~ParseTree () {}

	//
	// operations for code generation
	//
	int EvalAttr_Pass0 ();
	int EvalAttr_Pass1 ();

	//
	// get generated code
	//
	InstructionList* Get_Code () {return root->Get_Code();}

	//
	// functions for debugging
	//
	int Dump (FILE* fp);
	int Dump () {return Dump(stdout);}
	int Dump (int ch);
};//end of class ParseTree



}//end of namespace codegen




#endif



