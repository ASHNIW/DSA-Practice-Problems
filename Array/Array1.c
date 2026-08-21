#include <stdio.h>
void martian_conv(int num){
    char buff[50];
    int i=0;
    int values[] = {1000, 500, 100, 50, 10, 5, 1};
    char symbols[] = {'R', 'G', 'B', 'P', 'Z', 'W', 'B'};
    for (int j=0;j<7;j++){
        while (num>=values[j]){
            buff[i++]=symbols[j];
            num-=values[j];
        }
    }
    buff[i]='\0';
    printf("%s\n",buff);
}
int main(){
    int n;
    int count=0;
    while (scanf("%d",&n)!=EOF && count<5){
        martian_conv(n);
        count++;
    }
    return 0;
}
