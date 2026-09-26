#include <stdio.h>

int main() {
    int r, c;
    if (scanf("%d %d", &r, &c) != 2) return 0;

    int arr[r][c];
    int arrTemp[r][c];
    int row_flag[r];
    int col_flag[c];

    int m, n;
    for (m = 0; m < r; m++) row_flag[m] = 0;
    for (n = 0; n < c; n++) col_flag[n] = 0;

    for (m = 0; m < r; m++) {
        for (n = 0; n < c; n++) {
            scanf("%d", &arr[m][n]);
            if (arr[m][n] == 1) {
                row_flag[m] = 1;
                col_flag[n] = 1;
            }
        }
    }

    for (m = 0; m < r; m++) {
        for (n = 0; n < c; n++) {
            if (row_flag[m] || col_flag[n]) {
                arrTemp[m][n] = 1;
            } else {
                arrTemp[m][n] = 0;
            }
        }
    }

    for (m = 0; m < r; m++) {
        for (n = 0; n < c; n++) {
            printf("%d ", arrTemp[m][n]);
        }
        printf("\n");
    }
    return 0;
}
