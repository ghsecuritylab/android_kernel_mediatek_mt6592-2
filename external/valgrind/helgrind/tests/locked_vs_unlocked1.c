
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


pthread_mutex_t mx = PTHREAD_MUTEX_INITIALIZER;

int x = 0;

void* child_fn ( void* arg )
{
   if (arg) pthread_mutex_lock(&mx);
   x = 1;
   if (arg) pthread_mutex_unlock(&mx);
   return NULL;
}

int main ( int argc, char** argv )
{
   int sw = argc > 1;
   pthread_t child1, child2;

   if (pthread_create(&child1, NULL, child_fn, (void*)(long)(sw ? 0 : 1))) {
      perror("pthread_create1");
      exit(1);
   }
   sleep(1); 
   if (pthread_create(&child2, NULL, child_fn, (void*)(long)(sw ? 1 : 0))) {
      perror("pthread_create1");
      exit(1);
   }

   if (pthread_join(child1, NULL)) {
      perror("pthread join1");
      exit(1);
   }

   if (pthread_join(child2, NULL)) {
      perror("pthread join2");
      exit(1);
   }

   return 0;
}
