#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct AdjNode {
    int id;
    struct AdjNode* prox;
} AdjNode;

typedef struct Vertice {
    int id;
    int valor_decimal;
    int base;
    char* label;
    AdjNode* adj;
    struct Vertice* prox;
} Vertice;

static Vertice* vertices = NULL;
static int proximo_id = 0;

void iniciar_grafo() {
    if (vertices == NULL) {
        vertices = NULL;
        proximo_id = 0;
    }
}

static Vertice* buscar_por_id(int id) {
    Vertice* v = vertices;
    while (v) {
        if (v->id == id) return v;
        v = v->prox;
    }
    return NULL;
}

int procurar_vertice(int valor_decimal, int base) {
    Vertice* v = vertices;
    while (v) {
        if (v->valor_decimal == valor_decimal && v->base == base) return v->id;
        v = v->prox;
    }
    return -1;
}

int criar_ou_obter_vertice(int valor_decimal, int base, const char* label) {
    int id = procurar_vertice(valor_decimal, base);
    if (id != -1) return id;

    Vertice* novo = (Vertice*) malloc(sizeof(Vertice));
    if (!novo) {
        printf("Erro: falha ao alocar vértice do grafo.\n");
        return -1;
    }
    novo->id = proximo_id++;
    novo->valor_decimal = valor_decimal;
    novo->base = base;
    novo->label = (char*) malloc(strlen(label) + 1);
    if (novo->label) strcpy(novo->label, label);
    novo->adj = NULL;
    novo->prox = vertices;
    vertices = novo;
    return novo->id;
}

static int adj_existe(AdjNode* head, int id) {
    AdjNode* a = head;
    while (a) {
        if (a->id == id) return 1;
        a = a->prox;
    }
    return 0;
}

void adicionar_aresta(int id1, int id2) {
    if (id1 == id2) return;
    Vertice* v1 = buscar_por_id(id1);
    Vertice* v2 = buscar_por_id(id2);
    if (!v1 || !v2) return;

    if (!adj_existe(v1->adj, id2)) {
        AdjNode* a = (AdjNode*) malloc(sizeof(AdjNode));
        a->id = id2; a->prox = v1->adj; v1->adj = a;
    }
    if (!adj_existe(v2->adj, id1)) {
        AdjNode* a = (AdjNode*) malloc(sizeof(AdjNode));
        a->id = id1; a->prox = v2->adj; v2->adj = a;
    }
}

void buscar_bfs_por_id(int startId) {
    if (startId < 0) return;
    // conta vértices para alocar arrays
    int n = proximo_id;
    int* visitado = (int*) calloc(n, sizeof(int));
    int* fila = (int*) malloc(n * sizeof(int));
    int qh = 0, qt = 0;

    Vertice* start = buscar_por_id(startId);
    if (!start) {
        printf("Vertice inicial não encontrado.\n");
        free(visitado); free(fila);
        return;
    }

    fila[qt++] = startId;
    visitado[startId] = 1;

    printf("Representações conectadas (BFS) a partir de '%s':\n", start->label);

    while (qh < qt) {
        int cur = fila[qh++];
        Vertice* v = buscar_por_id(cur);
        if (!v) continue;
        printf(" - %s\n", v->label);
        AdjNode* a = v->adj;
        while (a) {
            if (!visitado[a->id]) {
                visitado[a->id] = 1;
                fila[qt++] = a->id;
            }
            a = a->prox;
        }
    }

    free(visitado); free(fila);
}

static void dfs_rec(Vertice* v, int* visitado) {
    if (!v) return;
    visitado[v->id] = 1;
    printf(" - %s\n", v->label);
    AdjNode* a = v->adj;
    while (a) {
        if (!visitado[a->id]) {
            Vertice* nv = buscar_por_id(a->id);
            dfs_rec(nv, visitado);
        }
        a = a->prox;
    }
}

void buscar_dfs_por_id(int startId) {
    if (startId < 0) return;
    int n = proximo_id;
    int* visitado = (int*) calloc(n, sizeof(int));
    Vertice* start = buscar_por_id(startId);
    if (!start) {
        printf("Vertice inicial não encontrado.\n");
        free(visitado);
        return;
    }

    printf("Representações conectadas (DFS) a partir de '%s':\n", start->label);
    dfs_rec(start, visitado);
    free(visitado);
}

void liberar_grafo() {
    Vertice* v = vertices;
    while (v) {
        Vertice* nxt = v->prox;
        free(v->label);
        AdjNode* a = v->adj;
        while (a) {
            AdjNode* an = a->prox;
            free(a);
            a = an;
        }
        free(v);
        v = nxt;
    }
    vertices = NULL;
    proximo_id = 0;
}
