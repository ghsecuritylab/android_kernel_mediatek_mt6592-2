#include <stdlib.h>

int main(void)
{
   int i;
   for (i = 0; i < 200; i++) {
      malloc(16);     
   }
   return 0;
}
