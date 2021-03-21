/*******************************************************************************
 *
 * source: [codegen.h]
 *
 ******************************************************************************/

#ifndef codegen_h

#define codegen_h

#include "ParseTree.h"
#include "SymbTbl.h"

namespace codegen {

extern SymbTbl* symb_table;

extern int num_PT_nodes;

extern ParseTree* parse_tree;

}//end of namespace codegen

#endif



