#include<stdio.h>
#include<math.h>
int main(){

int p;
int i;
int r;
int breakLoop = 1; //determines if the loop needs to end
printf("Enter a prime number: ");
scanf("%d", &p);

for(i = 2; i<=p-1; i++){
 for(r = 1; r<=p-2; r++){

 breakLoop = 1;
printf("%d\n", (int)pow(i,r)%p);

   if((int)pow(i,r)%p == 1){
    breakLoop = 0;
    break;
   } 
  }

printf(" \n");

 if(breakLoop == 1){
 break;
 }
}



printf("%d is a generator of Z_%d", i, p);
}
