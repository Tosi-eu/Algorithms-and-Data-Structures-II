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
  int i = 0;
  while (i < no->num_chaves && id > no->livros[i].id) {
    i++;
  }
  return i;
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

  for (int i = 0; i < MAX_KEYS / 2; i++) {
    novo_filho->livros[i] = filho->livros[i + MAX_KEYS / 2];
    novo_filho->num_chaves++;
  }

  if (!filho->folha) {
    for (int i = 0; i < MAX_CHILDREN / 2; i++) {
      novo_filho->filhos[i] = filho->filhos[i + MAX_CHILDREN / 2];
    }
  }

  filho->num_chaves = MAX_KEYS / 2;

  inserir_filho(pai, novo_filho, indice);
  inserir_chave(pai, filho->livros[MAX_KEYS / 2]);

  filho->num_chaves--;
  for (int i = MAX_KEYS / 2; i < MAX_KEYS; i++) {
    if (!filho->folha) {
      filho->filhos[i + 1] = NULL;
    }
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