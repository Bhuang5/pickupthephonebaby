#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>


int main(int argc, char *argv[]){
  int semid;
  int key = ftok("writefile" , 22);
  int sc;
  FILE *f;
  int file;
  
  
  if (strcmp(ret[0], "-c")){
    int fd = open(ret[0], O_CREAT | O_WRONLY | O_APPEND, 0644);
    close(fd);
  
    sm = shmget(key, 1024, IPC_CREAT | 0664);
    printf("shared mem created!! %d\n", sm);
    
    semid = semget(key, 1, IPC_CREAT | 0644);
    printf("semaphore created %d\n", semid);

    union semun{
      int val;
    }su;
    su.val = 1;
    //setting semaphore value
    sc = semctl(semid, 0, SETVAL, su);
    printf("value set: %d\n", sc);
  }

  if (strcmp(ret[0], "-r")){
    
  }

  
  /*
  int semid = semget(ftok("makefile",22),1,0);
  printf("[%d] Before access %d\n",getpid(),x);
  struct sembuf sb;
  sb.sem_num = 0;
  sb.sem_flg = SEM_UNDO;
  sb.sem_op = -1;

  semop(semid, &sb, 1);
  printf("[%d] Im in!\n", getpid());

  //sleep(x);
  sb.sem_op=1;
  semop(semid,&sb,1);

  printf("[%d] Im done!\n", getpid());

    */
}
