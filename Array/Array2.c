#include <stdio.h>

int main() {
    int rows, cols;
    if (scanf("%d %d", &rows, &cols) != 2) return 0;
    char arr[rows][cols];
    int left = 0, right = cols - 1, top = 0, bottom = rows - 1;
    int count = 0;
    while (top <= bottom && right >= left) {
        char c = (count % 2 == 0) ? 'Y' : '0';
        for (int i = left; i <= right; i++) {
            arr[top][i] = c;
        }
        top++;
        for (int i = top; i <= bottom; i++) {
            arr[i][right] = c;
        }
        right--;
        if (top <= bottom) {
            for (int i = right; i >= left; i--) {
                arr[bottom][i] = c;
            }
            bottom--;
        }
        if (left <= right) {
            for (int i = bottom; i >= top; i--) {
                arr[i][left] = c;
            }
            left++;
        }
        count++;
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%c ", arr[i][j]);
        }
        printf("\n");
    }
    return 0;
}
