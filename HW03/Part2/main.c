#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "mpi.h"
#include "functions.h"

int main (int argc, char **argv) {

  MPI_Init(&argc,&argv);

  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&size);
  //size = 20;

  //seed value for the randomizer 
  double seed = clock()+rank; //this will make your program run differently everytime
 // double seed = rank; //uncomment this and your program will behave the same everytime it's run

  srand(seed);

  //begin with rank 0 getting user's input
  unsigned int n;

  unsigned int p, g, h, x;
  /* Q3.1 Make rank 0 setup the ELGamal system and
    broadcast the public key information */
  if (rank == 0)
  {
  printf("Enter a number of bits: "); fflush(stdout);
  char status = scanf("%u",&n);
    n = 21;

  //make sure the input makes sense
  if ((n<3)||(n>31)) {//Updated bounds. 2 is no good, 31 is actually ok
    printf("Unsupported bit size.\n");
    return 0;   
  }
  printf("\n");

  //declare storage for an ElGamal cryptosytem
  //unsigned int p, g, h, x;

  //setup an ElGamal cryptosystem
  setupElGamal(n,&p,&g,&h,&x);
  }

  MPI_Bcast(&p,
            1,
            MPI_INT,
            0,
            MPI_COMM_WORLD);

  MPI_Bcast(&g,
            1,
            MPI_INT,
            0,
            MPI_COMM_WORLD);

  MPI_Bcast(&h,
            1,
            MPI_INT,
            0,
            MPI_COMM_WORLD);

  //Suppose we don't know the secret key. Use all the ranks to try and find it in parallel
  if (rank==0)
    printf("Using %d processes to find the secret key...\n", size);

  /*Q3.2 We want to loop through values i=0 .. p-2
     determine start and end values so this loop is 
     distributed amounst the MPI ranks  */
  unsigned int N = p-1; //total loop size
  unsigned int start, end;
  start = 0;
  end = start + N;
  unsigned int range = N/size;
  start = rank*range;
  end = start+range;
  unsigned int remainder = N%size;
// && remainder !=0
range = N/size;
if(remainder !=0)
{
  if(rank<remainder)
    { 
      range = range+1;
      start = rank*range;
      end = start+range;
   }
   else
   {
     range = range+1;
     start = rank*range;
     end = start+range;
   }

}
  double startTime;
  startTime = MPI_Wtime();
  unsigned int foundKey = 0;  
  unsigned int Ninterval = 0;
  unsigned int flag = 0;
  MPI_Request request;
  MPI_Status status;
  //loop through the values from 'start' to 'end'
  for (unsigned int i=start;i<end;i++) 
  {
    MPI_Iprobe(MPI_ANY_SOURCE,
               3,
               MPI_COMM_WORLD,
               &flag,
               &status);
   if(flag!=0){
    MPI_Irecv(&foundKey,
              1,
              MPI_INT,
              MPI_ANY_SOURCE,
              3,
              MPI_COMM_WORLD,
              &request);
              }
               
    if(modExp(g,i+1,p)==h)
    {
      printf("Secret key found! x = %u \n", i+1);
      foundKey = 1;
    }
    if(Ninterval == 10)
    {
    if(foundKey == 1)
      {
        for(i=0; i<size; i++)
        {
         MPI_Isend(&foundKey,
                   1,
                   MPI_INT,
                   i,
                   3,
                   MPI_COMM_WORLD,
                   &request);
      }
    
        if(foundKey == 1)
        {
         break;
        }
     }
      Ninterval = 0;
    }
  Ninterval = Ninterval+1;
  }
  MPI_Barrier(MPI_COMM_WORLD);
  double runTime = MPI_Wtime() - startTime;
  double workTime = N/runTime;

  if(rank == 0)
  {
  printf("The runtime is: %f\n", runTime);
  printf("The throughput is: %f\n", workTime);
  }
  
  MPI_Finalize();
  return 0;
}
