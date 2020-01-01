#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

union semun {
  int              val;    /* Value for SETVAL */
  struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
  unsigned short  *array;  /* Array for GETALL, SETALL */
  struct seminfo  *__buf;  /* Buffer for IPC_INFO */
};

#define KEY 24601
#define SEG_SIZE 100

int main (int argc, char *argv[]) {

    //shared memory
    int shmd;
    char * data;

    //semaphore
    int semd;
    int v, r;

    //file
    int file;

    if (argc == 1) {
        printf("missing flag\n");
        return 0;
    }

    else {
        if (strcmp(argv[1],"-c") == 0) {
            
            //make shared memory
            shmd = shmget(KEY, SEG_SIZE, IPC_CREAT | 0644);
            data = shmat(shmd,0,0);

            //make semaphore
            semd = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0644);

            if (semd == -1) {
                printf("error %d: %s\n", errno, strerror(errno));
                semd = semget(KEY, 1, 0);
                v = semctl(semd, 0, GETVAL, 0);
                printf("semctl returned: %d\n", v);
            }

            else {
                union semun us;
                us.val = 1;
                r = semctl(semd, 0, SETVAL, us);
                printf("semctl returned: %d\n", r);
            }

            //make file
            file = open("story",O_TRUNC | O_CREAT | O_RDWR, 0644);
        }

        else if (strcmp(argv[1],"-v") == 0) {
            printf("The story so far:\n");

        }

        else if (strcmp(argv[1],"-r") == 0) {

            //remove shared memory
            shmctl(shmd, IPC_RMID, 0);

            //remove semaphore
            semctl(semd, IPC_RMID, 0);
        }

        else {
            printf("invalid flag\n");
            return 0;
        }
    }

    return 0;
}