#include<stdio.h>
#include<math.h>
int main(){

int p;
int i;
int r;
int counter;
int breakLoop = 1; //determines if the loop needs to end
printf("Enter a prime number: ");
scanf("%d", &p);

for(i = 2; i<=p-1; i++){

counter = 1;

 for(r = 1; r<=p-2; r++){

counter = counter*i%p;
 breakLoop = 1;

     if(counter == 1){
    breakLoop = 0;
    break;
   } 
  }


 if(breakLoop == 1){
 break;
 }
}



printf("%d is a generator of Z_%d.\n", i, p);
}
