#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>

// ========== STRUCTS ==========

typedef struct {
    char ID[4];
    char tipo[17]; //AGV, braco-articulado, esteira, sorter, transelevador
    char setorAssociado[5];
    char estado[11];
    char IDo[5];
    char prioridade[6];
} Equipamento;

// ========== FUNCOES ==========

void limpaBuffer() {
    int c;
    while (c = getchar() != '\n' && c != EOF);
}

void readString(char s[], int size) {
    fgets(s, size, stdin);
    limpaBuffer();
    s[strcspn(s,"\n")] = '\0';
}

void readInt(int *num) {
    scanf("%d", num);
    limpaBuffer();
}

int isNumber(char c) {
    if (c >= 0x30 && c <= 0x39) {
        return 1;
    }

    return 0;
}

int isLetter(char c) {
    if (toupper(c) >= 0x41 && toupper(c) <= 0x5A) {
        return 1;
    }
    return 0;
}

int verificar(char s[], int size) {
    int i, success = 0, numOnly = 1;

    for (i = 0; i < strlen(s); i++) {
        if (isLetter(s[i])) {
            numOnly = 0;
            break;
        }
    }

    size--;

    for (i = 0; i < strlen(s); i++) {
        if (i <= (size / 2) - 1 && !numOnly) {
            if (isLetter(s[i])) {
                success++;
            }
        } else {
            if (isNumber(s[i])) {
                success++;
            }
        }
    }

    if (success == size) {
        return 1;
    }

    return 0;
}


// ========== MAIN ==========


int main() {
    Equipamento equipamento, equipamentoTemp;
    int input;

    setlocale(LC_ALL, "portuguese");

    do {
        system("cls");
        printf("Escreva o ID do equipamento: ");
        readString(equipamentoTemp.ID, sizeof(equipamentoTemp.ID));

        if (verificar(equipamentoTemp.ID, sizeof(equipamentoTemp.ID))) {
            strcpy(equipamento.ID, equipamentoTemp.ID);
        } else {
            printf("\nID Inv�lido\n\n");
            system("pause");
        }
    } while (!verificar(equipamentoTemp.ID, sizeof(equipamentoTemp.ID)));


    do {
        input = 0;

        system("cls");
        printf("Escolha o tipo de equipamento: \n\n\t");
        printf("1: AGV\n\t");
        printf("2: Bra�o-Articulado\n\t");
        printf("3: Esteira\n\t");
        printf("4: sorter\n\t");
        printf("5: transelevador\n\n> ");
        readInt(&input);

        switch(input) {
            case 1:
                strcpy(equipamento.tipo, "AGV");
                break;
            case 2:
                strcpy(equipamento.tipo, "BRACO-ARTICULADO");
                break;
            case 3:
                strcpy(equipamento.tipo, "ESTEIRA");
                break;
            case 4:
                strcpy(equipamento.tipo, "SORTER");
                break;
            case 5:
                strcpy(equipamento.tipo, "TRANSELEVADOR");
                break;
            default:
                printf("\nINPUT INVALIDO\n\n");
                system("pause");

        }
    } while (input < 1 || input > 5);

    do {
        system("cls");
        printf("Escreva o Setor Associado ao equipamento: ");
        readString(equipamentoTemp.setorAssociado, sizeof(equipamentoTemp.setorAssociado));

        if (verificar(equipamentoTemp.setorAssociado, sizeof(equipamentoTemp.setorAssociado))) {
            strcpy(equipamento.setorAssociado, equipamentoTemp.setorAssociado);
        } else {
            printf("\nID Inv�lido\n\n");
            system("pause");
        }
    } while (!verificar(equipamentoTemp.setorAssociado, sizeof(equipamentoTemp.setorAssociado)));

    do {
        input = 0;

        system("cls");
        printf("Qual � o Estado Operacional atual do equipamento? \n\n\t");
        printf("1: Ativo\n\t");
        printf("2: Inativo\n\t");
        printf("3: Manuten��o\n\n> ");
        readInt(&input);

        switch(input) {
            case 1:
                strcpy(equipamento.estado, "ATIVO");
                break;
            case 2:
                strcpy(equipamento.estado, "INATIVO");
                break;
            case 3:
                strcpy(equipamento.estado, "MANUTENCAO");
                break;
            default:
                printf("\nINPUT INVALIDO\n\n");
                system("pause");

        }
    } while (input < 1 || input > 3);

    do {
        system("cls");
        printf("Escreva o ID do Operador do equipamento: ");
        readString(equipamentoTemp.IDo, sizeof(equipamentoTemp.IDo));

        if (verificar(equipamentoTemp.IDo, sizeof(equipamentoTemp.IDo))) {
            strcpy(equipamento.IDo, equipamentoTemp.IDo);
        } else {
            printf("\nID Inv�lido\n\n");
            system("pause");
        }
    } while (!verificar(equipamentoTemp.IDo, sizeof(equipamentoTemp.IDo)));

    do {
        input = 0;

        system("cls");
        printf("Qual � a Import�ncia (N�vel de Prioridade) do equipamento? \n\n\t");
        printf("1: Baixa\n\t");
        printf("2: M�dia\n\t");
        printf("3: Alta\n\n> ");
        readInt(&input);

        switch(input) {
            case 1:
                strcpy(equipamento.prioridade, "BAIXA");
                break;
            case 2:
                strcpy(equipamento.prioridade, "MEDIA");
                break;
            case 3:
                strcpy(equipamento.prioridade, "ALTA");
                break;
            default:
                printf("\nINPUT INVALIDO\n\n");
                system("pause");

        }
    } while (input < 1 || input > 3);

    system("cls");
    printf("Registro:\n\n\tID: %s\n\tTipo: %s\n\tSetor Associado: %s\n\tEstado Operacional: %s\n\tID do Operador: %s\n\tPrioridade: %s\n", equipamento.ID, equipamento.tipo, equipamento.setorAssociado, equipamento.estado, equipamento.IDo, equipamento.prioridade);

    return 0;
}
