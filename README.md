# Simulador-de-player-em-C
Um simulador de player de músicas feito em c/cpp que utiliza lógica de FIFO e LIFO para administrar as playlists.


Funcionamento geral.
O sistema implementa uma lista duplamente encadeada que armazena dados de músicas em seus nós de forma dinâmica. 
O sistema permite que usuário crie uma playlist inserindo novas músicas na posição que desejar. Ao selecionar a opção de reprodução os dados salvos na playlist são carregados numa fila de reprodução, outra lista duplamente encadeada declarada internamente, caso prefira o usuário pode selecionar o modo de reprodução aleatória, em que a fila de reprodução é carregada com os dados da playlist fora de ordem.
Durante a reprodução a música selecionada é carregada em um buffer, ao avançar o buffer descarrega seus dados em uma pilha e carrega os dados da próxima música na fila. Ao retroceder o buffer descarrega seus dados no início da fila e carrega a música salva no topo da pilha (histórico de reprodução).
O usuário pode também adicionar novas músicas no final da fila de reprodução enquanto o player estiver tocando as músicas já carregadas.
Além disse foram implementadas diversas funções auxiliares para garantir o melhor funcionamento do sistema.
Funções do sistema.
novoNodo – essa função inicializa novos nós com dados inseridos pelo usuário e ponteiros apontando para valores default.
insereFim – insere nós no final da lista.
insereMeio – insere nós no meio da fila de acordo com a posição fornecida pelo usuário.
insereInicio – insere nós no início da fila.
removeInicio – remove nós do início da fila.
removeMeio – remove nós do meio da fila de acordo com a posição fornecida pelo usuário.
removeFim – remove nós do fim da fila.
embaralha – implementa o algoritmo de Fisher – Yates para embaralhar os nós da lista de forma aleatória. Funciona ao carregar os nós da lista fornecida para a função em posições aleatórias de um vetor de ponteiros. As posições são sorteadas usando a função “rand”. Quando o vetor de ponteiros está totalmente preenchido a função entra em um loop que reconstrói a lista com os elementos reordenados.
mostraLista – função que imprime os elementos da playlist em forma de tabela.
Index – função que atualiza os indicies das músicas na playlist. É chamada sempre que uma nova música é adicionada.
inserPlaylist – essa função é implementada unicamente para inserir músicas na playlist principal.  Recebe como entrada via terminal os dados da música a ser adicionada e chama as funções “insereMeio” e “index”.
buscaMusicas – função que percorre a playlist comparando os valores salvos com os valores fornecidos. Se há incidências do valor buscado, a função retorna uma tabela com essas incidências. Se não, retorna uma mensagem negativa.
liberaMemoria – libera os ponteiros fornecidos para a função.
Reprodução – essa função implementa a lógica de reprodução do player. Recebe como parâmetro a playlist principal e carrega internamente os ponteiros “fila”, “pilha” e “buffer” para que alterações feitas pelo usuário durante a reprodução da playlist não afetem a playlist original.
