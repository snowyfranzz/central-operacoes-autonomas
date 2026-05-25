- Dashboard
```
+------------------------------------------------------------------------------+
|               Orbytec Sistemas Integrados - Setor VX27 - Dashboard           |
+-------------------------+--------------------------+-------------------------+
|  Ocorrências Recentes:  |    Operadores Ativos:    |   Equipamentos Ativos:  |
|=========================|==========================|=========================|
|                         |                          |                         |
|                         |                          |                         |
|                         |                          |                         |c
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
|    1. Cadastro Operador / Módulo.         3. Consultar Registros.            |
|                                                                              |
|    2. Atualizar Opções do Sistema.        4. Ver Relatórios Operacionais.    |
|                                                                              |
|    5. Ajuda e Suporte ao Usuário.         6. Sair do Programa.               |
+------------------------------------------------------------------------------+
>
```


=========================================================================


- 1
```
O que deseja fazer? (1. Cadastrar Operador | 2. Cadastrar Módulo)
> 
```

- 1.1
```
(system cls)

Cadastro de Operador:

> ID do Operador (4 Dígitos):  
> Nome do Operador (Máximo de 70 Caractéres): 
> Setor (2 Letras, 2 Dígitos):
> Nível Operacional (BASICO, INTERMEDIARIO, SUPERVISOR):
```

- Cadastro de Módulo 1.2
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


- 2
```
(system cls)

Menu:
- 1. Atualizar estado operacional de um módulo.
- 2. Atualizar estado de disponibilidade de um operador.
- 3. Mover equipamentos entre setores.
- 4. Registrar uma ocorrência.
- 5. Desativar Registros.
```

- 2.1
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

- 2.2
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

- 2.3
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

- 2.4
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