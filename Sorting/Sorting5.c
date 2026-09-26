#include <stdio.h>

typedef long long ll;

struct Street {
    ll l;
    ll r;
};

int main() {
    int t;
    if (scanf("%d", &t) != 1) return 0;
    while (t--) {
        ll n, L;
        scanf("%lld %lld", &n, &L);
        struct Street streets[2005];
        for (ll i = 0; i < n; i++) {
            scanf("%lld %lld", &streets[i].l, &streets[i].r);
            if (streets[i].l > streets[i].r) {
                ll tmp = streets[i].l;
                streets[i].l = streets[i].r;
                streets[i].r = tmp;
            }
        }
        int possible = 0;
        for (ll i = 0; i < n; i++) {
            ll start = streets[i].l;
            ll target = start + L;
            ll cur_right = start;
            while (cur_right < target) {
                ll maxright = cur_right;
                for (ll j = 0; j < n; j++) {
                    if (streets[j].l <= cur_right && streets[j].r <= target) {
                        if (streets[j].r > maxright) {
                            maxright = streets[j].r;
                        }
                    }
                }
                if (cur_right == maxright) {
                    break;
                }
                cur_right = maxright;
            }
            if (cur_right == target) {
                possible = 1;
                break;
            }
        }
        if (possible) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }
    return 0;
}
