#include <unistd.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/ipc.h>


int main(int argc, char *argv[]){
  int sem = semget(ftok("makefile", 122016), 1, IPC_CREAT | 0644 );
  int mem = shmget( ftok("makefile", 2016), 4, IPC_CREAT | 0644);

  char input[2016];


  struct sembuf buf = {0, -1, SEM_UNDO};
  //printf("%d\n",sem );
  int* memInfo = shmat(mem, 0, 0);
  int readFile = open("read.txt", O_RDONLY);
  int writeFile = open("read.txt", O_CREAT | O_APPEND | O_WRONLY , 0644);
  
  int mesLen = *(memInfo);
  char mes[mesLen + 1];
  lseek(readFile, -1 * mesLen, SEEK_END);
  read(readFile, mes, mesLen);
  mes[mesLen] = 0;
  
  close(readFile);
  
  printf("Your message!\n");
  printf("Message: %s\n",mes);
  

  printf("What's your response? \n");
  fgets(input, 2016, stdin);
  write(writeFile, input, strlen(input));
  close(writeFile);
  *memInfo = strlen(input);

  buf.sem_num = 1;
  semop(sem, &buf, 1);


  return 0;
}
