/*******************************************************************************
 *
 * source: [SymbTbl.h]
 *
 ******************************************************************************/

#ifndef SymbTbl_h

#define SymbTbl_h



/*******************************************************************************
 *
 * data structure of a symbol table
 *
 ******************************************************************************/

namespace codegen {

class SymbTbl {
	//
	// to store the array of symbols with its register ID
	//
	char**		id;
	int*		reg;
	int*		value;
	int			num_ids;
	int			num_regs;

	//
	// design parameters
	//
	static const int	MaxNameLen=80;
	static const int	MaxEntries=200;

	//
	// internal utility functions
	//
	int Find_ID (char* id_string);
	int AllocID_Register (char* id_string);

public:
	static const int	st_NA = -1;
	static const int	st_Success = 0;
	static const int	st_Fail=-1;

	SymbTbl ();
	~SymbTbl ();
	bool HasID (char* id_string) {
		return (Find_ID(id_string)!=st_NA)? true: false;
	}

	int NewID (char* id_string) {
		if (HasID(id_string))
			return st_Success;
		else
			return AllocID_Register(id_string);
	}

	int RegID (char* id_string) {
		int p = Find_ID(id_string);
		return (p!=st_NA)? reg[p]: st_NA;
	}

	int Alloc_NewReg () {
		return num_regs++;
	}
};//end of class SymbTbl



}//end of namespace codegen


#endif