#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>

#define PORT 8080
#define SERVER_IP "192.168.0.7" // Private IP address

int main()
{
    // Create socket
    struct sockaddr_in server_address;

    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd < 0)
    {
        perror("socket error\n");
        return -1;
    }

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_address.sin_port = htons(PORT);

    int server_address_len = sizeof(server_address);

    // Bind
    if (bind(sfd, (struct sockaddr *)&server_address, server_address_len) < 0)
    {
        perror("bind error\n");
        return -1;
    }

    // Listen for incoming connections
    if (listen(sfd, 0) < 0)
    {
        perror("listen error\n");
        return -1;
    }

    printf("The server is listening for incoming connections\n");

    // Handle connections
    while (1)
    {
        // Accept connection
        int cfd = accept(sfd, (struct sockaddr *)&server_address, (socklen_t *)&server_address_len);

        // Send response
        const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello, World!\r\n";

        if (send(cfd, response, strlen(response), 0) < 0)
        {
            perror("send error\n");
            return -1;
        }
        printf("message sent\n");

        // Close socket
        close(cfd);
    }
}
