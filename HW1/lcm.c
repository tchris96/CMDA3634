#include <stdio.h>

int a,b;

int GCD(int a, int b){

if(b == 0){
return a;
   }
else{
GCD(b, a%b);
}
}

void main(){
int a,b,c;

printf("Enter the first number: ");
scanf("%d", &a);

printf("Enter the second number: ");
scanf("%d", &b);
if(GCD(a,b) != 0){
c = a*b/(GCD(a,b));
}
printf("The least common multiple of %d and %d is %d\n", a, b, c);

}


