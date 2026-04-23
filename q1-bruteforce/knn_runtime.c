/*
===============================================================================
KNN Runtime Analysis (Improved)

TEST:
- Random points
- Larger sizes for measurable timing
- Multiple runs for averaging

OBSERVATION:
- Time grows approximately O(n log n)
===============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct {
    double x, y;
} Point;

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

/* Comparator for qsort */
int cmp(const void *a, const void *b) {
    PD *p1 = (PD *)a;
    PD *p2 = (PD *)b;
    return (p1->dist > p2->dist) - (p1->dist < p2->dist);
}

/* KNN computation */
void knn(Point *points, int n, Point query, int k) {
    PD *arr = (PD *)malloc(n * sizeof(PD));

    for (int i = 0; i < n; i++) {
        arr[i].dist = distance(points[i], query);
        arr[i].p = points[i];
    }

    qsort(arr, n, sizeof(PD), cmp);

    free(arr);
}

/* Generate random points */
void gen(Point *points, int n) {
    for (int i = 0; i < n; i++) {
        points[i].x = rand() % 1000;
        points[i].y = rand() % 1000;
    }
}

int main() {
    /* Larger sizes for proper measurement */
    int sizes[] = {1000, 5000, 10000, 50000, 100000, 200000};
    int num_sizes = 6;

    int k = 5;
    Point query = {500, 500};

    int runs = 50;  // number of repetitions for averaging

    printf("n\tTime (sec)\n");

    for (int i = 0; i < num_sizes; i++) {
        int n = sizes[i];

        Point *points = malloc(n * sizeof(Point));
        gen(points, n);

        clock_t start = clock();

        /* Run multiple times */
        for (int r = 0; r < runs; r++) {
            knn(points, n, query, k);
        }

        clock_t end = clock();

        double total_time = (double)(end - start) / CLOCKS_PER_SEC;
        double avg_time = total_time / runs;

        printf("%d\t%.6f\n", n, avg_time);

        free(points);
    }

    return 0;
}