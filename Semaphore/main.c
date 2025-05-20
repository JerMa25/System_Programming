#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>

sem_t semaphore;

//fonction executee par les threads
void *fonction(void *arg){
    int id = *(int*)arg;
    printf("Le thread %d attend la ressource\n",id);
    sem_wait(&semaphore);//wait
    printf("Le thread %d entre dans la zone critique\n",id);
    sleep(10);
    printf("Le thread %d quitte la zone critique\n",id);
    sem_post(&semaphore);//signal
    pthread_exit(NULL);
}

int main(){
    //initialise le semaphore
    sem_init(&semaphore,0,1);

    pthread_t t1,t2;
    int id1 = 1, id2 = 2; //identifiants des threads

    //creation des threads
    pthread_create(&t1, NULL, fonction, &id1);
    pthread_create(&t2, NULL, fonction, &id2);

    //Attend  que les threads finissent
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    //detruire le semaphore
    sem_destroy(&semaphore);
    return 0;
}
