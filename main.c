#include <stdio.h>     // Para operações de entrada e saída (printf, fprintf, fopen, fclose)
#include <locale.h>    // Para configurar a localidade (ex.: setlocale para Português)
#include <stdlib.h>    // Para funções de utilidade geral (ex.: exit)
#include <time.h>      // Para obter a data e hora atuais (ex.: time, localtime)
#include "tokens.h"    // Declaração do enum TokenType, estrutura Token e funções relacionadas

int main() {
    setlocale(LC_ALL, "Portuguese");

    int continuar = 1;
    while (continuar) {
        // Obter a data e hora atuais para criar nomes de arquivos únicos
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);

        // Formatando nomes dos arquivos com base na data e hora
        char output_filename[64];
        snprintf(output_filename, sizeof(output_filename), "output_%d-%02d-%02d_%02d-%02d-%02d.txt",
                 tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
                 tm.tm_hour, tm.tm_min, tm.tm_sec);

        // Solicitar a escolha do usuário
        int escolha;
        printf("Escolha um arquivo de entrada:\n");
        printf("1. input1.p-\n");
        printf("2. input2.p-\n");
        printf("3. input3.p-\n");
        printf("Digite sua escolha (1-3): ");
        scanf("%d", &escolha);

        // Determinar o nome do arquivo de entrada com base na escolha do usuário
        char *input_filename;
        switch (escolha) {
            case 1: input_filename = "input1.p-"; break;
            case 2: input_filename = "input2.p-"; break;
            case 3: input_filename = "input3.p-"; break;
            default: printf("Escolha inválida. Usando input1.p- por padrão.\n");
                     input_filename = "input1.p-"; break;
        }

        // Abrir o arquivo de entrada para leitura
        FILE *source = fopen(input_filename, "r");
        if (source == NULL) {
            printf("Erro ao abrir o arquivo de entrada.\n");
            return 1;
        }

        // Abrir o arquivo de saída para gravação
        FILE *output = fopen(output_filename, "w");
        if (output == NULL) {
            fprintf(stderr, "Erro ao abrir o arquivo %s\n", output_filename);
            fclose(source); // Fecha o arquivo de entrada caso haja erro
            exit(1);
        }

        // Inicia a leitura do primeiro token e grava em output
        while (1) {
            Token token = nextToken(source);
            fprintf(output, "Token: %d, Lexema: %s, Descrição: %s\n", token.type, token.lexeme, tokenTypeToString(token.type));
            if (token.type == TOKEN_EOF) break;
        }

        // Fecha os arquivos
        fclose(source);
        fclose(output);

        printf("Analise lexica concluida. Verifique '%s' para detalhes.\n", output_filename);

        // Perguntar ao usuário se deseja continuar
        printf("Deseja analisar outro arquivo? (1 - Sim, 0 - Nao): ");
        scanf("%d", &continuar);
    }

    return 0;
}
