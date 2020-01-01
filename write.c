#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

#define KEY 24601

int main() {

  int file = open("story",O_WRONLY | O_APPEND);
  
  int semd;
  int v, r;

  semd = semget(KEY, 1, 0);
  struct sembuf sb;
  sb.sem_num = 0;
  //sb.sem_flg = SEM_UNDO;
  sb.sem_op = -1;

  semop(semd, &sb, 1);
  
  //display last line
  //printf("Last addition: ");


  //write new line
  printf("Your addition: ");
  dup2(file,STDIN_FILENO);
  sleep(10);

  sb.sem_op = 1;
  semop(semd, &sb, 1);

  return 0;
}