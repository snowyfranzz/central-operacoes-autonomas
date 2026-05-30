#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
/*
    Operador operadores[50];
    Equipamento equipamentos[150], equipamentoTemp;
    int Nequipamentos, input, i;
*/

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

void pause() {
    printf("\nAperte ENTER para continuar. ");
    limpaBuffer();
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

void printEquipamento(Equipamentos equipamento) {
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

int verificaIdUnicoEquipamento(char idAtual[], Equipamentos listaStruct[], int listaSize){
    int i;

    for (i = 0; i < listaSize; i++) {
        if (strcmp(idAtual, listaStruct[i].ID) == 0) {
            return 0;
        }
    }

    return 1;
}

int verificaIdUnicoOperador(char idAtual[], Operadores listaStruct[], int listaSize){
    int i;

    for (i = 0; i < listaSize; i++) {
        if (strcmp(idAtual, listaStruct[i].ID) == 0) {
            return 0;
        }
    }

    return 1;
}

// DASHBOARD
void printDashboard(Operadores operadores[], int nOperadores, Equipamentos equipamentos[], int nEquipamentos) {
    system("cls || clear");
    printf("+------------------------------------------------------------------------------+\n");
    printf("|               Orbytec Sistemas Integrados - Setor VX27 - Dashboard           |\n");
    printf("+-------------------------+--------------------------+-------------------------+\n");
    printf("|  Ocorrências Recentes:  |    Operadores Ativos:    |   Equipamentos Ativos:  |\n");
    printf("|=========================|==========================|=========================|\n");

    for (int i = 0; i < 10; i++) {

        // OCORRENCIAS
        // vazia por agora -> esperando a implementacao das ocorrencias
        printf("| %-23s ", "");

        // OPERADORES ATIVOS
        printf("| ");
        if (i < nOperadores) {
            printf("%s - %s", operadores[i].ID, operadores[i].estado);

            int espacoGasto = strlen(operadores[i].ID) + strlen(operadores[i].estado) + 3;
            int espacoRestante = 24 - espacoGasto;

            for (int j = 0; j < espacoRestante; j++) {
                printf(" ");
            }
        } else {
            printf("%-24s", "");
        }
        printf(" ");

        // EQUIPAMENTOS ATIVOS
        printf("| ");
        if (i < nEquipamentos) {
            printf("%s - %s", equipamentos[i].ID, equipamentos[i].estado);

            int espacoGasto = strlen(equipamentos[i].ID) + strlen(equipamentos[i].estado) + 3;
            int espacoRestante = 23 - espacoGasto;

            for (int j = 0; j < espacoRestante; j++) {
                printf(" ");
            }
        } else {
            printf("%-23s", "");
        }
        printf(" |\n");
    }

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

Equipamentos registrarEquipamento(Equipamentos equipamentos[], int nEquipamentos) {
    Equipamentos equipamento, equipamentoTemp;
    int input;

    //pega  guarda o ID do usuario
    do {
        //le um string
        system("cls || clear");
        printf("Cadastro de equipamento:\n\n");
        printf("> ID do equipamento (1 Letra, 2 Dígitos): ");
        readString(equipamentoTemp.ID, sizeof(equipamentoTemp.ID));

        //verifica se for valido
        if (verificar(equipamentoTemp.ID, sizeof(equipamentoTemp.ID), 0)) {
            if (verificaIdUnicoEquipamento(equipamentoTemp.ID, equipamentos, nEquipamentos)) {
                strcpy(equipamento.ID, equipamentoTemp.ID);
            } else {
                printf("\nID já cadastrado\n\n");
                pause();
            }
        } else {
            printf("\nID Inválido\n\n");
            pause();
        }
    } while (!verificar(equipamentoTemp.ID, sizeof(equipamentoTemp.ID), 0) || !verificaIdUnicoEquipamento(equipamentoTemp.ID, equipamentos, nEquipamentos));

    //pega e guarda o tipo de equipamento
    do {
        //le numero inteiro
        input = 0;

        system("cls || clear");
        printf("Categorias Operacionais:\n\n\t");
        printf("1. AGV\n\t");
        printf("2. BRACO_ARTICULADO\n\t");
        printf("3. ESTEIRAS\n\t");
        printf("4. SORTERS\n\t");
        printf("5. TRANSELEVADOR\n\t\n> Categoria: ");
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
                pause();

        }
    } while (input < 1 || input > 5);

    //pega e guarda o setor
    do {
        //le string
        system("cls || clear");
        printf("> Setor (2 Letras, 2 Dígitos): ");
        readString(equipamentoTemp.setorAssociado, sizeof(equipamentoTemp.setorAssociado));

        //verifica se eh valido
        if (verificar(equipamentoTemp.setorAssociado, sizeof(equipamentoTemp.setorAssociado), 0)) {
            strcpy(equipamento.setorAssociado, equipamentoTemp.setorAssociado);
        } else {
            printf("\nSetor Inválido\n\n");
            pause();
        }
    } while (!verificar(equipamentoTemp.setorAssociado, sizeof(equipamentoTemp.setorAssociado), 0));

    //pega e guarda o estado
    do {
        //le numero inteiro
        input = 0;

        system("cls || clear");
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
                pause();

        }
    } while (input < 1 || input > 3);

    //pega e guarda o ID do operador
    do {
        //le string
        system("cls || clear");
        printf("> ID do Operador Associado (4 Dígitos): ");
        readString(equipamentoTemp.IDo, sizeof(equipamentoTemp.IDo));

        //verifica se eh valido
        if (verificar(equipamentoTemp.IDo, sizeof(equipamentoTemp.IDo), 1)) {
            strcpy(equipamento.IDo, equipamentoTemp.IDo);
        } else {
            printf("\nID Inválido\n\n");
            pause();
        }
    } while (!verificar(equipamentoTemp.IDo, sizeof(equipamentoTemp.IDo), 1));

    //pega e guarda a prioridade
    do {
        //le numero inteiro
        input = 0;

        system("cls || clear");
        printf("> Nível de Prioridade (1. BAIXA, 2. MEDIA, 3. ALTA): ");
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
                pause();

        }
    } while (input < 1 || input > 3);

    return equipamento;
}

// CADASTRO DE OPERADOR
Operadores registrarOperador(Operadores operadores[], int nOperadores){
    Operadores op;
    int localInput = 0;
    int len = 0;

    system("cls || clear");

    printf("Cadastro de Operador:\n\n");
    do {
        system("cls");

        printf("> ID do Operador (4 Dígitos, outros serão desconsiderados):  ");
        readString(op.ID, sizeof(op.ID));

        if (verificar(op.ID, sizeof(op.ID), 1)) {
            if (!verificaIdUnicoOperador(op.ID, operadores, nOperadores)) {
                printf("\nID já cadastrado!\n\n");
                pause();
            }
        } else {
            printf("\nID Inválido!\n\n");
            pause();
        }
    } while ((!verificar(op.ID, sizeof(op.ID), 1)) || (!verificaIdUnicoOperador(op.ID, operadores, nOperadores)));

    system("cls");
    printf("> Nome do Operador (Máximo de 70 Caractéres): ");
    readString(op.nome, sizeof(op.nome));

    do {
        system("cls");
        printf("> Setor (2 Letras, 2 Dígitos - outros serão desconsiderados): ");
        readString(op.setorAssociado, sizeof(op.setorAssociado));

        if (!verificar(op.setorAssociado, sizeof(op.setorAssociado), 0)) {
            printf("\nSetor Inválido!\n\n");
            pause();
        }
    } while (!verificar(op.setorAssociado, sizeof(op.setorAssociado), 0));

    do {
        system("cls");
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
                system("pause");
        }

    }while(localInput != 1 && localInput != 2 && localInput != 3);


    do {
        system("cls");
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
                system("pause");
        }
    }while(localInput != 1 && localInput != 2 && localInput != 3 && localInput != 4);

    printf("\n\nOperador cadastrado com sucesso!\n");
    pause();

    return op;
}


// ========== MAIN ==========
int main() {
    Equipamentos equipamentos[150], equipamentoTemp;
    Operadores operadores[50], operadorTemp;

    int nEquipamentos = 0, nOperadores = 0, equipamentoEscolhido = -1, operadorEscolhido = -1;
    int input, shutdown = 0, i;

    setlocale(LC_ALL, "portuguese");

    while(!shutdown){
        printDashboard(operadores, nOperadores, equipamentos, nEquipamentos);
        input = scanfInput();

        switch(input){
            case 1:
                if (nOperadores < 50){
                    operadores[nOperadores] = registrarOperador(operadores, nOperadores);
                    nOperadores++;
                } else {
                    printf("ERRO: O número máximo de operadores (50) já foi registrado!");
                    pause();
                    system("cls || clear");
                }

                break;

            case 2:
                if (nEquipamentos < 150){
                    equipamentos[nEquipamentos] = registrarEquipamento(equipamentos, nEquipamentos);
                    nEquipamentos++;
                } else {
                    printf("ERRO: O número máximo de equipamentos (150) já foi registrado!");
                    pause();
                    system("cls || clear");
                }
                break;

            case 3:
                do {
                    system("cls");
                    input = 0;
                    printf("Escolha o que atualizar:\n\n1: Estado Operacional de um Equipamento\n2: Disponibilidade de Operadores\n3: Setor de um Equipamento\n4: Registrar Ocorrencias\n5: Desativar Registros\n6: Voltar\n\n> ");
                    readInt(&input);
                    switch(input) {
                        case 1:
                            if (nEquipamentos > 0) {
                                do {
                                    system("cls");

                                    equipamentoEscolhido = -1;

                                    printf("Escreva o ID do equipamento que você quer modificar: ");
                                    readString(equipamentoTemp.ID, sizeof(equipamentoTemp.ID));

                                    for (i = 0; i < nEquipamentos; i++) {
                                        if (strcmp(equipamentos[i].ID, equipamentoTemp.ID) == 0) {
                                            equipamentoEscolhido = i;
                                            break;
                                        }

                                        if (i + 1 == nEquipamentos) {
                                            printf("\nID INVALIDO\n\n");
                                            system("pause");
                                        }
                                    }
                                } while (equipamentoEscolhido == -1);

                                do {
                                    //le numero inteiro
                                    input = 0;

                                    system("cls");
                                    printf("Qual é o Novo Estado Operacional do equipamento? \n\n\t");
                                    printf("1: Ativo\n\t");
                                    printf("2: Inativo\n\t");
                                    printf("3: Manutenção\n\n> ");
                                    readInt(&input);

                                    //verifica o numero
                                    switch(input) {
                                        case 1:
                                            strcpy(equipamentos[equipamentoEscolhido].estado, "ATIVO");
                                            break;
                                        case 2:
                                            strcpy(equipamentos[equipamentoEscolhido].estado, "INATIVO");
                                            break;
                                        case 3:
                                            strcpy(equipamentos[equipamentoEscolhido].estado, "MANUTENCAO");
                                            break;
                                        default:
                                            printf("\nINPUT INVALIDO\n\n");
                                            system("pause");

                                    }
                                } while (input < 1 || input > 3);
                            } else {
                                printf("\nNão existem equipamentos ainda\n\n");
                                system("pause");
                            }
                            break;
                        case 2:
                            if (nOperadores > 0) {
                                do {
                                    system("cls");

                                    operadorEscolhido = -1;

                                    printf("Escreva o ID do operador que você quer modificar: ");
                                    readString(operadorTemp.ID, sizeof(operadorTemp.ID));

                                    for (i = 0; i < nOperadores; i++) {
                                        if (strcmp(operadores[i].ID, operadorTemp.ID) == 0) {
                                            operadorEscolhido = i;
                                            break;
                                        }

                                        if (i + 1 == nOperadores) {
                                            printf("\nID INVALIDO\n\n");
                                            system("pause");
                                        }
                                    }
                                } while (operadorEscolhido == -1);

                                do {
                                    //le numero inteiro
                                    input = 0;

                                    system("cls");
                                    printf("Qual é o novo status do operador? \n\n\t");
                                    printf("1: Ativo\n\t");
                                    printf("2: Ocupado\n\t");
                                    printf("3: Inativo\n\t ");
                                    printf("4: Bloqueado\n\n> ");
                                    readInt(&input);

                                    //verifica o numero
                                    switch(input) {
                                        case 1:
                                            strcpy(operadores[0].estado, "ATIVO");
                                            break;
                                        case 2:
                                            strcpy(operadores[0].estado, "Ocupado");
                                            break;
                                        case 3:
                                            strcpy(operadores[0].estado, "Inativo");
                                            break;
                                        case 4:
                                            strcpy(operadores[0].estado, "Bloqueado");
                                            break;
                                        default:
                                            printf("\nINPUT INVALIDO\n\n");
                                            system("pause");

                                    }
                                } while (input < 1 || input > 3);
                            } else {
                                printf("\nNão existem operadores ainda\n\n");
                                system("pause");
                            }
                            break;
                        case 3:
                            if (nEquipamentos > 0) {
                                do {
                                    system("cls");

                                    equipamentoEscolhido = -1;

                                    printf("Escreva o ID do equipamento que você quer modificar: ");
                                    readString(equipamentoTemp.ID, sizeof(equipamentoTemp.ID));

                                    for (i = 0; i < nEquipamentos; i++) {
                                        if (strcmp(equipamentos[i].ID, equipamentoTemp.ID) == 0) {
                                            equipamentoEscolhido = i;
                                            break;
                                        }

                                        if (i + 1 == nEquipamentos) {
                                            printf("\nID INVALIDO\n\n");
                                            system("pause");
                                        }
                                    }
                                } while (equipamentoEscolhido == -1);

                                //pega e guarda o setor
                                do {
                                    //le string
                                    system("cls");
                                    printf("Escreva o novo Setor Associado ao equipamento: ");
                                    readString(equipamentoTemp.setorAssociado, sizeof(equipamentoTemp.setorAssociado));

                                    //verifica se eh valido
                                    if (verificar(equipamentoTemp.setorAssociado, sizeof(equipamentoTemp.setorAssociado), 0)) {
                                        strcpy(equipamentos[0].setorAssociado, equipamentoTemp.setorAssociado);
                                    } else {
                                        printf("\nSetor Inválido\n\n");
                                        system("pause");
                                    }
                                } while (!verificar(equipamentoTemp.setorAssociado, sizeof(equipamentoTemp.setorAssociado), 0));
                            } else {
                                printf("\nNão existem equipamentos ainda\n\n");
                                system("pause");
                            }
                            break;
                        case 4:
                            break;
                        case 5:
                            break;
                        case 6:
                            break;
                        default:
                            printf("\nINVALIDO\n\n");
                            system("pause");
                    }
                } while (input != 6);
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
                pause();
                system("cls || clear");
            }
    }
    return 0;
}
