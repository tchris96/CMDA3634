#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "functions.h"


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
//  unsigned int n3;
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
  //setupElGamal(n,&p,&g,&h,&x);
  printf("n is %d\n", n);
  printf("p is %d\n", p);
  printf("g is %d\n", g);
  printf("h is %d\n", h);
  printf("x is %d\n", x);
  for(unsigned int m2=0; m2<n2; m2++)
  {
    fscanf(file2, "%u  %u", Zmessage+m2, a+m2);
  }
//find a zmessage and a
 int numOfCypher = 0;
 numOfCypher = n2;
printf("%d\n", Zmessage[0]);
printf("%d\n", a[0]);
  // find the secret key
  if (x==0 || modExp(g,x,p)!=h) {
    printf("Finding the secret key...\n");
    double startTime = clock();
    for (unsigned int i=0;i<p-1;i++) {
      if (modExp(g,i+1,p)==h) {
        printf("Secret key found! x = %u \n", i+1);
        x=i+1;
      } 
    }
    double endTime = clock();

    double totalTime = (endTime-startTime)/CLOCKS_PER_SEC;
    double work = (double) p;
    double throughput = work/totalTime;

    printf("Searching all keys took %g seconds, throughput was %g values tested per second.\n", totalTime, throughput);
  }
  fclose(file1);
  fclose(file2);
  free(data1);
 // free(Zmessage);
  //free(a);
  /* Q3 After finding the secret key, decrypt the message */
  
  ElGamalDecrypt(Zmessage,a,numOfCypher,p,x);
  int bufferSize = 1024;
  unsigned char *message = (unsigned char *) malloc(bufferSize*sizeof(unsigned char));
  unsigned int charsPerInt = ((n-1)/8)*numOfCypher;
  convertZToString(Zmessage, numOfCypher, message, charsPerInt);
  printf("Decrypted message = \"%s\"\n", message);
  printf("\n");
  return 0;
}
