#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Para lidar com a string de hexadecimal
#include <math.h>   // Para pow() na conversão de hex
#include "pilha.h"  // Importante: incluir nossa pilha!

// --- Funções Auxiliares da Aplicação ---

// Converte um char '0'-'9', 'A'-'F' para seu valor int
int hex_char_para_int(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    } else if (c >= 'A' && c <= 'F') {
        return c - 'A' + 10;
    } else if (c >= 'a' && c <= 'f') {
        return c - 'a' + 10;
    }
    return -1; // Erro
}

// Converte uma string hexadecimal para um número decimal
int hex_para_decimal(char* hex) {
    int len = strlen(hex);
    int decimal = 0;
    int potencia = 0;

    // Itera da direita para a esquerda (ex: "2A")
    for (int i = len - 1; i >= 0; i--) {
        int valor_char = hex_char_para_int(hex[i]);
        if (valor_char == -1) {
            printf("Erro: Caractere hexadecimal inválido '%c'\n", hex[i]);
            return -1;
        }
        decimal += valor_char * pow(16, potencia);
        potencia++;
    }
    return decimal;
}

// Função principal da aplicação
int main() {
    Pilha* pilha = criar_pilha(); // Cria a pilha UMA VEZ
    int opcao;
    
    do {
        printf("\n--- Conversor de Bases (usando Pilha) ---\n");
        printf("1. Decimal para Binário\n");
        printf("2. Hexadecimal para Binário\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            // --- Decimal para Binário ---
            int decimal;
            printf("Digite o número decimal: ");
            scanf("%d", &decimal);

            if (decimal == 0) {
                printf("Binário: 0\n");
            } else {
                int num = decimal;
                while (num > 0) {
                    push(pilha, num % 2); // Empilha o resto da divisão por 2
                    num = num / 2;
                }

                printf("Binário: ");
                while (!esta_vazia(pilha)) {
                    printf("%d", pop(pilha)); // Desempilha para imprimir na ordem correta
                }
                printf("\n");
            }

        } else if (opcao == 2) {
            // --- Hexadecimal para Binário ---
            char hex[50]; // Suporta um número hex de até 50 chars
            printf("Digite o número hexadecimal (ex: 2A): ");
            scanf("%s", hex);

            int decimal = hex_para_decimal(hex); // 1. Converte Hex -> Dec

            if (decimal == -1) {
                continue; // Volta ao menu se deu erro
            }
            if (decimal == 0) {
                printf("Binário: 0\n");
            } else {
                // 2. Usa a MESMA lógica de Dec -> Bin
                int num = decimal;
                while (num > 0) {
                    push(pilha, num % 2);
                    num = num / 2;
                }

                printf("Binário: ");
                while (!esta_vazia(pilha)) {
                    printf("%d", pop(pilha));
                }
                printf("\n");
            }

        } else if (opcao == 0) {
            printf("Saindo...\n");
        } else {
            printf("Opção inválida!\n");
        }

    } while (opcao != 0);

    liberar_pilha(pilha); // Libera toda a memória antes de fechar
    return 0;
}