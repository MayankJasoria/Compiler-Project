from pyvis.network import Network

net = Network(height="70%", width="100%", directed=True, layout=True)

net.add_node("h1", hidden=True, physics=False)
net.add_node("h2", hidden=True, physics=False)
net.add_node("AST_NODE_PROGRAM_0x937640", title=r"AST_NODE_PROGRAM_0x937640 {<br \> &emsp;No information here!<br \>}")

net.add_edge("AST_NODE_PROGRAM_0x937640", "h1", hidden=True, physics=False)
net.add_edge("AST_NODE_PROGRAM_0x937640", "h2", hidden=True, physics=False)

net.add_node("AST_NODE_MODULEDECLARATION_0x9376b0", title=r"AST_NODE_MODULEDECLARATION_0x9376b0 {<br \> &emsp;No information here!<br \>}")
net.add_edge("AST_NODE_PROGRAM_0x937640", "AST_NODE_MODULEDECLARATION_0x9376b0")
net.add_node("AST_NODE_MODULELIST_0x937790", title=r"AST_NODE_MODULELIST_0x937790 {<br \> &emsp;No information here!<br \>}")
net.add_edge("AST_NODE_PROGRAM_0x937640", "AST_NODE_MODULELIST_0x937790")
net.add_node("AST_NODE_MODULELIST_0x93b010", title=r"AST_NODE_MODULELIST_0x93b010 {<br \> &emsp;No information here!<br \>}")
net.add_edge("AST_NODE_PROGRAM_0x937640", "AST_NODE_MODULELIST_0x93b010")
net.add_node("AST_NODE_MODULELIST_0x93cea0", title=r"AST_NODE_MODULELIST_0x93cea0 {<br \> &emsp;No information here!<br \>}")
net.add_edge("AST_NODE_PROGRAM_0x937640", "AST_NODE_MODULELIST_0x93cea0")
net.add_node("AST_NODE_MODULEDECLARATION_0x9376b0", title=r"AST_NODE_MODULEDECLARATION_0x9376b0 {<br \> &emsp;No information here!<br \>}")
net.add_node("AST_NODE_LEAF_0x937720", title=r"AST_NODE_LEAF_0x937720 {<br \> &emsp;type: AST_LEAF_ID<br \>&emsp;lex: NULL<br \>}")
net.add_edge("AST_NODE_MODULEDECLARATION_0x9376b0", "AST_NODE_LEAF_0x937720")
net.add_node("AST_NODE_MODULELIST_0x937790", title=r"AST_NODE_MODULELIST_0x937790 {<br \> &emsp;No information here!<br \>}")
net.add_node("AST_NODE_MODULE_0x937800", title=r"AST_NODE_MODULE_0x937800 {<br \> &emsp;No information here!<br \>}")
net.add_edge("AST_NODE_MODULELIST_0x937790", "AST_NODE_MODULE_0x937800")
net.add_node("AST_NODE_MODULELIST_0x93b010", title=r"AST_NODE_MODULELIST_0x93b010 {<br \> &emsp;No information here!<br \>}")
net.add_node("AST_NODE_STATEMENT_0x93b0c0", title=r"AST_NODE_STATEMENT_0x93b0c0 {<br \> &emsp;No information here!<br \>}")
net.add_edge("AST_NODE_MODULELIST_0x93b010", "AST_NODE_STATEMENT_0x93b0c0")
net.add_node("AST_NODE_MODULELIST_0x93cea0", title=r"AST_NODE_MODULELIST_0x93cea0 {<br \> &emsp;No information here!<br \>}")
net.add_node("AST_NODE_MODULE_0x93cf50", title=r"AST_NODE_MODULE_0x93cf50 {<br \> &emsp;No information here!<br \>}")
net.add_edge("AST_NODE_MODULELIST_0x93cea0", "AST_NODE_MODULE_0x93cf50")
net.add_node("AST_NODE_LEAF_0x937720", title=r"AST_NODE_LEAF_0x937720 {<br \> &emsp;type: AST_LEAF_ID<br \>&emsp;lex: NULL<br \>}")
net.add_node("AST_NODE_MODULE_0x937800", title=r"AST_NODE_MODULE_0x937800 {<br \> &emsp;No information here!<br \>}")
net.add_node("AST_NODE_LEAF_0x937870", title=r"AST_NODE_LEAF_0x937870 {<br \> &emsp;type: AST_LEAF_ID<br \>&emsp;lex: NULL<br \>}")
net.add_edge("AST_NODE_MODULE_0x937800", "AST_NODE_LEAF_0x937870")
net.add_node("AST_NODE_INPUTLIST_0x9378e0", title=r"AST_NODE_INPUTLIST_0x9378e0 {<br \> &emsp;No information here!<br \>}")
net.add_edge("AST_NODE_MODULE_0x937800", "AST_NODE_INPUTLIST_0x9378e0")
net.add_node("AST_NODE_OUTPUTLIST_0x937eb0", title=r"AST_NODE_OUTPUTLIST_0x937eb0 {<br \> &emsp;No information here!<br \>}")
net.add_edge("AST_NODE_MODULE_0x937800", "AST_NODE_OUTPUTLIST_0x937eb0")
net.add_node("AST_NODE_STATEMENT_0x9380e0", title=r"AST_NODE_STATEMENT_0x9380e0 {<br \> &emsp;No information here!<br \>}")
net.add_edge("AST_NODE_MODULE_0x937800", "AST_NODE_STATEMENT_0x9380e0")
net.add_node("AST_NODE_STATEMENT_0x93b0c0", title=r"AST_NODE_STATEMENT_0x93b0c0 {<br \> &emsp;No information here!<br \>}")
net.add_node("AST_NODE_DECLARESTMT_0x93b170", title=r"AST_NODE_DECLARESTMT_0x93b170 {<br \> &emsp;No information here!<br \>}")
net.add_edge("AST_NODE_STATEMENT_0x93b0c0", "AST_NODE_DECLARESTMT_0x93b170")
net.add_node("AST_NODE_STATEMENT_0x93b5c0", title=r"AST_NODE_STATEMENT_0x93b5c0 {<br \> &emsp;No information here!<br \>}")
net.add_edge("AST_NODE_STATEMENT_0x93b0c0", "AST_NODE_STATEMENT_0x93b5c0")
net.add_node("AST_NODE_MODULE_0x93cf50", title=r"AST_NODE_MODULE_0x93cf50 {<br \> &emsp;No information here!<br \>}")
net.add_node("AST_NODE_LEAF_0x93d020", title=r"AST_NODE_LEAF_0x93d020 {<br \> &emsp;type: AST_LEAF_ID<br \>&emsp;lex: NULL<br \>}")
net.add_edge("AST_NODE_MODULE_0x93cf50", "AST_NODE_LEAF_0x93d020")
net.add_node("AST_NODE_INPUTLIST_0x93d0d0", title=r"AST_NODE_INPUTLIST_0x93d0d0 {<br \> &emsp;No information here!<br \>}")
net.add_edge("AST_NODE_MODULE_0x93cf50", "AST_NODE_INPUTLIST_0x93d0d0")
net.add_node("AST_NODE_STATEMENT_0x93d6a0", title=r"AST_NODE_STATEMENT_0x93d6a0 {<br \> &emsp;No information here!<br \>}")
net.add_edge("AST_NODE_MODULE_0x93cf50", "AST_NODE_STATEMENT_0x93d6a0")
net.add_node("AST_NODE_LEAF_0x937870", title=r"AST_NODE_LEAF_0x937870 {<br \> &emsp;type: AST_LEAF_ID<br \>&emsp;lex: NULL<br \>}")
net.add_node("AST_NODE_INPUTLIST_0x9378e0", title=r"AST_NODE_INPUTLIST_0x9378e0 {<br \> &emsp;No information here!<br \>}")
net.add_node("AST_NODE_LEAF_0x9379a0", title=r"AST_NODE_LEAF_0x9379a0 {<br \> &emsp;type: AST_LEAF_ID<br \>&emsp;lex: NULL<br \>}")
net.add_edge("AST_NODE_INPUTLIST_0x9378e0", "AST_NODE_LEAF_0x9379a0")
net.add_node("AST_NODE_ARRAY_0x937a50", title=r"AST_NODE_ARRAY_0x937a50 {<br \> &emsp;No information here!<br \>}")
net.add_edge("AST_NODE_INPUTLIST_0x9378e0", "AST_NODE_ARRAY_0x937a50")
net.add_node("AST_NODE_INPUTLIST_0x937c80", title=r"AST_NODE_INPUTLIST_0x937c80 {<br \> &emsp;No information here!<br \>}")
net.add_edge("AST_NODE_INPUTLIST_0x9378e0", "AST_NODE_INPUTLIST_0x937c80")
net.add_node("AST_NODE_OUTPUTLIST_0x937eb0", title=r"AST_NODE_OUTPUTLIST_0x937eb0 {<br \> &emsp;No information here!<br \>}")
net.add_node("AST_NODE_LEAF_0x937f70", title=r"AST_NODE_LEAF_0x937f70 {<br \> &emsp;type: AST_LEAF_ID<br \>&emsp;lex: NULL<br \>}")
net.add_edge("AST_NODE_OUTPUTLIST_0x937eb0", "AST_NODE_LEAF_0x937f70")
