#include <stdio.h>
int main(){
    int T;
    scanf("%d",&T);
    for (int i=0;i<T;i++){
        int n;
        scanf("%d",&n);
        int arr[n];
        for (int i=0;i<n;i++){
            scanf("%d",&arr[i]);
        }
        int k=0;
        int found=0;
        while(k<n-1){
            while (k<n-1 && arr[k+1]<=arr[k]){
                k++;
            }
            if (k==n-1){
                break;
            }
            int buy=k;
            k++;
            while (k<n && arr[k]>arr[k-1]){
                k++;
            }
            int sell=k-1;
            printf("(%d %d) ",buy,sell);
            found=1;
        }
        if (found==0){
            printf("No Profit");
        }
        printf("\n");

    }
    return 0;
}
