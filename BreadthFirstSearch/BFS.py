class graph:
    def __init__(self):
        self.Adj = {}
    
    def build(self, A):
        for x in A:
            if x[0] not in self.Adj:
                self.Adj[x[0]] = [x[1]]
            else:
                self.Adj[x[0]].append(x[1])
    
    def bft(self, s):
        parent = {}
        for v in self.Adj.keys():
            parent[v] = None
        parent[s] = s
        level = []
        level.append([s])
        i = 1
        while True:
            L = []
            for u in level[i - 1]:
                for v in self.Adj[u]:
                    if v != None and parent[v] == None:
                        L.append(v)
                        parent[v] = u
            if L == []: break
            level.append(L)
            i += 1
        return level
    
    def bfs(self, s, t):
        parent = {}
        path = []
        for v in self.Adj.keys():
            parent[v] = None
        parent[s] = s
        level = []
        level.append([s])
        i = 1
        flag = True
        while flag:
            L = []
            for u in level[i - 1]:
                for v in self.Adj[u]:
                    if v != None and parent[v] == None and flag:
                        L.append(v)
                        parent[v] = u
                        if v == t: 
                            flag = False
                            end = v
            if L == []: break
            level.append(L)
            i += 1
        path.append(end)
        while parent[end] != s:
            path.append(parent[end])
            end = parent[end]
        path.append(s)
        path.reverse()
        return path
            
G = graph()
A = [('A', 'B'), ('B', 'C'), ('C', 'D'), ('C', 'E'), ('D', 'F'), ('E', 'F'), ('F', 'D'), 
     ('B', 'A'), ('C', 'B'), ('D', 'C'), ('E', 'C'), ('F', 'E')]
B = [('A', 'B'), ('B', 'A'), ('B', 'C'), ('C', 'B'), ('A', 'E'), ('E', 'A'), ('B', 'D'), 
     ('D', 'B'), ('E', 'C'), ('C', 'E')]
C = [(0, 1), (0, 3), (0, 4), (1, 2), (1, 4), (2, 5), (3, 4), (3, 6), (4, 5), (4, 7),
     (5, None), (6, 4), (6, 7), (7, 8), (7, 5), (8, None)]
G.build(C)
#print(G.Adj)
level = G.bft(0)
print(level)
path = G.bfs(0, 8)
print(path)
