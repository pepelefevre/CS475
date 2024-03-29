/*/////////////////////////////////////////////////////////////////////////////
//
// File name : sieve.c
// Author    : Nissa Osheim
// Date      : 2010/19/10
// Desc      : Finds the primes up to N
//
// updated Wim Bohm
//
//
/////////////////////////////////////////////////////////////////////////////*/



#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "timer.h"

#define BLKSIZE 1000000
#define MIN(x,y) (((x) < (y)) ? (x) : (y))

int main(int argc, char **argv) {

   long N  = 100;

   char *mark;
   long *primes;

   long   size;
   long   curr;
   long   i,ii, j,n;
   long   count;
   long blockStart;
   long start=0;
long primesq=0;
long oddprime=0;
   /* Time */

   double time;

   if ( argc > 1 ) N  = atoi(argv[1]);

   /* Start Timer */

   initialize_timer ();
   start_timer();

   size = (N+1)*sizeof(char);
   mark = (char *)malloc(size);
   primes = (long *)malloc((N/2)*sizeof(long));

   for (i=2; i<=N; i=i+1){
     mark[i]=0;
   }

   count = 0;

   curr=3;       /*first prime*/
   for (j=0; curr*curr<=N; j++) {
     primes[j] = curr;  //Store primes in array
     count++;		//Numprimes
   for (i=curr*curr; i*i<=N; i=i+(2*curr)){
      mark[i]=1;
   }
   while (mark[curr+=2]) ; /* do nothing */
   }

   for(ii=curr; ii<=N; ii+=100000)   //Block loop
      for(j=0; j<count; j++) {         //Iterate through primes
	primesq=primes[j]*primes[j];
	oddprime=primes[j]*(primes[j]+2);
	start=(primesq<curr) ? oddprime : primesq;	
	for(i=start; i<=MIN(N,(ii+100000)); i=i+(primes[j])) {
            mark[i]=1;
}
}

   /* stop timer */
   stop_timer();
   time=elapsed_time ();

   /*number of primes*/
   count = 1;
   for(i = 3; i <=N; i+=2){
        if(mark[i] == 0) {
        	//  printf("\t prime %ld  \n",i );
        	++count;
        }

   }
   printf("There are %ld primes less than or equal to %ld\n", count, N);
   /* print results */
   printf("First three primes:");
   j = 1;
   printf("%d ", 2);
   for ( i=3 ; i <= N && j < 3; i+=2 ) {
      if (mark[i]==0){
            printf("%ld ", i);
            ++j;
      }
   }
   printf("\n");

   printf("Last three primes:");
   j = 0;
   n=(N%2?N:N-1);
   for (i = n; i > 1 && j < 3; i-=2){
     if (mark[i]==0){
        printf("%ld ", i);
        j++;
     }
   }
   printf("\n");


   printf("elapsed time = %lf (sec)\n", time);

   free(mark);
   return 0;
}


