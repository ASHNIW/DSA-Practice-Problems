#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void solve() {
    int n;
    if (scanf("%d", &n) != 1) return;
    
    int *boy_crush = (int *)malloc((n + 1) * sizeof(int));
    int *girl_crush = (int *)malloc((n + 1) * sizeof(int));
    int *boy_target = (int *)calloc(n + 1, sizeof(int));
    int *girl_target = (int *)calloc(n + 1, sizeof(int));
    int *boy_in = (int *)calloc(n + 1, sizeof(int));
    int *girl_in = (int *)calloc(n + 1, sizeof(int));
    
    for (int i = 1; i <= n; i++) {
        scanf("%d", &boy_crush[i]);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &girl_crush[i]);
    }
    
    for (int x = 1; x <= n; x++) {
        int g = boy_crush[x];
        int z = girl_crush[g];
        if (x != z) {
            boy_target[x] = z;
            boy_in[z]++;
        }
    }
    
    for (int y = 1; y <= n; y++) {
        int b = girl_crush[y];
        int w = boy_crush[b];
        if (y != w) {
            girl_target[y] = w;
            girl_in[w]++;
        }
    }
    
    int max_beatings = 0;
    for (int i = 1; i <= n; i++) {
        if (boy_in[i] > max_beatings) max_beatings = boy_in[i];
        if (girl_in[i] > max_beatings) max_beatings = girl_in[i];
    }
    
    int mutual_pairs = 0;
    for (int x = 1; x <= n; x++) {
        int z = boy_target[x];
        if (z > x && boy_target[z] == x) {
            mutual_pairs++;
        }
    }
    for (int y = 1; y <= n; y++) {
        int w = girl_target[y];
        if (w > y && girl_target[w] == y) {
            mutual_pairs++;
        }
    }
    
    printf("%d %d\n", max_beatings, mutual_pairs);
    
    free(boy_crush);
    free(girl_crush);
    free(boy_target);
    free(girl_target);
    free(boy_in);
    free(girl_in);
}

int main() {
    int t;
    if (scanf("%d", &t) != 1) return 0;
    
    while(true) {
        if (t <= 0) break;
        t--;
        solve();
    }
    return 0;
}
