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

//leia o input do usuario
void readString(char s[], int size) {
    fgets(s, size, stdin);
    limpaBuffer();
    s[strcspn(s,"\n")] = '\0';
}

//leia um valor inteiro do usuario
void readInt(int *num) {
    scanf("%d", num);
    limpaBuffer();
}

//verifica se o caracter eh um numero
int isNumber(char c) {
    if (c >= 0x30 && c <= 0x39) {
        return 1;
    }

    return 0;
}

//verifica se o caracter eh uma letra
int isLetter(char c) {
    if (toupper(c) >= 0x41 && toupper(c) <= 0x5A) {
        return 1;
    }
    return 0;
}

//verifica o input (se o input foi valido), funciona para strings numericos, strings de 1 letra e 2 digitos, e strings de 2 letras e 2 digitos
int verificar(char s[], int size) {
    int i, success = 0, numOnly = 1;

    //verifica se eh um string numerico
    for (i = 0; i < strlen(s); i++) {
        if (isLetter(s[i])) {
            numOnly = 0;
            break;
        }
    }

    size--; //tira o '\0' do tamanho total

    //se estiver na primeira metade, verifica se eh letra, se não, verifica se eh numero
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

    //se tem a quantidade certa de letras e numeros, a funcao eh verdadeira
    if (success == size) {
        return 1;
    }

    //se nao, a funcao eh falsa
    return 0;
}


// ========== MAIN ==========


int main() {
    Equipamento equipamento, equipamentoTemp;
    int input;

    setlocale(LC_ALL, "portuguese");

    //pega  guarda o ID do usuario
    do {
        //le um string
        system("cls");
        printf("Escreva o ID do equipamento: ");
        readString(equipamentoTemp.ID, sizeof(equipamentoTemp.ID));

        //verifica se for valido
        if (verificar(equipamentoTemp.ID, sizeof(equipamentoTemp.ID))) {
            strcpy(equipamento.ID, equipamentoTemp.ID);
        } else {
            printf("\nID Inválido\n\n");
            system("pause");
        }
    } while (!verificar(equipamentoTemp.ID, sizeof(equipamentoTemp.ID)));

    //pega e guarda o tipo de equipamento
    do {
        //le numero inteiro
        input = 0;

        system("cls");
        printf("Escolha o tipo de equipamento: \n\n\t");
        printf("1: AGV\n\t");
        printf("2: Braço-Articulado\n\t");
        printf("3: Esteira\n\t");
        printf("4: sorter\n\t");
        printf("5: transelevador\n\n> ");
        readInt(&input);

        //verifica se eh valido
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

    //pega e guarda o setor
    do {
        //le string
        system("cls");
        printf("Escreva o Setor Associado ao equipamento: ");
        readString(equipamentoTemp.setorAssociado, sizeof(equipamentoTemp.setorAssociado));

        //verifica se eh valido
        if (verificar(equipamentoTemp.setorAssociado, sizeof(equipamentoTemp.setorAssociado))) {
            strcpy(equipamento.setorAssociado, equipamentoTemp.setorAssociado);
        } else {
            printf("\nID Inválido\n\n");
            system("pause");
        }
    } while (!verificar(equipamentoTemp.setorAssociado, sizeof(equipamentoTemp.setorAssociado)));

    //pega e guarda o estado
    do {
        //le numero inteiro
        input = 0;

        system("cls");
        printf("Qual é o Estado Operacional atual do equipamento? \n\n\t");
        printf("1: Ativo\n\t");
        printf("2: Inativo\n\t");
        printf("3: Manutenção\n\n> ");
        readInt(&input);

        //verifica o numero
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

    //pega e guarda o ID do operador
    do {
        //le string
        system("cls");
        printf("Escreva o ID do Operador do equipamento: ");
        readString(equipamentoTemp.IDo, sizeof(equipamentoTemp.IDo));

        //verifica se eh valido
        if (verificar(equipamentoTemp.IDo, sizeof(equipamentoTemp.IDo))) {
            strcpy(equipamento.IDo, equipamentoTemp.IDo);
        } else {
            printf("\nID Inválido\n\n");
            system("pause");
        }
    } while (!verificar(equipamentoTemp.IDo, sizeof(equipamentoTemp.IDo)));

    //pega e guarda a prioridade
    do {
        //le numero inteiro
        input = 0;

        system("cls");
        printf("Qual é a Importáncia (Nível de Prioridade) do equipamento? \n\n\t");
        printf("1: Baixa\n\t");
        printf("2: Média\n\t");
        printf("3: Alta\n\n> ");
        readInt(&input);

        //verifica se eh valido
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

    //imprime o resultado final
    system("cls");
    printf("Registro:\n\n\tID: %s\n\tTipo: %s\n\tSetor Associado: %s\n\tEstado Operacional: %s\n\tID do Operador: %s\n\tPrioridade: %s\n", equipamento.ID, equipamento.tipo, equipamento.setorAssociado, equipamento.estado, equipamento.IDo, equipamento.prioridade);

    return 0;
}
