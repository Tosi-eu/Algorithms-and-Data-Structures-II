#include "arvore_b.h"
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

No *criar_no() {
  No *novo_no = (No *)malloc(sizeof(No));
  novo_no->num_chaves = 0;
  novo_no->folha = 1;
  for (int i = 0; i < MAX_CHILDREN; i++) {
    novo_no->filhos[i] = NULL;
  }
  return novo_no;
}

int buscar_chave(No *no, int id) {
  int esquerda = 0;
  int direita = no->num_chaves - 1;

  while (esquerda <= direita) {
    int meio = (esquerda + direita) / 2;

    if (no->livros[meio].id == id) {
      return meio; // Chave encontrada
    } else if (no->livros[meio].id < id) {
      esquerda = meio + 1; // Buscar na metade direita
    } else {
      direita = meio - 1; // Buscar na metade esquerda
    }
  }

  return esquerda; // Chave não encontrada, retorna o índice onde deveria estar
}

void inserir_chave(No *no, Livro livro) {
  int i = no->num_chaves;
  while (i > 0 && livro.id < no->livros[i - 1].id) {
    no->livros[i] = no->livros[i - 1];
    i--;
  }
  no->livros[i] = livro;
  no->num_chaves++;
}

void inserir_filho(No *no, No *filho, int indice) {
  int i = no->num_chaves;
  while (i > indice) {
    no->filhos[i + 1] = no->filhos[i];
    i--;
  }
  no->filhos[indice + 1] = filho;
}

void dividir_no(No *pai, int indice, No *filho) {
  No *novo_filho = criar_no();
  novo_filho->folha = filho->folha;

  int i;
  if (indice < MAX_KEYS / 2) {
    // Redistribuição para a esquerda
    for (i = 0; i < MAX_KEYS / 2 - 1; i++) {
      novo_filho->livros[i] = filho->livros[i + MAX_KEYS / 2 + 1];
      novo_filho->num_chaves++;
    }

    if (!filho->folha) {
      for (i = 0; i < MAX_CHILDREN / 2; i++) {
        novo_filho->filhos[i] = filho->filhos[i + MAX_CHILDREN / 2 + 1];
      }
    }

    novo_filho->filhos[novo_filho->num_chaves] =
        filho->filhos[MAX_CHILDREN - 1];

    filho->num_chaves = MAX_KEYS / 2 - 1;

    for (i = pai->num_chaves; i > indice; i--) {
      pai->filhos[i + 1] = pai->filhos[i];
    }
    pai->filhos[indice + 1] = novo_filho;
    pai->filhos[indice] = filho;

    for (i = pai->num_chaves - 1; i >= indice; i--) {
      pai->livros[i + 1] = pai->livros[i];
    }
    pai->livros[indice] = filho->livros[MAX_KEYS / 2];
    pai->num_chaves++;
  } else {
    // Redistribuição para a direita
    for (i = 0; i < MAX_KEYS / 2 - 1; i++) {
      novo_filho->livros[i] = filho->livros[i + MAX_KEYS / 2 + 2];
      novo_filho->num_chaves++;
    }

    if (!filho->folha) {
      for (i = 0; i < MAX_CHILDREN / 2; i++) {
        novo_filho->filhos[i] = filho->filhos[i + MAX_CHILDREN / 2 + 2];
      }
    }

    novo_filho->filhos[novo_filho->num_chaves] =
        filho->filhos[MAX_CHILDREN - 1];

    filho->num_chaves = MAX_KEYS / 2;

    for (i = pai->num_chaves; i > indice + 1; i--) {
      pai->filhos[i + 1] = pai->filhos[i];
    }
    pai->filhos[indice + 1] = novo_filho;

    for (i = pai->num_chaves - 1; i >= indice + 1; i--) {
      pai->livros[i + 1] = pai->livros[i];
    }
    pai->livros[indice + 1] = filho->livros[MAX_KEYS / 2 + 1];
    pai->num_chaves++;
  }
}

void inserir(No **raiz, Livro livro) {
  if ((*raiz) == NULL) {
    (*raiz) = criar_no();
    inserir_chave((*raiz), livro);
  } else {
    No *raiz_temporaria = (*raiz);
    No *no_pai = NULL;
    int indice = 0;

    while (raiz_temporaria != NULL && raiz_temporaria->num_chaves == MAX_KEYS) {
      indice = buscar_chave(raiz_temporaria, livro.id);
      no_pai = raiz_temporaria;
      raiz_temporaria = raiz_temporaria->filhos[indice];
    }

    if (raiz_temporaria != NULL) {
      inserir_chave(raiz_temporaria, livro);
    } else {
      inserir_chave(no_pai, livro);
      dividir_no(no_pai, indice, no_pai->filhos[indice]);
    }
  }

  // Atualizar arquivos de dado e índice após a inserção
  FILE *arquivo_dados = fopen("dados.bin", "wb+");
  FILE *arquivo_indice = fopen("indice.bin", "wb+");

  if (arquivo_dados == NULL || arquivo_indice == NULL) {
    return;
  }

  // Escrever o livro no arquivo de dados
  fwrite(&livro, sizeof(Livro), 1, arquivo_dados);

  // Escrever o índice no arquivo de índice
  int id = livro.id;
  fwrite(&id, sizeof(int), 1, arquivo_indice);
  long posicao = ftell(arquivo_dados) - sizeof(Livro);
  fwrite(&posicao, sizeof(long), 1, arquivo_indice);

  // Fechar os arquivos
  fclose(arquivo_dados);
  fclose(arquivo_indice);
}

No *buscar(No *raiz, int id) {
  if (raiz == NULL) {
    return NULL;
  }

  int indice = buscar_chave(raiz, id);
  if (indice < raiz->num_chaves && raiz->livros[indice].id == id) {
    return raiz;
  }

  if (raiz->folha) {
    return NULL;
  }

  return buscar(raiz->filhos[indice], id);
}

void exibir_livro(Livro livro) {
  printf("----------------------------------------------------------\n");
  printf("%d - %s - %s\n", livro.id, livro.titulo, livro.autor);
}

void exibir_arvore(No *raiz) {
  if (raiz != NULL) {
    for (int i = 0; i < raiz->num_chaves; i++) {
      exibir_livro(raiz->livros[i]);
    }

    if (!raiz->folha) {
      for (int i = 0; i <= raiz->num_chaves; i++) {
        exibir_arvore(raiz->filhos[i]);
      }
    }
  }
}

Livro livro_vazio() {
  Livro livro;
  livro.id = -1;
  strcpy(livro.titulo, "");
  strcpy(livro.autor, "");
  return livro;
}
