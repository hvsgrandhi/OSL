#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024  // Size of the shared memory segment

int main() {
    key_t key = ftok("/tmp", 'S'); // Use the same key as the server to access the shared memory
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Get the shared memory segment ID
    int shmid = shmget(key, SHM_SIZE, 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    // Attach the shared memory segment to the client's address space
    char *shm = shmat(shmid, NULL, 0);
    if (shm == (char *)(-1)) {
        perror("shmat");
        exit(1);
    }

    // Read the message from the shared memory
    printf("Message received from shared memory: %s\n", shm);

    // Detach the shared memory segment
    shmdt(shm);

    // Delete the shared memory segment (optional)
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
