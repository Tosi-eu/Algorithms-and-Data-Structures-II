#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char* titulo;
    char* autor;
} Registro;

int main() {
    // abrir arquivo para leitura em modo binario
    FILE* arq = fopen("registros.bin", "rb");
    if (!arq) {
        perror("Erro ao abrir arquivo");
        return EXIT_FAILURE;
    }

    // obter tamanho do arquivo em bytes
    fseek(arq, 0, SEEK_END);
    long int tamanho_arquivo = ftell(arq);
    fseek(arq, 0, SEEK_SET);

    // definir quantos registros devem ser exibidos a partir do final do arquivo
    int m = 3;

    // calcular quantos bytes precisam ser lidos a partir do final do arquivo
    long int tamanho_leitura = m * sizeof(Registro);

    // calcular a posicao inicial da leitura
    long int byte_offset = tamanho_arquivo - tamanho_leitura;

    // posicionar o ponteiro de arquivo no local desejado
    fseek(arq, byte_offset, SEEK_SET);

    // ler os registros a partir do byte_offset
    Registro reg;
    while (fread(&reg.id, sizeof(int), 1, arq) == 1) {
        // ler titulo
        int tamanho_titulo;
        fread(&tamanho_titulo, sizeof(int), 1, arq);
        reg.titulo = malloc(tamanho_titulo + 1);
        fread(reg.titulo, tamanho_titulo, 1, arq);
        reg.titulo[tamanho_titulo] = '\0';

        // ler autor
        int tamanho_autor;
        fread(&tamanho_autor, sizeof(int), 1, arq);
        reg.autor = malloc(tamanho_autor + 1);
        fread(reg.autor, tamanho_autor, 1, arq);
        reg.autor[tamanho_autor] = '\0';

        // exibir registro
        printf("Id: %d\n", reg.id);
        printf("Titulo: %s\n", reg.titulo);
        printf("Autor: %s\n", reg.autor);
        printf("Byte offset: %ld\n\n", ftell(arq));
    }

    // fechar arquivo
    fclose(arq);

    return 0;
}
