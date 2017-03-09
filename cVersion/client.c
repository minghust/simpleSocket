#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <syslog.h>
#include <stdlib.h>
#include <errno.h>
#include <arpa/inet.h>
#include <unistd.h>
#define MAX_LISTEN_NUM 5
#define SEND_BUF_SIZE 100
#define RECV_BUF_SIZE 100
#define SERVER_PORT 3500
int main()
{
    /* -------------Variable definition---------------*/
    int flag = 0;
    int clientSocket;
    long retlen;
    unsigned long sendlen;
    char *pbuf;
    char recvbuf[RECV_BUF_SIZE];
    char sendbuf[SEND_BUF_SIZE];
    struct sockaddr_in *serverAddr = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
    /* ------------------------------------------------ */
    
    /* ---------------Initialize socket---------------- */
    serverAddr->sin_family = AF_INET;
    inet_aton("127.0.0.1", (struct in_addr *)&(serverAddr->sin_addr)); // change host "127.0.0.1" to big endian
    serverAddr->sin_port = htons(SERVER_PORT);
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(clientSocket < 0)
    {
        printf("CREATE SOCKET ERROR\n");
        return 0;
    }
    if(connect(clientSocket, (struct sockaddr *)serverAddr, sizeof(*serverAddr)) < 0)
    {
        printf("CONNECT ERROR\n");
        return 0;
    }
    
    printf("THIS IS CLIENT：D\n");
    /* ----------------------------------------------- */
    
    /* ---------------Data processing----------------- */
    while(1)
    {
        if(!flag) // Send
        {
            pbuf = sendbuf;
            printf("\nCLIENT('q OR Q' TO QUIT): ");
            fgets(sendbuf, SEND_BUF_SIZE, stdin);
            sendlen = strlen(sendbuf) + 1;
            retlen = send(clientSocket, pbuf, sendlen, 0);
            if(retlen < 0)
            {
                if(errno == EINTR)
                    retlen = 0;
                else
                {
                    close(clientSocket);
                    return 0;
                }
            }
            if(*pbuf == 'q' || *pbuf == 'Q')
            {
                printf("\n...\n");
                pbuf = recvbuf;
                recv(clientSocket, pbuf, RECV_BUF_SIZE, 0);
                if(!strcmp(recvbuf, "!@clientDisconnect"))
                {
                    close(clientSocket);
                    break;
                }
                else
                    printf("\nOH! QUIT ERROR!");
            }
            flag = 1;
        }
        else // Receive
        {
            pbuf = recvbuf;
            retlen = recv(clientSocket, pbuf, RECV_BUF_SIZE, 0);
            if(*pbuf == 'q' || *pbuf == 'Q')
            {
                char serverDisconnect[] = "!@serverDisconnect";
                pbuf = serverDisconnect;
                send(clientSocket, pbuf, strlen(serverDisconnect) + 1, 0);
                close(clientSocket);
                break;
            }
            if(retlen < 0)
            {
                if(errno == EINTR)
                    retlen = 0;
                else
                {
                    close(clientSocket);
                    printf("\nRECEIVE DATA ERROR!");
                    return 0;
                }
            }
            printf("\nMESSAGE FROM SERVER: %s",recvbuf);
            flag = 0;
        }
    }
    /* ------------------------------------------------- */
    printf("\nProgram by Ming Zhang, obey MIT LICENSE:D\nBye~\n\n");
    return 0;

}
