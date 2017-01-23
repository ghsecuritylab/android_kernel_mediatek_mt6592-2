

#include <stdio.h>

#define N_MBYTES 64

#define N_INTS_PER_MBYTE (1048576 / sizeof(int))

int rec ( int depth )
{
   int i, zzz;
   int arr[N_INTS_PER_MBYTE];
   if (depth == 0) return 0;
   for (i = 0; i < N_INTS_PER_MBYTE; i++)
      arr[i] = i * depth;
   zzz = rec(depth-1);
   for (i = 0; i < N_INTS_PER_MBYTE; i++)
       zzz += arr[i];
   return zzz;
}


int main ( void )
{
   int sum;
   fprintf(stderr, "lsframe2: start\n");
   sum = rec(N_MBYTES);
   fprintf(stderr, "lsframe2: done, result is %d\n", sum);
   return 0;
}
