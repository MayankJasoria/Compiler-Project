import gdb
import re

# use one of these depending on python version
import sys
#reload(sys)
#sys.setdefaultencoding('utf8')

if sys.version_info[0] < 3:
	# python 2
	import Queue
else:
	#python 3
	import queue as Queue	

import os

class SimpleCommand(gdb.Command):

	def __init__(self):
		# This registers our class as "simple_command"
		super(SimpleCommand, self).__init__("ast", gdb.COMMAND_DATA)

		# use one of these lines depending on python version
		# self.q = queue.Queue(-1)
		self.q = Queue.Queue(-1)
		
		self.first = True

		self.f = open("ast_graph.py", "w")
		
		#print >> self.f, "from pyvis.network import Network\n"
		#print >> self.f, "net = Network(height=\"70%\", width=\"100%\", directed=True, layout=True)\n"
		#print >> self.f, "net.add_node(\"h1\", hidden=True, physics=False)"
		#print >> self.f, "net.add_node(\"h2\", hidden=True, physics=False)"

		self.ptfile("from pyvis.network import Network\n")
		self.ptfile("net = Network(height=\"70%\", width=\"100%\", directed=True, layout=True)\n")
		self.ptfile("net.add_node(\"h1\", hidden=True, physics=False)")
		self.ptfile("net.add_node(\"h2\", hidden=True, physics=False)")
		
	def invoke(self, arg, from_tty):
		# When we call "simple_command" from gdb, this is the method
		# that will be called.
		print("AST Debug! args: ", arg)

		"""
		1. convert arg to ASTNode* root
		2. parse the struct, print it, and traverse in pre order 
		"""
		# ast_root = gdb.parse_and_eval(arg)
		# print("ROOT: ")
		# print(ast_root['parent'] == 0x0)
		# data = ast_root['nodeData']['condStmt']
		# print(data)
		# ast_child = ast_root['child']
		# print(ast_child['type'])
		
		self.q.put(gdb.parse_and_eval(arg))
		self.bfs()

		#print >> self.f, "\nnet.show_buttons(filter_=['physics'])"
		#print >> self.f, "net.show(\"ast.html\")"
		self.ptfile("\nnet.show_buttons(filter_=['physics'])")
		self.ptfile("net.show(\"ast.html\")")

		self.f.close()

		print("Please wait while the AST graph is being created. It should open up in your browser automatically!\nIn case it does not show up, open ast_graph.html in the working directory.")
		os.system('python ast_graph.py')
		

		# json.dumps(ast_root, indent=4)

	def bfs(self):
		"""
			print:
				address of parent
				address of previous node
				address of next node
				address of child
				type
		"""
		if self.q.empty():
			return

		node = self.q.get()
		
		# node_name = node['type'],"_",node
		
		#title = r"{}_{} {{<br \> &emsp;No information here!<br \>}}".format(node['type'], node)
		
		#print >> self.f, "net.add_node(\"{}_{}\", title=\"{}\")".format(node['type'], node, title)
		
		#print(node['type'])
		if str(node['type']) == 'AST_NODE_LEAF':
			#print('..True..')
			leaf = node['nodeData']['leaf'].referenced_value()
			tn = leaf['tn']
			#print(tn)
			leaf_type = leaf['type']
			if tn == 0x0:
				lex = 'NULL'
			else:
				#print(tn['lex'])
				lex = tn['lex'].string(length=25)
				lex = re.sub(r'[\00-\7f]',r'', lex) 
			title = r"{}_{} {{<br \> &emsp;type: {}<br \>&emsp;lex: {}<br \>}}".format(node['type'], node, leaf_type, lex)
		else:
			title = r"{}_{} {{<br \> &emsp;No information here!<br \>}}".format(node['type'], node)	

		self.ptfile("net.add_node(\"{}_{}\", title=r\"{}\")".format(node['type'], node, title))
		# if this is the first node, force it to be root
		if self.first is True:
			#print >> self.f, "\nnet.add_edge(\"{}_{}\", \"h1\", hidden=True, physics=False)".format(node['type'], node)
			#print >> self.f, "net.add_edge(\"{}_{}\", \"h2\", hidden=True, physics=False)\n".format(node['type'], node)
			self.ptfile("\nnet.add_edge(\"{}_{}\", \"h1\", hidden=True, physics=False)".format(node['type'], node))
			self.ptfile("net.add_edge(\"{}_{}\", \"h2\", hidden=True, physics=False)\n".format(node['type'], node))
			self.first = False
		
		# define this node in the graph
		
		#print(node['type'])
		# add all children to queue

		child = node['child']

		while child != 0x0:
			self.q.put(child)

			# child_name = child['type'],"_",child
			
			#title = r"{}_{} {{<br \>&emsp;No information here!<br \>}}".format(child['type'], child)
			if str(child['type']) == 'AST_NODE_LEAF':
				#print('..True..')
				leaf = child['nodeData']['leaf'].referenced_value()
				tn = leaf['tn']
				leaf_type = leaf['type']
				if tn == 0x0:
					lex = 'NULL'
				else:
					#print(tn['lex'])
					lex = tn['lex'].string(length=25)
					lex = re.sub(r'[\00-\7f]',r'', lex) 
				title = r"{}_{} {{<br \> &emsp;type: {}<br \>&emsp;lex: {}<br \>}}".format(child['type'], child, leaf_type, lex)
			else:
				title = r"{}_{} {{<br \> &emsp;No information here!<br \>}}".format(child['type'], child)	

			#print >> self.f, "net.add_node(\"{}_{}\", title=\"{}\")".format(node['type'], node, title)
			#print >> self.f, "net.add_edge(\"{}_{}\", \"{}_{}\")".format(node['type'], node, child['type'], child)

			self.ptfile("net.add_node(\"{}_{}\", title=r\"{}\")".format(child['type'], child, title))
			self.ptfile("net.add_edge(\"{}_{}\", \"{}_{}\")".format(node['type'], node, child['type'], child))
			#self.G.add_node(child_name)
			#self.G.add_edge(node_name, child_name)

			child = child['next']

		# print details: comment out to avoid printing on console and waiting for while write
		#print("[\n\tParent: {},\n\tPrev: {},\n\tNext: {},\n\tChild: {},\n\tType: {}\n]"
		#	.format(node['parent'], node['prev'], node['next'], node['child'], node['type']))

		self.bfs()

	def ptfile(self, text):
		# use one of these, depending on the python version
		#print >> self.f, text
		# print(text ,file = self.f)
		#if sys.version_info[0] < 3:
			# python 2
		print >> self.f, text
		#else:
			#python 3
			#print(text ,file = self.f)

# This registers our class to the gdb runtime at "source" time.
SimpleCommand()