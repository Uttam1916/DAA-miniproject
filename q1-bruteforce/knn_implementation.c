/*
===============================================================================
K-Nearest Neighbors (Brute Force) - Implementation in C

ALGORITHM:
1. Compute distance from query point to all n points
2. Store (distance, point)
3. Sort by distance
4. Pick first k points

TIME COMPLEXITY:
- Distance computation: O(n)
- Sorting: O(n log n)
- Total: O(n log n)

LIMITATIONS:
- Computes all distances
- Sorting overhead
- Not efficient for large datasets

BETTER APPROACH:
- k-d tree: average O(log n) query
===============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Structure for point */
typedef struct {
    double x, y;
} Point;

/* Store point with distance */
typedef struct {
    double dist;
    Point p;
} PD;

/* Euclidean distance */
double distance(Point a, Point b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

/* Comparator for sorting */
int cmp(const void *a, const void *b) {
    PD *p1 = (PD *)a;
    PD *p2 = (PD *)b;
    if (p1->dist < p2->dist) return -1;
    if (p1->dist > p2->dist) return 1;
    return 0;
}

/* KNN function */
void knn(Point *points, int n, Point query, int k) {
    PD *arr = (PD *)malloc(n * sizeof(PD));

    /* compute distances */
    for (int i = 0; i < n; i++) {
        arr[i].dist = distance(points[i], query);
        arr[i].p = points[i];
    }

    /* sort */
    qsort(arr, n, sizeof(PD), cmp);

    /* print k nearest */
    printf("Nearest %d neighbors:\n", k);
    for (int i = 0; i < k; i++) {
        printf("(%.2f, %.2f) distance = %.2f\n",
               arr[i].p.x, arr[i].p.y, arr[i].dist);
    }

    free(arr);
}

/* Test function */
void test_basic() {
    Point points[] = {{1,2}, {3,4}, {5,6}, {7,8}};
    Point query = {4,5};
    int n = 4, k = 2;

    printf("Query: (%.1f, %.1f)\n", query.x, query.y);
    knn(points, n, query, k);
}

int main() {
    printf("KNN Brute Force\n\n");
    test_basic();
    return 0;
}