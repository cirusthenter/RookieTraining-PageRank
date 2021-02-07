import networkx as nx

# GRAPH_FILE = "simple.digraph"
GRAPH_FILE = "p2p-Gnutella04.txt"

g = nx.DiGraph()
f = open(GRAPH_FILE, "r")
for line in f.readlines():
    u, v = map(int, line.split())
    g.add_edge(u, v)

p_dict = nx.pagerank(g, alpha=0.9)
print(p_dict)
print(p_dict[10878])
