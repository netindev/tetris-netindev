#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5

// Estrutura da peça
typedef struct {
    char tipo;
    int id;
} Peca;

// Estrutura da fila circular
typedef struct {
    Peca elementos[TAM_FILA];
    int inicio;
    int fim;
    int qtd;
} Fila;

// Função para gerar tipo de peça aleatória
char gerarTipo() {
    char tipos[] = {'I', 'O', 'T', 'L', 'J', 'S', 'Z'};
    return tipos[rand() % 7];
}

// Função para gerar uma nova peça automaticamente
Peca gerarPeca(int id) {
    Peca nova;
    nova.tipo = gerarTipo();
    nova.id = id;
    return nova;
}

// Inicializa a fila circular
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->qtd = 0;
}

// Verifica se a fila está cheia
int filaCheia(Fila *f) {
    return f->qtd == TAM_FILA;
}

// Verifica se a fila está vazia
int filaVazia(Fila *f) {
    return f->qtd == 0;
}

// Enfileira uma nova peça
void enqueue(Fila *f, Peca p) {
    if (filaCheia(f)) {
        printf("⚠️  Fila cheia! Não é possível inserir.\n");
        return;
    }
    f->elementos[f->fim] = p;
    f->fim = (f->fim + 1) % TAM_FILA;
    f->qtd++;
}

// Remove a peça da frente da fila
Peca dequeue(Fila *f) {
    Peca removida = {'-', -1};
    if (filaVazia(f)) {
        printf("⚠️  Fila vazia! Não há peças para jogar.\n");
        return removida;
    }
    removida = f->elementos[f->inicio];
    f->inicio = (f->inicio + 1) % TAM_FILA;
    f->qtd--;
    return removida;
}

// Mostra o estado atual da fila
void mostrarFila(Fila *f) {
    printf("\n🎮 Fila de Peças Futuras (%d/%d):\n", f->qtd, TAM_FILA);
    if (filaVazia(f)) {
        printf("   [Fila Vazia]\n");
        return;
    }

    int i = f->inicio;
    for (int c = 0; c < f->qtd; c++) {
        Peca p = f->elementos[i];
        printf("   [%d] Peça %c (ID: %d)\n", c + 1, p.tipo, p.id);
        i = (i + 1) % TAM_FILA;
    }
}

// Programa principal
int main() {
    srand(time(NULL));

    Fila fila;
    inicializarFila(&fila);
    int proximoID = 1;

    // Inicializa a fila com 5 peças
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(&fila, gerarPeca(proximoID++));
    }

    int opcao;
    do {
        printf("\n===== TETRIS STACK - Nível Novato =====\n");
        printf("1 - Jogar peça (remover da frente)\n");
        printf("2 - Mostrar fila\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                Peca jogada = dequeue(&fila);
                if (jogada.id != -1) {
                    printf("\n🧱 Jogando peça %c (ID %d)...\n", jogada.tipo, jogada.id);
                    // Reinsere nova peça automaticamente
                    Peca nova = gerarPeca(proximoID++);
                    enqueue(&fila, nova);
                }
                mostrarFila(&fila);
                break;
            }
            case 2:
                mostrarFila(&fila);
                break;
            case 0:
                printf("\n👋 Encerrando o jogo. Até a próxima!\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
