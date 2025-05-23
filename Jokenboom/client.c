#include "common_module.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>

/* Alguns trechos de código foram inspirados nas aplicações da Playlist de Programação de Sockets
do Prof. Ítalo Cunha, e serão devidamente sinalizados. 
Vídeo-aula disponível em: https://www.youtube.com/watch?v=tJ3qNtv0HVs&list=PLyrH0CFXIM5Wzmbv-lC-qvoBejsa803Qk&ab_channel=%C3%8DtaloCunha*/

// Printa a forma correta de fornecer as informações IP e porta
// argc conta o número de argumentos passados pela linha de comando
// argv e um vetor com os argumentos, onde cada argumento é uma string
void auxUso(int argc, char **argv){ /* Trecho inspirado na aula do Prof. Ítalo Cunha */
    printf("Entrada para utilização: %s <server IP> <server port>\n", argv[0]);
    return;
}

int main(int argc, char **argv){
    if (argc != 3) { 
        auxUso(argc, argv);
    }

    struct sockaddr_storage server_addr; // Armazena o endereço do servidor

    // Configurar o endereço de rede (v4 ou v6) em uma estrutura do tipo sockaddre_storage
    int auxConf = configura_addr(argv[1], argv[2], &server_addr);
    if (auxConf != 0){ 
        auxUso(argc, argv);
    }

    int sock;
    sock = socket(server_addr.ss_family, SOCK_STREAM, 0); // Criação de um socket do tipo SOCK_STREAM

    struct sockaddr *addr = (struct sockaddr *)(&server_addr); // Faz um cast de sockaddr_storage para sockaddr

    int conn = connect(sock, addr, sizeof(server_addr)); // Tenta conexão com o servidor através do socket criado

    if ( conn == 0) { // Se conexão bem-sucedida, exibe mensagem de exito
        printf("Conectado ao servidor.\n");
    }

    //
    
    close(sock); // Fecha o socket
    return 0;
}
