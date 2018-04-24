#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "cuda.h"
#include "functions.c"


__device__ Amodprod(unsigned int a, unsigned int b, unsigned int p)
  {
    unsigned int za = a;
    unsigned int ab = 0;
    while(b>0)
    {
      if(b%2 == 1) ab = (ab + za) % p;
      za = (2 * za) % p;
      b /= 2;
    }
  return ab;
  }
__device__ AmodExp(unsigned int a, unsigned int b, unsigned int p)
  {
    unsigned int z = a;
    unsigned int aExpb = 1;
    while (b>0)
    {
      if(b%2==1) aExpb = Amodprod(aExpb, z, p);
      z = modprod(z,z,p);
      b /= 2;
    }
  return aExpb;
  }
__global__ findSecretKey(unsigned int n, unsigned int p, unsigned int g, unsigned int h, unsigned int *x)
  {
  int threadId = threadIdx.x;
  int blockId = blockIdx.x;
  int Nblock = blockDim.x;
  int id = threadId + blockID*Nblock;
    if(x==0 || AmodExp(g,x,p)!=h)
      {
      if(id<pow(2,n))
        {
    if(AmodExp(g,i+1,p) ==h)
            {
               *x[0] = i+1;
            }
        }
      }
   }

int main (int argc, char **argv) {

  //declare storage for an ElGamal cryptosytem
  unsigned int n, p, g, h, x;
  unsigned int Nints;

  //get the secret key from the user
  printf("Enter the secret key (0 if unknown): "); fflush(stdout);
  char stat = scanf("%u",&x);

  printf("Reading file.\n");

  /* Q3 Complete this function. Read in the public key data from public_key.txt
    and the cyphertexts from messages.txt. */

  FILE* file1 = fopen("public_key.txt","r");
  FILE* file2 = fopen("message.txt", "r");
  unsigned int n1;
  unsigned int n2;
  fscanf(file1, "%d", &n1);
  fscanf(file2, "%d", &n2);
  unsigned int *data1 = (int *) malloc(n1*sizeof(int));
  unsigned int *Zmessage = (int *) malloc(n2*sizeof(int));
  unsigned int *a = (int *) malloc(n2*sizeof(int));
  //read in first file
  for(unsigned int m1=0; m1<n1; m1++)
  {
    fscanf(file1, "%u", data1+m1);
  }
  n = n1;
  p = data1[0];
  g = data1[1];
  h = data1[2];
  printf("n is %d\n", n);
  printf("p is %d\n", p);
  printf("g is %d\n", g);
  printf("h is %d\n", h);
  printf("x is %d\n", x);
  //read in second file
  for(unsigned int m2=0; m2<n2; m2++)
  {
    fscanf(file2, "%u  %u", Zmessage+m2, a+m2);
  }
  int numOfCypher = 0;
  numOfCypher = n2;
  printf("%d\n", Zmessage[0]);
  printf("%d\n", a[0]); 
//  double endTime = clock();
//  double totalTime = (endTime-startTime)/CLOCKS_PER_SEC;
//  double work =(double) p;
//  double throughput = work/totalTime;
//  printf("Searching all keys took %g seconds, throughput was %g values per second. \n", totalTime,throughput);
  }
  fclose(file1);
  fclose(file2);
  free(data1);
  //make cuda kernal
  //device arrays
//  int Nre = atoi(argv[1]);
//  int Nim = atoi(argv[2]);
  int Nthreads = 32;
  dim3 B(Nthreads,1,1);
  dim3 G(((p+Nthreads-1))/Nthreads,1,1);
  double *d_a, *h_a;
//  int N = 1024*1024;
  cudaMalloc(&d_a,Nthreads*sizeof(double));
  h_a = (double *) malloc(Nthreads*sizeof(double));
  //calculate secret key with cuda
  double startTime = clock();
  makeKernal<<<G,B>>>(N,a,b,c);
  findSecretKey<<<G,B>>>(n,p,g,h,x);
  cudaDeviceSynchronize();
  cudaMemcpy(h_a,d_a,Nre*Nim*sizeof(float),cudaMemcpyDeviceToHost);
  ElGamalDecrypt(Zmessage,a,numOfCypher,p,x);
  free(h_a);
  cudaFree(d_a);
  //done with cuda
  double endTime = clock();
  double totalTime = (endTIme-startTime)/CLOCKS_PER_SEC;
  double work = (double) p;
  double throughput = work/totalTime;
  printf("Searching all keys took %g seconds, throughput was %g values per second. \n", totalTime, throughput);
  int bufferSize = 1024;
  unsigned char *message = (unsigned char *) malloc(bufferSize*sizeof(unsigned char));
  unsigned int charsPerInt = ((n-1)/8)*numOfCypher;
  convertZToString(Zmessage, numOfCypher, message, charsPerInt);
  printf("Decrypted message = \s\"\n", message);
  printf("\n");
  /* Part 2. Start this program by first copying the contents of the main function from 
     your completed decrypt.c main function. */

  /* Q4 Make the search for the secret key parallel on the GPU using CUDA. */

  return 0;
}
