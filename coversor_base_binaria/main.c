#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "pilha.h"
#include "grafo.h"

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
    for (int i = 0; i < len; ++i) {
        int valor_char = hex_char_para_int(hex[i]);
        if (valor_char == -1) return -1; // Sinaliza erro
        decimal = decimal * 16 + valor_char;
    }
    return decimal;
}

// --- Função Central de Lógica (Requisito: Generalização e Modo Didático) ---
// Retorna o número de elementos empilhados (ou -1 em erro)
int converter_decimal_para_base_n(Pilha* pilha, Pilha* passos, int decimal, int base, int modo_didatico) {
    // Validação de segurança
    if (base < 2 || base > 16) {
        printf("Erro: Base %d inválida. Suportamos apenas bases de 2 a 16.\n", base);
        return -1;
    }
    
    // Garante que a pilha de resultado esteja limpa antes de começar
    limpar_pilha(pilha);
    if (passos) limpar_pilha(passos);

    if (decimal == 0) {
        printf("Resultado (Base %d): 0\n", base);
        return 0;
    }

    int num = decimal;
    int contador_passos = 1;
    int empilhados = 0;

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
        empilhados++;
        if (passos) push(passos, resto);
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
    printf("Elementos empilhados: %d\n", empilhados);
    return empilhados;
}

// Imprime a pilha `p` sem modificá-la. Mostra os restos na ordem em que foram gerados
// (do primeiro resto ao último). Não altera a pilha.
void imprimir_passos(Pilha* p) {
    if (!p) return;
    if (esta_vazia(p)) { printf("(Nenhum passo registrado)\n"); return; }
    // Conta nós e armazena em array
    int count = 0;
    Node* cur = p->topo;
    while (cur) { count++; cur = cur->prox; }
    int* arr = (int*) malloc(sizeof(int) * count);
    if (!arr) { printf("Erro: falha ao alocar memória para imprimir passos.\n"); return; }
    cur = p->topo;
    int i = 0;
    while (cur) { arr[i++] = cur->valor; cur = cur->prox; }
    // arr[0] é topo (último resto), imprimir de arr[count-1]..arr[0] para ordem cronológica
    printf("Passos (restos sucessivos):\n");
    for (int j = count-1; j >= 0; --j) printf(" - Resto: %d\n", arr[j]);
    free(arr);
}

// Gera a representação textual de `decimal` na `base` e escreve em `outbuf`.
// `buflen` é o tamanho do buffer. Garante string terminada.
void obter_representacao_decimal_para_base(int decimal, int base, char* outbuf, size_t buflen) {
    if (buflen == 0) return;
    if (base < 2 || base > 16) {
        snprintf(outbuf, buflen, "(base inválida)");
        return;
    }
    if (decimal == 0) {
        snprintf(outbuf, buflen, "0 (%s)", base==10?"decimal": (base==2?"binario": (base==8?"octal": (base==16?"hexadecimal":"base"))));
        return;
    }

    char temp[128];
    int pos = 0;
    int num = decimal;
    while (num > 0 && pos < (int)sizeof(temp)-1) {
        int resto = num % base;
        if (resto < 10) temp[pos++] = '0' + resto;
        else temp[pos++] = 'A' + (resto - 10);
        num /= base;
    }
    if (pos == 0) temp[pos++] = '0';
    // inverter
    int outpos = 0;
    for (int i = pos-1; i >= 0 && outpos < (int)buflen-1; --i) outbuf[outpos++] = temp[i];
    // adiciona sufixo com nome da base
    const char* nome = "base";
    if (base == 10) nome = "decimal";
    else if (base == 2) nome = "binario";
    else if (base == 8) nome = "octal";
    else if (base == 16) nome = "hexadecimal";

    int rem = buflen - outpos;
    if (rem > 0) {
        snprintf(outbuf + outpos, rem, " (%s)", nome);
    } else {
        // garante terminação
        outbuf[outpos-1] = '\0';
    }
}

// --- Menu Principal ---
int main() {
    Pilha* pilha = criar_pilha();
    Pilha* passos = criar_pilha();
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
        printf("6. Ver todas as representações relacionadas a um número (BFS/DFS)\n");
        printf("7. Mostrar passos da última conversão\n");
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
        char repr_buf[128];

        switch (opcao) {
            case 1: { // Dec -> Bin
                printf("Digite o número Decimal: ");
                if (scanf("%d", &decimal) != 1) { printf("Erro: entrada inválida.\n"); while(getchar()!='\n'); break; }
                if (decimal < 0) { printf("Erro: Números negativos não suportados.\n"); break; }
                limpar_pilha(passos);
                converter_decimal_para_base_n(pilha, passos, decimal, 2, modo_didatico);
                // atualiza grafo: cria vértices e aresta entre decimal e binário
                iniciar_grafo(); // garante que grafo foi iniciado (chamada idempotente)
                obter_representacao_decimal_para_base(decimal, 10, repr_buf, sizeof(repr_buf));
                char origem_label[128]; snprintf(origem_label, sizeof(origem_label), "%d (decimal)", decimal);
                int id_origem = criar_ou_obter_vertice(decimal, 10, origem_label);
                obter_representacao_decimal_para_base(decimal, 2, repr_buf, sizeof(repr_buf));
                int id_dest = criar_ou_obter_vertice(decimal, 2, repr_buf);
                adicionar_aresta(id_origem, id_dest);
                break;
            }

            case 2: { // Dec -> Hex
                printf("Digite o número Decimal: ");
                if (scanf("%d", &decimal) != 1) { printf("Erro: entrada inválida.\n"); while(getchar()!='\n'); break; }
                if (decimal < 0) { printf("Erro: Números negativos não suportados.\n"); break; }
                limpar_pilha(passos);
                converter_decimal_para_base_n(pilha, passos, decimal, 16, modo_didatico);
                iniciar_grafo();
                char origem_label2[128]; snprintf(origem_label2, sizeof(origem_label2), "%d (decimal)", decimal);
                int id_origem2 = criar_ou_obter_vertice(decimal, 10, origem_label2);
                obter_representacao_decimal_para_base(decimal, 16, repr_buf, sizeof(repr_buf));
                int id_dest2 = criar_ou_obter_vertice(decimal, 16, repr_buf);
                adicionar_aresta(id_origem2, id_dest2);
                break;
            }

            case 3: { // Dec -> Base N
                printf("Digite o número Decimal: ");
                if (scanf("%d", &decimal) != 1) { printf("Erro: entrada inválida.\n"); while(getchar()!='\n'); break; }
                if (decimal < 0) { printf("Erro: Números negativos não suportados.\n"); break; }
                printf("Digite a Base de destino (2-16): ");
                if (scanf("%d", &base_n) != 1) { printf("Erro: entrada inválida.\n"); while(getchar()!='\n'); break; }
                if (base_n < 2 || base_n > 16) { printf("Erro: base fora do intervalo permitido.\n"); break; }
                limpar_pilha(passos);
                converter_decimal_para_base_n(pilha, passos, decimal, base_n, modo_didatico);
                iniciar_grafo();
                char origem_label3[128]; snprintf(origem_label3, sizeof(origem_label3), "%d (decimal)", decimal);
                int id_origem3 = criar_ou_obter_vertice(decimal, 10, origem_label3);
                obter_representacao_decimal_para_base(decimal, base_n, repr_buf, sizeof(repr_buf));
                int id_dest3 = criar_ou_obter_vertice(decimal, base_n, repr_buf);
                adicionar_aresta(id_origem3, id_dest3);
                break;
            }

            case 4: { // Hex -> Dec
                printf("Digite o Hexadecimal (ex: 1A, FF): ");
                if (scanf("%s", hex) != 1) { printf("Erro: entrada inválida.\n"); while(getchar()!='\n'); break; }
                decimal = hex_para_decimal(hex);
                if (decimal != -1) {
                    printf("\n> Valor em Decimal: %d\n", decimal);
                    // Reutiliza a lógica para mostrar o binário também, como bônus
                    printf("> Conversão automática para Binário:\n");
                    limpar_pilha(passos);
                    converter_decimal_para_base_n(pilha, passos, decimal, 2, 0); // Sem modo didático aqui para não poluir
                    iniciar_grafo();
                    // cria vértices: hexadecimal e decimal
                    char origem_hex_label[128]; snprintf(origem_hex_label, sizeof(origem_hex_label), "%s (hexadecimal)", hex);
                    int id_hex = criar_ou_obter_vertice(decimal, 16, origem_hex_label);
                    char origem_dec_label[128]; snprintf(origem_dec_label, sizeof(origem_dec_label), "%d (decimal)", decimal);
                    int id_dec = criar_ou_obter_vertice(decimal, 10, origem_dec_label);
                    adicionar_aresta(id_hex, id_dec);
                    // também cria vértice para binário e conecta ao decimal
                    obter_representacao_decimal_para_base(decimal, 2, repr_buf, sizeof(repr_buf));
                    int id_bin = criar_ou_obter_vertice(decimal, 2, repr_buf);
                    adicionar_aresta(id_dec, id_bin);
                } else {
                    printf("Erro: Hexadecimal inválido.\n");
                }
                break;
            }

            case 7: {
                printf("Passos da última conversão:\n");
                imprimir_passos(passos);
                break;
            }

            case 6: {
                // Ver representações relacionadas (BFS/DFS)
                printf("Escolha a base da representação de entrada:\n");
                printf("1. Decimal\n2. Binario\n3. Octal\n4. Hexadecimal\n");
                printf("Base (1-4): ");
                int escolha_base;
                if (scanf("%d", &escolha_base) != 1) { printf("Entrada inválida.\n"); while(getchar()!= '\n'); break; }
                char valor_str[128];
                printf("Digite a representação (ex: 13 ou 1101 ou F): ");
                scanf("%s", valor_str);
                int valor_decimal = -1;
                int base_in = 10;
                if (escolha_base == 1) { base_in = 10; valor_decimal = atoi(valor_str); }
                else if (escolha_base == 2) { base_in = 2; // parse binario
                    valor_decimal = 0; for (size_t i=0;i<strlen(valor_str);++i){ char c=valor_str[i]; if (c=='0'||c=='1'){ valor_decimal = valor_decimal*2 + (c-'0'); } else { valor_decimal = -1; break; } }
                }
                else if (escolha_base == 3) { base_in = 8; valor_decimal = (int) strtol(valor_str, NULL, 8); }
                else if (escolha_base == 4) { base_in = 16; valor_decimal = hex_para_decimal(valor_str); }
                else { printf("Base inválida.\n"); break; }

                if (valor_decimal == -1) { printf("Erro: representação inválida.\n"); break; }

                int id_start = procurar_vertice(valor_decimal, base_in);
                if (id_start == -1) { printf("Nenhuma representação registrada para esse valor/base.\n"); break; }

                printf("Escolha o método: 1-BFS, 2-DFS: "); int metodo; scanf("%d", &metodo);
                if (metodo == 1) buscar_bfs_por_id(id_start);
                else buscar_dfs_por_id(id_start);
                break;
            }

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
    liberar_pilha(passos);
    return 0;
}