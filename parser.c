
#include "parserDef.h"

void insertElement (int idx, char * str, typeOfSymbol t, nonterminal e) {
	symbol s;
	s.NT = e;
	HT[idx].sym = s;
	strcpy(HT[idx].str, str);
	HT[idx].tag = t;
}

void populateHashTable() {

	char * nonterminals[] = { 
		"program",
		"moduledeclarations",
		"moduledeclaration",
		"othermodules",
		"drivermodule",
		"module",
		"ret",
		"input_plist",
		"input_plistnew",
		"output_plist",
		"output_plistnew",
		"type",
		"datatype",
		"moduledef",
		"statements",
		"statement",
		"iostmt",
		"whichid",
		"index",
		"simplestmt",
		"assignmentstmt",
		"modulereusestmt",
		"optional",
		"idlist",
		"idlistnew",
		"expression",
		"arithorboolexpr",
		"arithorboolexprnew",
		"relopexpr",
		"relopexprnew",
		"arithmeticexpr",	
		"arithmeticexprnew",
		"term",
		"termnew",
		"factor",
		"var",
		"pm",
		"md",
		"logicalop",
		"elationalop",
		"declarestmt",
		"condionalstmt",
		"casestmts",
		"casestmtsnew",
		"value",
		"default",
		"iterativestmt",
		"range"
	}
	int i;
	for(int i = 0; i < 48; i++) {
		int idx = hash(nonterminals[i]);
		insertElement(id, nonterminals[i], NT, i);
	}

	
}



