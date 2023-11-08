#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIFO1 "fifo1"
#define FIFO2 "fifo2"
#define MAX_BUF 1024

int main() {
    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    int fd1 = open(FIFO1, O_WRONLY);
    int fd2 = open(FIFO2, O_RDONLY);

    char sentence[MAX_BUF];

    while (1) {
        printf("Enter a sentence (or 'exit' to quit): ");
        fgets(sentence, MAX_BUF, stdin);

        if (strcmp(sentence, "exit\n") == 0) {
            close(fd1);
            close(fd2);
            break;
        }

        write(fd1, sentence, strlen(sentence) + 1);

        char result[MAX_BUF];
        read(fd2, result, sizeof(result));
        printf("Received from the receiver: %s\n", result);
    }

    unlink(FIFO1);
    unlink(FIFO2);

    return 0;
}
