

#define _GNU_SOURCE


#include <pthread.h> 
#include <stdio.h>   
#include <stdlib.h>  
#include <string.h>  
#include <unistd.h>  
#include "../../drd/drd.h"
#include "../../config.h"


#define BARRIER_SERIAL_THREAD -1



typedef struct
{
  unsigned thread_count;
  
  volatile unsigned wait_count;
  volatile unsigned barrier_count;
} barrier_t;

struct threadinfo
{
  int        thread_num;
  barrier_t* b;
  pthread_t  tid;
  int*       array;
  int        iterations;
};



static int s_silent;



static void barrier_init(barrier_t* b, unsigned count)
{
  b->thread_count = count;
  b->wait_count = 0;
  b->barrier_count = 0;
  ANNOTATE_BARRIER_INIT(b, count, 0);
}

static void barrier_destroy(barrier_t* b)
{
  ANNOTATE_BARRIER_DESTROY(b);
  memset(b, 0, sizeof(*b));
}

static int barrier_wait(barrier_t* b)
{
  int res;
  unsigned barrier_count;

  res = 0;
  ANNOTATE_BARRIER_WAIT_BEFORE(b);
  barrier_count = b->barrier_count;
  if (__sync_add_and_fetch(&b->wait_count, 1) == b->thread_count)
  {
    __sync_sub_and_fetch(&b->wait_count, b->thread_count);
    __sync_add_and_fetch(&b->barrier_count, 1);
    res = BARRIER_SERIAL_THREAD;
  }
  else
  {
    while (b->barrier_count == barrier_count)
    {
#ifndef HAVE_PTHREAD_YIELD
      
      usleep(100 * 1000);
#else
      pthread_yield();
#endif
    }
  }
  ANNOTATE_BARRIER_WAIT_AFTER(b);
  return res;
}

static void* threadfunc(struct threadinfo* p)
{
  int i;
  int* const array = p->array;
  barrier_t* const b = p->b;
  if (! s_silent)
    printf("thread %d iteration 0\n", p->thread_num);
  barrier_wait(b);
  for (i = 0; i < p->iterations; i++)
  {
    if (! s_silent)
      printf("thread %d iteration %d; writing to %p\n",
             p->thread_num, i + 1, &array[i]);
    array[i] = i;
    barrier_wait(b);
  }
  return 0;
}

static void barriers_and_races(const int nthread, const int iterations)
{
  const struct timespec delay = { 0, 100 * 1000 * 1000 };
  int i;
  struct threadinfo* t;
  barrier_t b;
  int* array;

  t = malloc(nthread * sizeof(struct threadinfo));
  array = malloc(iterations * sizeof(array[0]));

  if (! s_silent)
    printf("&array[0] = %p\n", array);

  barrier_init(&b, nthread);

  for (i = 0; i < nthread; i++)
  {
    t[i].thread_num = i + 1;
    t[i].b = &b;
    t[i].array = array;
    t[i].iterations = iterations;
    pthread_create(&t[i].tid, 0, (void*(*)(void*))threadfunc, &t[i]);
    nanosleep(&delay, 0);
  }

  for (i = 0; i < nthread; i++)
    pthread_join(t[i].tid, 0);

  barrier_destroy(&b);

  free(array);
  free(t);
}

int main(int argc, char** argv)
{
  int nthread;
  int iterations;

  nthread    = (argc > 1) ? atoi(argv[1]) : 2;
  iterations = (argc > 2) ? atoi(argv[2]) : 3;
  s_silent   = (argc > 3) ? atoi(argv[3]) : 0;

  barriers_and_races(nthread, iterations);

  fprintf(stderr, "Done.\n");

  return 0;
}
