#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXP 1000
#define BUFLEN 100

char ponies[MAXP][BUFLEN];
char *gems[] = {
    "NONE", "Garnet", "Amethyst", "Aquamarine", "Diamond", "Emerald", "Pearl",
    "Ruby", "Peridot", "Sapphire", "Tourmaline", "Topaz", "Lapis", 0
};

int get_gem_rank(char *name) {
    int max_rank = 0;
    char temp[BUFLEN];
    strcpy(temp, name);
    char *token = strtok(temp, " ");
    while (token != NULL) {
        for (int i = 1; gems[i] != 0; i++) {
            if (strcmp(token, gems[i]) == 0) {
                if (i > max_rank) {
                    max_rank = i;
                }
            }
        }
        token = strtok(NULL, " ");
    }
    return max_rank;
}

int main() {
    int n = 0;
    char line[BUFLEN];
    while (fgets(line, sizeof(line), stdin)) {
        line[strcspn(line, "\r\n")] = 0;
        if (strlen(line) == 0) continue;
        if (strcmp(line, "END") == 0) break;
        strcpy(ponies[n++], line);
    }
    
    int ranks[MAXP];
    for (int i = 0; i < n; i++) {
        ranks[i] = get_gem_rank(ponies[i]);
    }
    
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            int a = j;
            int b = j + 1;
            int swap = 0;
            if (ranks[a] < ranks[b]) {
                swap = 1;
            } else if (ranks[a] == ranks[b]) {
                if (strcmp(ponies[a], ponies[b]) > 0) {
                    swap = 1;
                }
            }
            if (swap) {
                char tname[BUFLEN];
                strcpy(tname, ponies[a]);
                strcpy(ponies[a], ponies[b]);
                strcpy(ponies[b], tname);
                int tr = ranks[a];
                ranks[a] = ranks[b];
                ranks[b] = tr;
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        printf("%s\n", ponies[i]);
    }
    return 0;
}
