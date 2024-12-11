#include <stdio.h>
#include <stdlib.h>

#define MAX_ALUNOS 100

// Definindo a estrutura para armazenar os dados do aluno
typedef struct {
    char nome[100];
    float notas[3];
    int frequencia;
    float mediaFinal;
    char situacao[20];
} Aluno;

// Função para calcular a média final com base nas duas maiores notas
float calcularMedia(Aluno *aluno) {
    // Ordenando as notas em ordem crescente
    float temp;
    for (int i = 0; i < 2; i++) {
        for (int j = i + 1; j < 3; j++) {
            if (aluno->notas[i] < aluno->notas[j]) {
                temp = aluno->notas[i];
                aluno->notas[i] = aluno->notas[j];
                aluno->notas[j] = temp;
            }
        }
    }
    // Calculando a média das duas maiores notas
    return (aluno->notas[0] + aluno->notas[1]) / 2.0;
}

// Função para verificar se o aluno está aprovado
void verificarSituacao(Aluno *aluno) {
    if (aluno->frequencia >= 75 && aluno->mediaFinal >= 7) {
        snprintf(aluno->situacao, sizeof(aluno->situacao), "Aprovado");
    } else {
        snprintf(aluno->situacao, sizeof(aluno->situacao), "Reprovado");
    }
}

// Função para obter os dados do aluno
void obterDadosAluno(Aluno *aluno) {
    printf("Digite o nome do aluno: ");
    fgets(aluno->nome, sizeof(aluno->nome), stdin);
    aluno->nome[strcspn(aluno->nome, "\n")] = '\0';  // Remove o caractere de nova linha do nome

    // Validando as notas
    int i;
    for (i = 0; i < 3; i++) {
        while (1) {
            printf("Digite a %dª nota do aluno (0 a 10): ", i + 1);
            scanf("%f", &aluno->notas[i]);
            if (aluno->notas[i] >= 0 && aluno->notas[i] <= 10) {
                break;  // Saímos do loop se a nota for válida
            } else {
                printf("Nota inválida! As notas devem estar entre 0 e 10.\n");
            }
        }
    }

    // Validando a frequência
    while (1) {
        printf("Digite a frequencia do aluno (0 a 100): ");
        scanf("%d", &aluno->frequencia);
        if (aluno->frequencia >= 0 && aluno->frequencia <= 100) {
            break;  // Frequência válida
        } else {
            printf("Frequência inválida! Deve ser entre 0 e 100.\n");
        }
    }

    // Calculando a média e verificando a situação do aluno
    aluno->mediaFinal = calcularMedia(aluno);
    verificarSituacao(aluno);
}

// Função para gerar o relatório dos alunos
void gerarRelatorio(Aluno alunos[], int quantidadeAlunos) {
    printf("\nRelatorio de Situacao dos Alunos:\n");
    printf("Nome\t\t\tMédia Final\tSituacao\n");
    printf("---------------------------------------------\n");

    for (int i = 0; i < quantidadeAlunos; i++) {
        printf("%-20s %.2f\t\t%s\n", alunos[i].nome, alunos[i].mediaFinal, alunos[i].situacao);
    }
}

int main() {
    Aluno alunos[MAX_ALUNOS];
    int quantidadeAlunos;

    // Solicitar a quantidade de alunos
    printf("Digite o numero de alunos: ");
    while (1) {
        scanf("%d", &quantidadeAlunos);
        if (quantidadeAlunos > 0 && quantidadeAlunos <= MAX_ALUNOS) {
            break;
        } else {
            printf("Numero invalido! O numero de alunos deve ser entre 1 e %d.\n", MAX_ALUNOS);
        }
    }
    getchar(); // Consumir o caractere de nova linha pendente

    // Obter os dados dos alunos
    for (int i = 0; i < quantidadeAlunos; i++) {
        printf("\nAluno %d\n", i + 1);
        obterDadosAluno(&alunos[i]);
    }

    // Gerar o relatório final
    gerarRelatorio(alunos, quantidadeAlunos);

    return 0;
}
