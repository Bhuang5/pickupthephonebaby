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

/*
int main(int argc, char *argv[]){
  if (argc == 1) return 0;
  if(!strncmp(argv[1], "-c", strlen(argv[1]))){
    union semun uni;
    int sem = semget(ftok("makefile", 122016), 1, IPC_CREAT | 0644 );
    int mem = shmget( ftok("makefile", 2016), 4, IPC_CREAT | 0644);
    uni.val = 1;
    semctl(sem, 0, SETVAL, uni);
    int file = open("read.txt", O_CREAT | O_TRUNC, 0644);
    close(file);
  } 

  else if (!strncmp(argv[1], "-r", strlen(argv[1]))){
    int sem = semget(ftok("makefile", 122016), 1, IPC_CREAT | 0644 );
    int mem = shmget( ftok("makefile", 2016), 4, IPC_CREAT | 0644);
    int file = open("read.txt", O_RDONLY, 0664);
    struct stat *words = (struct stat*)malloc(sizeof(struct stat));
    stat("read.txt", words);
    if(words->st_size){
      char call[words->st_size];
      read(file, call, words->st_size);
      printf("call transcript:\n%s\n", call);
    }
    close(file);
    semctl(sem, 0, IPC_RMID);
    shmctl(mem, IPC_RMID, 0);
    free(words);
  } 

  else if (!strncmp(argv[1], "-v", strlen(argv[1]))){
    int sem = semget(ftok("makefile", 122016), 1, IPC_CREAT | 0644 );
    int val = semctl(sem, 0, GETVAL);
    int file = open("read.txt", O_RDONLY, 0664);
    struct stat *info = (struct stat*)malloc(sizeof(struct stat));
    stat("read.txt", info);
    if(info->st_size){
      char message[info->st_size];
      read(file, message, info->st_size);
      printf("message: %s\n", message);
    }
    close(file);
    free(info);
  }
  return 0;
}
*/



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
  
      
   
   

