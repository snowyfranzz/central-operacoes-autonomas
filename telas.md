- Dashboard
```
+------------------------------------------------------------------------------+
|               Orbytec Sistemas Integrados - Setor VX27 - Dashboard           |
+-------------------------+--------------------------+-------------------------+
|  Ocorrências Recentes:  |    Operadores Ativos:    |   Equipamentos Ativos:  |
|=========================|==========================|=========================|
|                         |                          |                         |
|                         |                          |                         |
|                         |                          |                         |
|                         |                          |                         |
|                         |                          |                         |
|                         |                          |                         |
|                         |                          |                         |
|                         |                          |                         |
|                         |                          |                         |
|                         |                          |                         |
+-------------------------+--------------------------+-------------------------+
|                                    Menu:                                     |
|==============================================================================|
|                                                                              |
|    1. Cadastro de Operadores.              4. Consultar Registros.           |
|                                                                              |
|    2. Cadastro de Equipamentos.            5. Ver Relatórios Operacionais.   |
|                                                                              |
|    3. Atualizar Dados do Sistema.          6. Sair do Programa.              |
+------------------------------------------------------------------------------+
>
```



=========================================================================



- 1
```
(system cls)

Cadastro de Operador:

> ID do Operador (4 Dígitos):  
> Nome do Operador (Máximo de 70 Caractéres): 
> Setor (2 Letras, 2 Dígitos):
> Nível Operacional (BASICO, INTERMEDIARIO, SUPERVISOR):
> Estado Operacional Atual ():
```


=========================================================================



- 2
```
Cadastro de equipamento:
(system cls)

> ID do equipamento (1 Letra, 2 Dígitos): 

Categorias Operacionais:

1. AGV
2. BRACO_ARTICULADO
3. ESTEIRAS
4. SORTERS
5. TRANSELEVADOR

> Código de categoria: 
> Setor (2 Letras, 2 Dígitos): 
> ID do Operador Associado (4 Dígitos): 
> Nível de Prioridade (BAIXA, MEDIA, ALTA): 
```


=========================================================================


- 3
```
(system cls)

Menu:
- 1. Atualizar estado operacional de um equipamento.
- 2. Atualizar estado de disponibilidade de um operador.
- 3. Mover equipamentos entre setores.
- 4. Registrar uma ocorrência.
- 5. Desativar Registros.
```

- 3.1
```
(cls)
equipamentos Registrados:

XXX - <Nome> | Setor: <setor> | Estado Operacional: <estado>
YYY - <Nome> | Setor: <setor> | Estado Operacional: <estado>

Qual equipamentovocê deseja atualizar? (ID)
>

Para qual estado você deseja atualizar o equipamento <ID>? (ATIVO, INATIVO, MANUTENCAO)
>
```

- 3.2
```
(cls)
Operadores Registrados:

XXXX - <Nome> | Setor: <setor> | Estado de Disponibilidade: <estado>
YYYY - <Nome> | Setor: <setor> | Estado de Disponibilidade: <estado>

Qual operador você deseja atualizar? (ID)
> 

Para qual estado você deseja atualizar o operador <ID>? (ATIVO, OCUPADO, INATIVO, BLOQUEADO)
>
```

- 3.3
```
(cls)
equipamentos Registrados:

XXX - <Nome> | Setor: <setor> | Estado Operacional: <estado>
YYY - <Nome> | Setor: <setor> | Estado Operacional: <estado>

Qual equipamentovocê deseja atualizar? (ID)
>

Para qual setor você deseja atualizar o equipamento<ID>? (<setores>)
>
```

- 3.4
```
// perguntar para a lucia
// atualmente: 
```

- 3.5
```
(cls)
Operadores Registrados:

XXXX - <Nome> | Setor: <setor> | Estado de Disponibilidade: <estado>
YYYY - <Nome> | Setor: <setor> | Estado de Disponibilidade: <estado>

Quem você deseja apagar o registro? (ID)
>
```


=========================================================================


- 4
```
(cls)
O que deseja fazer? 
- 1. Pesquisar estado de operador 
- 2. Pesquisar estado de equipamento
- 3. Pesquisar os operadores livres para operar um equipamento

> 
```

- 4.1
```
> Como quer efetuar a pesquisa? (1. ID | 2. Nome):
> Insira o <nome ou id> do operador:

<nome> - XXX
Setor: <setor>
Estado de Dispoonibilidade: <estado>
Operações Realizadas: <operacoes>
```

- 4.2
```
> Insira o ID do equipamento:

<nome> - XXXX
Setor: <setor>
Estado Operacional: <estado>
```

- 4.3
```
> Insira o ID do equipamento: 

<nome> - XXX
Setor: <setor>
Estado de Dispoonibilidade: ATIVO

<nome> - YYY
Setor: <setor>
Estado de Dispoonibilidade: ATIVO

<nome> - ZZZ
Setor: <setor>
Estado de Dispoonibilidade: ATIVO
```


=========================================================================


- 5
```
(cls)
Qual relatório você deseja gerar?

1. Listar todos os operadores e suas respectivas informações
2. Listar todos os equipamentos e suas respectivas informações
3. Listar as informações dos Operadores de um Setor
4. Listar as informações dos Equipamentos de um Setor
5. Listar as informações de todos os registros em um Setor
6. Listar os operadores de cada setor com o maior número de operações realizadas
```

- 5.1
```
(cls)
===== OPERADORES =====

<nome> - XXXX
Setor: <setor>
Estado de Dispoonibilidade: <estado>
Operações Realizadas: <operacoes>

<nome> - YYYY
Setor: <setor>
Estado de Dispoonibilidade: <estado>
Operações Realizadas: <operacoes>

<nome> - ZZZZ
Setor: <setor>
Estado de Dispoonibilidade: <estado>
Operações Realizadas: <operacoes>
```

- 5.2
```
===== EQUIPAMENTOS =====
<nome> - XXX
Setor: <setor>
Estado de Dispoonibilidade: <estado>
Ultima Manutenção: <ultima_manutencao>

<nome> - YYY
Setor: <setor>
Estado de Dispoonibilidade: <estado>
Ultima Manutenção: <ultima_manutencao>

<nome> - ZZZ
Setor: <setor>
Estado de Dispoonibilidade: <estado>
Ultima Manutenção: <ultima_manutencao>
```

- 5.3
```
(cls)
===== OPERADORES - SETOR <setor> =====

<nome> - XXXX
Setor: <setor>
Estado de Dispoonibilidade: <estado>
Operações Realizadas: <operacoes>

<nome> - ZZZZ
Setor: <setor>
Estado de Dispoonibilidade: <estado>
Operações Realizadas: <operacoes>
```


- 5.4
```
===== EQUIPAMENTOS - SETOR <setor> =====

<tipo> - XXX
Setor: <setor>
Estado de Dispoonibilidade: <estado>
ID Operador: <idop>
Prioridade: <prioridade>
Ultima Manutenção: <ultima_manutencao>

<nome> - YYY
Setor: <setor>
Estado de Dispoonibilidade: <estado>
Ultima Manutenção: <ultima_manutencao>
```

- 5.5
```
===== SETOR <setor> =====

- Equipamentos:
<nome> - XXX
Setor: <setor>
Estado de Dispoonibilidade: <estado>
Ultima Manutenção: <ultima_manutencao>

<nome> - YYY
Setor: <setor>
Estado de Dispoonibilidade: <estado>
Ultima Manutenção: <ultima_manutencao>


- Operadores:
<nome> - XXXX
Setor: <setor>
Estado de Dispoonibilidade: <estado>
Operações Realizadas: <operacoes>

<nome> - ZZZZ
Setor: <setor>
Estado de Dispoonibilidade: <estado>
Operações Realizadas: <operacoes>
```


=========================================================================



## Perguntas p/ fazer para a lucia
2. Perguntas se a quantidade de tipos esta boa (tipos: braço articulado, esteiras, veiculos guiados automaticamente (AVGs), sorters, transelevadores)
3. Como devemos registrar as ocorrenias -> tipos de ocorrencias? strings de descricao? so string de descricao, operador / eqiuipamento
4. Quantos relatórios devemos gerar?
5. Em que estado o operador deve ser inicializado OU devemos adicionar uma oção para o inicializar em um estado ja? perguntar