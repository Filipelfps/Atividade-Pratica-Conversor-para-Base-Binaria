# 🚀 Atividade Prática 02: Conversor de Bases com Pilha

Este projeto foi desenvolvido para a disciplina de Estrutura de Dados (IDP) e consiste na implementação de uma **Pilha (Stack)** dinâmica em linguagem C.

Como aplicação prática, a estrutura de dados é utilizada como componente central de um sistema que converte números das bases **Decimal** e **Hexadecimal** para a base **Binária**.


---

## 👨‍💻 Integrantes do Grupo

* Daniel Henrique Pontes
* Leandro Filipe
* Arthur Amorim Dias
* Igor Magalhães

---

## 🛠️ Sobre a Implementação

O projeto segue os requisitos de modularização exigidos, separando a lógica da estrutura de dados da lógica da aplicação.

### 1. Estrutura de Dados: Pilha Dinâmica (`pilha.h` e `pilha.c`)

A Pilha foi implementada utilizando **alocação dinâmica de memória** (`malloc` e `free`) e ponteiros. Ela é composta por `Nodes` (Nós) que se conectam, onde a Pilha principal armazena apenas o ponteiro para o `topo`.

Funções essenciais implementadas:
* `criar_pilha()`: Aloca e inicializa uma nova pilha.
* `push()`: Insere um novo elemento no topo da pilha.
* `pop()`: Remove e retorna o elemento do topo da pilha.
* `top()`: Apenas consulta o elemento do topo sem removê-lo.
* `esta_vazia()`: Verifica se a pilha não possui elementos.
* `liberar_pilha()`: Libera toda a memória alocada pela pilha.

### 2. Aplicação Prática: Conversor de Bases (`main.c`)

O arquivo `main.c` contém a interface de usuário (menu) e a lógica de conversão.

* **Decimal para Binário:** O número decimal é dividido sucessivamente por 2, e os **restos** (0 ou 1) são empilhados (`push`). Ao final, a pilha é desempilhada (`pop`), revelando o número binário na ordem correta.
* **Hexadecimal para Binário:** O número hexadecimal (string) é primeiro convertido para seu equivalente em **Decimal**. Em seguida, utiliza-se a mesma lógica de Decimal para Binário descrita acima.

---

## ⚙️ Como Compilar e Executar

Este projeto foi desenvolvido e testado no ambiente **GitHub Codespaces**, utilizando o compilador **GCC**.

### 1. Compilação

Para compilar o projeto, utilize o seguinte comando no terminal (certifique-se de estar na pasta `conversor_base_binaria`):

```bash
gcc main.c pilha.c -o conversor -lm
