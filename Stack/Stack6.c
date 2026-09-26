#include <stdio.h>

void calculateSpan(int price[], int n, int S[]) {
    int st[n];
    int top = -1;

    st[++top] = 0;
    S[0] = 1;

    for (int i = 1; i < n; i++) {
        while (top >= 0 && price[st[top]] <= price[i]) {
            top--;
        }
        S[i] = (top == -1) ? (i + 1) : (i - st[top]);
        st[++top] = i;
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d%c", arr[i], (i == n - 1) ? '\n' : ' ');
    }
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    int price[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &price[i]);
    }
    int S[n];
    calculateSpan(price, n, S);
    printArray(S, n);
    return 0;
}
