//
// File name   : knap.c
// Description : Dynamic Programming for the 0/1 knapsack  problem. 
//
// Corey LeFevre
// CS475
// PA3 Knapsack

#include <stdio.h>
#include <stdlib.h>
#include "timer.h"


#define    MAX(x,y)   ((x)>(y) ? (x) : (y))
#define    table(i,j)    table[(i)*(C+1)+(j)]

int main(int argc, char **argv) {

   FILE   *fp;
   int    N, C;                   // # of objects, capacity 
   int    *weights, *profits;     // weights and profits
   int    verbose;

   // Temp variables
   int    i, j, count, size, ii;

   // Time
   double time;

   // Read input file:
   //  first line:  # of objects, knapsack capacity, 
   //  next lines:   weight and profit  of next object (1 object per line)
   if ( argc > 1 ) {
      fp = fopen(argv[1], "r"); 
      if ( fp == NULL) {
         printf("[ERROR] : Failed to read file named '%s'.\n", argv[1]);
         exit(1);
      }
   } else {
      printf("USAGE : %s [filename].\n", argv[0]);
      exit(1);
   }

   if (argc > 2) verbose = 1; else verbose = 0;

   fscanf(fp, "%d %d", &N, &C);
   printf("The number of objects is %d, and the capacity is %d.\n", N, C);

   size    = N * sizeof(int);
   weights = (int *)malloc(size);
   profits = (int *)malloc(size);

   if ( weights == NULL || profits == NULL ) {
      printf("[ERROR] : Failed to allocate memory for weights/profits.\n");
      exit(1);
   }


   for ( i=0 ; i < N ; i++ ) {
      count = fscanf(fp, "%d %d", &(weights[i]), &(profits[i]));
      if ( count != 2 ) {
         printf("[ERROR] : Input file is not well formatted.\n");
         exit(1);
      }
   }

   fclose(fp);

   
   initialize_timer ();
   start_timer();

   // Solve for the optimal profit (create the table)
int** table;
table = (int**) malloc((N+1)*sizeof(int*));


#pragma omp parallel
{
#pragma omp for
for (i = 0; i < N+1; i++)
   table[i] = (int*) malloc((C+1)*sizeof(int));

#pragma omp for
  for (i = 0; i<=C; i++)
    table[0][i]=0;

#pragma omp for
  for (i = 0; i<=N; i++)
    table[i][0]=0;
}

#pragma omp parallel private(i,j,ii) 
{
//Top half
#pragma omp for ordered
  for (ii = 1; ii<=N; ii++) {
    for (i=ii, j=1; i>=1; i--, j++) {
      if (weights[i-1] <= j)
#pragma omp ordered
        table[i][j] = MAX(profits[i-1] + table[i-1][j-weights[i-1]], table[i-1][j]); 
      else
#pragma omp ordered
        table[i][j] = table[i-1][j];
    }
   }

//Middlebottm
#pragma omp for ordered
  for (ii = 2; ii<=C; ii++) {
    for (i=N, j=ii; i>= 1 && j<=C; i--, j++) {
      if (weights[i-1] <= j)
#pragma omp ordered
        table[i][j] = MAX(profits[i-1] + table[i-1][j-weights[i-1]], table[i-1][j]); 
      else
#pragma omp ordered
        table[i][j] = table[i-1][j];
    }
   }

}
   // We only time the creation of the table

  stop_timer();
   time = elapsed_time ();

  int opt = table[N][C];
   printf("The optimal profit is %d Time taken : %lf.\n", opt, time);

 // End of "Solve for the optimal profit"

/*
printf("Table:\n");
for (i = 0; i <= N; i++) {
for (j = 0; j <= C; j++) {
printf(" | %d |", table[i][j]);
}
printf("\n\n");
}
*/

// Find the solution (choice vector) by backtracking through the table
  int* sol;
  sol = (int*) calloc(N, sizeof(int));
  int s = (N==50) ? 2 : 1;
  for (i = N; i>=s; i--) {
    if (opt == profits[i-1]+table[i-1][C-weights[i-1]] ) {
       sol[i-1] = 1;
       opt = table[i-1][C-weights[i-1]];
       C -= weights[i-1];
    }
    else { 
       sol[i-1] = 0;
  }

}

      if (verbose) {
	// print the solution vector 
      printf("Solution vector is: \n-->");
	for (i = 0; i < N; i++)
	  printf(" %d", sol[i]);
	printf("\n");

     }

/*
   free(weights);
   free(profits);
   for (i = 0; i <= N; i++)
     free(table[i]);
   free(table);
*/
   return 0;
}
