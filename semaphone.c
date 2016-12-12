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
  

  if (!strcmp(argv[1], "-c")){
    int fd = open("read.txt", O_CREAT | O_WRONLY | O_APPEND, 0644);
    close(fd);
  
    sm = shmget(key, 1024, IPC_CREAT | 0664);
    printf("shared mem created!! %d\n", sm);
    
    semid = semget(key, 1, IPC_CREAT | 0644);
    printf("semaphore created %d\n", semid);

    union semun su;
    su.val = 1;
    sc = semctl(semid, 0, SETVAL, su);
    printf("value set: %d\n", sc);
  }
  
  if(!strcmp(argv[1], "-r")){
    semid = semget(key, 1, 0);
    sc = semctl(semid, 0, IPC_RMID);
      printf("semaphore removed: %d\n", sc);
  }
  if(!strcmp(argv[1], "-v" )){
	int c;
	FILE *file = fopen("read.txt", "r");
	char store[255];
	while (fgets(store, sizeof(store), file)){
	  printf("%s", store);
	}
	fclose(file);
  }

}
  
      
   
   
