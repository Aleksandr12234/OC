#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define BUFFER_SIZE 13
#define READERS 3
#define WRITERS 3
#define MAX_LINES 20


sem_t mutex;  
sem_t write_mutex;

char buffer[BUFFER_SIZE];
int readers_count = 0;


int write_delay = 10;
int read_delay = 3;

char* cities[] = {"Novosibirsk", "Semipalatink", "Ekaretinburg"};

void* writer_func(void* arg) {
    int id = *(int*)arg;
    char* city = cities[id];
    int len = strlen(city);
    
    while (1) {
        sem_wait(&write_mutex);
        
        strncpy(buffer, city, len/2);
        buffer[len] = '\0';
        printf("%*sWriter %d (1/2): %s\n", id * 30, "", id, buffer);
        //printf("Writer %d (1/2): %s\n", id, buffer);
        
        sem_post(&write_mutex);
        
        usleep((rand() % (write_delay * 100)) * 1000);
        
        sem_wait(&write_mutex);
        
        strcpy(buffer, city);
        printf("%*sWriter %d (2/2): %s\n", id * 30, "", id, buffer);
        
        sem_post(&write_mutex);
        
        sleep(2 + rand()/RAND_MAX);
    }
    return NULL;
}


void* reader_func(void* arg) {
    int id = *(int*)arg;
    int lines = 0;
    
    while (lines < MAX_LINES) {
        sleep(rand()/RAND_MAX*3);
        usleep((rand() % (read_delay * 100)) * 1000);
        
        sem_wait(&mutex);
        readers_count++;
        if (readers_count == 1) {
            sem_wait(&write_mutex);
        }
        sem_post(&mutex);
        
        printf("%*sReader %d: %s\n", id * 30, "", id, buffer);
        lines++;
        
        sem_wait(&mutex);
        readers_count--;
        if (readers_count == 0) {
            sem_post(&write_mutex);
        }
        sem_post(&mutex);
    }
    
    //printf("______________________________\n", id);
    return NULL;
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    
    if (argc == 3) {
        write_delay = atoi(argv[1]);
        read_delay = atoi(argv[2]);
    }
    
    strcpy(buffer, "empty");

    sem_init(&mutex, 0, 1);
    sem_init(&write_mutex, 0, 1); 
    
    pthread_t writers[WRITERS];
    pthread_t readers[READERS];
    int writer_ids[WRITERS];
    int reader_ids[READERS];
    
    for (int i = 0; i < WRITERS; i++) {
        writer_ids[i] = i;
        pthread_create(&writers[i], NULL, writer_func, &writer_ids[i]);
    }
    
    for (int i = 0; i < READERS; i++) {
        reader_ids[i] = i;
        pthread_create(&readers[i], NULL, reader_func, &reader_ids[i]);
    }
    
    for (int i = 0; i < READERS; i++) {
        pthread_join(readers[i], NULL);
    }
    
    for (int i = 0; i < WRITERS; i++) {
        pthread_cancel(writers[i]);
        pthread_join(writers[i], NULL);
    }
    
    sem_destroy(&mutex);
    sem_destroy(&write_mutex);
    
    return 0;
}
