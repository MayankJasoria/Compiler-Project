import gdb
import Queue

class SimpleCommand(gdb.Command):

	def __init__(self):
		# This registers our class as "simple_command"
		super(SimpleCommand, self).__init__("ast", gdb.COMMAND_DATA)
		self.q = Queue.Queue(-1)

		self.f = open(r"c:\Users\Mayank\Documents\BITS\Compiler Construction\Compiler-Project\graph.py", "w")
		print >> self.f, "import networkx as nx\n"
		print >> self.f, "import matplotlib.pyplot as plt"
		print >> self.f, "G = nx.DiGraph()\n"
		
	def invoke(self, arg, from_tty):
		# When we call "simple_command" from gdb, this is the method
		# that will be called.
		print("Hello from AST Debug! arg: ", arg)

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

		print >> self.f, "nx.draw(G, with_labels = True)"
		print >> self.f, "plt.show()"

		self.f.close()
		

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

		print >> self.f, "G.add_node(\"{}_{}\")".format(node['type'], node)
		

		# define this node in the graph
		
		print(node['type'])
		# add all children to queue

		child = node['child']

		while child != 0x0:
			self.q.put(child)

			# child_name = child['type'],"_",child

			print >> self.f, "G.add_node(\"{}_{}\")".format(child['type'], child)
			print >> self.f, "G.add_edge(\"{}_{}\", \"{}_{}\")".format(node['type'], node, child['type'], child)
			#self.G.add_node(child_name)
			#self.G.add_edge(node_name, child_name)

			child = child['next']

		# print details
		print("[\n\tParent: {},\n\tPrev: {},\n\tNext: {},\n\tChild: {},\n\tType: {}\n]"
			.format(node['parent'], node['prev'], node['next'], node['child'], node['type']))

		self.bfs()

# This registers our class to the gdb runtime at "source" time.
SimpleCommand()