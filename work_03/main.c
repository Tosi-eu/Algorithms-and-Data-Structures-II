#include "arvore_b.h"
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

  setlocale(LC_ALL, "Portuguese");
  No *raiz = NULL;

  char comando[150];
  int id;
  char titulo[150];
  char autor[150];

  while (strcmp(comando, "EXIT") != 0) {
    setbuf(stdin, NULL);
    fgets(comando, 150, stdin);

    if (sscanf(comando, "SEARCH id='%d'", &id) == 1) {
      No *resultado = buscar(raiz, id);
      if (resultado != NULL) {
        exibir_livro(resultado->livros[buscar_chave(resultado, id)]);
      } else {
        printf("----------------------------------------------------------\n");
        printf("Não encontrado\n");
      }
    } else if (sscanf(comando, "ADD id='%d' titulo='%[^']' autor='%[^']'", &id,
                      titulo, autor) == 3) {
      Livro livro;
      livro.id = id;
      strcpy(livro.titulo, titulo);
      strcpy(livro.autor, autor);

      No *resultado = buscar(raiz, id);
      if (resultado == NULL) {
        inserir(&raiz, livro);
        printf("----------------------------------------------------------\n");
        printf("Registro inserido\n");
      } else {
        printf("----------------------------------------------------------\n");
        printf("Erro ao inserir registro, chave primária duplicada\n");
      }
    }
  }

  return 0;
}
