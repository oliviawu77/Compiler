/*******************************************************************************
 *
 * source: [Instruction.cpp]
 *
 ******************************************************************************/

#include <stdlib.h>
#include <stdio.h>

#include "Instruction.h"

namespace codegen {

Instruction::Instruction (int opc, int dst, int src_1, int src_0)
{
	opcode = opc;
	dest_reg = dst;
	src1_reg = src_1;
	src0_reg = src_0;
}//end of constructor Instruction

Instruction::Instruction (int dst, int value, int is_constant)
{
	dest_reg = dst;
	if (is_constant){
		opcode = OPC_ASSIGN_Constant;
		Constant = value;
	}
	else if (! is_constant){
		opcode =  OPC_ASSIGN_Register;
		src1_reg = value;
	}
}

int
Instruction::Print (FILE* fp)
{
	switch (opcode) {
		case OPC_NOP:
			fprintf(fp, "nop\n");
			break ;

		case OPC_ADD:
			fprintf(fp, "add r%d, r%d, r%d\n", dest_reg, src1_reg, src0_reg);
			break ;

		case OPC_SUB:
			fprintf(fp, "sub r%d, r%d, r%d\n", dest_reg, src1_reg, src0_reg);
			break ;

		case OPC_MULT:
			fprintf(fp, "mul r%d, r%d, r%d\n", dest_reg, src1_reg, src0_reg);
			break ;

		case OPC_ASSIGN_Constant:
			fprintf(fp, "add r%d, %d, 0\n", dest_reg, Constant);
			break ;

		case OPC_ASSIGN_Register:
			fprintf(fp, "add r%d, r%d, 0\n", dest_reg, src1_reg);
			break ;	

		default:
			fprintf(fp, "Invalid instruction\n");
			return -1;
	}//end switch(opcode)
}//end of function Print



}//end of namespace codegen

