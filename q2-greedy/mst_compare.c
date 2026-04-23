#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define V 5
#define E 6

char names[] = {'A','B','C','D','E'};

/* Edge structure */
typedef struct {
    int u, v, w;
} Edge;

/* Graph edges */
Edge edges[E] = {
    {0,1,2}, {0,2,3}, {1,2,1},
    {1,3,4}, {2,4,5}, {3,4,1}
};

/* ===================== KRUSKAL ===================== */

int parent[V];

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

void unionSet(int a, int b) {
    parent[find(a)] = find(b);
}

int cmp(const void* a, const void* b) {
    return ((Edge*)a)->w - ((Edge*)b)->w;
}

int kruskal() {
    printf("\n--- Kruskal Trace ---\n");

    for (int i = 0; i < V; i++) parent[i] = i;

    qsort(edges, E, sizeof(Edge), cmp);

    printf("Sorted edges:\n");
    for (int i = 0; i < E; i++) {
        printf("(%c-%c, %d)\n", names[edges[i].u], names[edges[i].v], edges[i].w);
    }

    int weight = 0;

    printf("\nSelected edges:\n");
    for (int i = 0; i < E; i++) {
        int u = edges[i].u;
        int v = edges[i].v;

        if (find(u) != find(v)) {
            unionSet(u, v);
            weight += edges[i].w;
            printf("(%c-%c, %d)\n", names[u], names[v], edges[i].w);
        }
    }

    printf("Total Weight = %d\n", weight);
    return weight;
}

/* ===================== PRIM ===================== */

int graph[V][V] = {
    {0,2,3,0,0},
    {2,0,1,4,0},
    {3,1,0,0,5},
    {0,4,0,0,1},
    {0,0,5,1,0}
};

int minKey(int key[], int mstSet[]) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++) {
        if (!mstSet[v] && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

int prim() {
    printf("\n--- Prim Trace ---\n");

    int parent[V];
    int key[V];
    int mstSet[V];

    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        mstSet[i] = 0;
    }

    key[0] = 0;
    parent[0] = -1;

    printf("Start from vertex A\n");

    for (int count = 0; count < V - 1; count++) {
        int u = minKey(key, mstSet);
        mstSet[u] = 1;

        printf("\nInclude vertex %c\n", names[u]);

        for (int v = 0; v < V; v++) {
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                key[v] = graph[u][v];
                parent[v] = u;
                printf("Update edge (%c-%c, %d)\n", names[u], names[v], graph[u][v]);
            }
        }
    }

    int weight = 0;
    printf("\nEdges in MST:\n");
    for (int i = 1; i < V; i++) {
        printf("(%c-%c, %d)\n", names[parent[i]], names[i], key[i]);
        weight += key[i];
    }

    printf("Total Weight = %d\n", weight);
    return weight;
}

/* ===================== MAIN ===================== */

int main() {
    clock_t start, end;

    start = clock();
    int prim_weight = prim();
    end = clock();
    double prim_time = (double)(end - start) / CLOCKS_PER_SEC;

    start = clock();
    int kruskal_weight = kruskal();
    end = clock();
    double kruskal_time = (double)(end - start) / CLOCKS_PER_SEC;

    printf("\n============================\n");
    printf("Prim MST Weight: %d\n", prim_weight);
    printf("Kruskal MST Weight: %d\n", kruskal_weight);

    printf("\nExecution Time:\n");
    printf("Prim: %f seconds\n", prim_time);
    printf("Kruskal: %f seconds\n", kruskal_time);

    return 0;
}