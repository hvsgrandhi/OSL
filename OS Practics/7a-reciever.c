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

    int fd1, fd2;

    fd1 = open(FIFO1, O_RDONLY);
    fd2 = open(FIFO2, O_WRONLY);

    
    FILE *outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        perror("File opening failed");
        exit(1);
    }

    char sentence[MAX_BUF];

    while (1) {
        read(fd1, sentence, sizeof(sentence));
	printf("recieved from sender %s", sentence);

        if (strcmp(sentence, "exit\n") == 0) {
            fclose(outputFile);
            close(fd1);
            close(fd2);
            break;
        }

        // Process the sentence
        int charCount = 0, wordCount = 0, lineCount = 0;
        int isWord = 0;

        for (int i = 0; sentence[i] != '\0'; i++) {
            charCount++;
            if (sentence[i] == ' ' || sentence[i] == '\n' || sentence[i] == '\t') {
                isWord = 0;
            } else if (!isWord) {
                isWord = 1;
                wordCount++;
            }
            if (sentence[i] == '\n') {
                lineCount++;
            }
        }
        close(fd1);

        // Write results to the file
        fprintf(outputFile, "Characters: %d, Words: %d, Lines: %d\n", charCount, wordCount, lineCount);
        fflush(outputFile);

        // Send the results back to the sender
        char result[MAX_BUF];
        sprintf(result, "Characters: %d, Words: %d, Lines: %d", charCount, wordCount, lineCount);
	
        write(fd2, result, strlen(result) + 1);
        fd1 = open(FIFO1, O_RDONLY);
    }

    unlink(FIFO1);
    unlink(FIFO2);

    return 0;
}


// less output.txt