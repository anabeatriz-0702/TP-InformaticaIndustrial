#include "common_module.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/socket.h>

/* Alguns trechos de código foram inspirados nas aplicações da Playlist de Programação de Sockets
do Prof. Ítalo Cunha, e serão devidamente sinalizados. 
Vídeo-aula disponível em: https://www.youtube.com/watch?v=tJ3qNtv0HVs&list=PLyrH0CFXIM5Wzmbv-lC-qvoBejsa803Qk&ab_channel=%C3%8DtaloCunha*/

// Printa a forma correta de fornecer as informações IP e porta
// argc conta o número de argumentos passados pela linha de comando
// argv e um vetor com os argumentos, onde cada argumento é uma string
void auxUso(int argc, char **argv){ /* Trecho inspirado na aula do Prof. Ítalo Cunha */
    printf("Entrada para utilização: %s <v4|v6> <server port>\n", argv[0]); 
    return; // Retorna erro
}

int main(int argc, char **argv){
    // Verificação do número de argumentos passados pela linha de comando
    if (argc != 3) { /* Trecho inspirado na aula do Prof. Ítalo Cunha */
        auxUso(argc, argv);
    }

    struct sockaddr_storage server_addr; // Armazena o endereço do servidor (suporta tanto v4 quanto v6)

    // Configurar um endereço de servidor para determinada rede
    int auxEnd = inicializar_addr_server(argv[1], argv[2], &server_addr);
    if (auxEnd != 0){ // Teste de erro de inicialização do endereço
        auxUso(argc, argv);
    }

    int sock;
    sock = socket(server_addr.ss_family, SOCK_STREAM, 0); // Criação de um socket do tipo SOCK_STREAM

    printf("Servidor iniciado em modo IP%s na porta %s. Aguardando conexão...\n", argv[1], argv[2]);

    int opt = 1; // Ativação 
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)); // Permitir reutilização do endereço IP e porta

    struct sockaddr *addr = (struct sockaddr *)(&server_addr); // Faz um cast de sockaddr_storage para sockaddr

    bind(sock, addr, sizeof(server_addr)); // Associa o socket ao endereço do servidor
    listen(sock, 1); // Socket em escuta para 1 cliente

    /* Trecho inspirado na aula do Prof. Ítalo Cunha: servidor aceitar conexões do cliente */
    struct sockaddr_storage addr_client; // Armazenar endereço do cliente
    struct sockaddr *c_addr = (struct sockaddr *)(&addr_client); 
    socklen_t addrlen_client = sizeof(addr_client); // Tamanho da estrutura que armazena o endereço do cliente

    int client_sock = accept(sock, c_addr, &addrlen_client); // Conexão aceita em um novo socket para o cliente
    // A comunicação será feita pelo socket do cliente
    printf("Cliente conectado.\n");
    
    while(1){
        // Lógica do Jokenboom

    }

    close(client_sock);
    close(sock); // Fecha o socket
    return 0;
}
