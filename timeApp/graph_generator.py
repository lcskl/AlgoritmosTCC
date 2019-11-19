class Graph:
    def __init__(self, n):
        self.n = n
        self.m = 0
        self.adjList = ( [] for i in range(n)) 
        self.degree  = ( 0  for i in range(n))
    
    def add_dir_edge(self, a, b):
        self.adjList[a].append(b)
        self.degree[b] += 1
        self.m += 1
    
    def add_undir_edge(self, a, b):
        self.adjList[a].append(b)
        self.adjList[b].append(a)
        self.degree[a] += 1
        self.degree[b] += 1
        self.m += 1
    
def generate_random_graph(n,connected):
    new_graph = Graph(n)

      
    




