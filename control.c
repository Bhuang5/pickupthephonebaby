#include <unistd.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/ipc.h>

int main(int argc, char *argv[]){
  int semid;
  int m;
  int key = ftok("writefile" , 22);
  int sc;
  FILE *f;
  int file;
  
  if(!strcmp(argv[1],"-c")){
    union semun su;
    m = shmget(key,1024, IPC_CREAT | IPC_EXCL | 0644);
    printf("memory: %d\n", m);
    file = open("read.txt", O_CREAT | O_TRUNC, 0644);
    printf("file: %d\n",file);
    semid = semget(key,1, IPC_CREAT | IPC_EXCL | 0644);
    printf("semaphore: %d\n",semid);
    su.val = 1;
    sc = semctl(semid,0,SETVAL,su);
    printf("value: %d\n",sc);
  }
  
  if(!strcmp(argv[1], "-r")){
	int c;
	FILE *file = fopen("read.txt", "r");
	char store[255];
	while (fgets(store, sizeof(store), file)){
	  printf("%s", store);
	}
	fclose(file);
  
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
  
      
   
   

