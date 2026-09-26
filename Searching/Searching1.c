#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LEN 100

char var[3][LEN];
char inp[3][LEN];

int main() {
    double m = 0, d = 0, x = 0;
    int m_idx = -1, d_idx = -1, x_idx = -1;
    for (int i = 0; i < 3; i++) {
        if (scanf("%s %s", var[i], inp[i]) != 2) return 0;
        if (strcmp(var[i], "M") == 0 || strcmp(var[i], "m") == 0) {
            if (strcmp(inp[i], "?") != 0) m = atof(inp[i]);
            else m_idx = i;
        } else if (strcmp(var[i], "D") == 0 || strcmp(var[i], "d") == 0) {
            if (strcmp(inp[i], "?") != 0) d = atof(inp[i]);
            else d_idx = i;
        } else if (strcmp(var[i], "X") == 0 || strcmp(var[i], "x") == 0) {
            if (strcmp(inp[i], "?") != 0) x = atof(inp[i]);
            else x_idx = i;
        }
    }
    if (x_idx != -1) {
        x = m / (-d);
        printf("x %.2f\n", x);
    } else if (d_idx != -1) {
        d = -m / x;
        printf("d %.2f\n", d);
    } else if (m_idx != -1) {
        m = -d * x;
        printf("m %.2f\n", m);
    }
    return 0;
}
