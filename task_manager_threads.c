#include <stdio.h>
#include<stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <wait.h>

pthread_mutex_t key_speak,key_shouting,key_playing;

// functions "tasks"
void* speak(void* arg)
{
    pthread_mutex_lock(&key_speak);
  printf("I am speaking!\n");
  fflush(stdout);
  sleep(1);
  pthread_mutex_unlock(&key_speak);
}

void *shouting(void* arg)
{
    pthread_mutex_lock(&key_shouting);
    printf("I am shouting!\n");
      fflush(stdout);   
    sleep(1);
   pthread_mutex_unlock(&key_shouting);
}

void *playing(void* arg)
{
    pthread_mutex_lock(&key_playing);
    printf("I am playing!\n");
    fflush(stdout);
    sleep(1);
    pthread_mutex_unlock(&key_playing);
}


int main(void)
{

    pthread_mutex_init(&key_playing,NULL);
    pthread_mutex_init(&key_shouting,NULL);
    pthread_mutex_init(&key_speak,NULL);
//array with tasks    
void* (*ergasies[3])(void*); //pointers poypairnoyns san parametro ena arg typou (void*) kai epistrefoun enan pointer typou (void*)
ergasies[0]=speak;
ergasies[1]=shouting;
ergasies[2]=playing;

//workers-threads
pthread_t  workers[3]; 

for (int i = 0; i < 3; i++)
{
    pthread_create(&workers[i],NULL,ergasies[i],NULL);
    /* code */
}

for (int i = 0; i < 3; i++)
{
    pthread_join(workers[i],NULL);
    /* code */
}

pthread_mutex_destroy(&key_playing);
pthread_mutex_destroy(&key_shouting);
pthread_mutex_destroy(&key_speak);
    return 0;
}
