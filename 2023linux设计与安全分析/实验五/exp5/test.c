#include<stdio.h>

int calc(int a,int b,int* sum)
{
    *sum = a + b;
    return 0;
}

int main(int argc,char *argv[])
{
    int a = 1;
    int b = 2;
    int sum = 0;

    printf("before calc: a = %d b = %d sum = %d\n",a,b,sum);
    calc(a,b,&sum);
    printf("after calc : a = %d b = %d sum = %d\n",a,b,sum);

    return 0;
}
