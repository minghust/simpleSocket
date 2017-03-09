#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h> // sockaddr_in
#include <stdlib.h>
#include <syslog.h>
#include <errno.h>
#include <unistd.h>

#define MAX_LISTEN_NUM 5
#define SEND_BUF_SIZE 100
#define RECV_BUF_SIZE 100
#define LISTEN_PORT 3500

int main()
{
    /* -------------Variable definition---------------*/
    int flag = 0;
    int listenSocket;
    int fromClientsock;
    unsigned long sendlen;
    long retlen;
    char *pbuf;
    char sendbuf[SEND_BUF_SIZE];
    char recvbuf[RECV_BUF_SIZE];
    
    struct sockaddr_in *serverAddr = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
    struct sockaddr_in *clientAddr = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
    unsigned int clientSocketLength = sizeof(*clientAddr);
    /* ------------------------------------------------ */
    
    /* ---------------Initialize socket---------------- */
    serverAddr->sin_family = AF_INET;
    serverAddr->sin_port = htons(LISTEN_PORT);       // change host little endian to big endian
    serverAddr->sin_addr.s_addr = htonl(INADDR_ANY); // change host "0.0.0.0" to big endian
    listenSocket = socket(AF_INET, SOCK_STREAM, 0);
    
    if(listenSocket < 0)
    {
        printf("CREATE SOCKET ERROR\n");
        return 0;
    }
    if(bind(listenSocket, (const struct sockaddr *)serverAddr, sizeof(*serverAddr)) < 0)
    {
        printf("BIND SOCKET ERROR\n");
        return 0;;
    }
    if(listen(listenSocket, MAX_LISTEN_NUM) < 0)
    {
        printf("LISTEN ERROR\n");
        return 0;;
    }
    
    fromClientsock = accept(listenSocket, (struct sockaddr *)clientAddr, &clientSocketLength);
    if(fromClientsock < 0)
    {
        printf("ACCEPTATION ERROR\n");
        exit(1);
    }
    
    printf("THIS IS SERVER：D\n");
    /* ----------------------------------------------- */
    
    /* ---------------Data processing----------------- */
    while(1)
    {
        if(!flag) // Receive
        {
            pbuf = recvbuf;
            retlen = recv(fromClientsock, pbuf, RECV_BUF_SIZE, 0);
            if(*pbuf == 'q' || *pbuf == 'Q')
            {
                char clientDisconnect[] = "!@clientDisconnect";
                pbuf = clientDisconnect;
                send(fromClientsock, pbuf, strlen(clientDisconnect) + 1, 0);
                close(fromClientsock);
                close(listenSocket);
                break;
            }
            if(retlen < 0)
            {
                if(errno == EINTR)
                    retlen = 0;
                else
                {
                    close(listenSocket);
                    printf("\nRECEIVE DATA ERROR!");
                    return 0;
                }
            }
            printf("\nMESSAGE FROM CILENT: %s",recvbuf);
            flag = 1;
        }
        else // Send
        {
            printf("\nSERVER('q OR Q' TO QUIT): ");
            fgets(sendbuf, SEND_BUF_SIZE, stdin);
            sendlen = strlen(sendbuf) + 1;
            pbuf = sendbuf;
            retlen = send(fromClientsock, pbuf, sendlen, 0);
            if(retlen < 0)
            {
                if(errno == EINTR)
                    retlen = 0;
                else
                {
                    close(listenSocket);
                    return 0;
                }
            }
            if(*pbuf == 'q' || *pbuf == 'Q')
            {
                printf("\n...\n");
                pbuf = recvbuf;
                recv(fromClientsock, pbuf, RECV_BUF_SIZE, 0);
                if(!strcmp(recvbuf, "!@serverDisconnect"))
                {
                    close(fromClientsock);
                    close(listenSocket);
                    break;
                }
                else
                    printf("\nOH! QUIT ERROR!");
            }
            flag = 0;
        }
    }
    /* ------------------------------------------------- */
    printf("\nProgram by Ming Zhang, obey MIT LICENSE:D\nBye~\n\n");
    return 0;
}
