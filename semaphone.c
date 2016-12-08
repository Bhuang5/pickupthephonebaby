#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

int main(){
  printf("Enter command: ");
  char *arg = calloc(1,255); 
  fgets(arg, 255, stdin);
  arg = strsep(&arg, "\n"); //Remove newline since "the newline is retained."
  //printf("%s\n", a);

  int key = ftok("makefile",22);
  int semid;
  int sc;
  
  //srand(time(NULL));
  //int x = random() % 10;
  if (strncmp(*arg, "-c", strlen(arg) == 0)){
    semid = semget(key, 1, IPC_CREAT | 0644);
    printf("semaphore createdL %d\n", semid);
    union semun{
      int val;
    }su;
    su.val = 1;
    //setting semaphore value
    sc = semctl(semid, 0, SETVAL, su);
    printf("value set: %d\n", sc);
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
