import heapq

def prim_mst(graph, start):
    visited = set()
    min_heap = [(0, start, None)]  # (weight, node, parent)
    
    mst = []
    total_weight = 0

    while min_heap:
        weight, node, parent = heapq.heappop(min_heap)

        if node in visited:
            continue

        visited.add(node)
        if parent is not None:
            mst.append((parent, node, weight))
            total_weight += weight

        for neighbor, w in graph[node]:
            if neighbor not in visited:
                heapq.heappush(min_heap, (w, neighbor, node))

    return mst, total_weight


# Example graph
graph = {
    'A': [('B', 2), ('C', 3)],
    'B': [('A', 2), ('C', 1), ('D', 4)],
    'C': [('A', 3), ('B', 1), ('E', 5)],
    'D': [('B', 4), ('E', 1)],
    'E': [('C', 5), ('D', 1)]
}

mst, weight = prim_mst(graph, 'A')
print("MST edges:", mst)
print("Total weight:", weight)