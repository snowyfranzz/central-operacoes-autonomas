#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>

#define MAXEQUIPAMENTOS 150
#define MAXOPERADORES 50

// ========== STRUCTS ==========

typedef struct setores {
    char setor[5];
} Setores;

typedef struct equipamentos {
    char ID[4];
    char tipo[17]; //AGV, braco-articulado, esteira, sorter, transelevador
    Setores setorAssociado;
    char estado[11];
    char IDo[5];
    char prioridade[6];
} Equipamentos;

typedef struct operadores {
    char ID[5];
    char nome[71];
    Setores setorAssociado;
    char nivelOp[14]; // BASICO, INTERMEDIARIO, SUPERVISOR
    char estado[10]; // ATIVO, OCUPADO, INATIVO, BLOQUEADO
    int quantOp;
} Operadores;

typedef struct ocorrencias {
    char ID[5];
    char emissor[17];
    char descricao[101];
} Ocorrencias;

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
    printf("\nSetor Associado: %s", equipamento.setorAssociado.setor);
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

int verificaIdUnicoOcorrencia(char idAtual[], Ocorrencias listaStruct[], int listaSize){
    int i;

    for (i = 0; i < listaSize; i++) {
        if (strcmp(idAtual, listaStruct[i].ID) == 0) {
            return 0;
        }
    }

    return 1;
}

int nivelOp(char nivel[]) {
    if (strcmp(nivel, "SUPERVISOR") == 0) {
        return 3;
    }
    if (strcmp(nivel, "INTERMEDIARIO") == 0) {
        return 2;
    }
    if (strcmp(nivel, "BASICO") == 0) {
        return 1;
    }
    return 0;
}

void sortOperadoresPorNivel(Operadores operadores[], int indices[], int tamanho) {
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = i + 1; j < tamanho; j++) {
            int rankA = nivelOp(operadores[indices[i]].nivelOp);
            int rankB = nivelOp(operadores[indices[j]].nivelOp);
            if (rankB > rankA || (rankA == rankB && strcmp(operadores[indices[i]].nome, operadores[indices[j]].nome) > 0)) {
                int temp = indices[i];
                indices[i] = indices[j];
                indices[j] = temp;
            }
        }
    }
}

// DASHBOARD
void printDashboard(Ocorrencias ocorrencias[], int nOcorrencias, Operadores operadores[], int nOperadores, Equipamentos equipamentos[], int nEquipamentos) {
    system("cls || clear");
    printf("+------------------------------------------------------------------------------+\n");
    printf("|               Orbytec Sistemas Integrados - Setor VX27 - Dashboard           |\n");
    printf("+-------------------------+--------------------------+-------------------------+\n");
    printf("|  Ocorrências Recentes:  |    Operadores Ativos:    |   Equipamentos Ativos:  |\n");
    printf("|=========================|==========================|=========================|\n");

    int operadoresAtivos[MAXOPERADORES];
    int nOperadoresAtivos = 0;

    for (int i = 0; i < nOperadores; i++) {
        if (strcmp(operadores[i].estado, "ATIVO") == 0) {
            operadoresAtivos[nOperadoresAtivos++] = i;
        }
    }

    sortOperadoresPorNivel(operadores, operadoresAtivos, nOperadoresAtivos);

    int maxLinhas = 10;
    int operadoresVisiveis = nOperadoresAtivos;
    int operadoresExcesso = 0;
    if (nOperadoresAtivos > maxLinhas) {
        operadoresVisiveis = maxLinhas - 1;
        operadoresExcesso = nOperadoresAtivos - operadoresVisiveis;
    }

    for (int i = 0; i < maxLinhas; i++) {
        // OCORRENCIAS
        printf("| ");
        if (i < nOcorrencias) {
            printf("%s - %s", ocorrencias[i].ID, ocorrencias[i].emissor);

            int espacoGasto = strlen(ocorrencias[i].ID) + strlen(ocorrencias[i].emissor) + 3;
            int espacoRestante = 23 - espacoGasto;

            for (int j = 0; j < espacoRestante; j++) {
                printf(" ");
            }
        } else {
            printf("%-23s", "");
        }
        printf(" ");

        // OPERADORES ATIVOS
        printf("| ");
        if (i < operadoresVisiveis) {
            int idx = operadoresAtivos[i];
            printf("%s - %s", operadores[idx].ID, operadores[idx].nivelOp);

            int espacoGasto = strlen(operadores[idx].ID) + strlen(operadores[idx].nivelOp) + 3;
            int espacoRestante = 24 - espacoGasto;
            for (int j = 0; j < espacoRestante; j++) {
                printf(" ");
            }
        } else if (operadoresExcesso > 0 && i == operadoresVisiveis) {
            char overflowTexto[25];
            snprintf(overflowTexto, sizeof(overflowTexto), "... Mais %d", operadoresExcesso);
            printf("%s", overflowTexto);

            int espacoGasto = strlen(overflowTexto);
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
        readString(equipamentoTemp.setorAssociado.setor, sizeof(equipamentoTemp.setorAssociado.setor));

        //verifica se eh valido
        if (verificar(equipamentoTemp.setorAssociado.setor, sizeof(equipamentoTemp.setorAssociado.setor), 0)) {
            strcpy(equipamento.setorAssociado.setor, equipamentoTemp.setorAssociado.setor);
        } else {
            printf("\nSetor Inválido\n\n");
            pause();
        }
    } while (!verificar(equipamentoTemp.setorAssociado.setor, sizeof(equipamentoTemp.setorAssociado.setor), 0));

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

Ocorrencias registrarOcorrencia(Ocorrencias ocorrencias[], int nOcorrencias){
    Ocorrencias ocorrencia;
    int localInput = 0;
    int len = 0;

    system("cls || clear");

    printf("Cadastro de Ocorrencia:\n\n");
    do {
        system("cls || clear");

        printf("> ID da Ocorrencia (4 Dígitos, outros serão desconsiderados):  ");
        readString(ocorrencia.ID, sizeof(ocorrencia.ID));

        if (verificar(ocorrencia.ID, sizeof(ocorrencia.ID), 1)) {
            if (!verificaIdUnicoOcorrencia(ocorrencia.ID, ocorrencias, nOcorrencias)) {
                printf("\nID já cadastrado!\n\n");
                pause();
            }
        } else {
            printf("\nID Inválido!\n\n");
            pause();
        }
    } while ((!verificar(ocorrencia.ID, sizeof(ocorrencia.ID), 1)) || (!verificaIdUnicoOcorrencia(ocorrencia.ID, ocorrencias, nOcorrencias)));

    system("cls || clear");
    printf("> Primeiro Nome do Emissor (Máximo de 16 Caractéres): ");
    readString(ocorrencia.emissor, sizeof(ocorrencia.emissor));

    system("cls || clear");
    printf("> Descrição da ocorrencia (Máximo de 100 caractéres): ");
    readString(ocorrencia.descricao, sizeof(ocorrencia.descricao));

    printf("\n\nOcorrencia cadastrada com sucesso!\n");
    pause();

    return ocorrencia;
}

Operadores registrarOperador(Operadores operadores[], int nOperadores){
    Operadores op;
    int localInput = 0;
    int len = 0;

    system("cls || clear");

    printf("Cadastro de Operador:\n\n");
    do {
        system("cls || clear");

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

    system("cls || clear");
    printf("> Nome do Operador (Máximo de 70 Caractéres): ");
    readString(op.nome, sizeof(op.nome));

    do {
        system("cls || clear");
        printf("> Setor (2 Letras, 2 Dígitos - outros serão desconsiderados): ");
        readString(op.setorAssociado.setor, sizeof(op.setorAssociado.setor));

        if (!verificar(op.setorAssociado.setor, sizeof(op.setorAssociado.setor), 0)) {
            printf("\nSetor Inválido!\n\n");
            pause();
        }
    } while (!verificar(op.setorAssociado.setor, sizeof(op.setorAssociado.setor), 0));

    do {
        system("cls || clear");
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
                pause();
        }

    }while(localInput != 1 && localInput != 2 && localInput != 3);


    do {
        system("cls || clear");
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
                pause();
        }
    }while(localInput != 1 && localInput != 2 && localInput != 3 && localInput != 4);

    printf("\n\nOperador cadastrado com sucesso!\n");
    pause();

    return op;
}

// ATUALIZAR DADOS DO SISTEMA
void atualizaDados(Equipamentos equipamentos[], int *nEquipamentos, Operadores operadores[], int *nOperadores, Ocorrencias ocorrencias[], int *nOcorrencias, Equipamentos equipamentoTemp, Operadores operadorTemp, Ocorrencias ocorrenciaTemp) {
    int input = 0;
    int i, equipamentoEscolhido = -1, operadorEscolhido = -1, ocorrenciaEscolhida = -1;

    do {
        system("cls || clear");
        input = 0;
        printf("Escolha o que atualizar:\n\n1: Estado Operacional de um Equipamento\n2: Disponibilidade de Operadores\n3: Setor de um Equipamento\n4: Registrar Ocorrencias\n5: Desativar Registros\n6: Voltar\n\n> ");
        readInt(&input);
        switch(input) {
            case 1:
                if (*nEquipamentos > 0) {
                    do {
                        system("cls || clear");

                        equipamentoEscolhido = -1;

                        printf("Escreva o ID do equipamento que você quer modificar: ");
                        readString(equipamentoTemp.ID, sizeof(equipamentoTemp.ID));

                        for (i = 0; i < *nEquipamentos; i++) {
                            if (strcmp(equipamentos[i].ID, equipamentoTemp.ID) == 0) {
                                equipamentoEscolhido = i;
                                break;
                            }

                            if (i + 1 == *nEquipamentos) {
                                printf("\nID INVALIDO\n\n");
                                pause();
                            }
                        }
                    } while (equipamentoEscolhido == -1);

                    do {
                        //le numero inteiro
                        input = 0;

                        system("cls || clear");
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
                                pause();

                        }
                    } while (input < 1 || input > 3);
                } else {
                    printf("\nNão existem equipamentos ainda\n\n");
                    pause();
                }
                break;
            case 2:
                if (*nOperadores > 0) {
                    do {
                        system("cls || clear");

                        operadorEscolhido = -1;

                        printf("Escreva o ID do operador que você quer modificar: ");
                        readString(operadorTemp.ID, sizeof(operadorTemp.ID));

                        for (i = 0; i < *nOperadores; i++) {
                            if (strcmp(operadores[i].ID, operadorTemp.ID) == 0) {
                                operadorEscolhido = i;
                                break;
                            }

                            if (i + 1 == *nOperadores) {
                                printf("\nID NAO ENCONTRADO\n\n");
                                pause();
                            }
                        }
                    } while (operadorEscolhido == -1);

                    do {
                        //le numero inteiro
                        input = 0;

                        system("cls || clear");
                        printf("Qual é o novo status do operador? \n\n\t");
                        printf("1: Ativo\n\t");
                        printf("2: Ocupado\n\t");
                        printf("3: Inativo\n\t ");
                        printf("4: Bloqueado\n\n> ");
                        readInt(&input);

                        //verifica o numero
                        switch(input) {
                            case 1:
                                strcpy(operadores[operadorEscolhido].estado, "ATIVO");
                                break;
                            case 2:
                                strcpy(operadores[operadorEscolhido].estado, "OCUPADO");
                                break;
                            case 3:
                                strcpy(operadores[operadorEscolhido].estado, "INATIVO");
                                break;
                            case 4:
                                strcpy(operadores[operadorEscolhido].estado, "BLOQUEADO");
                                break;
                            default:
                                printf("\nINPUT INVALIDO\n\n");
                                pause();

                        }
                    } while (input < 1 || input > 4);
                } else {
                    printf("\nNão existem operadores ainda\n\n");
                    pause();
                }
                break;
            case 3:
                if (*nEquipamentos > 0) {
                    do {
                        system("cls || clear");

                        equipamentoEscolhido = -1;

                        printf("Escreva o ID do equipamento que você quer modificar: ");
                        readString(equipamentoTemp.ID, sizeof(equipamentoTemp.ID));

                        for (i = 0; i < *nEquipamentos; i++) {
                            if (strcmp(equipamentos[i].ID, equipamentoTemp.ID) == 0) {
                                equipamentoEscolhido = i;
                                break;
                            }

                            if (i + 1 == *nEquipamentos) {
                                printf("\nID NAO ENCONTRADO\n\n");
                                pause();
                            }
                        }
                    } while (equipamentoEscolhido == -1);

                    //pega e guarda o setor
                    do {
                        //le string
                        system("cls || clear");
                        printf("Escreva o novo Setor Associado ao equipamento: ");
                        readString(equipamentoTemp.setorAssociado.setor, sizeof(equipamentoTemp.setorAssociado.setor));

                        //verifica se eh valido
                        if (verificar(equipamentoTemp.setorAssociado.setor, sizeof(equipamentoTemp.setorAssociado.setor), 0)) {
                            strcpy(equipamentos[equipamentoEscolhido].setorAssociado.setor, equipamentoTemp.setorAssociado.setor);
                        } else {
                            printf("\nSetor Inválido\n\n");
                            pause();
                        }
                    } while (!verificar(equipamentoTemp.setorAssociado.setor, sizeof(equipamentoTemp.setorAssociado.setor), 0));
                } else {
                    printf("\nNão existem equipamentos ainda\n\n");
                    pause();
                }
                break;
            case 4:
                do {
                    input = 0;
                    system("cls || clear");

                    printf("Escolha:\n\n");
                    printf("\t1: Registrar Ocorrencia\n");
                    printf("\t2: Remover Ocorrencia\n");
                    printf("\t3: Voltar\n\n> ");
                    readInt(&input);

                    switch(input) {
                        case 1:
                            if (*nOcorrencias < MAXEQUIPAMENTOS){
                                ocorrencias[*nOcorrencias] = registrarOcorrencia(ocorrencias, *nOcorrencias);
                                (*nOcorrencias)++;
                            } else {
                                printf("ERRO: O número máximo de ocorrencias (%2d) já foi registrado!", MAXEQUIPAMENTOS);
                                pause();
                                system("cls || clear");
                            }
                            break;
                        case 2:
                            if (*nOcorrencias > 0) {
                                system("cls || clear");

                                ocorrenciaEscolhida = -1;

                                printf("Escreva o ID da ocorrencia que você quer tirar do registro: ");
                                readString(ocorrenciaTemp.ID, sizeof(ocorrenciaTemp.ID));

                                for (i = 0; i < *nOcorrencias; i++) {
                                    if (strcmp(ocorrencias[i].ID, ocorrenciaTemp.ID) == 0) {
                                        ocorrenciaEscolhida = i;
                                        break;
                                    }

                                    if (i + 1 == *nOcorrencias) {
                                        printf("\nID NAO ENCONTRADO\n\n");
                                        pause();
                                    }
                                }

                                if (ocorrenciaEscolhida != -1) {
                                    for (i = ocorrenciaEscolhida; i < *nOcorrencias - 1; i++) {
                                        ocorrencias[i] = ocorrencias[i + 1];
                                    }
                                    (*nOcorrencias)--;
                                }
                            } else {
                                printf("\nNão existem ocorrencias ainda\n\n");
                                pause();
                            }
                            break;
                        case 3:
                            break;
                        default:
                            printf("\nINPUT INVALIDO\n\n");
                            pause();
                    }
                } while (input != 3);
                break;
            case 5:
                do {
                    system("cls || clear");
                    input = 0;

                    printf("1: Desativar Operador\n");
                    printf("2: Desativar Equipamento\n");
                    printf("3: Voltar\n\n> ");

                    readInt(&input);

                    switch(input) {
                        case 1:
                            if (*nOperadores > 0) {
                                system("cls || clear");

                                operadorEscolhido = -1;

                                printf("Escreva o ID do operador que você quer tirar do registro: ");
                                readString(operadorTemp.ID, sizeof(operadorTemp.ID));

                                for (i = 0; i < *nOperadores; i++) {
                                    if (strcmp(operadores[i].ID, operadorTemp.ID) == 0) {
                                        operadorEscolhido = i;
                                        break;
                                    }

                                    if (i + 1 == *nOperadores) {
                                        printf("\nID NAO ENCONTRADO\n\n");
                                        pause();
                                    }
                                }

                                if (operadorEscolhido != -1) {
                                    for (i = operadorEscolhido; i < *nOperadores - 1; i++) {
                                        operadores[i] = operadores[i + 1];
                                    }
                                    (*nOperadores)--;
                                }
                            } else {
                                printf("\nNão existem operadores ainda\n\n");
                                pause();
                            }
                            break;
                        case 2:
                            if (*nEquipamentos > 0) {
                                system("cls || clear");

                                equipamentoEscolhido = -1;

                                printf("Escreva o ID do equipamento que você quer tirar do registro: ");
                                readString(equipamentoTemp.ID, sizeof(equipamentoTemp.ID));

                                for (i = 0; i < *nEquipamentos; i++) {
                                    if (strcmp(equipamentos[i].ID, equipamentoTemp.ID) == 0) {
                                        equipamentoEscolhido = i;
                                        break;
                                    }

                                    if (i + 1 == *nEquipamentos) {
                                        printf("\nID NAO ENCONTRADO\n\n");
                                        pause();
                                    }
                                }

                                if (equipamentoEscolhido != -1) {
                                    for (i = equipamentoEscolhido; i < *nEquipamentos - 1; i++) {
                                        equipamentos[i] = equipamentos[i + 1];
                                    }
                                    (*nEquipamentos)--;
                                }
                            } else {
                                printf("\nNão existem equipamentos ainda\n\n");
                                pause();
                            }
                            break;
                        case 3:
                            break;
                        default:
                            printf("\nINPUT INVALIDO\n\n");
                            pause();
                    }
                } while (input != 3);
                break;
            case 6:
                break;
            default:
                printf("\nINVALIDO\n\n");
                pause();
        }
    } while (input != 6);
}

void consultarRegistros(Operadores operadores[], int nOperadores, Equipamentos equipamentos[], int nEquipamentos) {
    int input;

    do {
        input = 0;
        system("cls || clear");
        printf("+--------------------------------------------------+\n");
        printf("|           Consulta de Registros                  |\n");
        printf("+--------------------------------------------------+\n");
        printf("| 1. Pesquisar Operador por Nome                   |\n");
        printf("| 2. Pesquisar Operador por ID                     |\n");
        printf("| 3. Pesquisar Estado Operacional de Equipamento   |\n");
        printf("| 4. Operadores livres para um Setor/Equipamento   |\n");
        printf("| 5. Voltar                                        |\n");
        printf("+--------------------------------------------------+\n");
        printf("> ");
        readInt(&input);

        switch (input) {

            // ── 1. BUSCA POR NOME ──────────────────────────────
            case 1: {
                char busca[71];
                int encontrou = 0, i;

                system("cls || clear");
                printf("Nome (ou parte do nome) do Operador: ");
                readString(busca, sizeof(busca));

                // converte busca para maiusculo para comparacao case-insensitive
                for (i = 0; busca[i]; i++) busca[i] = toupper(busca[i]);

                printf("\n%-6s %-71s %-5s %-14s %-10s %-5s\n",
                       "ID", "Nome", "Setor", "Nivel", "Estado", "Ops");
                printf("------------------------------------------------------------------------\n");

                for (i = 0; i < nOperadores; i++) {
                    // copia nome em maiusculo para comparar
                    char nomeUpper[71];
                    int j;
                    strcpy(nomeUpper, operadores[i].nome);
                    for (j = 0; nomeUpper[j]; j++) nomeUpper[j] = toupper(nomeUpper[j]);

                    if (strstr(nomeUpper, busca) != NULL) {
                        printf("%-6s %-71s %-5s %-14s %-10s %-5d\n",
                               operadores[i].ID,
                               operadores[i].nome,
                               operadores[i].setorAssociado.setor,
                               operadores[i].nivelOp,
                               operadores[i].estado,
                               operadores[i].quantOp);
                        encontrou = 1;
                    }
                }

                if (!encontrou) {
                    printf("\nNenhum operador encontrado com esse nome.\n");
                }

                pause();
                break;
            }

            // ── 2. BUSCA POR ID ────────────────────────────────
            case 2: {
                char buscaID[5];
                int encontrou = 0, i;

                system("cls || clear");
                printf("ID do Operador (4 digitos): ");
                readString(buscaID, sizeof(buscaID));

                for (i = 0; i < nOperadores; i++) {
                    if (strcmp(operadores[i].ID, buscaID) == 0) {
                        printf("\n+------------------------------------------+\n");
                        printf("| Operador encontrado:                     |\n");
                        printf("+------------------------------------------+\n");
                        printf("  ID         : %s\n", operadores[i].ID);
                        printf("  Nome       : %s\n", operadores[i].nome);
                        printf("  Setor      : %s\n", operadores[i].setorAssociado.setor);
                        printf("  Nivel      : %s\n", operadores[i].nivelOp);
                        printf("  Estado     : %s\n", operadores[i].estado);
                        printf("  Operacoes  : %d\n", operadores[i].quantOp);
                        encontrou = 1;
                        break;
                    }
                }

                if (!encontrou) {
                    printf("\nOperador com ID '%s' nao encontrado.\n", buscaID);
                }

                pause();
                break;
            }

            // ── 3. ESTADO DE UM EQUIPAMENTO ───────────────────
            case 3: {
                char buscaEq[4];
                int encontrou = 0, i;

                system("cls || clear");
                printf("ID do Equipamento (1 letra + 2 digitos): ");
                readString(buscaEq, sizeof(buscaEq));

                for (i = 0; i < nEquipamentos; i++) {
                    if (strcmp(equipamentos[i].ID, buscaEq) == 0) {
                        printf("\n+------------------------------------------+\n");
                        printf("| Equipamento encontrado:                  |\n");
                        printf("+------------------------------------------+\n");
                        printf("  ID              : %s\n", equipamentos[i].ID);
                        printf("  Tipo            : %s\n", equipamentos[i].tipo);
                        printf("  Setor           : %s\n", equipamentos[i].setorAssociado.setor);
                        printf("  Estado          : %s\n", equipamentos[i].estado);
                        printf("  Operador Assoc. : %s\n", equipamentos[i].IDo);
                        printf("  Prioridade      : %s\n", equipamentos[i].prioridade);
                        encontrou = 1;
                        break;
                    }
                }

                if (!encontrou) {
                    printf("\nEquipamento com ID '%s' nao encontrado.\n", buscaEq);
                }

                pause();
                break;
            }

            // ── 4. OPERADORES LIVRES PARA UM SETOR/EQUIPAMENTO ─
            case 4: {
                char buscaSetor[5];
                char buscaEqID[4];
                int encontrou = 0, i;
                char nivelNecessario[14] = "";

                system("cls || clear");
                printf("Setor de interesse (2 letras + 2 digitos): ");
                readString(buscaSetor, sizeof(buscaSetor));

                // converte para maiusculo
                for (i = 0; buscaSetor[i]; i++) buscaSetor[i] = toupper(buscaSetor[i]);

                // verifica se o setor existe nos equipamentos e descobre a prioridade
                printf("\nID do Equipamento para verificar prioridade (ou ENTER para ignorar): ");
                readString(buscaEqID, sizeof(buscaEqID));

                if (strlen(buscaEqID) > 0) {
                    for (i = 0; i < nEquipamentos; i++) {
                        if (strcmp(equipamentos[i].ID, buscaEqID) == 0) {
                            // equipamento de prioridade ALTA exige nivel SUPERVISOR ou INTERMEDIARIO
                            // equipamento de prioridade MEDIA exige INTERMEDIARIO ou SUPERVISOR
                            // equipamento de prioridade BAIXA aceita qualquer nivel
                            if (strcmp(equipamentos[i].prioridade, "ALTA") == 0) {
                                strcpy(nivelNecessario, "SUPERVISOR");
                                printf("\nEquipamento de prioridade ALTA — necessario nivel SUPERVISOR.\n");
                            } else if (strcmp(equipamentos[i].prioridade, "MEDIA") == 0) {
                                strcpy(nivelNecessario, "INTERMEDIARIO");
                                printf("\nEquipamento de prioridade MEDIA — necessario nivel INTERMEDIARIO ou SUPERVISOR.\n");
                            } else {
                                printf("\nEquipamento de prioridade BAIXA — qualquer nivel aceito.\n");
                            }
                            break;
                        }
                    }
                }

                printf("\nOperadores disponiveis (ATIVO) no setor %s:\n", buscaSetor);
                printf("\n%-6s %-30s %-14s %-5s\n", "ID", "Nome", "Nivel", "Ops");
                printf("------------------------------------------------------------\n");

                for (i = 0; i < nOperadores; i++) {
                    char setorUpper[5];
                    int j;
                    strcpy(setorUpper, operadores[i].setorAssociado.setor);
                    for (j = 0; setorUpper[j]; j++) setorUpper[j] = toupper(setorUpper[j]);

                    // operador deve estar ATIVO e no setor correto
                    if (strcmp(operadores[i].estado, "ATIVO") != 0) continue;
                    if (strcmp(setorUpper, buscaSetor) != 0) continue;

                    // filtra por nivel se ha exigencia
                    if (strlen(nivelNecessario) > 0) {
                        if (strcmp(nivelNecessario, "SUPERVISOR") == 0) {
                            if (strcmp(operadores[i].nivelOp, "SUPERVISOR") != 0) continue;
                        } else if (strcmp(nivelNecessario, "INTERMEDIARIO") == 0) {
                            if (strcmp(operadores[i].nivelOp, "BASICO") == 0) continue;
                        }
                    }

                    printf("%-6s %-30s %-14s %-5d\n",
                           operadores[i].ID,
                           operadores[i].nome,
                           operadores[i].nivelOp,
                           operadores[i].quantOp);
                    encontrou = 1;
                }

                if (!encontrou) {
                    printf("\nNenhum operador disponivel encontrado para esse setor/equipamento.\n");
                }

                pause();
                break;
            }

            case 5:
                break;

            default:
                printf("\nOpcao invalida!\n");
                pause();
        }

    } while (input != 5);
}

// ========== MAIN ==========
int main() {
    int input, shutdown = 0, i, j;
    int nOperadores = 0, nEquipamentos = 0, nOcorrencias = 0;
    Operadores operadores[MAXOPERADORES], operadorTemp = {{0}};
    Equipamentos equipamentos[MAXEQUIPAMENTOS], equipamentoTemp = {{0}};
    Ocorrencias ocorrencias[MAXEQUIPAMENTOS], ocorrenciaTemp = {{0}};

    setlocale(LC_ALL, "portuguese");

    while(!shutdown){

        //reorganiza os Equipamentos em base a prioridade
        if (nEquipamentos > 0) {
            for (i = 0; i < nEquipamentos; i++) {
                for (j = nEquipamentos - 1; j > i; j--) {
                    if (strcmp(equipamentos[j].prioridade, "ALTA") == 0 && strcmp(equipamentos[i].prioridade, "ALTA") != 0) {
                        equipamentoTemp = equipamentos[i];
                        equipamentos[i] = equipamentos[j];
                        equipamentos[j] = equipamentoTemp;
                    }
                }
            }

            for (i = 0; i < nEquipamentos; i++) {
                for (j = nEquipamentos - 1; j > i; j--) {
                    if (strcmp(equipamentos[j].prioridade, "MEDIA") == 0 && strcmp(equipamentos[i].prioridade, "MEDIA") != 0 && strcmp(equipamentos[i].prioridade, "ALTA") != 0) {
                        equipamentoTemp = equipamentos[i];
                        equipamentos[i] = equipamentos[j];
                        equipamentos[j] = equipamentoTemp;
                    }
                }
            }
        }

        printDashboard(ocorrencias, nOcorrencias, operadores, nOperadores, equipamentos, nEquipamentos);
        input = scanfInput();

        switch(input){
            case 1:
                if (nOperadores < MAXOPERADORES){
                    operadores[nOperadores] = registrarOperador(operadores, nOperadores);
                    nOperadores++;
                } else {
                    printf("ERRO: O número máximo de operadores (%2d) já foi registrado!", MAXOPERADORES);
                    pause();
                    system("cls || clear");
                }

                break;

            case 2:
                if (nEquipamentos < MAXEQUIPAMENTOS){
                    equipamentos[nEquipamentos] = registrarEquipamento(equipamentos, nEquipamentos);
                    nEquipamentos++;
                } else {
                    printf("ERRO: O número máximo de equipamentos (%3d) já foi registrado!",MAXEQUIPAMENTOS);
                    pause();
                    system("cls || clear");
                }
                break;

            case 3:
                atualizaDados(equipamentos, &nEquipamentos, operadores, &nOperadores, ocorrencias, &nOcorrencias, equipamentoTemp, operadorTemp, ocorrenciaTemp);
                break;

            case 4:
                consultarRegistros(operadores, nOperadores, equipamentos, nEquipamentos);
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
