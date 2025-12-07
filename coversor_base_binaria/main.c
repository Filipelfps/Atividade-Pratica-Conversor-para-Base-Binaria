#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "pilha.h"

// --- Funções Auxiliares ---

int hex_char_para_int(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    return -1;
}

int hex_para_decimal(char* hex) {
    int len = strlen(hex);
    int decimal = 0;
    int potencia = 0;

    for (int i = len - 1; i >= 0; i--) {
        int valor_char = hex_char_para_int(hex[i]);
        if (valor_char == -1) return -1; // Sinaliza erro
        decimal += valor_char * pow(16, potencia);
        potencia++;
    }
    return decimal;
}

// --- Função Central de Lógica (Requisito: Generalização e Modo Didático) ---
void converter_decimal_para_base_n(Pilha* pilha, int decimal, int base, int modo_didatico) {
    // Validação de segurança
    if (base < 2 || base > 16) {
        printf("Erro: Base %d inválida. Suportamos apenas bases de 2 a 16.\n", base);
        return;
    }
    
    // Garante que a pilha esteja limpa antes de começar
    limpar_pilha(pilha);

    if (decimal == 0) {
        printf("Resultado (Base %d): 0\n", base);
        return;
    }

    int num = decimal;
    int contador_passos = 1;

    if (modo_didatico) {
        printf("\n--- Passo a Passo (Decimal %d -> Base %d) ---\n", decimal, base);
        printf("LOGICA: Dividir sucessivamente por %d e empilhar os restos.\n", base);
    }

    // Loop de Divisão e Empilhamento
    while (num > 0) {
        int resto = num % base;
        int quociente = num / base;

        if (modo_didatico) {
            printf("[%02d] %d / %d = %d (Resto: %d) -> PUSH(%d)\n", 
                   contador_passos++, num, base, quociente, resto, resto);
        }

        push(pilha, resto);
        num = quociente;
    }

    // Exibição do Resultado (Desempilhando)
    printf("\nResultado (Base %d): ", base);
    
    while (!esta_vazia(pilha)) {
        int valor = pop(pilha);
        
        // Converte valores >= 10 para letras (A-F)
        if (valor < 10) {
            printf("%d", valor);
        } else {
            printf("%c", 'A' + (valor - 10));
        }
    }
    printf("\n");
}

// --- Menu Principal ---
int main() {
    Pilha* pilha = criar_pilha();
    int opcao;
    int modo_didatico = 0; // 0 = Desligado, 1 = Ligado

    do {
        printf("\n=========================================\n");
        printf("      CONVERSOR DE BASES (COM PILHA)     \n");
        printf("=========================================\n");
        printf("Modo Didático: [%s]\n", modo_didatico ? "LIGADO" : "DESLIGADO");
        printf("-----------------------------------------\n");
        printf("1. Decimal -> Binário\n");
        printf("2. Decimal -> Hexadecimal\n");
        printf("3. Decimal -> Base N (2 a 16)\n");
        printf("4. Hexadecimal -> Decimal (e Binário)\n");
        printf("5. Ligar/Desligar Modo Didático\n");
        printf("0. Sair\n");
        printf("-----------------------------------------\n");
        printf("Opção: ");
        
        if (scanf("%d", &opcao) != 1) {
            printf("Erro: Entrada inválida.\n");
            while(getchar() != '\n'); // Limpa buffer
            continue;
        }

        int decimal = -1;
        int base_n;
        char hex[50];

        switch (opcao) {
            case 1: // Dec -> Bin
                printf("Digite o número Decimal: ");
                scanf("%d", &decimal);
                if (decimal < 0) { printf("Erro: Números negativos não suportados.\n"); break; }
                converter_decimal_para_base_n(pilha, decimal, 2, modo_didatico);
                break;

            case 2: // Dec -> Hex
                printf("Digite o número Decimal: ");
                scanf("%d", &decimal);
                if (decimal < 0) { printf("Erro: Números negativos não suportados.\n"); break; }
                converter_decimal_para_base_n(pilha, decimal, 16, modo_didatico);
                break;

            case 3: // Dec -> Base N
                printf("Digite o número Decimal: ");
                scanf("%d", &decimal);
                if (decimal < 0) { printf("Erro: Números negativos não suportados.\n"); break; }
                
                printf("Digite a Base de destino (2-16): ");
                scanf("%d", &base_n);
                converter_decimal_para_base_n(pilha, decimal, base_n, modo_didatico);
                break;

            case 4: // Hex -> Dec
                printf("Digite o Hexadecimal (ex: 1A, FF): ");
                scanf("%s", hex);
                decimal = hex_para_decimal(hex);
                
                if (decimal != -1) {
                    printf("\n> Valor em Decimal: %d\n", decimal);
                    // Reutiliza a lógica para mostrar o binário também, como bônus
                    printf("> Conversão automática para Binário:\n");
                    converter_decimal_para_base_n(pilha, decimal, 2, 0); // Sem modo didático aqui para não poluir
                } else {
                    printf("Erro: Hexadecimal inválido.\n");
                }
                break;

            case 5: // Toggle Didático
                modo_didatico = !modo_didatico;
                printf(">> Modo Didático alterado para: %s <<\n", modo_didatico ? "LIGADO" : "DESLIGADO");
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opção desconhecida.\n");
        }

    } while (opcao != 0);

    liberar_pilha(pilha);
    return 0;
}