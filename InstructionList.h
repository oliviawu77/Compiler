/*******************************************************************************
 *
 * source: [InstructionList.h]
 *
 ******************************************************************************/

#ifndef InstructionList_h

#define InstructionList_h

#include <stdio.h>

#include "Instruction.h"



/*******************************************************************************
 *
 * data structure of an instruction list
 *
 ******************************************************************************/

namespace codegen {

class InstructionList {
	//
	// the data structure
	//
	Instruction**	insn;
	int				num_insns;

	//
	// design parameters
	//
	static const int	MaxLen=200;

public:
	InstructionList ();
	~InstructionList ();

	int Append (Instruction* i) {
		insn[num_insns++] = i;
		return 0;
	}
	int Print (FILE* fp) {
		int i;

		for (i=0; i<num_insns; i++)
			insn[i]->Print(fp);

		return 0;
	}

	int NumInstructions () {return num_insns;}

	Instruction* Get_Instruction (int index) {return insn[index];}
};//end of class InstructionList



}//end of namespace codegen



#endif



