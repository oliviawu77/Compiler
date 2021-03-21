/*******************************************************************************
 *
 * source: [InstructionList.cpp]
 *
 ******************************************************************************/

#include <stdlib.h>
#include <stdio.h>

#include "InstructionList.h"

namespace codegen {

InstructionList::InstructionList ()
{
	int i;

	insn = new Instruction*[MaxLen];
	num_insns = 0;

	for (i=0; i<MaxLen; i++) insn[i] = NULL;
}//end of function InstructionList

InstructionList::~InstructionList ()
{
	int i;

	delete insn;
}//end of destructor ~InstructionList()



}//end of namespace codegen



