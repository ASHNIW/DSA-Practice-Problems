#include <stdio.h>
#include <string.h>

int main() {
    char s[1005];
    if (!fgets(s, sizeof(s), stdin)) return 0;
    
    int l = strlen(s);
    while (l > 0 && (s[l - 1] == '\n' || s[l - 1] == '\r')) {
        s[--l] = '\0';
    }
    
    int freq[256] = {0};
    int i;
    for(i=0;i<l;i++) {
        freq[(unsigned char)s[i]]++;
    }
    
    int max_cnt = -1;
    char best_char = 0;
    
    for (i = 0; i < 256; i++) {
        if (freq[i] > max_cnt) {
            max_cnt = freq[i];
            best_char = (char)i;
        }
    }
    
    printf("%c %d\n", best_char, max_cnt);
    return 0;
}
