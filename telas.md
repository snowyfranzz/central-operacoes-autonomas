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
```


=========================================================================



- 2
```
Cadastro de Módulo:
(system cls)

> ID do Módulo (1 Letra, 2 Dígitos): 
> Categoria Operacional (SENSOR, SCANNER, BRACO_ROBOTICO): 
> Setor (2 Letras, 2 Dígitos):
> ID do Operador Associado (4 Dígitos):
> Nível de Prioridade (BAIXA, MEDIA, ALTA):
```


=========================================================================


- 3
```
(system cls)

Menu:
- 1. Atualizar estado operacional de um módulo.
- 2. Atualizar estado de disponibilidade de um operador.
- 3. Mover equipamentos entre setores.
- 4. Registrar uma ocorrência.
- 5. Desativar Registros.
```

- 3.1
```
(cls)
Módulos Registrados:

XXX - <Nome> | Setor: <setor> | Estado Operacional: <estado>
YYY - <Nome> | Setor: <setor> | Estado Operacional: <estado>

Qual módulo você deseja atualizar? (ID)
>

Para qual estado você deseja atualizar o módulo <ID>? (ATIVO, INATIVO, MANUTENCAO)
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
Módulos Registrados:

XXX - <Nome> | Setor: <setor> | Estado Operacional: <estado>
YYY - <Nome> | Setor: <setor> | Estado Operacional: <estado>

Qual módulo você deseja atualizar? (ID)
>

Para qual setor você deseja atualizar o módulo <ID>? (<setores>)
>
```

- .4
```
// perguntar para a lucia
```

- 2.5
```
// perguntar para a lucia
```


=========================================================================


- 3
```
(cls)
O que deseja fazer? 
- 1. Pesquisar estado de operador 
- 2. Pesquisar estado de módulo 
- 3. Pesquisar os operadores livres para operar um módulo

> 
```

- 3.1
```
>  Como quer efetuar a pesquisa? (1. ID | 2. Nome):
> Insira o <nome ou id> do operador:

<nome> - XXX
Setor: <setor>
Estado de Dispoonibilidade: <estado>
```

- 3.2
```
> Insira o ID do módulo:

<nome> - XXXX
Setor: <setor>
Estado Operacional: <estado>
```

-3.3
```
> Insira o ID do módulo que precisa ser operado: 

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



perguntas:
1- quais setores existem dentro da orbytec?
2- quais tipos nos (time) vamos definir?
3- o que determina um operador como alguem que pode operar uma das maquinas / modulos?
4- Avaliar e decidir se um
operador pode controlar simultaneamente vários equipamento