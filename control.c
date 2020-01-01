#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>

#define KEY 31415

int main (int argc, char *argv[]) {

    if (argc == 0) {
        printf("missing flag\n");
        return 0;
    }

    else {
        if (strcmp(argv[1],"-c")) {
            printf("detects -c\n");
        }
    }

    return 0;
}