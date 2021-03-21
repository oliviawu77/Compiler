/*******************************************************************************
 *
 * source: [ParseTreeNode.h]
 *
 ******************************************************************************/

#ifndef ParseTreeNode_h

#define ParseTreeNode_h

#include <stdio.h>

#include "Instruction.h"
#include "InstructionList.h"



/*******************************************************************************
 *
 * data structure of a parse tree node
 *
 ******************************************************************************/

namespace codegen {

class ParseTreeNode {
	//
	// specify the rule and elements
	//
	int					node_id;
	int					rule;
	ParseTreeNode**		child;
	char*				F_id;
	int					Number;

	//
	// attributes associated with the production rule
	//
	int					dest_regid;
	Instruction*		insn;
	InstructionList*	code;
	int					isConstant;

	int					src1_regid;
	int					src0_regid;
	//
	// design parameters
	//
	static const int	MaxIdLen=80;
	static const int	MaxChild=3;

	//
	// common initialization
	//
	int Init ();

	//
	// utilitfy functions
	//
	int Append_InsnList (InstructionList* dst, InstructionList* src);

	//
	// methods to evaluate attributes
	//
	int EvalAttr_Dest ();
	int EvalAttr_Instruction ();
	int EvalAttr_Code ();

public:
	//
	// status flags
	//
	static const int		st_Success=0;
	static const int		st_Fail=-1;
	static const int		st_NA=-1;

	//
	// rules
	//
	static const int	Rule_0=0;		//function-definition -> decl-specifier declarator fct-body
	static const int	Rule_1=1;		//decl-specifier -> type-specifier
	static const int	Rule_2=2;		//type-specifier -> simple-type-name
	static const int	Rule_3=3;		//simple-type-name -> INT
	static const int	Rule_4=4;		//declarator -> declarator ()
	static const int	Rule_5=5;		//declarator -> dname
	static const int	Rule_6=6;		//dname -> name
	static const int	Rule_7=7;		//name -> ID
	static const int	Rule_8=8;		//fct-body -> compound-statement
	static const int	Rule_9=9;		//compound-statement -> { statement-list }
	static const int	Rule_10=10;		//statement-list -> statement
	static const int	Rule_11=11;		//statement-list -> statement-list statement
	static const int	Rule_12=12;		//statement -> expression-statement
	static const int	Rule_13=13;		//statement -> declaration-statement
	static const int	Rule_14=14;		//statement -> jump-statement
	static const int	Rule_15=15;		//expression-statement -> expression ;
	static const int	Rule_16=16;		//expression -> assignment-expression
	static const int	Rule_17=17;		//expression -> expression, assignment-expression
	static const int	Rule_18=18;		//assignment-expression -> additive-expression
	static const int	Rule_19=19;		//assignment-expression -> assignment-expression = additive-expression
	static const int	Rule_20=20;		//additive-expression -> multiplicative-expression
	static const int	Rule_21=21;		//additive-expression -> additive-expression + multiplicative-expression
	static const int	Rule_22=22;		//multiplicative-expression -> primary-expression
	static const int	Rule_23=23;		//multiplicative-expression -> multiplicative-expression * primary-expression
	static const int	Rule_24=24;		//primary-expression -> literal
	static const int	Rule_25=25;		//primary-expression -> name
	static const int	Rule_26=26;		//literal -> NUM
	static const int	Rule_27=27;		//declaration-statement -> declaration
	static const int	Rule_28=28;		//declaration -> decl-specifier declarator-list
	static const int	Rule_29=29;		//declarator-list -> init-declarator
	static const int	Rule_30=30;		//declarator-list -> declarator-list, init-declarator
	static const int	Rule_31=31;		//init-declarator -> declarator
	static const int	Rule_32=32;		//jump-statement -> RETURN 	expression ;
	static const int	Rule_33=33;		//statement -> NL

	//
	// constructor and destructor
	//
	ParseTreeNode (int rule_id, ParseTreeNode* child_0, ParseTreeNode *child_1) {
		Init();
		rule = rule_id;
		child[0] = child_0;
		child[1] = child_1;
	}

	ParseTreeNode (int rule_id, ParseTreeNode* child_0, ParseTreeNode *child_1, ParseTreeNode *child_2) {
		Init();
		rule = rule_id;
		child[0] = child_0;
		child[1] = child_1;
		child[2] = child_2;
	}
	ParseTreeNode (char* id_string);
	ParseTreeNode (int num);
	~ParseTreeNode () {delete child;}

	//
	// methods to get attributes
	//
	int Attr_DestRegID () {return dest_regid;}
	int Attr_DestRegValue () {return Number;}
	int Attr_DestRegValueConstant () {return isConstant;}
	void setConstant () {isConstant = 1;}
	Instruction* Attr_Instruction () {return insn;}
	InstructionList* Attr_Code () {return code;}

	//
	// interface to get contents
	//
	int NodeID () {return node_id;}
	InstructionList* Get_Code () {return code;}
	ParseTreeNode* Get_Child (int index) {return child[index];}

	//
	// methods to evaluate attributes during the code generation flow
	//
	int EvalAttr_Pass0 ();
	int EvalAttr_Pass1 ();

	//
	// other methods
	//
	int PrintInstruction (FILE* fp) {return insn->Print(fp);}
	int PrintCode (FILE* fp) {return code->Print(fp);}

	//
	// debug support
	//
	int Dump (FILE* fp);
	int Dump () {return Dump(stdout);};
	int Dump (int ch);
	int Dump_SubTree (FILE* fp);
	int Dump_SubTree () {return Dump_SubTree(stdout);}
	int Dump_SubTree (int ch);
};//end of class ParseTreeNode



}//end of namespace codegen



#endif



