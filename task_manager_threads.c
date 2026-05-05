#include <stdio.h>
#include<stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <wait.h>

// functions "tasks"
void* speak(void* arg)
{
  printf("I am speaking!\n");

}

void *shouting(void* arg)
{
    printf("I am shouting!\n");
}

void *playing(void* arg)
{
    printf("I am playing!\n");
}


int main(void)
{

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


    return 0;
}