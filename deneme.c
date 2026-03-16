#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
    FILE *fp = fopen("deneme.txt", "a");

    int a = 5;
    fprintf(fp,"%d",a);
    int b= 10;
     fprintf(fp,"%d",b);
    return 0;
}