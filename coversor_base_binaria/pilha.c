#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>

// Cria e inicializa uma pilha vazia
Pilha* criar_pilha() {
    Pilha* pilha = (Pilha*) malloc(sizeof(Pilha));
    
    // Validação de robustez: verifica se o malloc funcionou
    if (pilha == NULL) {
        printf("ERRO FATAL: Falha ao alocar memória para a Pilha!\n");
        exit(EXIT_FAILURE);
    }
    
    pilha->topo = NULL;
    return pilha;
}

// Verifica se a pilha está vazia
int esta_vazia(Pilha* pilha) {
    return (pilha->topo == NULL);
}

// Insere um elemento no topo da pilha (push)
void push(Pilha* pilha, int valor) {
    Node* novo_no = (Node*) malloc(sizeof(Node));
    if (novo_no == NULL) {
        printf("Erro: Falha na alocação de memória (Stack Overflow simulado)!\n");
        return;
    }
    novo_no->valor = valor;
    novo_no->prox = pilha->topo;
    pilha->topo = novo_no;
}

// Remove e retorna o elemento do topo da pilha (pop)
int pop(Pilha* pilha) {
    if (esta_vazia(pilha)) {
        printf("Erro: A pilha está vazia (Stack Underflow)!\n");
        return -1;
    }
    Node* temp = pilha->topo;
    int valor_removido = temp->valor;
    pilha->topo = temp->prox;
    free(temp);
    return valor_removido;
}

// Apenas consulta o valor no topo
int top(Pilha* pilha) {
    if (esta_vazia(pilha)) {
        return -1;
    }
    return pilha->topo->valor;
}

// Esvazia a pilha removendo todos os nós (limpeza lógica)
void limpar_pilha(Pilha* pilha) {
    while (!esta_vazia(pilha)) {
        pop(pilha);
    }
}

// Libera toda a memória alocada (para fechar o programa)
void liberar_pilha(Pilha* pilha) {
    limpar_pilha(pilha); // Garante que os nós sejam liberados
    free(pilha);         // Libera a estrutura da pilha
}