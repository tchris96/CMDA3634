#include <stdio.h>

int a, b;

int GCD(int a, int b){

if(b == 0){
return a;
}
else{
GCD(b, a%b);
}
}

void main(){
int a,b;

printf("Enter the first number: ");
scanf("%d",&a);

printf("Enter the second number: ");
scanf("%d", &b);
if(GCD(a,b) == 1){

printf("%d and %d are coprime.\n", a, b);

}

else if(GCD(a,b) != 1){

printf("%d and %d are not coprime.\n",a, b);
}

else {
printf("Invalid entry.\n");
}


}

