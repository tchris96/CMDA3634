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
      if(b%2==1) aExpb = modprod(aExpb, z, p);
      z = modprod(z,z,p);
      b /= 2;
    }
  return aExpb;
  }
//__device__ AconvertZToString(unsigned int *Z, unsigned int Nints, unsigned char *string, unsigned int Nchars)
//  {
//    unsigned int charsPerInt = Nchars/Nints;
//    for (int i=0; i<Nints; i++){
//      string[i*charsPerInt + charsPerInt-1-n] = z%256;
//      z /=256;
//    }
//  }
//  string[Nints*charsPerInt] = '\0';
//}
//__device__ AElGamalDecrypt(unsigned int *m, unsigned int *a, unsigned int Nintsm unsigned int p, unsigned int x){
//  for(unsigned int i=0; i<Nints;i++)
//  {
//    unsigned int s = modExp(a[i],x,p);
//    unsigned int invS = modExp(s,p-2,p);
//    m[i] = modprod(m[i], invS,p);
//  }
//}
__device__ findSecretKey(unsigned int n, unsigned int p, unsigned int g, unsigned int h, unsigned int x)
  {
    if(x==0 || AmodExp(g,x,p)!=h)
    {
      printf("Finding the secret key...\n");
      double startTime = clock();
      for(unsigned int i=0; i<p-1;i++)
      {
        if(AmodExp(g,i+1,p) ==h)
        {
          printf("Secret key found! x = %u \n", i+1);
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
  for(unsigned int m2=0; m2<n2; m2++)
  {
    fscanf(file2, "%u  %u", Zmessage+m2, a+m2);
  }
  int numOfCypher = 0;
  numOfCypher = n2;
  printf("%d\n", Zmessage[0]);
  printf("%d\n", a[0]); 
//  if(x==0 || AmodExp(g,x,p)!=h){
//  printf("Finding the secret key...\n");
//  double startTime = clock();  
//  for(unsigned int i = 0; i<p-1;i++){
//  if(AmodExp(g,i+1,p)==h){
//  printf("Secret key found! x = %u \n", i+1);
//  x=i+1;
//  }
//  }
  double endTime = clock();
  double totalTime = (endTime-startTime)/CLOCKS_PER_SEC;
  double work =(double) p;
  double throughput = work/totalTime;
  printf("Searching all keys took %g seconds, throughput was %g values per second. \n", totalTime,throughput);
  }
  fclose(file1);
  fclose(file2);
  free(data1);
  //make cuda kernal

  //device arrays
  int Nre = atoi(argv[1]);
  int Nim = atoi(argv[2]);
  int Nthreads = atoi(argv[3]);
  dim3 B(Nthreads,Nthreads,1);
  dim3 G((Nre+Nthreads-1)/Nthreads,(Nim+Nthreads-1)/Nthreads,1);
  double *d_a, *h_a;
  cudaMalloc(&d_a,N*sizeof(double));
  h_a = (double *) malloc(N*sizeof(double));
  //calculate secret key with cuda
  findSecretKey<<<G,B>>>(n,p,g,h,x);
  cudaDeviceSynchronize();
  cudaMemcpy(h_a,d_a,Nre*Nim*sizeof(float),cudaMemcpyDeviceToHost);
  ElGamalDecrypt(Zmessage,a,numOfCypher,p,x);
  free(h_a);
  cudaFree(d_a);
  //done with cuda
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
