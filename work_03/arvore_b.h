#ifndef ARVORE_B
#define ARVORE_B

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEYS 2300
#define MAX_CHILDREN (MAX_KEYS + 1)

typedef struct {
  int id;
  char titulo[100];
  char autor[100];
} Livro;

typedef struct No {
  int num_chaves;
  Livro livros[MAX_KEYS];
  struct No *filhos[MAX_CHILDREN];
  int folha;
} No;

void inserir_filho(No *no, No *filho, int indice);
No *criar_no();
int buscar_chave(No *no, int id);
void inserir_chave(No *no, Livro livro);
void inserir_filho(No *no, No *filho, int indice);
void dividir_no(No *pai, int indice, No *filho);
void inserir(No **raiz, Livro livro);
No *buscar(No *raiz, int id);
void exibir_livro(Livro livro);
void exibir_arvore(No *raiz);
Livro livro_vazio();
#endif