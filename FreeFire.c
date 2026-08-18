#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20

// Criação da struct
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// Funções obrigatórias
void selectionSortPrioridade(Componente vetor[], int n);
void insertionSortTipo(Componente vetor[], int n);
void bubbleSortNome(Componente vetor[], int n);
int buscaBinariaPorNome(Componente vetor[], int n, char chave[]);
void mostrarComponentes(Componente vetor[], int n);
void medirTempo(void (*algoritmo)(Componente[], int), Componente vetor[], int tamanho);

void removerQuebraLinha(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

// Ordena os componentes por prioridade
void selectionSortPrioridade(Componente vetor[], int n) {
    long long comparacoes = 0;

    for (int i = 0; i < n - 1; i++) {
        int menor = i;
        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (vetor[j].prioridade < vetor[menor].prioridade) {
                menor = j;
            }
        }
        if (menor != i) {
            Componente temp = vetor[i];
            vetor[i] = vetor[menor];
            vetor[menor] = temp;
        }
    }

    printf("\nOrdenacao por prioridade concluida (Selection Sort).\n");
    printf("Comparacoes realizadas: %lld\n", comparacoes);
}

// Ordena os componentes por tipo
void insertionSortTipo(Componente vetor[], int n) {
    long long comparacoes = 0;

    for (int i = 1; i < n; i++) {
        Componente atual = vetor[i];
        int j = i - 1;

        while (j >= 0) {
            comparacoes++;
            if (strcmp(vetor[j].tipo, atual.tipo) > 0) {
                vetor[j + 1] = vetor[j];
                j--;
            } else {
                break;
            }
        }
        vetor[j + 1] = atual;
    }

    printf("\nOrdenacao por tipo concluida (Insertion Sort).\n");
    printf("Comparacoes realizadas: %lld\n", comparacoes);
}

// Ordena os componentes por nome
void bubbleSortNome(Componente vetor[], int n) {
    long long comparacoes = 0;

    for (int i = 0; i < n - 1; i++) {
        int trocou = 0;
        for (int j = 0; j < n - i - 1; j++) {
            comparacoes++;
            if (strcmp(vetor[j].nome, vetor[j + 1].nome) > 0) {
                Componente temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
                trocou = 1;
            }
        }
        if (!trocou) {
            break;
        }
    }

    printf("\nOrdenacao por nome concluida (Bubble Sort).\n");
    printf("Comparacoes realizadas: %lld\n", comparacoes);
}

// Realiza a busca binária por nome
int buscaBinariaPorNome(Componente vetor[], int n, char chave[]) {
    int inicio = 0;
    int fim = n - 1;
    int comparacoes = 0;

    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;
        comparacoes++;

        int comp = strcmp(vetor[meio].nome, chave);
        if (comp == 0) {
            printf("Comparacoes na busca binaria: %d\n", comparacoes);
            return meio;
        }
        if (comp < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    printf("Comparacoes na busca binaria: %d\n", comparacoes);
    return -1;
}

// Exibe os componentes cadastrados
void mostrarComponentes(Componente vetor[], int n) {
    if (n == 0) {
        printf("\nNenhum componente cadastrado.\n");
        return;
    }

    printf("\n------------------------------------------------------------\n");
    printf("%-4s | %-25s | %-15s | %-10s\n", "Item", "Nome", "Tipo", "Prioridade");
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-4d | %-25s | %-15s | %-10d\n", i + 1, vetor[i].nome, vetor[i].tipo, vetor[i].prioridade);
    }
    printf("------------------------------------------------------------\n");
}

// Mede e exibe o tempo de execução do algoritmo
void medirTempo(void (*algoritmo)(Componente[], int), Componente vetor[], int tamanho) {
    clock_t inicio = clock();
    algoritmo(vetor, tamanho);
    clock_t fim = clock();

    double tempo_ms = ((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000.0;
    printf("Tempo de execucao: %.4f ms\n", tempo_ms);
}

// Interface do usuário
int main() {
    Componente componentes[MAX_COMPONENTES];
    int total = 0;
    int ordenadoPorNome = 0;
    int opcao;

    do {
        printf("\n=== TORRE DE RESGATE - MONTAGEM ===\n");
        printf("1. Cadastrar componente (%d/%d)\n", total, MAX_COMPONENTES);
        printf("2. Listar componentes\n");
        printf("3. Ordenar por Nome (Bubble Sort)\n");
        printf("4. Ordenar por Tipo (Insertion Sort)\n");
        printf("5. Ordenar por Prioridade (Selection Sort)\n");
        printf("6. Buscar componente-chave (Busca Binaria)\n");
        printf("0. Sair\n");
        printf("Opcao: ");

        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n');
            opcao = -1;
            continue;
        }
        getchar();

        switch (opcao) {
            case 1:
                if (total >= MAX_COMPONENTES) {
                    printf("\nLimite maximo de componentes atingido!\n");
                } else {
                    printf("\nNovo Componente:\n");
                    printf("Nome: ");
                    fgets(componentes[total].nome, sizeof(componentes[total].nome), stdin);
                    removerQuebraLinha(componentes[total].nome);

                    printf("Tipo: ");
                    fgets(componentes[total].tipo, sizeof(componentes[total].tipo), stdin);
                    removerQuebraLinha(componentes[total].tipo);

                    do {
                        printf("Prioridade (1 a 10): ");
                        scanf("%d", &componentes[total].prioridade);
                        getchar();
                        if (componentes[total].prioridade < 1 || componentes[total].prioridade > 10) {
                            printf("Valor invalido! Digite um numero de 1 a 10.\n");
                        }
                    } while (componentes[total].prioridade < 1 || componentes[total].prioridade > 10);

                    total++;
                    ordenadoPorNome = 0;
                    printf("Componente cadastrado com sucesso!\n");
                }
                break;

            case 2:
                mostrarComponentes(componentes, total);
                break;

            case 3:
                if (total == 0) {
                    printf("\nNenhum componente cadastrado.\n");
                } else {
                    medirTempo(bubbleSortNome, componentes, total);
                    mostrarComponentes(componentes, total);
                    ordenadoPorNome = 1;
                }
                break;

            case 4:
                if (total == 0) {
                    printf("\nNenhum componente cadastrado.\n");
                } else {
                    medirTempo(insertionSortTipo, componentes, total);
                    mostrarComponentes(componentes, total);
                    ordenadoPorNome = 0;
                }
                break;

            case 5:
                if (total == 0) {
                    printf("\nNenhum componente cadastrado.\n");
                } else {
                    medirTempo(selectionSortPrioridade, componentes, total);
                    mostrarComponentes(componentes, total);
                    ordenadoPorNome = 0;
                }
                break;

            case 6:
                if (total == 0) {
                    printf("\nNenhum componente cadastrado.\n");
                } else if (!ordenadoPorNome) {
                    printf("\nA busca binaria so pode ser feita apos ordenar por nome (opcao 3).\n");
                } else {
                    char chave[30];
                    printf("\nNome do componente-chave para busca: ");
                    fgets(chave, sizeof(chave), stdin);
                    removerQuebraLinha(chave);

                    int posicao = buscaBinariaPorNome(componentes, total, chave);

                    if (posicao != -1) {
                        printf("\n[Componente-chave encontrado!]\n");
                        printf("Posicao: %d\n", posicao + 1);
                        printf("Nome: %s\n", componentes[posicao].nome);
                        printf("Tipo: %s\n", componentes[posicao].tipo);
                        printf("Prioridade: %d\n", componentes[posicao].prioridade);
                        printf("Status: Torre pronta para montagem!\n");
                    } else {
                        printf("\nComponente-chave '%s' nao encontrado.\n", chave);
                    }
                }
                break;

            case 0:
                printf("\nSaindo...\n");
                break;

            default:
                printf("\nOpcao invalida. Tente novamente.\n");
                break;
        }

    } while (opcao != 0);

    return 0;
}
