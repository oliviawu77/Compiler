/*******************************************************************************
 *
 * source: [Instruction.h]
 *
 ******************************************************************************/

#ifndef Instruction_h

#define Instruction_h

#include <stdio.h>



/*******************************************************************************
 *
 * list of opcode for instructions
 *
 ******************************************************************************/

#define OPC_NOP		0
#define OPC_ADD		1
#define OPC_SUB		2
#define OPC_MULT	3
#define OPC_ASSIGN_Constant	4
#define OPC_ASSIGN_Register	5




/*******************************************************************************
 *
 * data structure to represent an instruction
 *
 ******************************************************************************/

namespace codegen {

class Instruction {
	//
	// fields of an instruction
	//
	int				opcode;
	int				dest_reg;
	int				src1_reg;
	int				src0_reg;
	int				Constant;

public:
	Instruction (int opc, int dst, int src_1, int src_0);
	Instruction (int dst, int value, int is_constant);
	~Instruction () {}
	int Print (FILE* fp);
};//end of class Instruction



}//end of namespace codegen



#endif



