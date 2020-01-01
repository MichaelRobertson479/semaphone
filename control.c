#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEY 31415

int main (int argc, char *argv[]) {

    if (argc == 1) {
        printf("missing flag\n");
        return 0;
    }

    else {
        if (strcmp(argv[1],"-c") == 0) {
            printf("detects -c\n");
        }

        else if (strcmp(argv[1],"-v") == 0) {
            printf("detects -v\n");
        }

        else if (strcmp(argv[1],"-r") == 0) {
            printf("detects -r\n");
        }

        else {
            printf("invalid flag\n");
            return 0;
        }
    }

    return 0;
}