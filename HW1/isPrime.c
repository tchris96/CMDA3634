#include<stdio.h>

int primeNumberCheck(int a){

for (int i = 2; i<=a/2; i++){ //check the first half of numbers going up to a, since a prime cant be divided by a number larger than half

if(a%i == 0)
{
return 0;  //only non-prime numbers can fall under this situation
}
}
return 1;
}

int main(){

int a; // the number inputed by the user


printf("Enter a number: ");
scanf("%d",&a);

if(a <= 1){
printf("%d is not prime.\n\n", a);

}

else if(a%2 == 0){ //number is odd

printf("%d is not prime.\n\n", a);

}

else if(a%2 == 1 && primeNumberCheck(a) == 1){

printf("%d is prime.\n\n", a);

}
else{
printf("%d is not prime.\n\n",a);
}
}
