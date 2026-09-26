#include <stdio.h>
#include <stdbool.h>

int A[309][309];
bool ok[309][309][309];

int main() {
    int T;
    if (scanf("%d", &T) != 1) return 0;
    while (T--) {
        int R, C, K;
        scanf("%d %d %d", &R, &C, &K);
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                scanf("%d", &A[i][j]);
            }
        }
        for (int i = 0; i < R; i++) {
            for (int c1 = 0; c1 < C; c1++) {
                int mn = A[i][c1];
                int mx = A[i][c1];
                for (int c2 = c1; c2 < C; c2++) {
                    if (A[i][c2] < mn) mn = A[i][c2];
                    if (A[i][c2] > mx) mx = A[i][c2];
                    if (mx - mn <= K) {
                        ok[i][c1][c2] = true;
                    } else {
                        ok[i][c1][c2] = false;
                    }
                }
            }
        }
        int max_area = 0;
        for (int c1 = 0; c1 < C; c1++) {
            for (int c2 = c1; c2 < C; c2++) {
                int width = c2 - c1 + 1;
                int current_h = 0;
                for (int r = 0; r < R; r++) {
                    if (ok[r][c1][c2]) {
                        current_h++;
                        int area = current_h * width;
                        if (area > max_area) max_area = area;
                    } else {
                        current_h = 0;
                    }
                }
            }
        }
        printf("%d\n", max_area);
    }
    return 0;
}
