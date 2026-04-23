#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define V 5
#define E 6

char names[] = {'A','B','C','D','E'};

/* edge list for Kruskal */
typedef struct {
    int u, v, w;
} Edge;

Edge edges[E] = {
    {0,1,2}, {0,2,3}, {1,2,1},
    {1,3,4}, {2,4,5}, {3,4,1}
};

/* ---------- adjacency list ---------- */
typedef struct Node {
    int v, w;
    struct Node* next;
} Node;

Node* adj[V] = {NULL};

/* add undirected edge */
void addEdge(int u, int v, int w) {
    Node* n1 = malloc(sizeof(Node));
    n1->v = v; n1->w = w; n1->next = adj[u];
    adj[u] = n1;

    Node* n2 = malloc(sizeof(Node));
    n2->v = u; n2->w = w; n2->next = adj[v];
    adj[v] = n2;
}

/* ---------- min heap ---------- */
typedef struct {
    int v, key;   // vertex and its current min weight
} HeapNode;

typedef struct {
    int size;
    int pos[V];        // position of vertex in heap
    HeapNode* arr[V];  // heap array
} MinHeap;

HeapNode* newNode(int v, int key) {
    HeapNode* n = malloc(sizeof(HeapNode));
    n->v = v; n->key = key;
    return n;
}

/* swap heap nodes */
void swap(HeapNode** a, HeapNode** b) {
    HeapNode* t = *a; *a = *b; *b = t;
}

/* maintain heap property */
void heapify(MinHeap* h, int i) {
    int smallest = i;
    int l = 2*i+1, r = 2*i+2;

    if (l < h->size && h->arr[l]->key < h->arr[smallest]->key)
        smallest = l;
    if (r < h->size && h->arr[r]->key < h->arr[smallest]->key)
        smallest = r;

    if (smallest != i) {
        h->pos[h->arr[i]->v] = smallest;
        h->pos[h->arr[smallest]->v] = i;
        swap(&h->arr[i], &h->arr[smallest]);
        heapify(h, smallest);
    }
}

/* remove minimum key vertex */
HeapNode* extractMin(MinHeap* h) {
    HeapNode* root = h->arr[0];
    HeapNode* last = h->arr[h->size-1];

    h->arr[0] = last;
    h->pos[root->v] = h->size-1;
    h->pos[last->v] = 0;

    h->size--;
    heapify(h, 0);

    return root;
}

/* update key and move up */
void decreaseKey(MinHeap* h, int v, int key) {
    int i = h->pos[v];
    h->arr[i]->key = key;

    while (i && h->arr[i]->key < h->arr[(i-1)/2]->key) {
        h->pos[h->arr[i]->v] = (i-1)/2;
        h->pos[h->arr[(i-1)/2]->v] = i;
        swap(&h->arr[i], &h->arr[(i-1)/2]);
        i = (i-1)/2;
    }
}

/* check if vertex still in heap */
int inHeap(MinHeap* h, int v) {
    return h->pos[v] < h->size;
}

/* ---------- Prim (heap + adjacency list) ---------- */
int prim() {
    printf("\n--- Prim Trace ---\n");

    int parent[V], key[V];
    MinHeap h;
    h.size = V;

    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        parent[i] = -1;
        h.arr[i] = newNode(i, key[i]);
        h.pos[i] = i;
    }

    key[0] = 0;
    decreaseKey(&h, 0, 0);

    printf("Start from A\n");

    while (h.size > 0) {
        HeapNode* min = extractMin(&h);
        int u = min->v;

        printf("Include %c\n", names[u]);

        Node* temp = adj[u];
        while (temp) {
            int v = temp->v;

            if (inHeap(&h, v) && temp->w < key[v]) {
                key[v] = temp->w;
                parent[v] = u;
                decreaseKey(&h, v, key[v]);
                printf("Update (%c-%c, %d)\n", names[u], names[v], temp->w);
            }
            temp = temp->next;
        }
    }

    int total = 0;
    printf("\nMST Edges:\n");
    for (int i = 1; i < V; i++) {
        printf("(%c-%c, %d)\n", names[parent[i]], names[i], key[i]);
        total += key[i];
    }

    printf("Total Weight = %d\n", total);
    return total;
}

/* ---------- Kruskal ---------- */
int parentUF[V];

/* find with path compression */
int find(int x) {
    if (parentUF[x] != x)
        parentUF[x] = find(parentUF[x]);
    return parentUF[x];
}

void unionSet(int a, int b) {
    parentUF[find(a)] = find(b);
}

/* sort edges by weight */
int cmp(const void* a, const void* b) {
    return ((Edge*)a)->w - ((Edge*)b)->w;
}

int kruskal() {
    printf("\n--- Kruskal Trace ---\n");

    for (int i = 0; i < V; i++) parentUF[i] = i;

    qsort(edges, E, sizeof(Edge), cmp);

    printf("Sorted edges:\n");
    for (int i = 0; i < E; i++)
        printf("(%c-%c, %d)\n", names[edges[i].u], names[edges[i].v], edges[i].w);

    int total = 0;

    printf("\nSelected:\n");
    for (int i = 0; i < E; i++) {
        int u = edges[i].u, v = edges[i].v;

        if (find(u) != find(v)) {
            unionSet(u, v);
            total += edges[i].w;
            printf("(%c-%c, %d)\n", names[u], names[v], edges[i].w);
        }
    }

    printf("Total Weight = %d\n", total);
    return total;
}

/* ---------- main ---------- */
int main() {
    addEdge(0,1,2);
    addEdge(0,2,3);
    addEdge(1,2,1);
    addEdge(1,3,4);
    addEdge(2,4,5);
    addEdge(3,4,1);

    clock_t s,e;

    s = clock();
    int p = prim();
    e = clock();
    double pt = (double)(e-s)/CLOCKS_PER_SEC;

    s = clock();
    int k = kruskal();
    e = clock();
    double kt = (double)(e-s)/CLOCKS_PER_SEC;

    printf("\nPrim = %d, Kruskal = %d\n", p, k);
    printf("Prim Time: %f\n", pt);
    printf("Kruskal Time: %f\n", kt);

    return 0;
}