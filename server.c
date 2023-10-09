#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define SERVER_IP "" // Private IP address

int main()
{
    // Declare variables
    int server_fd, new_socket;
    struct sockaddr_in address; // Struct holds address information
    int addrlen = sizeof(address);

    // Create a socket
    // Return value should be handled
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    // Configure address
    address.sin_family = AF_INET; // Address uses IPV4
    address.sin_addr.s_addr = inet_addr(SERVER_IP); // Set up address
    address.sin_port = htons(PORT); // Convert PORT from host byte order to network byte order and set it up

    // Bind socket to IP and port 
    // Return value should be handled
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));

    // Listen for incoming requests
    // Return value should be handled
    listen(server_fd, 3);

    // Continuously handle incoming connections
    while (1)
    {
        // Accept an incoming connection
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);

        // Draft a response
        const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello, World!\r\n";

        // Send the response
        send(new_socket, response, strlen(response), 0);

        // Close the socket
        close(new_socket);
    }
}
