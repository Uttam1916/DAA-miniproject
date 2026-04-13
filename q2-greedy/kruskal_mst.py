def find(parent, x):
    if parent[x] != x:
        parent[x] = find(parent, parent[x])
    return parent[x]

def union(parent, rank, x, y):
    rootX = find(parent, x)
    rootY = find(parent, y)

    if rootX != rootY:
        if rank[rootX] > rank[rootY]:
            parent[rootY] = rootX
        elif rank[rootX] < rank[rootY]:
            parent[rootX] = rootY
        else:
            parent[rootY] = rootX
            rank[rootX] += 1

def kruskal_mst(vertices, edges):
    parent = {v: v for v in vertices}
    rank = {v: 0 for v in vertices}

    edges.sort(key=lambda x: x[2])

    mst = []
    total_weight = 0

    for u, v, w in edges:
        if find(parent, u) != find(parent, v):
            union(parent, rank, u, v)
            mst.append((u, v, w))
            total_weight += w

    return mst, total_weight


vertices = ['A', 'B', 'C', 'D', 'E']
edges = [
    ('A','B',2), ('A','C',3), ('B','C',1),
    ('B','D',4), ('C','E',5), ('D','E',1)
]

mst, weight = kruskal_mst(vertices, edges)
print("Kruskal MST:", mst)
print("Total weight:", weight)