import math

def euclidean_distance(p1, p2):
    return math.sqrt((p1[0] - p2[0])**2 + (p1[1] - p2[1])**2)

def k_nearest_neighbors(points, query, k):
    distances = []
    
    for p in points:
        dist = euclidean_distance(p, query)
        distances.append((dist, p))
    
    distances.sort(key=lambda x: x[0])
    
    return [point for (_, point) in distances[:k]]

if __name__ == "__main__":
    points = [(1,2), (3,4), (5,6), (7,8)]
    query = (4,5)
    k = 2

    print("k nearest neighbors:", k_nearest_neighbors(points, query, k))