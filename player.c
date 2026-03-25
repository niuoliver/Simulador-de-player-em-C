#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

// Estrutura de um nó das listas duplamente encadeadas
typedef struct Nodo{
    char nome[64];
    char artista[64];
    float duracao;
    int posicao;
    struct Nodo *prox;
    struct Nodo *ant;
} Nodo;

// função para a inicialização de novos Nodos.
Nodo *novoNodo(char nome[], char artista[], float duracao){
    Nodo *novo = (Nodo*)malloc(sizeof(Nodo));
    if(novo==NULL){
        printf("Erro de alocação na memória.\n");
        return NULL;
    }

    strcpy(novo->nome, nome);
    strcpy(novo->artista, artista);
    novo->duracao = duracao;
    novo->posicao = 0;
    novo->ant = NULL;
    novo->prox = NULL;

    return novo;
}

// inserção de valores no final de listas.
Nodo *insereFim(Nodo *lista, char nome[], char artista[], float duracao){
    Nodo *novo = novoNodo(nome, artista, duracao);
    if(novo==NULL){return lista;}

    if(lista==NULL){return novo;}

    Nodo *temp = lista;
    while(temp->prox!=NULL){
        temp=temp->prox;
    }
    temp->prox = novo;
    novo->ant = temp;

    return lista;
}

// inserção de valores no inicio de listas.
Nodo *insereInicio(Nodo *lista, char nome[], char artista[], float duracao){
    Nodo *novo = novoNodo(nome, artista, duracao);
    if(novo==NULL){return lista;}

    if(lista!=NULL){
        novo->prox = lista;
        lista->ant = novo;
    }
    
    return novo;
}

// inserção de valores no meio de listas.
Nodo *insereMeio(Nodo *lista, char nome[], char artista[], float duracao, int posicao){
    if(lista==NULL || posicao <= 1){
        return insereInicio(lista, nome, artista, duracao);
    }

    Nodo *novo = novoNodo(nome, artista, duracao);
    if(novo==NULL){return lista;}

    Nodo *temp = lista;
    int contador = 1;
    
    // Navega até a posição desejada ou até o final
    while(temp->prox != NULL && contador < posicao - 1){
        temp = temp->prox;
        contador++;
    }

    // Insere após o nó temp
    novo->prox = temp->prox;
    novo->ant = temp;
    
    if(temp->prox != NULL){
        temp->prox->ant = novo;
    }
    temp->prox = novo;

    return lista;
}

//remoção de elementos do inicio de listas.
Nodo *removeInicio(Nodo *lista){
    if(lista == NULL){
        printf("Lista vazia.\n");
        return NULL;
    }

    Nodo *temp = lista;
    lista = lista->prox;
    if(lista != NULL){
        lista->ant = NULL;
    }
    free(temp);

    return lista;
}

//remoção de elementos do fim de listas.
Nodo *removeFim(Nodo *lista){
    if(lista==NULL){return NULL;}

    // Caso tenha apenas um elemento
    if(lista->prox == NULL){
        free(lista);
        return NULL;
    }

    Nodo *temp = lista;
    while(temp->prox != NULL){
        temp = temp->prox;
    }
    
    temp->ant->prox = NULL;
    free(temp);

    return lista;
}

// remoção de elementos do meio de listas.
Nodo *removeMeio(Nodo *lista, int posicao){
    if(lista == NULL){
        return NULL;
    }
    
    // Caso especial: remover o primeiro elemento
    if(posicao == 1){
        return removeInicio(lista);
    }

    Nodo *temp = lista;
    int contador = 1;

    while(temp != NULL && contador < posicao){
        temp = temp->prox;
        contador++;
    }

    if(temp == NULL){
        printf("Posição não encontrada.\n");
        return lista;
    }

    // Ajusta os ponteiros dos nós vizinhos
    if(temp->ant != NULL){
        temp->ant->prox = temp->prox;
    }
    if(temp->prox != NULL){
        temp->prox->ant = temp->ant;
    }

    free(temp);
    return lista;
}

//função que ordena músicas de forma aleatória na fila(algoritmo de Fisher-Yates).
Nodo *embaralha(Nodo *lista){
    if(lista==NULL){return NULL;}

    //contando o número de nós.
    int tam = 0;
    Nodo *aux = lista;
    while(aux!=NULL){
        tam++;
        aux = aux->prox;
    }

    //cria vetor de ponteiros para reordenar os nós.
    Nodo **vetor = (Nodo**)malloc(tam * sizeof(Nodo *));
    aux = lista;
    for(int i=0;i<tam;i++){
        vetor[i] = aux;
        aux = aux->prox;
    }

    //embaralha o vetor.
    srand(time(NULL));
    for(int i=tam-1;i>0;i--){
        int j = rand()%(i+1);
        //swap de valores dentro do vetor.
        Nodo *temp = vetor[i];
        vetor[i] = vetor[j];
        vetor[j] = temp;
    }

    //reconstrução da lista encadeada.
    for(int i=0;i<tam;i++){
        if(i == 0){
            vetor[i]->ant = NULL;
            vetor[i]->prox = vetor[i+1];
        } else if(i == tam-1){
            vetor[i]->ant = vetor[i-1];
            vetor[i]->prox = NULL;
        } else {
            vetor[i]->ant = vetor[i-1];
            vetor[i]->prox = vetor[i+1];
        }
    }

    //atualização do ponteiro do início da lista.
    Nodo *novaLista = vetor[0];
    free(vetor);

    return novaLista;
}

//---Modularização do programa---------------------------------------------------------------------

// função que imprime todos os elementos da playlist.
void mostraLista(Nodo *lista){
    if(lista==NULL){
        printf("Lista vazia.\n");
        return;
    }

    Nodo *temp = lista;
    printf("Sua playlist:\n");
    while(temp!=NULL){
        printf("[%d]. Música - %s. Artista - %s. Duração - %.2f.\n", temp->posicao, temp->nome, temp->artista, temp->duracao);
        temp=temp->prox;
    }
    printf("\n");
}

//função para a correção dos índices das músicas na playlist.
Nodo *indx(Nodo *playlist){
    if(playlist==NULL){
        return NULL;
    }
    int idx = 1;
    Nodo *aux = playlist;
    while(aux!=NULL){
        aux->posicao = idx;
        aux = aux->prox;
        idx++;
    }
    return playlist;
}

// função para inserção de músicas via terminal(insere músicas na playlist principal).
Nodo *inserePlaylist(Nodo *playlist){
    char nome[64], artista[64];
    float duracao;
    int pos;
    
    printf("Insira o nome da sua música: ");
    scanf(" %s", nome);
    printf("Insira o nome do artista: ");
    scanf(" %s", artista);
    printf("Insira a duração da música: ");
    scanf("%f", &duracao);
    
    if(playlist != NULL){
        mostraLista(playlist);
        printf("Insira a posição em que deseja inserir a música: ");
        scanf("%d", &pos);
        playlist = insereMeio(playlist, nome, artista, duracao, pos);
    } else {
        playlist = insereInicio(playlist, nome, artista, duracao);
    }
    
    playlist = indx(playlist);
    return playlist;
}

//função que busca músicas com base em valores fornecidos.
void buscaMusicas(Nodo *playlist){
    if(playlist==NULL){
        printf("Lista vazia.\n");
        return;
    }

    Nodo *search = playlist;
    bool encontrado = false;
    char entry[64];

    printf("Digite o nome da música ou artista: ");
    scanf("%s", entry);

    while(search!=NULL){
        if(strstr(search->nome, entry) != NULL || strstr(search->artista, entry) != NULL){
            printf("Música encontrada: %s. Artista - %s. Duração - %.2f\n", search->nome, search->artista, search->duracao);
            encontrado = true;
        }
        search = search->prox;
    }
    if(encontrado==false){
        printf("Nenhuma referência encontrada.\n");
    }
}

//função para a liberação de memória chamada ao encerrar funções e ao encerrar o programa.
void liberaMemoria(Nodo *lista){
    while(lista!=NULL){
        Nodo *temp = lista;
        lista = lista->prox;
        free(temp);
    }
}

// função para reprodução da playlist.
void reproducao(Nodo *playlist){
    if(playlist == NULL){
        printf("Playlist vazia.\n");
        return;
    }
    
    Nodo *fila = NULL; // fila de reprodução
    Nodo *pilha = NULL; // histórico de reprodução
    Nodo *buffer = NULL; // música atual
    int op;
    char status[16] = "tocando";

    // Copia a playlist para a fila de reprodução
    Nodo *temp = playlist;
    while(temp != NULL){
        fila = insereFim(fila, temp->nome, temp->artista, temp->duracao);
        temp = temp->prox;
    }

    // Escolha do modo de reprodução
    printf("Escolha o modo de reproducao: [1].normal - [2].shuffle.\n");
    scanf("%d", &op);
    if(op == 2){
        fila = embaralha(fila);
    }

    // Inicializa o buffer com a primeira música
    if(fila != NULL){
        buffer = fila;
        fila = removeInicio(fila);
    }

    // Menu de reprodução
    char nome[64], artista[64];
    float duracao;
    
    while(buffer != NULL){
        printf("\n%s: %s — %s (%.2f)\n", status, buffer->nome, buffer->artista, buffer->duracao);
        printf("[1] anterior | [2] pausa | [3] próxima | [4] adicionar | [5] mostrar fila | [0] sair\n> ");
        scanf("%d", &op);
        
        switch (op){
            case 1: // anterior
                if(pilha != NULL){
                    // Move a música atual para o início da fila
                    fila = insereInicio(fila, buffer->nome, buffer->artista, buffer->duracao);
                    // Recupera a música anterior da pilha
                    buffer = pilha;
                    pilha = removeInicio(pilha);
                    strcpy(status, "tocando");
                } else {
                    printf("Não há música anterior.\n");
                }
                break;
                
            case 2: // pausa
                if(strcmp(status, "pausado") == 0){
                    strcpy(status, "tocando");
                } else {
                    strcpy(status, "pausado");
                }
                break;
                
            case 3: // próxima
                if(fila != NULL){
                    // Adiciona a música atual ao histórico
                    pilha = insereInicio(pilha, buffer->nome, buffer->artista, buffer->duracao);
                    // Pega a próxima música da fila
                    buffer = fila;
                    fila = removeInicio(fila);
                    strcpy(status, "tocando");
                } else {
                    printf("Fim da playlist.\n");
                    // Se chegou ao fim, volta para o início
                    if(pilha != NULL){
                        fila = pilha;
                        pilha = NULL;
                        fila = embaralha(fila); // Reembaralha para recomeçar
                        buffer = fila;
                        fila = removeInicio(fila);
                    }
                }
                break;
                
            case 4: // adicionar
                printf("Insira as informações da música:\n");
                printf("nome: ");
                scanf("%s", nome);
                printf("artista: ");
                scanf("%s", artista);
                printf("duracao: ");
                scanf("%f", &duracao);
                fila = insereFim(fila, nome, artista, duracao);
                break;
                
            case 5: // mostrar fila
                mostraLista(fila);
                break;
                
            case 0: // sair
                printf("Reprodução encerrada :)\n");
                liberaMemoria(fila);
                liberaMemoria(pilha);
                return;
                
            default:
                printf("Opção inválida.\n");
        }
    }
    
    printf("Playlist finalizada.\n");
    liberaMemoria(fila);
    liberaMemoria(pilha);
}

int main() {
    Nodo *playlist = NULL; // playlist criada pelo usuário
    int op, pos;
    
    while(1){
        printf("\n===== MENU =====\n");
        printf("[1] Inserir música\n[2] Reproduzir playlist\n[3] Mostrar playlist\n[4] Buscar música\n[5] Remover música\n[0] Sair\n> ");
        scanf("%d", &op);

        switch (op){
            case 1:
                playlist = inserePlaylist(playlist);
                break;
            case 2:
                reproducao(playlist);
                break;
            case 3:
                mostraLista(playlist);
                break;
            case 4:
                buscaMusicas(playlist);
                break;
            case 5:
                if(playlist != NULL){
                    mostraLista(playlist);
                    printf("\nInsira o índice da música que deseja remover: ");
                    scanf("%d", &pos);
                    playlist = removeMeio(playlist, pos);
                    playlist = indx(playlist); // Reindexa após remoção
                } else {
                    printf("Playlist vazia.\n");
                }
                break;
            case 0:
                printf("Até logo :)\n");
                liberaMemoria(playlist);
                return 0;
            default:
                printf("Opção inválida.\n");
        }
    }
    
    return 0;
}