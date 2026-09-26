#include <stdio.h>
#include <stdlib.h>

#define MAXN 400005

long long arr[MAXN];
long long vals[MAXN];
int bit[MAXN];
int n, q, sz;

char qtype[MAXN];
long long qa1[MAXN];
long long qa2[MAXN];

int cmp(const void *a, const void *b) {
    long long x = *(const long long *)a;
    long long y = *(const long long *)b;
    return x < y ? -1 : (x > y ? 1 : 0);
}

int index_of(long long x) {
    int lo = 1, hi = sz, ans = sz + 1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (vals[mid] >= x) {
            ans = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    return ans;
}

int upper_of(long long x) {
    int lo = 1, hi = sz, ans = 0;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (vals[mid] <= x) {
            ans = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return ans;
}

void update(int i, int x) {
    while (i <= sz) {
        bit[i] += x;
        i += i & (-i);
    }
}

int query(int i) {
    int res = 0;
    while (i > 0) {
        res += bit[i];
        i -= i & (-i);
    }
    return res;
}

int main() {
    int i;
    char op;
    if (scanf("%d %d", &n, &q) != 2) return 0;
    for (i = 1; i <= n; i++) {
        scanf("%lld", &arr[i]);
        vals[sz++] = arr[i];
    }
    for (i = 0; i < q; i++) {
        scanf(" %c", &op);
        qtype[i] = op;
        if (op == '!') {
            int k;
            long long x;
            scanf("%d %lld", &k, &x);
            qa1[i] = k;
            qa2[i] = x;
            vals[sz++] = x;
        } else {
            long long a, b;
            scanf("%lld %lld", &a, &b);
            qa1[i] = a;
            qa2[i] = b;
        }
    }

    qsort(vals, (size_t)sz, sizeof(long long), cmp);
    int uniq = 0;
    int j = 0;
    while (j < sz) {
        int k = j;
        while (k < sz && vals[k] == vals[j]) k++;
        vals[uniq++] = vals[j];
        j = k;
    }
    sz = uniq;

    for (i = 1; i <= n; i++) update(index_of(arr[i]), 1);
    for (i = 0; i < q; i++) {
        if (qtype[i] == '!') {
            int k = (int)qa1[i];
            update(index_of(arr[k]), -1);
            arr[k] = qa2[i];
            update(index_of(arr[k]), 1);
        } else {
            printf("%d\n", query(upper_of(qa2[i])) - query(index_of(qa1[i]) - 1));
        }
    }
    return 0;
}