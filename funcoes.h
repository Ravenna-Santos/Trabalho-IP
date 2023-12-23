#ifndef FUNCOES_H
#define FUNCOES_H
#include <stdio.h>
#include <stdlib.h>

// Structs
typedef struct {
  int matricula;
  float notas[7];
  char nome[50];
  int codTurma;
  int faltas[7];
} aluno;

typedef struct {
  aluno *alunos;
  int qtdAlunos;
  int id;
} turma;

// Funções
void linha();
void cadastrar_aluno(aluno *alunos, int *qtde, int *capacidade);
void adicionar_aluno(aluno aluno);
void ler_alunos(aluno *alunos, int *qtde, int *capacidade);
void remover_aluno(aluno *alunos, int *qtde, int *capacidade);
void reescrever_alunos(aluno *alunos, int *qtde);
void listar_alunos(aluno *alunos, int *qtde, int *capacidade);

#endif