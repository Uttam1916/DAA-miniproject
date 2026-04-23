/*
===============================================================================
KNN Runtime Analysis

TEST:
- Random points
- Sizes: 100 to 20000
- Measure execution time

OBSERVATION:
- Time grows ~ n log n
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

double distance(Point a, Point b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

int cmp(const void *a, const void *b) {
    PD *p1 = (PD *)a;
    PD *p2 = (PD *)b;
    return (p1->dist > p2->dist) - (p1->dist < p2->dist);
}

void knn(Point *points, int n, Point query, int k) {
    PD *arr = (PD *)malloc(n * sizeof(PD));

    for (int i = 0; i < n; i++) {
        arr[i].dist = distance(points[i], query);
        arr[i].p = points[i];
    }

    qsort(arr, n, sizeof(PD), cmp);

    free(arr);
}

/* generate random points */
void gen(Point *points, int n) {
    for (int i = 0; i < n; i++) {
        points[i].x = rand() % 1000;
        points[i].y = rand() % 1000;
    }
}

int main() {
    int sizes[] = {100, 500, 1000, 5000, 10000, 20000};
    int k = 5;
    Point query = {500, 500};

    printf("n\tTime (sec)\n");

    for (int i = 0; i < 6; i++) {
        int n = sizes[i];

        Point *points = malloc(n * sizeof(Point));
        gen(points, n);

        clock_t start = clock();
        knn(points, n, query, k);
        clock_t end = clock();

        double t = (double)(end - start) / CLOCKS_PER_SEC;

        printf("%d\t%f\n", n, t);

        free(points);
    }

    return 0;
}