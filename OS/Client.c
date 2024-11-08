#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>

#define SHM_KEY 1234
#define SHM_SIZE 1024

int main() {
    // Getting the shared memory segment using the same key as the server
    int shmid = shmget(SHM_KEY, SHM_SIZE, 0666);
    if (shmid == -1) {
        perror("shmget failed");
        exit(1);
    }

    // Attaching to the shared memory
    char *shm_ptr = (char *)shmat(shmid, NULL, 0);
    if (shm_ptr == (char *)-1) {
        perror("shmat failed");
        exit(1);
    }

    // Reading the message from shared memory
    printf("Client: Waiting for message from server...\n");
    while (*shm_ptr == '\0') {  // Wait until the server writes something
        sleep(1);
    }

    printf("Client: Received message from server: %s\n", shm_ptr);

    // Indicate that the client has read the message
    *shm_ptr = '*';  // Change the first byte to '*' to signal the server

    shmdt(shm_ptr);  // Detach from shared memory

    printf("Client: Finished reading the message and signaling server.\n");
    return 0;
}

