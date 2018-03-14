#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <omp.h>

int main(int argc, char **argv) {

  //long long Ncircle = 0;
  //seed random number generator
  // Q2b: get the number of threads to run with from agrv and 
  // add OpenMP API code to set number of threads here
  int Nthreads = 1;

  Nthreads = (int)atoi(argv[0]); 
 
  omp_set_num_threads(Nthreads);

  struct drand48_data *drandData; 
  drandData = (struct drand48_data*) malloc(Nthreads*sizeof(struct drand48_data));

  // Q2c: add an OpenMP parallel region here, wherein each thread initializes 
  //      one entry in drandData using srand48_r and seed based on thread number

  // int rank = omp_get_thread_num();
  // double seed = srand48_r(rank);
 /// long long int Ntotal = 0;
  //long long int Ncircle = 0;
  long long int Ntrials = 10000000;

  double start_time = omp_get_wtime();
  #pragma omp parallel for
  for(int n=0; n<Ntrials; n++)
  {
  long int seed = 0;
  int rank = omp_get_thread_num();
  seed = rank;
  srand48_r(seed, drandData+rank);  

  //need running tallies
 // long long int Ntotal=0;
 // long long int Ncircle=0;
  }
// printf("test");
  long long int Ncircles = 0;
  long long int Ntotal = 0;
//  printf("a");
  #pragma omp parallel for reduction(+:Ncircles)
  for (long long int n=0; n<Ntrials; n++) {
    double rand1;
    double rand2;
//  printf("b");
  int rank = omp_get_thread_num();
    //gererate two random numbers (use the thread id to offset drandData)
    drand48_r(drandData+rank, &rand1);
    drand48_r(drandData+rank, &rand2);
    
    double x = -1 + 2*rand1; //shift to [-1,1]
    double y = -1 + 2*rand2;


    //check if its in the circle
    if (sqrt(x*x+y*y)<=1) Ncircles++;
    Ntotal++;

    if (n%100 ==0) {
      double pi = 4.0*Ncircles/ (double) (n);
      printf("Our estimate of pi is %g \n", pi);
    }
//  printf("c");
  }

  //return Ncircle;
  double pi = 4.0*Ncircles/ (double) (Ntotal);
  printf("Our final estimate of pi is %g \n", pi);

  //printf("The time required is %n \n", time);
  free(drandData);  
  double time = omp_get_wtime() - start_time;
  printf("The time required is %f \n", time);

  return 0;
}
