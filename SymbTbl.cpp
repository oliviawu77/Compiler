/*******************************************************************************
 *
 * source: [SymbTbl.cpp]
 *
 ******************************************************************************/

#include <stdlib.h>
#include <string.h>

#include "SymbTbl.h"

namespace codegen {

SymbTbl::SymbTbl ()
{
	int i;

	id = new char*[MaxEntries];
	reg = new int[MaxEntries];
	value = new int[MaxEntries];
	num_ids = 0;
	num_regs = 0;

	for (i=0; i<MaxEntries; i++) {
		id[i] = NULL;
		reg[i] = st_NA;
		value[i] = 0;
	}
}//end of function SymbTbl

SymbTbl::~SymbTbl ()
{
	int i;

	for (i=0; i<MaxEntries; i++) {
		if (id[i]!=NULL) delete id[i];
	}//end for i

	delete id;
	delete reg;
	delete value;
}//end of function ~SymbTbl

int
SymbTbl::Find_ID (char* id_string)
{
	int i;

	for (i=0; i<num_regs; i++) {
		if (strcmp(id[i], id_string)==0) return i;
	}//end for i

	return st_NA;
}//end of function Find_ID

int
SymbTbl::AllocID_Register (char* id_string)
{
	int cur_id;

	cur_id = num_ids++;
	id[cur_id] = new char[MaxNameLen];
	memccpy (id[cur_id], id_string, 0, MaxNameLen);
	reg[cur_id] = num_regs++;

	return st_Success;
}//end of function AllocID_Register




}//end of namespace codegen



