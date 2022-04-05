/**
 * Example client program that uses thread pool.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "threadpool.h"

struct data
{
    int a;
    int b;
};

void add(void *param)
{
    struct data *temp;
    temp = (struct data*)param;

    printf("I add two values %d and %d result = %d\n",temp->a, temp->b, temp->a + temp->b);
}

int main(void)
{
    // create some work to do
    struct data work[30];
    for(int i=0;i<30;i++){
        work[i].a=rand()%1000;
        work[i].b=rand()%1000;
    }

    // initialize the thread pool
    pool_init();

    // submit the work to the queue
    for(int i=0;i<30;i++){
        int error;
        error=pool_submit(&add,&work[i]);
        if(error)
             printf("Sumbitting work[%d] failed\n",i);
    }
    // may be helpful 
    sleep(3);

    pool_shutdown();

    return 0;
}
