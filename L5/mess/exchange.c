#include <stdio.h>
#include "mpi.h"
#include <stdlib.h>
#include <math.h>

/* exchange
   In this program
      process 0 exchanges data with process 1:
        it sends n messages to process 1 and receives n messages from process 1, 
      process p-1 exchanges data with process p-2:
        it sends n messages to process p-2 and receives n messages from process p-2, 
      all other processes i exchange data both with their predecessor and their successor
        i sends n messages to process i+1 and receives n messages from process i+1,
        i sends n messages to process i-1 and receives n messages from process i-1,  
   Think about the send / receive order

*/

int main(int argc, char **argv)
    {

    double startwtime, endwtime;
    float  elapsed_time, bandwidth;

    int id;	    	     /* process id */
    int p;		     /* number of processes */
    char* message;	     /* storage for the message */
    int i, n, v, msg_size;   /* n: number of times message sent, v: verbose */
    MPI_Status status;	     /* return status for receive */


    MPI_Init( &argc, &argv );
    MPI_Comm_rank( MPI_COMM_WORLD, &id );
    MPI_Comm_size( MPI_COMM_WORLD, &p );

    if(p<2) {
	fprintf (stderr, "p < 2 NO GOOD\n");
	goto EXIT;
    }
    if (argc < 3) {
	fprintf (stderr, "need msg count and msg size as params\n");
	goto EXIT;
    }
    if ((sscanf (argv[1], "%d", &n) < 1) ||
        (sscanf (argv[2], "%d", &msg_size) < 1)) {
	fprintf (stderr, "need msg count and msg size as params\n");
	goto EXIT;
    }
    message = (char*)malloc (msg_size);
    if (argc > 3) v=1; else v=0;  /* are we in verbose mode? */


    /* don't start timer until everybody is active */
    MPI_Barrier(MPI_COMM_WORLD); 

    if( id == 0 ) {
	startwtime = MPI_Wtime();
        // do n imes:
        // exchange message of msg_size chars with 1
	for (i=0; i<n; i++){
	MPI_Send(&message, msg_size, MPI_BYTE, 1, i, MPI_COMM_WORLD);
	MPI_Recv(message, msg_size, MPI_BYTE, 1, i, MPI_COMM_WORLD, &status);
	}	

        MPI_Barrier(MPI_COMM_WORLD);  /*make sure all the processes are done */
	endwtime =MPI_Wtime();
	elapsed_time = endwtime-startwtime;  /* find the run time */
        printf(" %f\n", elapsed_time);
        fflush(stdout);
 
    } else if (id == (p-1) ) {
        // do n imes:
        // exchange message of msg_size chars with p-2
	for (i=0; i<n; i++){	
	MPI_Recv(message, msg_size, MPI_BYTE, p-2, i, MPI_COMM_WORLD, &status);
	MPI_Send(&message, msg_size, MPI_BYTE, p-2, i, MPI_COMM_WORLD);
	}

        MPI_Barrier(MPI_COMM_WORLD); 

    } else {
      // do n times
      //    exchange message with previous process
      //    exchange message with next process 
	for (i=0; i<n; i++){	
	MPI_Recv(message, msg_size, MPI_BYTE, id-1, i, MPI_COMM_WORLD, &status);
	MPI_Send(&message, msg_size, MPI_BYTE, id-1, i, MPI_COMM_WORLD);
	MPI_Send(&message, msg_size, MPI_BYTE, id+1, i, MPI_COMM_WORLD);
	MPI_Recv(message, msg_size, MPI_BYTE, id+1, i, MPI_COMM_WORLD, &status);
	}
        MPI_Barrier(MPI_COMM_WORLD); 
    }	    

EXIT:
    MPI_Finalize();
    return 0;
}

