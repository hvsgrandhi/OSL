#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_READERS 3
#define NUM_WRITERS 2

pthread_t readers[NUM_READERS];
pthread_t writers[NUM_WRITERS];

int shared_data = 0;  // Shared data that readers and writers access
int reader_count = 0; // Number of active readers

pthread_mutex_t mutex;       // Mutex for controlling access to the reader_count
pthread_mutex_t write_mutex; // Mutex for controlling write access to shared_data

void *reader_thread(void *arg) {
    int reader_id = *(int *)arg;
    while (1) {
        pthread_mutex_lock(&mutex);
        reader_count++;
        if (reader_count == 1) {
            pthread_mutex_lock(&write_mutex); // First reader locks write access
        }
        pthread_mutex_unlock(&mutex);

        // Reading shared data
        printf("Reader %d reads: %d\n", reader_id, shared_data);

        pthread_mutex_lock(&mutex);
        reader_count--;
        if (reader_count == 0) {
            pthread_mutex_unlock(&write_mutex); // Last reader unlocks write access
        }
        pthread_mutex_unlock(&mutex);

        // Simulate reading
        sleep(1);
    }
}

void *writer_thread(void *arg) {
    int writer_id = *(int *)arg;
    while (1) {
        pthread_mutex_lock(&write_mutex);

        // Writing to shared data
        shared_data++;
        printf("Writer %d writes: %d\n", writer_id, shared_data);

        pthread_mutex_unlock(&write_mutex);

        // Simulate writing
        sleep(1);
    }
}

int main() {
    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&write_mutex, NULL);

    int reader_ids[NUM_READERS];
    int writer_ids[NUM_WRITERS];

    // Create reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader_thread, &reader_ids[i]);
    }

    // Create writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer_thread, &writer_ids[i]);
    }

    // Wait for reader threads to finish
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }

    // Wait for writer threads to finish
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&write_mutex);

    return 0;
}
