#include <stdio.h>

int a,b;

int GCD(int a,int b){


if(b == 0){
return a;
   }
else{
GCD(b, a%b);
}
}

void main(){

int a, b, c;

printf("Enter the first number: ");
scanf("%d", &a );

printf("Enter the second number: ");
scanf("%d", &b);
c = GCD(a,b);
printf("The greatest common divisor of %d", a);
printf(" and %d is %d\n.",b, c);

}
