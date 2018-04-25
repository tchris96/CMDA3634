#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "functions.h"

int main (int argc, char **argv) {

	//seed value for the randomizer 
  double seed = clock(); //this will make your program run differently everytime
  //double seed = 0; //uncomment this and your program will behave the same everytime it's run

  srand(seed);

  int bufferSize = 1024;
  unsigned char *message = (unsigned char *) malloc(bufferSize*sizeof(unsigned char));

  printf("Enter a message to encrypt: ");
  int stat = scanf (" %[^\n]%*c", message); //reads in a full line from terminal, including spaces

  //declare storage for an ElGamal cryptosytem
  unsigned int n, p, g, h;

  printf("Reading file.\n");
  
  /* Q2 Complete this function. Read in the public key data from public_key.txt,
    convert the string to elements of Z_p, encrypt them, and write the cyphertexts to 
    message.txt */

  FILE* file = fopen("public_key.txt", "r");

  unsigned int amount;

  fscanf(file, "%u", &amount);
 
  unsigned int *data = (int *) malloc(n*sizeof(unsigned int));

  for (int m=0;m<amount;m++)
  { 
    fscanf(file, "%u", data+m);
  }
  n = amount;
  p = data[0];
  g = data[1];
  h = data[2];
//printf("n is %d\n",n);
//printf("p is %d\n",p);
//printf("g is %d\n",g);
//printf("h is %d\n",h);

  int numOfCypher = amount;
  unsigned int charsPerInt = (n-1)/8;
  unsigned int Nchars = strlen(message);
  unsigned int Nints = strlen(message)/charsPerInt;
  unsigned int *Zmessage = (unsigned int *) malloc(Nints*sizeof(unsigned int));
  unsigned int *a = (unsigned int *) malloc(Nints*sizeof(unsigned int));
  convertStringToZ(message, Nchars,Zmessage, Nints);
  ElGamalEncrypt(Zmessage,a,Nints,p,g,h);
  FILE* file2 = fopen("message.txt", "w");
  fprintf(file2, "%d\n", Nints);
  for(int i=0; i<Nints; i++)
  {
    fprintf(file2, "%d %d\n", Zmessage[i], a[i]);
  }
  fclose(file);
  fclose(file2);
  free(data);  
  return 0;
}
