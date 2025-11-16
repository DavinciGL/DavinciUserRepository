#include <sys/socket.h>
#include <string.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        perror("socket");
        exit(1);
    }

    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_port = htons(12345),  // Use htons for portability
        .sin_addr.s_addr = INADDR_ANY
    };

    if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind");
        exit(1);
    }

    listen(s, 10);

    while (1) {
        int client_fd = accept(s, NULL, NULL);
        if (client_fd < 0) {
            perror("accept");
            continue;
        }

        char buffer[256] = {0};
        recv(client_fd, buffer, sizeof(buffer) - 1, 0);

        // Expecting: GET /file.html HTTP/1.1
        if (strncmp(buffer, "GET ", 4) != 0) {
            close(client_fd);
            continue;
        }

        char *f = buffer + 5;
        char *space = strchr(f, ' ');
        if (!space) {
            close(client_fd);
            continue;
        }
        *space = '\0';

        int opened_fd = open(f, O_RDONLY);
        if (opened_fd < 0) {
            const char *not_found = "HTTP/1.1 404 Not Found\r\n\r\nFile not found";
            send(client_fd, not_found, strlen(not_found), 0);
        } else {
            const char *ok = "HTTP/1.1 200 OK\r\n\r\n";
            send(client_fd, ok, strlen(ok), 0);
            sendfile(client_fd, opened_fd, NULL, 256);
            close(opened_fd);
        }

        close(client_fd);
    }

    close(s);
    return 0;
}