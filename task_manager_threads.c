#include <stdio.h>
#include<stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <wait.h>
#include <semaphore.h>

//pthread_mutex_t key_work;
int counter=0;
sem_t sem;

void* (*ergasies[3])(void*); //pointers poypairnoyns san parametro ena arg typou (void*) kai epistrefoun enan pointer typou (void*)

   // functions "tasks"
void* speak(void* arg)
{
    //pthread_mutex_lock(&key_speak);
  printf("Thread %d:I am speaking!\n",*(int*)arg);
  fflush(stdout);
  sleep(1);
  counter++;
  //pthread_mutex_unlock(&key_speak);
}

void *shouting(void* arg)
{
    //pthread_mutex_lock(&key_shouting);
    printf("Thread %d:I am shouting!\n",*(int*)arg);
      fflush(stdout);   
    sleep(1);
    counter++;
   //pthread_mutex_unlock(&key_shouting);
}

void *playing(void* arg)
{
    //pthread_mutex_lock(&key_playing);
    printf("Thread %d:I am playing!\n",*(int*)arg);
    fflush(stdout);
    sleep(1);
    counter++;
    //pthread_mutex_unlock(&key_playing);
}


void* work(void* arg)
{
    int number;    
 
    while (counter<10)
    {
        sem_wait(&sem);
      // pthread_mutex_lock(&key_work);
         number=counter%3;
        // sleep(2);

         ergasies[number](arg);
           
        // counter++;
         
         sem_post(&sem);
       //pthread_mutex_unlock(&key_work); 
       sleep(1);
    }
    
   

}


int main(void)
{

    sem_init(&sem,0,1);
//pthread_mutex_init(&key_work,NULL);
ergasies[0]=speak;
ergasies[1]=shouting;
ergasies[2]=playing;
   
//array with tasks    


//workers-threads
pthread_t  workers[2]; 


for (int i = 0; i < 2; i++)
{
    int *x=malloc(sizeof(int));
    if (x==NULL)
    {
        perror("Error at malloc!\n");
        return 1;
        /* code */
    }
    *x=i+1;
    
    
    pthread_create(&workers[i],NULL,&work,x);
    /* code */
}

for (int i = 0; i < 2; i++)
{
    pthread_join(workers[i],NULL);
    /* code */
}


sem_destroy(&sem);
//pthread_mutex_destroy(&key_work);
    return 0;
}
