//7b
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>
#define SHM_KEY 1234
#define SHM_SIZE 1024
int main() {
    int shmid = shmget(SHM_KEY, SHM_SIZE, 0666 | IPC_CREAT);
    if (shmid == -1) 
{
        perror("shmget failed");
        exit(1);
    }
    char *shm_ptr = (char *)shmat(shmid, NULL, 0);
    if (shm_ptr == (char *)-1) 
{
        perror("shmat failed");
        exit(1);
    }
    printf("Server: Enter a message to write to shared memory: ");
    fgets(shm_ptr, SHM_SIZE, stdin);
    shm_ptr[strlen(shm_ptr) - 1] = '\0';
    printf("Server: Message written to shared memory: %s\n", shm_ptr);
    printf("Server: Waiting for client to read the message...\n");
    while (*shm_ptr != '*') {
        sleep(1);
    }

    shmdt(shm_ptr);

    shmctl(shmid, IPC_RMID, NULL);
    printf("Server: Shared memory cleaned up. Exiting.\n");
    return 0;
}




