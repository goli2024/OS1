#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>  // Add this header for sleep() function

#define buff_size 5  // Define the buffer size

// Structure to hold buffer and synchronization tools
typedef struct {
    int in, out, buffer[5];
    sem_t full, empty;
    pthread_mutex_t lock;
} BUFFER;

BUFFER b1;
int item = 1;

void init();
void *producer(void *num);
void *consumer(void *num);

int main() {
    int i, np, nc;
    pthread_t pid[buff_size], cid[buff_size];

    // Get the number of producers and consumers from user input
    printf("\nEnter the number of Producers: ");
    scanf("%d", &np);

    printf("\nEnter the number of Consumers: ");
    scanf("%d", &nc);

    // Initialize the buffer and semaphores
    init();

    // Create producer threads
    for (i = 0; i < np; i++) {
        int *arg = (int *)malloc(sizeof(*arg)); // Dynamically allocate memory for each argument
        *arg = i;
        pthread_create(&pid[i], NULL, producer, arg);
        printf("\nThread for Producer %d Created.\n", i);
    }

    // Create consumer threads
    for (i = 0; i < nc; i++) {
        int *arg = (int *)malloc(sizeof(*arg)); // Dynamically allocate memory for each argument
        *arg = i;
        pthread_create(&cid[i], NULL, consumer, arg);
        printf("\nThread for Consumer %d Created.\n", i);
    }

    // Wait for all producer threads to finish
    for (i = 0; i < np; i++) {
        pthread_join(pid[i], NULL);
        printf("\n-------- Thread for Producer %d Joined at End.\n", i);
    }

    // Wait for all consumer threads to finish
    for (i = 0; i < nc; i++) {
        pthread_join(cid[i], NULL);
        printf("\n-------- Thread for Consumer %d Joined at End.\n", i);
    }

    return 0;
}

// Initialize the buffer and semaphores
void init() {
    b1.in = 0;
    b1.out = 0;
    sem_init(&b1.empty, 0, buff_size);  // Buffer size is the initial value for empty slots
    sem_init(&b1.full, 0, 0);           // No items in the buffer initially
    pthread_mutex_init(&b1.lock, NULL); // Initialize the mutex lock
}

// Producer thread function
void *producer(void *num) {
    int i, value, z;

    i = *(int *)num;  // Get producer ID
    free(num);         // Free the dynamically allocated memory for thread argument

    printf("\n-------- Thread for Producer %d started the process for production of Items.\n", i);

    while (1) {
        z = (rand() % 10) + 1;  // Random sleep time for the producer
        sleep(z);  // Sleep for z seconds (POSIX sleep function)

        sem_wait(&b1.empty);  // Wait if the buffer is full
        pthread_mutex_lock(&b1.lock);  // Lock the critical section

        // Produce an item and put it in the buffer
        printf("\nProducer %d produced item %d (|)\n", i, item);
        b1.buffer[(b1.in++) % buff_size] = item++;  // Put the item in the buffer
        pthread_mutex_unlock(&b1.lock);  // Unlock the critical section

        sem_post(&b1.full);  // Signal that there is a new item in the buffer
    }
}

// Consumer thread function
void *consumer(void *num) {
    int i, cons, z;

    i = *(int *)num;  // Get consumer ID
    free(num);         // Free the dynamically allocated memory for thread argument

    printf("\n-------- Thread for Consumer %d started the process for Consumption of Items.\n", i);

    while (1) {
        z = (rand() % 10) + 1;  // Random sleep time for the consumer
        sleep(z);  // Sleep for z seconds (POSIX sleep function)

        sem_wait(&b1.full);  // Wait if the buffer is empty
        pthread_mutex_lock(&b1.lock);  // Lock the critical section

        // Consume an item from the buffer
        cons = b1.buffer[(b1.out++) % buff_size];
        printf("\n--------------------------------------------Consumer %d consumed item %d (x)\n", i, cons);
        pthread_mutex_unlock(&b1.lock);  // Unlock the critical section

        sem_post(&b1.empty);  // Signal that there is space in the buffer
    }
}

