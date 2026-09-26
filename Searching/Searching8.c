#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CMDS 5
#define MAXWORDS 100

void substitute(char *sentence, char *lists[CMDS][MAXWORDS], int *list_counts) {
    int used[CMDS] = {0};

    for (int pass = 0; pass < 2; pass++) {
        char result[4000] = "";
        char *ptr = sentence;

        while (*ptr) {
            if (*ptr == '[') {
                ptr++;
                char placeholder[10];
                int j = 0;
                while (*ptr && *ptr != ']') {
                    placeholder[j++] = *ptr++;
                }
                placeholder[j] = '\0';
                if (*ptr == ']') ptr++;

                int cat = -1;
                if (strcmp(placeholder, "N") == 0) cat = 0;
                else if (strcmp(placeholder, "AV") == 0) cat = 1;
                else if (strcmp(placeholder, "V") == 0) cat = 2;
                else if (strcmp(placeholder, "AJ") == 0) cat = 3;

                if (cat >= 0 && used[cat] < list_counts[cat]) {
                    strcat(result, lists[cat][used[cat]]);
                    used[cat]++;
                } else {
                    strncat(result, "[", 1);
                    strncat(result, placeholder, strlen(placeholder));
                    strncat(result, "]", 1);
                }
            } else {
                strncat(result, ptr, 1);
                ptr++;
            }
        }

        printf("%s\n", result);
    }
}

int main() {
    char line[4000];
    char sentence[4000];
    char *lists[CMDS][MAXWORDS];
    int list_counts[CMDS];
    char *cmds[CMDS] = {"NOUNS", "ADVERBS", "VERBS", "ADJECTIVES", "END"};

    sentence[0] = '\0';

    for (int i = 0; i < CMDS; i++) {
        list_counts[i] = 0;
        for (int j = 0; j < MAXWORDS; j++) {
            lists[i][j] = NULL;
        }
    }

    int current_section = -1;

    while (fgets(line, sizeof(line), stdin)) {
        line[strcspn(line, "\n")] = 0;

        if (strcmp(line, "END") == 0) {
            if (sentence[0] != '\0') {
                substitute(sentence, lists, list_counts);
            }
            break;
        }

        if (strchr(line, '[') != NULL) {
            if (sentence[0] != '\0') {
                substitute(sentence, lists, list_counts);

                for (int i = 0; i < CMDS; i++) {
                    for (int j = 0; j < list_counts[i]; j++) {
                        free(lists[i][j]);
                    }
                }

                for (int i = 0; i < CMDS; i++) {
                    list_counts[i] = 0;
                    for (int j = 0; j < MAXWORDS; j++) {
                        lists[i][j] = NULL;
                    }
                }
            }

            strcpy(sentence, line);
            current_section = -1;
            continue;
        }

        int is_header = -1;
        for (int i = 0; i < CMDS - 1; i++) {
            if (strcmp(line, cmds[i]) == 0) {
                is_header = i;
                break;
            }
        }

        if (is_header >= 0) {
            current_section = is_header;
        } else if (current_section >= 0 && list_counts[current_section] < MAXWORDS) {
            lists[current_section][list_counts[current_section]] = strdup(line);
            list_counts[current_section]++;
        }
    }

    for (int i = 0; i < CMDS; i++) {
        for (int j = 0; j < list_counts[i]; j++) {
            free(lists[i][j]);
        }
    }

    return 0;
}