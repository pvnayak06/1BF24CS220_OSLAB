#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5

// Shared buffer and synchronization variables
int buffer[BUFFER_SIZE];
int in = 0;  // Points to the next free position in buffer
int out = 0; // Points to the first filled position in buffer
int item_count = 0;

// Semaphores
sem_t empty;    // Counts empty slots in buffer
sem_t full;     // Counts full slots in buffer
pthread_mutex_t mutex; // Mutual exclusion lock

int total_items = 0;  // Total items to produce/consume

/**
 * Producer thread function
 * Produces items and places them in the shared buffer
 */
void* producer(void* arg) {
    for (int i = 0; i < total_items; i++) {
        // Wait if buffer is full
        sem_wait(&empty);
        
        // Critical section - access shared buffer
        pthread_mutex_lock(&mutex);
        buffer[in] = item_count;
        printf("Produced: %d at buffer[%d]\n", item_count, in);
        fflush(stdout);
        in = (in + 1) % BUFFER_SIZE;
        item_count++;
        pthread_mutex_unlock(&mutex);
        
        // Signal that there's data to consume
        sem_post(&full);
        
        // Small delay for realistic behavior
        usleep(50000);
    }
    
    pthread_exit(NULL);
}

/**
 * Consumer thread function
 * Consumes items from the shared buffer
 */
void* consumer(void* arg) {
    for (int i = 0; i < total_items; i++) {
        // Wait if buffer is empty
        sem_wait(&full);
        
        // Critical section - access shared buffer
        pthread_mutex_lock(&mutex);
        int consumed_item = buffer[out];
        printf("Consumed: %d from buffer[%d]\n", consumed_item, out);
        fflush(stdout);
        out = (out + 1) % BUFFER_SIZE;
        pthread_mutex_unlock(&mutex);
        
        // Signal that there's space to produce
        sem_post(&empty);
        
        // Small delay for realistic behavior
        usleep(75000);
    }
    
    pthread_exit(NULL);
}

int main() {
    pthread_t producer_thread;
    pthread_t consumer_thread;
    
    // Get input from user
    printf("Enter number of items to produce/consume: ");
    scanf("%d", &total_items);
    printf("Result:\n");
    
    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE);  // Buffer starts with BUFFER_SIZE empty slots
    sem_init(&full, 0, 0);              // No items to consume initially
    
    // Initialize mutex
    pthread_mutex_init(&mutex, NULL);
    
    // Create producer thread
    pthread_create(&producer_thread, NULL, producer, NULL);
    
    // Create consumer thread
    pthread_create(&consumer_thread, NULL, consumer, NULL);
    
    // Wait for both to finish
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);
    
    // Cleanup
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);
    
    return 0;
}
