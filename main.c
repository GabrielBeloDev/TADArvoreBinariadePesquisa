    #include "abp.h"
    #include <locale.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    int cmp(void *data, void *key) {
        Time *timeData = (Time *)data;
        Time *timeKey = (Time *)key;
        return strcmp(timeData->nome, timeKey->nome);
    }

    void visit(void *data) {
        Time *time = (Time *)data;
        printf("\nTime: %s", time->nome);
    }

    int main(void) {
        setlocale(LC_ALL, "Portuguese_Brazil");
        TNode *t = NULL;
        Time *time;
        int opcao = 0;
        int arvoreCriada = 0;

        do {
            printf("\n\n|------------------------------------------------|\n");
            printf("|                      MENU                      |\n");
            printf("|------------------------------------------------|\n");
            printf("|| 1. Criar uma Árvore Vazia\n");
            printf("|| 2. Inserir time na Arvore Binaria de Pesquisa\n");
            printf("|| 3. Remover time especificado na Arvore Binaria de Pesquisa\n");
            printf("|| 4. Consultar se um time está na Arvore Binaria de Pesquisa\n");
            printf("|| 5. Listar todos os times da Arvore Binaria de Pesquisa\n");
            printf("|| 6. Destruir a Árvore\n");
            printf("|| 7. Sair\n");
            printf("||- Sua escolha: ");
            scanf("%d", &opcao);
            getchar();

            switch (opcao) {
            case 1:
                destroyTree(t);
                t = NULL;
                arvoreCriada = 1;
                printf("\nÁrvore vazia criada!\n");
                break;
            case 2:
                if (!arvoreCriada) {
                    printf("\nPrimeiro crie uma árvore vazia!\n");
                    break;
                }
                time = (Time *)malloc(sizeof(Time));
                printf("\nDigite o nome do time: ");
                fgets(time->nome, 50, stdin);
                time->nome[strcspn(time->nome, "\n")] = 0;
                t = abpInsert(t, time, cmp);
                printf("\nTime inserido.\n");
                break;
            case 3:
                if (!arvoreCriada || t == NULL) {
                    printf("\nNão há times na árvore para remover!\n");
                    break;
                }
                time = (Time *)malloc(sizeof(Time));
                printf("\nDigite o nome do time a remover: ");
                fgets(time->nome, 50, stdin);
                time->nome[strcspn(time->nome, "\n")] = 0;
                void *data = NULL;
                t = abpRemove(t, time, cmp, &data);
                if (data != NULL) {
                    printf("\nTime '%s' removido da arvore!\n", ((Time *)data)->nome);
                    free(data);
                } else {
                    printf("\nTime não encontrado na arvore!\n");
                }
                free(time);
                break;
            case 4:
              if (!arvoreCriada) {
                printf("\nPrimeiro crie uma árvore vazia!\n");
                break;
              }
              if (t == NULL) {
                printf("\nNão há times na árvore para consultar!\n");
                break;
              }
              time = (Time *)malloc(sizeof(Time));
              printf("\nDigite o nome do time que deseja encontrar: ");
              fgets(time->nome, 50, stdin);
              time->nome[strcspn(time->nome, "\n")] = 0;
              Time *foundTime = (Time *)abpQuery(t, time, cmp);
              if (foundTime != NULL) {
                printf("\nO time '%s' está na arvore!\n", foundTime->nome);
              } else {
                printf("\nTime não encontrado na arvore!\n");
              }
              free(time);
              break;
            case 5:
              if (!arvoreCriada) {
                printf("\nPrimeiro crie uma árvore vazia!\n");
                break;
              }
              if (t == NULL) {
                printf("\nNão há times na árvore para listar!\n");
                break;
              }
              simetrico(t, visit);
              break;
            case 6:
                if (!arvoreCriada) {
                    printf("\nNão há árvore para destruir!\n");
                    break;
                }
                destroyTree(t);
                t = NULL;
                arvoreCriada = 0;
                printf("\nÁrvore destruída!\n");
                break;
            case 7:
                printf("\nSaindo...\n");
                destroyTree(t);
                break;
            default:
                printf("\nDigite uma opcao valida!\n");
            }
        } while (opcao != 7);

        return 0;
    }
