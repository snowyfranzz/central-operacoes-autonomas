#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>

// ========== STRUCTS ==========

typedef struct equipamentos {
    char ID[4];
    char tipo[17]; //AGV, braco-articulado, esteira, sorter, transelevador
    char setorAssociado[5];
    char estado[11];
    char IDo[5];
    char prioridade[6];
} Equipamentos;

typedef struct operadores {
    char ID[5];
    char nome[71];
    char setorAssociado[5]; 
    char nivelOp[14]; // BASICO, INTERMEDIARIO, SUPERVISOR
    char estado[10]; // ATIVO, OCUPADO, INATIVO, BLOQUEADO
    int quantOp;
} Operadores;

// ========== FUNCOES ==========

void limpaBuffer() {
    int c;
    while (c = getchar() != '\n' && c != EOF);
}

int scanfInput() {
    int input;

    printf("> ");
    scanf("%i", &input);
    limpaBuffer();

    return input;
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

void printEquipamento(Equipamento equipamento) {
    printf("\nID: %s", equipamento.ID);
    printf("\nTipo: %s", equipamento.tipo);
    printf("\nSetor Associado: %s", equipamento.setorAssociado);
    printf("\nEstado Operacional: %s", equipamento.estado);
    printf("\nID do Operador: %s", equipamento.IDo);
    printf("\nPrioridade: %s", equipamento.prioridade);
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
int verificar(char s[], int size, int numOnly) {
    int i, success = 0;

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
// DASHBOARD PRINCIPAL
void printDashboard() {
    system("cls");
    printf("+------------------------------------------------------------------------------+\n");
    printf("|               Orbytec Sistemas Integrados - Setor VX27 - Dashboard           |\n");
    printf("+-------------------------+--------------------------+-------------------------+\n");
    printf("|  Ocorrências Recentes:  |    Operadores Ativos:    |   Equipamentos Ativos:  |\n");
    printf("|=========================|==========================|=========================|\n");
    printf("|                         |                          |                         |\n");
    printf("|                         |                          |                         |\n");
    printf("|                         |                          |                         |\n");
    printf("|                         |                          |                         |\n");
    printf("|                         |                          |                         |\n");
    printf("|                         |                          |                         |\n");
    printf("|                         |                          |                         |\n");
    printf("|                         |                          |                         |\n");
    printf("|                         |                          |                         |\n");
    printf("|                         |                          |                         |\n");
    printf("+-------------------------+--------------------------+-------------------------+\n");
    printf("|                                    Menu:                                     |\n");
    printf("|==============================================================================|\n");
    printf("|                                                                              |\n");
    printf("|    1. Cadastro de Operadores.              4. Consultar Registros.           |\n");
    printf("|                                                                              |\n");
    printf("|    2. Cadastro de Equipamentos.            5. Ver Relatórios Operacionais.   |\n");
    printf("|                                                                              |\n");
    printf("|    3. Atualizar Dados do Sistema.          6. Sair do Programa.              |\n");
    printf("+------------------------------------------------------------------------------+\n");
}

Equipamento registrarEquipamento() {
    Equipamento equipamento, equipamentoTemp;
    int input;

    //pega  guarda o ID do usuario
    do {
        //le um string
        system("cls");
        printf("Escreva o ID do equipamento: ");
        readString(equipamentoTemp.ID, sizeof(equipamentoTemp.ID));

        //verifica se for valido
        if (verificar(equipamentoTemp.ID, sizeof(equipamentoTemp.ID), 0)) {
            strcpy(equipamento.ID, equipamentoTemp.ID);
        } else {
            printf("\nID Inválido\n\n");
            system("pause");
        }
    } while (!verificar(equipamentoTemp.ID, sizeof(equipamentoTemp.ID), 0));

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
        if (verificar(equipamentoTemp.setorAssociado, sizeof(equipamentoTemp.setorAssociado), 0)) {
            strcpy(equipamento.setorAssociado, equipamentoTemp.setorAssociado);
        } else {
            printf("\nSetor Inválido\n\n");
            system("pause");
        }
    } while (!verificar(equipamentoTemp.setorAssociado, sizeof(equipamentoTemp.setorAssociado), 0));

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
        if (verificar(equipamentoTemp.IDo, sizeof(equipamentoTemp.IDo), 1)) {
            strcpy(equipamento.IDo, equipamentoTemp.IDo);
        } else {
            printf("\nID Inválido\n\n");
            system("pause");
        }
    } while (!verificar(equipamentoTemp.IDo, sizeof(equipamentoTemp.IDo), 1));

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

    return equipamento;
}


// CADASTRO DE OPERADOR
Operadores cadastroOp(){
    Operadores op;
    int localInput = 0;
    int len = 0;

    system("cls");

    printf("Cadastro de Operador:\n\n");
    do {
        printf("> ID do Operador (4 Dígitos, outros serão desconsiderados):  ");
        readString(op.ID, sizeof(op.ID));

        if (!verificar(op.ID, sizeof(op.ID), 1)) {
            printf("\nID Inválido!\n\n");
            system("pause");
        } 
    } while (!verificar(op.ID, sizeof(op.ID), 1));
    
    printf("> Nome do Operador (Máximo de 70 Caractéres): ");
    readString(op.nome, sizeof(op.nome));
    
    do {
        printf("> Setor (2 Letras, 2 Dígitos - outros serão desconsiderados): ");
        readString(op.setorAssociado, sizeof(op.setorAssociado));

        if (!verificar(op.setorAssociado, sizeof(op.setorAssociado), 0)) {
            printf("\nSetor Inválido!\n\n");
            system("pause");
        } 
    } while (!verificar(op.setorAssociado, sizeof(op.setorAssociado), 0));

    do {
        printf("> Nível Operacional (1. BASICO, 2. INTERMEDIARIO, 3. SUPERVISOR): ");
        if (scanf("%i", &localInput) != 1) {
            localInput = 0;
        }
        limpaBuffer();
        
        switch (localInput){
            case 1:
                strcpy(op.nivelOp, "BASICO");
                break;
            case 2:
                strcpy(op.nivelOp, "INTERMEDIARIO");
                break;
            case 3:
                strcpy(op.nivelOp, "SUPERVISOR");
                break;
            default:
                printf("ERRO. Você inseriu o número do nível que você quer? Tente novamente.\n");
        }

    }while(localInput != 1 && localInput != 2 && localInput != 3);

    
    do {
        printf("> Estado Operacional Atual (1. ATIVO, 2. OCUPADO, 3. INATIVO, 4. BLOQUEADO): ");
        if (scanf("%i", &localInput) != 1) {
            localInput = 0;
        }
        limpaBuffer();
        
        switch (localInput){
            case 1:
                strcpy(op.estado, "ATIVO");
                break;
            case 2:
                strcpy(op.estado, "OCUPADO");
                break;
            case 3:
                strcpy(op.estado, "INATIVO");
                break;
            case 4:
                strcpy(op.estado, "BLOQUEADO");
                break;
            default:
                printf("ERRO. Você inseriu o número do estado que você quer? Tente novamente.\n");
        }
    }while(localInput != 1 && localInput != 2 && localInput != 3 && localInput != 4);

    printf("\n\nOperador cadastrado com sucesso!\n");
    system("pause");

    return op;
}


// ========== MAIN ==========


int main() {
    Equipamentos equipamentos[150], equipamentoTemp;

    int input;
    int shutdown = 0;

    setlocale(LC_ALL, "portuguese");

    while(!shutdown){
        printDashboard();
        input = scanfInput();

        switch(input){
            case 1:
                cadastroOp();
                break;

            case 2:
                registrarEquipamento();
                break;

            case 3:
                //atualizarDados();
                break;

            case 4:
                //consultarRegistros();
                break;

            case 5:
                //relatoriosOp();
                break;

            case 6:
                shutdown = 1;
                break;

            default:
                printf("Comando inválido!");
                system("pause");
                system("cls");
            }
    }
    return 0;
}
