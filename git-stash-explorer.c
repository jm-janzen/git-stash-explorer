#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const int SIZE = 256;

int main(int argc, char *argv[]) {

    FILE *stash_pipe;
    stash_pipe = popen("git stash list", "r");
    if ( ! stash_pipe) {
        fprintf(stderr, "Could not read from git stash pipe\n");
        return EXIT_FAILURE;
    }

    int key = -1;
    char stash_key[SIZE];
    char stash_desc[SIZE];
    fscanf(stash_pipe, "%s %256[^\n]", stash_key, stash_desc);
    char *tok = strtok(stash_key, "{");
    while (tok != NULL) {
        if (strcmp(tok, "stash@")) {
            key = atoi(tok);
            break;
        }
        tok = strtok(NULL, "}");
    }

    printf("[%d]: %s", key, stash_desc);


    return 0;
}

