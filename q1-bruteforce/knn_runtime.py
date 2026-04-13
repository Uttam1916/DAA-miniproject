import random
import time
from math import sqrt

def distance(p1, p2):
    return sqrt((p1[0]-p2[0])**2 + (p1[1]-p2[1])**2)

def knn(points, q, k):
    d = [(distance(p, q), p) for p in points]
    d.sort()
    return d[:k]

sizes = [100, 500, 1000, 5000, 10000, 20000]

for n in sizes:
    pts = [(random.randint(0,1000), random.randint(0,1000)) for _ in range(n)]
    q = (50,50)
    
    start = time.time()
    knn(pts, q, 5)
    end = time.time()
    
    print(f"n = {n}, time = {end - start:.6f} seconds")