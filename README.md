# Sistema de atendimento veterinário com filas de prioridade

Programa em C, de terminal, que organiza a fila de atendimento de uma clínica veterinária. Feito na disciplina de Estruturas de Dados (PUC-Campinas).

Os pets são cadastrados como **emergência** ou **normal**, e a emergência sempre é atendida primeiro. Quem já foi atendido vai para um histórico que pode ser consultado depois.

## Estrutura de dados

O sistema usa três **filas encadeadas** (FIFO), implementadas do zero com `malloc` e ponteiros, sem bibliotecas prontas:

| Fila | Função |
|---|---|
| Emergência | Pets que precisam de atendimento urgente |
| Normal | Pets de atendimento comum |
| Atendidos | Histórico de quem já passou pelo atendimento |

Ao atender, o programa retira o primeiro da fila de emergência. Se ela estiver vazia, retira o primeiro da fila normal. O pet atendido é inserido no fim da fila de atendidos.

Cada pet guarda: ID, nome, espécie, idade, data de nascimento e prioridade.

## Funcionalidades

1. Cadastrar pet (emergência ou normal), com validação dos dados digitados
2. Atender o próximo pet, priorizando emergência
3. Buscar pet por ID, por nome (ou parte do nome) ou pelos dois
4. Relatório das filas de espera
5. Mostrar quem é o próximo a ser atendido
6. Relatório dos pets já atendidos

## Arquivos

- `main.c`: menu e funções de cada operação
- `FILA.h`: estrutura da fila e operações básicas (criar, inserir, retirar, buscar, liberar memória)

## Como rodar

```bash
gcc main.c -o veterinario
./veterinario
```

O programa usa `system("cls")` e `system("pause")`, então foi pensado para rodar no Windows. Em Linux ou macOS funciona, mas a limpeza de tela e a pausa não terão efeito.

## O que pratiquei

- Implementação de fila encadeada com alocação dinâmica de memória
- Uso de múltiplas filas para simular prioridade
- Validação de entrada do usuário no terminal
- Organização do código em cabeçalho (`.h`) e arquivo principal

