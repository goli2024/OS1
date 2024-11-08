#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>  // Include this for sleep()

sem_t rw_mutex;  // Writer lock
sem_t mutex;     // Reader lock (to avoid race on read_count)
int read_count = 0;  // Counter for the number of readers

// Reader thread function
void* reader(void* arg) {
    int reader_id = *((int*)arg);  // Get reader ID from argument

    sem_wait(&mutex);  // Enter critical section for read_count modification
    read_count++;
    if (read_count == 1)  // If this is the first reader, lock the writer mutex
        sem_wait(&rw_mutex);
    sem_post(&mutex);  // Exit critical section

    // Reading process
    printf("Reader %d is reading\n", reader_id);
    sleep(1);  // Simulate reading
    printf("Reader %d finished reading\n", reader_id);

    sem_wait(&mutex);  // Enter critical section for read_count modification
    read_count--;
    if (read_count == 0)  // If this is the last reader, release the writer lock
        sem_post(&rw_mutex);
    sem_post(&mutex);  // Exit critical section

    pthread_exit(NULL);
}

// Writer thread function
void* writer(void* arg) {
    int writer_id = *((int*)arg);  // Get writer ID from argument

    sem_wait(&rw_mutex);  // Lock the writer mutex to prevent readers and other writers

    // Writing process
    printf("Writer %d is writing\n", writer_id);
    sleep(1);  // Simulate writing
    printf("Writer %d finished writing\n", writer_id);

    sem_post(&rw_mutex);  // Release the writer mutex

    pthread_exit(NULL);
}

int main() {
    int num_readers, num_writers;

    // Get number of readers and writers from the user
    printf("Enter the number of readers: ");
    scanf("%d", &num_readers);
    printf("Enter the number of writers: ");
    scanf("%d", &num_writers);

    pthread_t readers[num_readers], writers[num_writers];
    int reader_ids[num_readers], writer_ids[num_writers];

    // Initialize semaphores
    sem_init(&rw_mutex, 0, 1);  // Initialize writer semaphore (1 means writer is allowed to proceed)
    sem_init(&mutex, 0, 1);      // Initialize reader semaphore (1 means no readers are in critical section)

    // Create reader threads
    for (int i = 0; i < num_readers; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    // Create writer threads
    for (int i = 0; i < num_writers; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    // Wait for all reader threads to finish
    for (int i = 0; i < num_readers; i++) {
        pthread_join(readers[i], NULL);
    }

    // Wait for all writer threads to finish
    for (int i = 0; i < num_writers; i++) {
        pthread_join(writers[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&rw_mutex);
    sem_destroy(&mutex);

    return 0;
}

