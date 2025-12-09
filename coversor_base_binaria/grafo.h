#ifndef GRAFO_H
#define GRAFO_H

#include <stddef.h>

// Inicializa estruturas do grafo (chamar antes de usar)
void iniciar_grafo();

// Cria ou obtém um vértice que representa o mesmo valor numérico em uma base
// `valor_decimal` é o valor numérico em base decimal; `base` é a base dessa representação;
// `label` é a string legível (ex: "1101 (binario)"). Retorna o id do vértice.
int criar_ou_obter_vertice(int valor_decimal, int base, const char* label);

// Adiciona aresta não-direcionada entre dois vértices (por id)
void adicionar_aresta(int id1, int id2);

// Busca e imprime componentes conectados a partir de um vértice (BFS)
void buscar_bfs_por_id(int startId);

// Busca e imprime componentes conectados a partir de um vértice (DFS)
void buscar_dfs_por_id(int startId);

// Procura um vértice existente por valor_decimal e base; retorna id ou -1
int procurar_vertice(int valor_decimal, int base);

// Libera estruturas do grafo
void liberar_grafo();

#endif // GRAFO_H
