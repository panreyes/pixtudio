#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

/** Returns true on success, or false if there was an error */
int SetSocketBlockingEnabled(int fd, int blocking) {
    if (fd < 0) {
        return -1;
    }

#ifdef WIN32
    unsigned long mode = blocking ? 0 : 1;
    return (ioctlsocket(fd, FIONBIO, &mode) == 0) ? 0 : -1;
#else
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags < 0) {
        return -1;
    }
    flags = blocking ? (flags&~O_NONBLOCK) : (flags|O_NONBLOCK);
    return (fcntl(fd, F_SETFL, flags) == 0) ? 0 : -1;
#endif
}


int main(int argc , char *argv[]) {
    int sock;
    struct sockaddr_in server;
    char message[1000] , server_reply[2000];

    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1) {
        fprintf(stderr, "Could not create socket\n");
    }
    printf("Socket created\n");

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons( 8888 );

    // Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0) {
        fprintf(stderr, "connect failed. Error\n");
        return 1;
    }

    printf("Connected\n");
    sleep(1);
    // Make the socket nonblocking so that we can read all the info
    // the server wants to send us
    SetSocketBlockingEnabled(sock, 0);
    // Read all the info the server wants to send us
    int retval;
    while((retval = recv(sock , server_reply , 2000 , 0)) >= 0) {
        printf("%s\n", server_reply);
    }
    SetSocketBlockingEnabled(sock, 1);

    // keep communicating with server
    while(1) {
        printf("Enter message : ");
        fscanf(stdin, "%s" , message);

        //Send some data
        if( send(sock , message , strlen(message) , 0) < 0) {
            fprintf(stderr, "Send failed\n");
            return 1;
        }

        //Receive a reply from the server
        if( recv(sock , server_reply , 2000 , 0) < 0) {
            fprintf(stderr, "recv failed\n");
            break;
        }

        printf("Server reply : ");
        printf("%s\n", server_reply);
    }

    close(sock);
    return 0;
}
