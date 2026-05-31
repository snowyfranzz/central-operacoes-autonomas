#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>

#define MAXEQUIPAMENTOS 150
#define MAXOPERADORES 50

typedef struct setores {
    char setor[5];
} Setores;

typedef struct equipamentos {
    char ID[4];
    char tipo[17];
    Setores setorAssociado;
    char estado[11];
    char IDo[5];
    char prioridade[6];
} Equipamentos;

typedef struct operadores {
    char ID[5];
    char nome[71];
    Setores setorAssociado;
    char nivelOp[14];
    char estado[10];
    int quantOp;
} Operadores;

typedef struct ocorrencias {
    char ID[5];
    char emissor[17];
    char descricao[101];
} Ocorrencias;



void limpaBuffer() {
    int c;
    while (c = getchar() != '\n' && c != EOF);
}

void pause() {
    printf("\nAperte ENTER para continuar. ");
    limpaBuffer();
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

void printEquipamento(Equipamentos equipamento) {
    printf("\nID: %s", equipamento.ID);
    printf("\nTipo: %s", equipamento.tipo);
    printf("\nSetor Associado: %s", equipamento.setorAssociado.setor);
    printf("\nEstado Operacional: %s", equipamento.estado);
    printf("\nID do Operador: %s", equipamento.IDo);
    printf("\nPrioridade: %s", equipamento.prioridade);
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


int verificar(char s[], int size, int numOnly) {
    int i, success = 0;

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
    int i = 0;
    int j = 0;
    int rankA = 0;
    int rankB = 0;
    int temp = 0;

    for (i = 0; i < tamanho - 1; i++) {
        for (j = i + 1; j < tamanho; j++) {
            rankA = nivelOp(operadores[indices[i]].nivelOp);
            rankB = nivelOp(operadores[indices[j]].nivelOp);
            if (rankB > rankA || (rankA == rankB && strcmp(operadores[indices[i]].nome, operadores[indices[j]].nome) > 0)) {
                temp = indices[i];
                indices[i] = indices[j];
                indices[j] = temp;
            }
        }
    }
}


void printDashboard(Ocorrencias ocorrencias[], int nOcorrencias, Operadores operadores[], int nOperadores, Equipamentos equipamentos[], int nEquipamentos) {
    system("cls || clear");
    printf("+------------------------------------------------------------------------------+\n");
    printf("|               Orbytec Sistemas Integrados - Setor VX27 - Dashboard           |\n");
    printf("+-------------------------+--------------------------+-------------------------+\n");
    printf("|  Ocorrências Recentes:  |    Operadores Ativos:    |   Equipamentos Ativos:  |\n");
    printf("|=========================|==========================|=========================|\n");

    int operadoresAtivos[MAXOPERADORES];
    int nOperadoresAtivos = 0;
    int i = 0;
    int j = 0;
    int k = 0;
    int maxLinhas = 10;
    int operadoresVisiveis = 0;
    int operadoresExcesso = 0;
    int espacoGasto = 0;
    int espacoRestante = 0;
    int digits = 0;

    for (i = 0; i < nOperadores; i++) {
        if (strcmp(operadores[i].estado, "ATIVO") == 0) {
            operadoresAtivos[nOperadoresAtivos++] = i;
        }
    }

    sortOperadoresPorNivel(operadores, operadoresAtivos, nOperadoresAtivos);

    operadoresVisiveis = nOperadoresAtivos;
    operadoresExcesso = 0;
    if (nOperadoresAtivos > maxLinhas) {
        operadoresVisiveis = maxLinhas - 1;
        operadoresExcesso = nOperadoresAtivos - operadoresVisiveis;
    }

    char ocorrenciaLines[10][24];
    int nOcorrenciaLines = 0;
    char textoLinha[24] = "";
    char descricao[101] = "";
    int lineLen = 0;
    int lastSpace = -1;
    int descPos = 0;
    int ocorrenciasVisiveis = 0;
    int ocorrenciasExcesso = 0;
    int countLen = 0;
    int temp = 0;
    char countText[4];

    for (k = nOcorrencias - 1; k >= 0 && nOcorrenciaLines < maxLinhas; k--) {
        textoLinha[0] = '\0';
        strcpy(textoLinha, ocorrencias[k].ID);
        strcat(textoLinha, " - ");
        strcat(textoLinha, ocorrencias[k].emissor);
        textoLinha[23] = '\0';
        strcpy(ocorrenciaLines[nOcorrenciaLines++], textoLinha);

        strcpy(descricao, ocorrencias[k].descricao);
        descPos = 0;

        while (descricao[descPos] != '\0' && nOcorrenciaLines < maxLinhas) {
            while (descricao[descPos] == ' ') {
                descPos++;
            }
            if (descricao[descPos] == '\0') {
                break;
            }
            lineLen = 0;
            lastSpace = -1;
            while (descricao[descPos + lineLen] != '\0' && lineLen < 23) {
                if (descricao[descPos + lineLen] == ' ') {
                    lastSpace = lineLen;
                }
                lineLen++;
            }

            if (descricao[descPos + lineLen] == '\0') {
                for (j = 0; j < lineLen; j++) {
                    textoLinha[j] = descricao[descPos + j];
                }
                textoLinha[lineLen] = '\0';
                descPos += lineLen;
            } else if (lastSpace > 0) {
                for (j = 0; j < lastSpace; j++) {
                    textoLinha[j] = descricao[descPos + j];
                }
                textoLinha[lastSpace] = '\0';
                descPos += lastSpace;
                while (descricao[descPos] == ' ') {
                    descPos++;
                }
            } else {
                for (j = 0; j < 23; j++) {
                    textoLinha[j] = descricao[descPos + j];
                }
                textoLinha[23] = '\0';
                descPos += 23;
            }

            strcpy(ocorrenciaLines[nOcorrenciaLines++], textoLinha);
        }

        ocorrenciasVisiveis++;
    }

    ocorrenciasExcesso = nOcorrencias - ocorrenciasVisiveis;
    if (ocorrenciasExcesso > 0) {
        countLen = 0;
        temp = ocorrenciasExcesso;
        while (temp > 0 && countLen < 3) {
            countText[countLen++] = '0' + (temp % 10);
            temp /= 10;
        }
        if (countLen == 0) {
            countText[countLen++] = '0';
        }
        for (j = 0; j < countLen / 2; j++) {
            char swap = countText[j];
            countText[j] = countText[countLen - 1 - j];
            countText[countLen - 1 - j] = swap;
        }
        countText[countLen] = '\0';

        textoLinha[0] = '.';
        textoLinha[1] = '.';
        textoLinha[2] = '.';
        textoLinha[3] = ' ';
        textoLinha[4] = 'M';
        textoLinha[5] = 'a';
        textoLinha[6] = 'i';
        textoLinha[7] = 's';
        textoLinha[8] = ' ';
        for (j = 0; j < countLen; j++) {
            textoLinha[9 + j] = countText[j];
        }
        textoLinha[9 + countLen] = '\0';

        if (nOcorrenciaLines < maxLinhas) {
            strcpy(ocorrenciaLines[nOcorrenciaLines++], textoLinha);
        } else {
            strcpy(ocorrenciaLines[maxLinhas - 1], textoLinha);
        }
    }

    for (i = 0; i < maxLinhas; i++) {

        printf("| ");
        if (i < nOcorrenciaLines) {
            printf("%-23s", ocorrenciaLines[i]);
        } else {
            printf("%-23s", "");
        }
        printf(" ");


        printf("| ");
        if (i < operadoresVisiveis) {
            k = operadoresAtivos[i];
            printf("%s - %s", operadores[k].ID, operadores[k].nivelOp);

            espacoGasto = strlen(operadores[k].ID) + strlen(operadores[k].nivelOp) + 3;
            espacoRestante = 24 - espacoGasto;
            for (j = 0; j < espacoRestante; j++) {
                printf(" ");
            }
        } else if (operadoresExcesso > 0 && i == operadoresVisiveis) {
            printf("... Mais %d", operadoresExcesso);
            digits = operadoresExcesso < 10 ? 1 : operadoresExcesso < 100 ? 2 : 3;
            espacoGasto = 9 + digits;
            espacoRestante = 24 - espacoGasto;
            for (j = 0; j < espacoRestante; j++) {
                printf(" ");
            }
        } else {
            printf("%-24s", "");
        }
        printf(" ");


        printf("| ");
        if (i < nEquipamentos) {
            printf("%s - %s", equipamentos[i].ID, equipamentos[i].estado);

            espacoGasto = strlen(equipamentos[i].ID) + strlen(equipamentos[i].estado) + 3;
            espacoRestante = 23 - espacoGasto;

            for (j = 0; j < espacoRestante; j++) {
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


    do {

        system("cls || clear");
        printf("Cadastro de equipamento:\n\n");
        printf("> ID do equipamento (1 Letra, 2 Dígitos): ");
        readString(equipamentoTemp.ID, sizeof(equipamentoTemp.ID));


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


    do {

        input = 0;

        system("cls || clear");
        printf("Categorias Operacionais:\n\n\t");
        printf("1. AGV\n\t");
        printf("2. BRACO_ARTICULADO\n\t");
        printf("3. ESTEIRAS\n\t");
        printf("4. SORTERS\n\t");
        printf("5. TRANSELEVADOR\n\t\n> Categoria: ");
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
                pause();

        }
    } while (input < 1 || input > 5);


    do {

        system("cls || clear");
        printf("> Setor (2 Letras, 2 Dígitos): ");
        readString(equipamentoTemp.setorAssociado.setor, sizeof(equipamentoTemp.setorAssociado.setor));


        if (verificar(equipamentoTemp.setorAssociado.setor, sizeof(equipamentoTemp.setorAssociado.setor), 0)) {
            strcpy(equipamento.setorAssociado.setor, equipamentoTemp.setorAssociado.setor);
        } else {
            printf("\nSetor Inválido\n\n");
            pause();
        }
    } while (!verificar(equipamentoTemp.setorAssociado.setor, sizeof(equipamentoTemp.setorAssociado.setor), 0));


    do {

        input = 0;

        system("cls || clear");
        printf("Qual é o Estado Operacional atual do equipamento? \n\n\t");
        printf("1: Ativo\n\t");
        printf("2: Inativo\n\t");
        printf("3: Manutenção\n\n> ");
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
                pause();

        }
    } while (input < 1 || input > 3);


    do {

        system("cls || clear");
        printf("> ID do Operador Associado (4 Dígitos): ");
        readString(equipamentoTemp.IDo, sizeof(equipamentoTemp.IDo));


        if (verificar(equipamentoTemp.IDo, sizeof(equipamentoTemp.IDo), 1)) {
            strcpy(equipamento.IDo, equipamentoTemp.IDo);
        } else {
            printf("\nID Inválido\n\n");
            pause();
        }
    } while (!verificar(equipamentoTemp.IDo, sizeof(equipamentoTemp.IDo), 1));


    do {

        input = 0;

        system("cls || clear");
        printf("> Nível de Prioridade (1. BAIXA, 2. MEDIA, 3. ALTA): ");
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
        localInput = 0;
        system("cls || clear");
        printf("> Nível Operacional (1. BASICO, 2. INTERMEDIARIO, 3. SUPERVISOR): ");
        readInt(&localInput);

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
        localInput = 0;
        system("cls || clear");
        printf("> Estado Operacional Atual (1. ATIVO, 2. OCUPADO, 3. INATIVO, 4. BLOQUEADO): ");
        readInt(&localInput);

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

    do {
        localInput = -1;
        system("cls || clear");
        printf("> Quantidade de Operações realizadas (só números positívos): ");
        readInt(&localInput);
        limpaBuffer();

        if (localInput <= -1) {
            printf("\nINPUT INVALIDO\n\n");
            system("pause");
        } else {
            op.quantOp = localInput;
        }

    }while(localInput <= -1);

    printf("\n\nOperador cadastrado com sucesso!\n");
    pause();

    return op;
}


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

                        input = 0;

                        system("cls || clear");
                        printf("Qual é o Novo Estado Operacional do equipamento? \n\n\t");
                        printf("1: Ativo\n\t");
                        printf("2: Inativo\n\t");
                        printf("3: Manutenção\n\n> ");
                        readInt(&input);


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

                        input = 0;

                        system("cls || clear");
                        printf("Qual é o novo status do operador? \n\n\t");
                        printf("1: Ativo\n\t");
                        printf("2: Ocupado\n\t");
                        printf("3: Inativo\n\t ");
                        printf("4: Bloqueado\n\n> ");
                        readInt(&input);


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


                    do {

                        system("cls || clear");
                        printf("Escreva o novo Setor Associado ao equipamento: ");
                        readString(equipamentoTemp.setorAssociado.setor, sizeof(equipamentoTemp.setorAssociado.setor));

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

                                    system("cls");
                                    printf("Ocorrencia Removida com Sucesso!\n\n");
                                    system("pause");

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

                                    system("cls");
                                    printf("Operador Removido com Sucesso!\n\n");
                                    system("pause");
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

                                    system("cls");
                                    printf("Equipamento Removido com Sucesso!\n\n");
                                    system("pause");
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
    int input = 0;
    int encontrou = 0;
    int i = 0;
    int j = 0;
    char busca[71] = "";
    char buscaID[5] = "";
    char buscaEq[4] = "";
    char buscaSetor[5] = "";
    char buscaEqID[4] = "";
    char nomeUpper[71] = "";
    char setorUpper[5] = "";
    char nivelNecessario[14] = "";

    do {
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


            case 1: {
                encontrou = 0;

                system("cls || clear");
                printf("Nome (ou parte do nome) do Operador: ");
                readString(busca, sizeof(busca));


                for (i = 0; busca[i]; i++) busca[i] = toupper(busca[i]);

                printf("\n%-6s %-71s %-5s %-14s %-10s %-5s\n",
                       "ID", "Nome", "Setor", "Nivel", "Estado", "Ops");
                printf("------------------------------------------------------------------------\n");

                for (i = 0; i < nOperadores; i++) {

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


            case 2: {
                encontrou = 0;

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


            case 3: {
                encontrou = 0;

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


            case 4: {
                encontrou = 0;
                nivelNecessario[0] = '\0';

                system("cls || clear");
                printf("Setor de interesse (2 letras + 2 digitos): ");
                readString(buscaSetor, sizeof(buscaSetor));


                for (i = 0; buscaSetor[i]; i++) buscaSetor[i] = toupper(buscaSetor[i]);


                printf("\nID do Equipamento para verificar prioridade (ou ENTER para ignorar): ");
                readString(buscaEqID, sizeof(buscaEqID));

                if (strlen(buscaEqID) > 0) {
                    for (i = 0; i < nEquipamentos; i++) {
                        if (strcmp(equipamentos[i].ID, buscaEqID) == 0) {

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
                    strcpy(setorUpper, operadores[i].setorAssociado.setor);
                    for (j = 0; setorUpper[j]; j++) setorUpper[j] = toupper(setorUpper[j]);


                    if (strcmp(operadores[i].estado, "ATIVO") != 0) continue;
                    if (strcmp(setorUpper, buscaSetor) != 0) continue;


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

void relatoriosOp(Operadores operadores[], int nOperadores, Equipamentos equipamentos[], int nEquipamentos) {
    int list = 0;
    int i = 0;
    int h = 0;
    char setorDet[5] = "";
    int melhorIndice = -1;
    int maior = -1;

    system("cls || clear");
    printf("\nQual relatório operacional você quer checar?");
    printf("\n1 --> Todos os operadores");
    printf("\n2 --> Informações dos operadores de um setor específico");
    printf("\n3 --> Informações dos equipamentos de um setor específico");
    printf("\n4 --> Informações do setor");
    printf("\n5 --> Operador de cada setor com maior número de atividades realizadas\n> ");
    readInt(&list);

    switch (list) {
        case 1:
            system("cls || clear");
            printf("Quantidade de operadores: %d\n", nOperadores);
            for (i = 0; i < nOperadores; i++) {
                printf("\nID: %s", operadores[i].ID);
                printf("\nNome: %s", operadores[i].nome);
                printf("\nSetor: %s", operadores[i].setorAssociado.setor);
                printf("\nNível Operacional: %s", operadores[i].nivelOp);
                printf("\nStatus: %s", operadores[i].estado);
                printf("\nQuantidade de operações: %d\n", operadores[i].quantOp);
            }
            pause();
            break;

        case 2:
            system("cls || clear");
            printf("Digite o setor desejado: ");
            readString(setorDet, sizeof(setorDet));
            for (i = 0; i < nOperadores; i++) {
                if (strcmp(operadores[i].setorAssociado.setor, setorDet) == 0) {
                    printf("\nID: %s", operadores[i].ID);
                    printf("\nNome: %s", operadores[i].nome);
                    printf("\nStatus: %s\n", operadores[i].estado);
                }
            }
            pause();
            break;

        case 3:
            system("cls || clear");
            printf("Digite o setor desejado: ");
            readString(setorDet, sizeof(setorDet));
            limpaBuffer();
            for (h = 0; h < nEquipamentos; h++) {
                if (strcmp(equipamentos[h].setorAssociado.setor, setorDet) == 0) {
                    printf("\nID: %s", equipamentos[h].ID);
                    printf("\nTipo: %s", equipamentos[h].tipo);
                    printf("\nEstado Operacional: %s\n", equipamentos[h].estado);
                }
            }
            pause();
            break;

        case 4:
            system("cls || clear");
            printf("Digite o setor desejado: ");
            readString(setorDet, sizeof(setorDet));
            limpaBuffer();
            for (i = 0; i < nOperadores; i++) {
                if (strcmp(operadores[i].setorAssociado.setor, setorDet) == 0) {
                    printf("\nID: %s", operadores[i].ID);
                    printf("\nNome: %s\n", operadores[i].nome);
                }
            }
            pause();
            break;

        case 5:
            system("cls || clear");
            printf("Digite o setor desejado: ");
            readString(setorDet, sizeof(setorDet));
            limpaBuffer();
            melhorIndice = -1;
            maior = -1;
            for (i = 0; i < nOperadores; i++) {
                if (strcmp(operadores[i].setorAssociado.setor, setorDet) == 0 && operadores[i].quantOp > maior) {
                    maior = operadores[i].quantOp;
                    melhorIndice = i;
                }
            }
            if (melhorIndice >= 0) {
                printf("\nO operador com mais operacoes do setor %s e %s\n", setorDet, operadores[melhorIndice].ID);
            } else {
                printf("\nNenhum operador encontrado no setor %s.\n", setorDet);
            }
            pause();
            break;

        default:
            printf("\nOpcao invalida!\n");
            pause();
            break;
    }
}


int main() {
    int input, shutdown = 0, i, j;
    int nOperadores = 0, nEquipamentos = 0, nOcorrencias = 0;
    Operadores operadores[MAXOPERADORES], operadorTemp = {{0}};
    Equipamentos equipamentos[MAXEQUIPAMENTOS], equipamentoTemp = {{0}};
    Ocorrencias ocorrencias[MAXEQUIPAMENTOS], ocorrenciaTemp = {{0}};

    setlocale(LC_ALL, "portuguese");

    while(!shutdown){
        input = 0;

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
        readInt(&input);

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
                relatoriosOp(operadores, nOperadores, equipamentos, nEquipamentos);
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
