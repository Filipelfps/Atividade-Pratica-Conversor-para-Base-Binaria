#ifndef PILHA_H
#define PILHA_H

#include <stdlib.h> // Para usar NULL

// 1. Definição do Nó (Node)
typedef struct Node {
    int valor;        // O valor armazenado (resto da divisão)
    struct Node* prox; // Ponteiro para o próximo nó
} Node;

// 2. Definição da Pilha (Stack)
typedef struct Pilha {
    Node* topo; // Ponteiro para o nó do topo
} Pilha;

// 3. Protótipos das Funções
Pilha* criar_pilha();                // Cria e inicializa a pilha
void push(Pilha* pilha, int valor);  // Empilha (Push)
int pop(Pilha* pilha);               // Desempilha (Pop)
int top(Pilha* pilha);               // Consulta o topo
int esta_vazia(Pilha* pilha);        // Verifica se está vazia
void limpar_pilha(Pilha* pilha);     // Esvazia a pilha sem liberar a estrutura principal
void liberar_pilha(Pilha* pilha);    // Libera toda a memória (struct + nós)

#endif // PILHA_H