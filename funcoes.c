#include "funcoes.h"

// Imprime uma linha
void linha() {
  printf("========================================\n");
}

// Pega as informações e cadastra o aluno
void cadastrar_aluno(aluno *alunos, int *qtde, int *capacidade) {
  aluno novo_aluno;
  
  printf("\nInforme os seguintes dados:\n");

  getchar();
  printf("\nNome: ");
  fgets(novo_aluno.nome, 50, stdin);
  
  printf("\nNúmero da matrícula: ");
  scanf("%d", &novo_aluno.matricula);
  while (novo_aluno.matricula / 100 != 20230) {
    printf("Matrícula inválida! O formato da matrícula deve ser 20230XX."
      "\nDigite novamente: ");
    scanf("%d", &novo_aluno.matricula);
  }
  alunos = ler_alunos(alunos, qtde, capacidade);
  int flag = 1;
  while (flag == 1) {
    int mat_igual = 0;
    for (int i = 0; i < *qtde; i++) {
      if (alunos[i].matricula == novo_aluno.matricula)
        mat_igual = 1;
    }
    if (mat_igual == 1) {
      printf("Matrícula já cadastrada! Digite novamente: ");
      scanf("%d", &novo_aluno.matricula);
      while (novo_aluno.matricula / 100 != 20230) {
        printf("Matrícula inválida! A matrícula deve seguir o formato: 20230XX."
          "\nDigite novamente: ");
        scanf("%d", &novo_aluno.matricula);
      }
    }
    else {
      flag = 0;
    }
  }

  printf("\nCódigo da turma: ");
  scanf("%d", &novo_aluno.codTurma);

  printf("\nNotas do aluno\n");
  for (int i = 1; i <= 7; i++) {
    printf("Nota disciplina %d: ", i);
    scanf("%f", &novo_aluno.notas[i-1]);
    while(novo_aluno.notas[i-1]<0 || novo_aluno.notas[i-1]>10)
      {  
        printf("Insira uma nota válida: ");
        scanf("%f", &novo_aluno.notas[i-1]);
      }
  }

  printf("\nFaltas do aluno\n");
  for (int i = 1; i <= 7; i++) {
    printf("Faltas disciplina %d: ", i);
    scanf("%d", &novo_aluno.faltas[i-1]);
  }

  adicionar_aluno(novo_aluno);
  *qtde += 1;

  printf("\nAluno cadastrado com sucesso!\n\n");
}

// Adiciona o aluno no arquivo
void adicionar_aluno(aluno aluno) {
  FILE *arq;
  arq = fopen("alunos.txt", "a");
  fprintf(arq, "%s%d\n%d\n", aluno.nome, aluno.matricula, aluno.codTurma);
  for (int i = 0; i < 7; i++) {
    fprintf(arq, "%.2f ", aluno.notas[i]);
  }
  fprintf(arq, "\n");
  for (int i = 0; i < 7; i++) {
    fprintf(arq, "%d ", aluno.faltas[i]);
  }
  fprintf(arq, "\n\n");
  fclose(arq);
}

// Lê o arquivo e armazena os dados em 'alunos'
aluno *ler_alunos(aluno *alunos, int *qtde, int *capacidade) {
  FILE *arq;
  int i = 0;
  arq = fopen("alunos.txt", "r");
  if(arq == NULL) {
    if (*qtde > 0)
      printf("ERRO! Não foi possivel abrir o arquivo.\n");
  }
  else{
    while(fscanf(arq, "%[^\n]%d\n%d\n%f %f %f %f %f %f %f\n%d %d %d %d %d %d %d\n", alunos[i].nome, &alunos[i].matricula, &alunos[i].codTurma, &alunos[i].notas[0], &alunos[i].notas[1], &alunos[i].notas[2], &alunos[i].notas[3], &alunos[i].notas[4], &alunos[i].notas[5], &alunos[i].notas[6], &alunos[i].faltas[0], &alunos[i].faltas[1], &alunos[i].faltas[2], &alunos[i].faltas[3], &alunos[i].faltas[4], &alunos[i].faltas[5], &alunos[i].faltas[6]) != EOF){
      i++;
      // Aumenta a capacidade de 'alunos' em 10 caso necessário
      if (i >= *capacidade) {
        *capacidade += 10;
        alunos = realloc(alunos, *capacidade * sizeof(aluno));
      }
    }
  fclose(arq);
  *qtde = i;
  return alunos;
  }
}

// Remove o aluno a partir do numéro da matrícula
void remover_aluno(aluno *alunos, int *qtde, int *capacidade) {
  int matricula, removido = 0;
    
  alunos = ler_alunos(alunos, qtde, capacidade);
  if (*qtde == 0) {
    printf("\nNão há alunos cadastrados!\n\n");
  }
  else {
    printf("\nDigite a matrícula do aluno que deseja remover: ");
    scanf("%d", &matricula);
    while (matricula / 100 != 20230) {
      printf("Matrícula inválida! Digite novamente: ");
      scanf("%d", &matricula);
    }
    
    for (int i = 0; i < *qtde; i++) {
      if (alunos[i].matricula == matricula) {
        removido = 1;
        for (int j = i; j < *qtde; j++) {
          alunos[j] = alunos[j+1];
        }
        break;
      }
    }
    if (removido == 1) {
      *qtde -= 1;
      reescrever_alunos(alunos, qtde);
      printf("\nAluno removido com sucesso!\n\n");
    }
    else {
      printf("\nAluno não encontrado!\n\n");
    }
  }
}

// Reescreve o arquivo a partir do vetor 'alunos'
void reescrever_alunos(aluno *alunos, int *qtde) {
  FILE *arq;
  arq = fopen("alunos.txt", "w");

  if(arq == NULL){
    printf("ERRO! Não foi possivel abrir o arquivo.\n");
  }
  else{
    for (int i = 0; i < *qtde; i++) {
      fprintf(arq, "%s\n%d\n%d\n", alunos[i].nome, alunos[i].matricula, alunos[i].codTurma);
      for (int j = 0; j < 7; j++) {
        fprintf(arq, "%.2f ", alunos[i].notas[j]);
      }
      fprintf(arq, "\n");
      for (int j = 0; j < 7; j++) {
        fprintf(arq, "%d ", alunos[i].faltas[j]);
      }
      fprintf(arq, "\n\n");
    }
    fclose(arq);
  }
}

//lista um aluno específico
void listar_aluno(aluno aluno){
  printf("\nNome: %s"
      "\nMatrícula: %d"
      "\nCódigo da turma: %d", aluno.nome, aluno.matricula, aluno.codTurma);

    printf("\nNotas: ");
    for (int j = 0; j < 7; j++) {
      printf(" %5.2f", aluno.notas[j]);
    }

    printf("\nFaltas:");
    for (int j = 0; j < 7; j++) {
      printf(" %5d", aluno.faltas[j]);
    }
    printf("\n");
  }

// Listar alunos cadastrados
aluno *listar_alunos_cadastrados(aluno *alunos, int *qtde, int *capacidade) {
  alunos = ler_alunos(alunos, qtde, capacidade);

  if (*qtde == 0) {
    printf("\nNão há alunos cadastrados!\n\n");
  }
  else {
    for (int i = 0; i < *qtde; i++) {
      listar_aluno(alunos[i]);
      printf("\n");
    }
  }
  return alunos;
}

// Classifica alunos como aprovados ou reprovados
// para aprovados reprovados retorna 1 para aprovados e 0 para reprovados

int classificar_alunos(aluno aluno){
  int aprovado = 1;
  for(int i = 0; i < 7; i++){
    if(aluno.notas[i] < 7.0){
      aprovado = 0;
      break;
    }
  }

  return aprovado;
}

// Lista alunos aprovados
aluno *listar_alunos_aprovados(aluno *alunos, int *qtde, int *capacidade) {
  alunos = ler_alunos(alunos, qtde, capacidade);
  aluno aluno;
  int qtd_aprovados = 0;

  if (*qtde == 0) {
    printf("\nNão há alunos cadastrados!\n\n");
  }
  else {
    for (int i = 0; i < *qtde; i++){
      aluno = alunos[i];
      if(classificar_alunos(aluno) == 1){
        listar_aluno(aluno);
        printf("\n");
        qtd_aprovados++;
      }
    }
    if(qtd_aprovados <= 0){
      printf("\nNão há alunos aprovados!\n\n");
    }
  }
  return alunos;
}


// Lista alunos aprovados
aluno *listar_alunos_reprovados(aluno *alunos, int *qtde, int *capacidade) {
  alunos = ler_alunos(alunos, qtde, capacidade);
  aluno aluno;
  int qtd_reprovados = 0;

  if (*qtde == 0) {
    printf("\nNão há alunos cadastrados!\n\n");
  }
  else {
    for (int i = 0; i < *qtde; i++){
      aluno = alunos[i];
      if(classificar_alunos(aluno) == 0){
        listar_aluno(aluno);
        printf("\n");
        qtd_reprovados++;
      }
    }
    if(qtd_reprovados <= 0){
      printf("\nNão há alunos reprovados!\n\n");
    }
  }
  return alunos;
}