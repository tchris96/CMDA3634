#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "functions.h"

//unsigned int modProd(unsigned int a, unsigned int b, unsigned int p);
//unsigned int modExp(unsigned int a, unsigned int b, unsigned int p);
//unsigned int isProbablyPrime(unsigned int N);

//unsigned int main(unsigned int N){

//unsigned int main(unsigned int a,unsigned int b,unsigned int p){
//printf("the value of modProd is: %d \n", modProd(a,b,p));
//printf("the value of modExp is: %d \n", modExp(a,b,p));
//printf("0 if probably NOT prime, 1 if it is. ");
//printf("the result is that %d \n", isProbablyPrime(N));
//}

//compute a*b mod p safely
unsigned int modProd(unsigned int a, unsigned int b, unsigned int p) {
 
  //scanf("%d", &a);
  //scanf("%d", &b);
  //scanf("%d", &p);

  
  unsigned int za = a;
  unsigned  int ab = 0;
  for (int i = 0; i < 32; i++){
  unsigned int b_i = (b >> i)&1;  

  if((b_i == 1)) ab = (ab + za)%p;
  za =( 2*za)%p;
  }  
  return ab;
}

//compute a^b mod p safely
  unsigned int modExp(unsigned int a, unsigned int b, unsigned int p) {
  unsigned int aExpb = 1;

  //printf("Enter a");
  //scanf("%d", &a);
  //printf("Enter b");
  //scanf("%d", &b);
  //printf("Enter p");
  //scanf("%d", &p);

  unsigned int z = a;
  
  for (unsigned int i = 0; i < 32; i++){
  unsigned int  b_i = (b >> i)&1;
    if(b_i == 1) aExpb = modProd(aExpb,z,p);
    else{
    z = modProd(z,z,p);
    }
  }
    return aExpb;
}

//returns either 0 or 1 randomly
unsigned int randomBit() {
  return rand()%2;
}

//returns a random integer which is between 2^{n-1} and 2^{n}
unsigned int randXbitInt(unsigned int n) {
  unsigned int r = 1;
  for (unsigned int i=0; i<n-1; i++) {
    r = r*2 + randomBit();
  }
  return r;
}

//tests for primality and return 1 if N is probably prime and 0 if N is composite
unsigned int isProbablyPrime(unsigned int N) {

  //scanf("%d", &N);

  if (N%2==0) return 0; //not interested in even numbers (including 2)
  

  unsigned int NsmallPrimes = 168;
  unsigned int smallPrimeList[168] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 
                                37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 
                                79, 83, 89, 97, 101, 103, 107, 109, 113, 
                                127, 131, 137, 139, 149, 151, 157, 163, 
                                167, 173, 179, 181, 191, 193, 197, 199, 
                                211, 223, 227, 229, 233, 239, 241, 251, 
                                257, 263, 269, 271, 277, 281, 283, 293, 
                                307, 311, 313, 317, 331, 337, 347, 349, 
                                353, 359, 367, 373, 379, 383, 389, 397, 
                                401, 409, 419, 421, 431, 433, 439, 443, 
                                449, 457, 461, 463, 467, 479, 487, 491, 
                                499, 503, 509, 521, 523, 541, 547, 557, 
                                563, 569, 571, 577, 587, 593, 599, 601, 
                                607, 613, 617, 619, 631, 641, 643, 647, 
                                653, 659, 661, 673, 677, 683, 691, 701, 
                                709, 719, 727, 733, 739, 743, 751, 757, 
                                761, 769, 773, 787, 797, 809, 811, 821, 
                                823, 827, 829, 839, 853, 857, 859, 863, 
                                877, 881, 883, 887, 907, 911, 919, 929, 
                                937, 941, 947, 953, 967, 971, 977, 983, 
                                991, 997};
  
  //scanf("%d", &N);

  //before using a probablistic primality check, check directly using the small primes list
  for (unsigned int n=1;n<NsmallPrimes;n++) {
    if (N==smallPrimeList[n])   return 1; //true
    if (N%smallPrimeList[n]==0) return 0; //false
  }

  //if we're testing a large number switch to Miller-Rabin primality test
  /* Q2.1: Complete this part of the isProbablyPrime function using the Miller-Rabin pseudo-code */
  unsigned int r,d;
  int number = (N-1);  
  r = 0;

  while (number%2 == 0)
  {
    number = number/2;
    r++;
  } 
  d = number;

  for (int n=0;n<NsmallPrimes;n++) {
  unsigned int x = modExp(smallPrimeList[n], d, N);
  if(x == 1 || x == (N-1))
  {
  continue;
  }  
  else{
  
  for(int i = 1; i < r; i++){
  x = modProd(x, x, N);
  if (x == 1) {
  printf("value is 0");
  return 0;
	}
  if(x == (N-1))
  {
    break;
  }
      }
  //printf("value is 0");
  //return 0; //false
   }
  }
  printf("value is 1");
  return 1; //true
}

//Finds a generator of Z_p using the assumption that p=2*q+1
unsigned int findGenerator(unsigned int p) {
  /* Q3.3: complete this function and use the fact that p=2*q+1 to quickly find a generator */
  int q; 
  q = (p-1)/2;

  for(int g=2; g<p; g++){
  
  if((g*g)%p != 1 && (unsigned int) (pow(g,q))%p != 1) return g;
    }
  }

//unsigned int main(){
 
//  printf("the result is %d: \n", isProbablyPrime(4337)); 
//}

