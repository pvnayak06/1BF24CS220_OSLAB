#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

// Semaphores for each fork
sem_t forks[NUM_PHILOSOPHERS];

// Statistics
int eat_count[NUM_PHILOSOPHERS] = {0};

/**
 * Dining Philosophers using asymmetric fork ordering
 * Even philosophers pick right fork first, then left
 * Odd philosophers pick left fork first, then right
 * This prevents deadlock
 */
void* philosopher(void* arg) {
    int id = *(int*)arg;
    free(arg);
    
    printf("Philosopher %d is thinking.\n", id);
    fflush(stdout);
    
    for (int cycle = 0; cycle < 3; cycle++) {
        int left = id;
        int right = (id + 1) % NUM_PHILOSOPHERS;
        
        if (id % 2 == 0) {
            // Even philosophers: pick right fork first
            printf("Philosopher %d picked up right fork %d.\n", id, right);
            fflush(stdout);
            sem_wait(&forks[right]);
            
            printf("Philosopher %d picked up left fork %d.\n", id, left);
            fflush(stdout);
            sem_wait(&forks[left]);
        } else {
            // Odd philosophers: pick left fork first
            printf("Philosopher %d picked up left fork %d.\n", id, left);
            fflush(stdout);
            sem_wait(&forks[left]);
            
            printf("Philosopher %d picked up right fork %d.\n", id, right);
            fflush(stdout);
            sem_wait(&forks[right]);
        }
        
        // Eating
        printf("Philosopher %d is eating.\n", id);
        fflush(stdout);
        eat_count[id]++;
        usleep(300000 + (rand() % 200000));
        
        // Put down forks
        printf("Philosopher %d put down forks %d and %d.\n", id, left, right);
        fflush(stdout);
        sem_post(&forks[left]);
        sem_post(&forks[right]);
        
        // Thinking
        printf("Philosopher %d is thinking.\n", id);
        fflush(stdout);
        usleep(200000 + (rand() % 150000));
    }
    
    pthread_exit(NULL);
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    
    // Initialize semaphores
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&forks[i], 0, 1);
    }
    
    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        int* id = malloc(sizeof(int));
        *id = i;
        pthread_create(&philosophers[i], NULL, philosopher, id);
    }
    
    // Wait for all philosophers to finish
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }
    
    // Cleanup
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_destroy(&forks[i]);
    }
    
    return 0;
}
