#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int pre[MAXN];
int in[MAXN];
int pos[MAXN];

void solve(int pre_l, int in_l, int len) {
    if (len <= 0) return;
    int root = pre[pre_l];
    int root_pos = pos[root];
    int left_len = root_pos - in_l;
    int right_len = len - 1 - left_len;
    
    solve(pre_l + 1, in_l, left_len);
    solve(pre_l + 1 + left_len, root_pos + 1, right_len);
    printf("%d ", root);
}

int main() {
    int n, i;
    if (scanf("%d", &n) != 1) return 0;
    for(i=1;i<=n;i++) {
        scanf("%d", &pre[i]);
    }
    for(i=1;i<=n;i++) {
        scanf("%d", &in[i]);
        pos[in[i]] = i;
    }
    solve(1, 1, n);
    printf("\n");
    return 0;
}
