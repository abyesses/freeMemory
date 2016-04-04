//
//  main.c
//  free_memory
//
//  Created by Abraham Esses on 4/4/16.
//  Copyright © 2016 Abraham Esses. All rights reserved.
//

#include <stdio.h>
#include <pthread.h>
typedef struct{
    char * tipo;
    void * valor;
}llave;
pthread_key_t var;

void destructor(void* args)
{
    llave * a = (llave *)args;
    if(a->tipo == "char*"){
        delete[] args;
    }
    if (a->tipo == "int*") {
        delete[] args;
    }
    //printf("\n valor: %s", (char*)args);
    //delete(pthread_getspecific(var));
}

void * Hilo1(void * id)
{
    char* valor;
    int res;
    llave a;
    if((valor = (char*)pthread_getspecific(var)) == NULL)
    {
        valor = new char[10];
        valor = "hola";
        a.tipo = "char *";
        a.valor = valor;
       
    }
    res = pthread_setspecific(var,a);
    
    printf("En el hilo 1 var = %s \n", (char *) pthread_getspecific(var));
    printf("TID1 en hilo 1 = %ld\n", pthread_self());
}


void * Hilo2(void * id)
{
    int* valor;
    int res;
    llave b;
    if((valor = (int*)pthread_getspecific(var)) == NULL)
    {
        valor = new int(50);
        b.tipo = "int *";
        b.valor = valor;
        
    }
    res = pthread_setspecific(var, b);
    
    printf("En el hilo 1 var = %i \n", *(int*) pthread_getspecific(var));
    printf("TID1 en hilo 1 = %ld\n", pthread_self());
}

int main(int argc, char **argv)
{
    pthread_t tid1, tid2;
    
    pthread_key_create(&var, destructor);
    
    pthread_create(&tid1, NULL, Hilo1, NULL);
    printf("TID1 = %ld\n", tid1);
    
    pthread_create(&tid2, NULL, Hilo2, NULL);
    printf("TID2 = %ld\n", tid2);
    
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    
    return 0;
}

