/*******************************************************************************
 *
 * source: [ParseTreeNode.cpp]
 *
 ******************************************************************************/

#include <stdlib.h>
#include <string.h>

#include "codegen.h"
#include "Instruction.h"
#include "InstructionList.h"

#include "ParseTreeNode.h"

namespace codegen {

int
ParseTreeNode::Init ()
{
	int i;

	node_id = num_PT_nodes++;
	rule = st_NA;

	child = new ParseTreeNode*[MaxChild];
	for (i=0; i<MaxChild; i++)
		child[i] = NULL;

	F_id = NULL;

	dest_regid = st_NA;
	insn = NULL;
	code = NULL;
	isConstant = 0;

	return st_Success;
}//end of function Init

ParseTreeNode::ParseTreeNode (char* id_string)
{
	Init();
	F_id = new char[MaxIdLen];
	memccpy(F_id, id_string, 0, MaxIdLen);

	rule = Rule_7;
}//end of constructor ParseTreeNode

ParseTreeNode::ParseTreeNode (int num)
{
	Init();
	Number = num;

	rule = Rule_26;
}//end of constructor ParseTreeNode

int
ParseTreeNode::Append_InsnList (InstructionList* dst, InstructionList* src)
{
	int num_insn;
	int i;

	num_insn = src->NumInstructions();

	for (i=0; i<num_insn; i++)
		dst->Append(src->Get_Instruction(i));

	return st_Success;
}//end of function Append_InsnList

int
ParseTreeNode::EvalAttr_Dest ()
{
	switch (rule) {

		case Rule_0:		//function-definition -> decl-specifier declarator fct-body
			break;
		
		case Rule_1:		//decl-specifier -> type-specifier
			break;

		case Rule_2:		//type-specifier -> simple-type-name
			break;

		case Rule_3:		//simple-type-name -> INT
			break;

		case Rule_4:		//declarator -> declarator ()
			dest_regid = child[0]->Attr_DestRegID();
			break;
		
		case Rule_5:		//declarator -> dname
			dest_regid = child[0]->Attr_DestRegID();
			break;
		
		case Rule_6:		//dname -> name
			dest_regid = child[0]->Attr_DestRegID();
			break;
		
		case Rule_7:		//name -> ID
			if (symb_table->HasID(F_id))
				dest_regid = symb_table->RegID(F_id);
			else {
				symb_table->NewID(F_id);
				dest_regid = symb_table->RegID(F_id);
			}		
			break;
		
		case Rule_8:		//fct-body -> compound-statement
			break;
		
		case Rule_9:		//compound-statement -> { statement-list }
			break;
	
		case Rule_10:		//statement-list -> statement
			break;
		
		case Rule_11:		//statement-list -> statement-list statement
			break;
		
		case Rule_12:		//statement -> expression-statement
			break;
		
		case Rule_13:		//statement -> declaration-statement
			break;
		
		case Rule_14:		//statement -> jump-statement
			break;
		
		case Rule_15:		//expression-statement -> expression ;
			break;
		
		case Rule_16:		//expression -> assignment-expression
			break;
		
		case Rule_17:		//expression -> expression, assignment-expression
			break;

		case Rule_18:		//assignment-expression -> additive-expression
			break;
		
		case Rule_19:		//assignment-expression -> assignment-expression = additive-expression
			dest_regid = child[0]->Attr_DestRegID();
			break;
		
		case Rule_20:		//additive-expression -> multiplicative-expression		
			dest_regid = child[0]->Attr_DestRegID();
			Number = child[0]->Attr_DestRegValue();
			isConstant = child[0]->Attr_DestRegValueConstant();
			break;
		
		case Rule_21:		//additive-expression -> additive-expression + multiplicative-expression			
			dest_regid = symb_table->Alloc_NewReg();
			break;
		
		case Rule_22:		//multiplicative-expression -> primary-expression
			dest_regid = child[0]->Attr_DestRegID();
			Number = child[0]->Attr_DestRegValue();
			isConstant = child[0]->Attr_DestRegValueConstant();
			break;
		
		case Rule_23:		//multiplicative-expression -> multiplicative-expression * primary-expression
			dest_regid = symb_table->Alloc_NewReg();
			break;
		
		case Rule_24:		//primary-expression -> literal
			Number = child[0]->Attr_DestRegValue();
			isConstant = child[0]->Attr_DestRegValueConstant();
			break;
		
		case Rule_25:		//primary-expression -> name
			dest_regid = child[0]->Attr_DestRegID();
			break;

		case Rule_26:		//literal -> NUM
			setConstant();
			break;
		
		case Rule_27:		//declaration-statement -> declaration
			break;
		
		case Rule_28:		//declaration -> decl-specifier declarator-list
			break;
		
		case Rule_29:		//declarator-list -> init-declarator
			dest_regid = child[0]->Attr_DestRegID();
			break;
		
		case Rule_30:		//declarator-list -> declarator-list, init-declarator
			break;
		
		case Rule_31:		//init-declarator -> declarator
			dest_regid = child[0]->Attr_DestRegID();
			break;

		case Rule_32:		//jump-statement -> RETURN 	expression ;
			break;

		case Rule_33:		//statement -> NL;
			break;

		default:
			dest_regid = st_NA;
	}//end switch(rule)

	return st_Success;
}//end of function EvalAttr_Dest

int
ParseTreeNode::EvalAttr_Instruction ()
{
	switch (rule) {
		
		case Rule_0:		//function-definition -> decl-specifier declarator fct-body
			insn = NULL;
			break;
		
		case Rule_1:		//decl-specifier -> type-specifier
			insn = NULL;
			break;

		case Rule_2:		//type-specifier -> simple-type-name
			insn = NULL;
			break;

		case Rule_3:		//simple-type-name -> INT
			insn = NULL;
			break;

		case Rule_4:		//declarator -> declarator ()
			insn = NULL;
			break;
		
		case Rule_5:		//declarator -> dname
			insn = NULL;
			break;
		
		case Rule_6:		//dname -> name
			insn = NULL;
			break;
		
		case Rule_7:		//name -> ID
			insn = NULL;
			break;
		
		case Rule_8:		//fct-body -> compound-statement
			insn = NULL;
			break;
		
		case Rule_9:		//compound-statement -> { statement-list }
			insn = NULL;
			break;
		
		case Rule_10:		//statement-list -> statement
			insn = NULL;
			break;
		
		case Rule_11:		//statement-list -> statement-list statement
			insn = NULL;
			break;
		
		case Rule_12:		//statement -> expression-statement
			insn = NULL;
			break;
		
		case Rule_13:		//statement -> declaration-statement
			insn = NULL;
			break;
		
		case Rule_14:		//statement -> jump-statement
			insn = NULL;
			break;
		
		case Rule_15:		//expression-statement -> expression ;
			insn = NULL;
			break;
		
		case Rule_16:		//expression -> assignment-expression
			insn = NULL;
			break;
		
		case Rule_17:		//expression -> expression, assignment-expression
			insn = NULL;
			break;

		case Rule_18:		//assignment-expression -> additive-expression
			insn = NULL;
			break;
		
		case Rule_19:		//assignment-expression -> assignment-expression = additive-expression
			if (child[1]->Attr_DestRegValueConstant() == 1){
				insn = new Instruction(child[0]->child[0]->Attr_DestRegID(),child[1]->Attr_DestRegValue(),1);
			}
			else{
				insn = new Instruction(child[0]->child[0]->Attr_DestRegID(),child[1]->Attr_DestRegID(),0);				
			}
			break;
		
		case Rule_20:		//additive-expression -> multiplicative-expression
			insn = NULL;
			break;
		
		case Rule_21:		//additive-expression -> additive-expression + multiplicative-expression
			insn = new Instruction(OPC_ADD, dest_regid,
				child[0]->Attr_DestRegID(), child[1]->Attr_DestRegID());
			break;
		
		case Rule_22:		//multiplicative-expression -> primary-expression
			insn = NULL;
			break;
		
		case Rule_23:		//multiplicative-expression -> multiplicative-expression * primary-expression
			insn = new Instruction(OPC_MULT, dest_regid,
				child[0]->Attr_DestRegID(), child[1]->Attr_DestRegID());
			break;
		
		case Rule_24:		//primary-expression -> literal
			insn = NULL;
			break;
		
		case Rule_25:		//primary-expression -> name
			insn = NULL;
			break;

		case Rule_26:		//literal -> NUM
			insn = NULL;
			break;
		
		case Rule_27:		//declaration-statement -> declaration
			insn = NULL;
			break;
		
		case Rule_28:		//declaration -> decl-specifier declarator-list
			insn = NULL;
			break;
		
		case Rule_29:		//declarator-list -> init-declarator
			insn = NULL;
			break;
		
		case Rule_30:		//declarator-list -> declarator-list, init-declarator
			insn = NULL;
			break;
		
		case Rule_31:		//init-declarator -> declarator
			insn = NULL;
			break;

		case Rule_32:		//jump-statement -> RETURN 	expression ;
			insn = NULL;
			break;

		case Rule_33:		//statement -> NL;
			insn = NULL;
			break;			
		default:
			insn = NULL;
	}//end switch(rule)

	return st_Success;
}//end of function EvalAttr_Instruction

int
ParseTreeNode::EvalAttr_Code ()
{
	code = new InstructionList;

	switch (rule) {

		case Rule_0:		//function-definition -> decl-specifier declarator fct-body
			break;
		
		case Rule_1:		//decl-specifier -> type-specifier
			Append_InsnList(code, child[0]->Attr_Code());	
			break;

		case Rule_2:		//type-specifier -> simple-type-name
			Append_InsnList(code, child[0]->Attr_Code());	
			break;

		case Rule_3:		//simple-type-name -> INT
			break;

		case Rule_4:		//declarator -> declarator ()
			Append_InsnList(code, child[0]->Attr_Code());	
			break;
		
		case Rule_5:		//declarator -> dname
			Append_InsnList(code, child[0]->Attr_Code());	
			break;
		
		case Rule_6:		//dname -> name
			Append_InsnList(code, child[0]->Attr_Code());			
			break;
		
		case Rule_7:		//name -> ID		
			break;
		
		case Rule_8:		//fct-body -> compound-statement
			break;
		
		case Rule_9:		//compound-statement -> { statement-list }
			break;

		case Rule_10:		//statement-list -> statement
			break;
		
		case Rule_11:		//statement-list -> statement-list statement
			break;
		
		case Rule_12:		//statement -> expression-statement
			break;
		
		case Rule_13:		//statement -> declaration-statement
			break;
		
		case Rule_14:		//statement -> jump-statement
			break;
		
		case Rule_15:		//expression-statement -> expression ;
			break;
		
		case Rule_16:		//expression -> assignment-expression
			Append_InsnList(code, child[0]->Attr_Code());	
			break;
		
		case Rule_17:		//expression -> expression, assignment-expression
			Append_InsnList(code, child[0]->Attr_Code());	
			break;

		case Rule_18:		//assignment-expression -> additive-expression
			Append_InsnList(code, child[0]->Attr_Code());	
			break;
		
		case Rule_19:		//assignment-expression -> assignment-expression = additive-expression
			Append_InsnList(code, child[0]->Attr_Code());
			Append_InsnList(code, child[1]->Attr_Code());
			code->Append(insn);			
			break;
		
		case Rule_20:		//additive-expression -> multiplicative-expression
			Append_InsnList(code, child[0]->Attr_Code());		
			break;
		
		case Rule_21:		//additive-expression -> additive-expression + multiplicative-expression
			Append_InsnList(code, child[0]->Attr_Code());
			Append_InsnList(code, child[1]->Attr_Code());
			code->Append(insn);			
			break;
		
		case Rule_22:		//multiplicative-expression -> primary-expression
			Append_InsnList(code, child[0]->Attr_Code());			
			break;
		
		case Rule_23:		//multiplicative-expression -> multiplicative-expression * primary-expression
			Append_InsnList(code, child[0]->Attr_Code());
			Append_InsnList(code, child[1]->Attr_Code());
			code->Append(insn);			
			break;
		
		case Rule_24:		//primary-expression -> literal
			break;
		
		case Rule_25:		//primary-expression -> name
			break;

		case Rule_26:		//literal -> NUM
			break;
		
		case Rule_27:		//declaration-statement -> declaration
			break;
		
		case Rule_28:		//declaration -> decl-specifier declarator-list
			break;
		
		case Rule_29:		//declarator-list -> init-declarator
			Append_InsnList(code, child[0]->Attr_Code());
			break;
		
		case Rule_30:		//declarator-list -> declarator-list, init-declarator
			Append_InsnList(code, child[0]->Attr_Code());
			Append_InsnList(code, child[1]->Attr_Code());
			break;
		
		case Rule_31:		//init-declarator -> declarator
			Append_InsnList(code, child[0]->Attr_Code());
			break;

		case Rule_32:		//jump-statement -> RETURN 	expression ;
			Append_InsnList(code, child[0]->Attr_Code());	
			break;

		case Rule_33:		//statement -> NL;
			break;
		default:
			break;
	}//end switch(rule)

	return st_Success;
}//end of function EvalAttr_Code

int
ParseTreeNode::EvalAttr_Pass0 ()
{
	int i;

	for (i=0; i<MaxChild; i++) {
		if (child[i]!=NULL)
			child[i]->EvalAttr_Pass0();
	}//end for i

	EvalAttr_Dest();
	EvalAttr_Instruction();

	return st_Success;
}//end of function EvalAttr_Pass0

int
ParseTreeNode::EvalAttr_Pass1 ()
{
	int i;

	for (i=0; i<MaxChild; i++) {
		if (child[i]!=NULL)
			child[i]->EvalAttr_Pass1();
	}//end for i

	EvalAttr_Code();
}//end of function EvalAttr_Pass1

int
ParseTreeNode::Dump (FILE* fp)
{
	/*
	int i;
	
	fprintf(fp, "========== Node %d =============\n", node_id);
	fprintf(fp, "rule: %d\n", rule);
	for (i=0; i<MaxChild; i++) {
		if (child[i]==NULL) continue;
		fprintf(fp, "child[%d]: %d\n", i, child[i]->NodeID());
	}
	if (F_id!=NULL)
		fprintf(fp, "F_id: %s\n", F_id);
	if (Number!=0)
		fprintf(fp, "Value: %d\n", Number);
	if (dest_regid != -1)
		fprintf(fp, "dest_regid: %d\n", dest_regid);
	*/
	if (insn!=NULL)
	 	insn->Print(fp);

	return st_Success;
}//end of function Dump

int
ParseTreeNode::Dump (int ch)
{
	FILE* fp;
	char file [80];

	sprintf(file, "debug_%02d.out", ch);
	fp = fopen(file, "w");
	Dump(fp);
	fclose(fp);

	return 0;
}//end of function Dump(ch)

int
ParseTreeNode::Dump_SubTree (FILE* fp)
{
	int i;

	for (i=0; i<MaxChild; i++) {
		if (child[i]==NULL) continue;
		child[i]->Dump_SubTree(fp);
	}

	Dump(fp);

	return st_Success;
}//end of function Dump_SubTree

int
ParseTreeNode::Dump_SubTree (int ch)
{
	FILE* fp;
	char file [80];

	sprintf(file, "debug_%02d.out", ch);
	fp = fopen(file, "w");
	Dump_SubTree(fp);
	fclose(fp);

	return 0;
}//end of function Dump_SubTree(ch)



}//end of namespace codegen

