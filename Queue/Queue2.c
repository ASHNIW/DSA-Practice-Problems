#include <stdio.h>
#include <string.h>

#define MAXN 200005

char s[MAXN];

int max(int a, int b) { return a > b ? a : b; }

int getLongest(int n) {
    if (n == 0) return 0;
    int max_len = 1;
    int cur_len = 1;
    for (int i = 1; i < n; i++) {
        if (s[i] == s[i - 1]) {
            cur_len++;
        } else {
            if (cur_len > max_len) max_len = cur_len;
            cur_len = 1;
        }
    }
    if (cur_len > max_len) max_len = cur_len;
    return max_len;
}

void pull(int k, int l, int r) {

}

int main() {
    if (scanf("%s", s) != 1) return 0;
    int n = strlen(s);
    int m;
    if (scanf("%d", &m) != 1) return 0;

    for (int i = 0; i < m; i++) {
        int idx;
        scanf("%d", &idx);
        idx--;
        if (s[idx] == '0') s[idx] = '1';
        else s[idx] = '0';

        printf("%d%c", getLongest(n), (i == m - 1) ? '\n' : ' ');
    }
    return 0;
}
