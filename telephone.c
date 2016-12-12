
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

  char inputMes[2016];

  printf("Wait please, and let the other person talk!\n");

  struct sembuf buf = {0, -1, SEM_UNDO};
  //printf("%d\n",sem );
  //semop(sem, &buf, 1);
  //printf("%d\n",sem );
  int* memInfo = shmat(mem, 0, 0);
  //printf("%d\n",sem );
  int readFile = open("read.txt", O_RDONLY);
  int writeFile = open("read.txt", O_CREAT | O_APPEND | O_WRONLY , 0644);
  //printf("%d\n",sem );
  
  int mesLen = *(memInfo);
  char mes[mesLen + 1];
  lseek(readFile, -1 * mesLen, SEEK_END);
  read(readFile, mes, mesLen);
  mes[mesLen] = 0;
  //printf("%d\n", mesLen);
  close(readFile);
  //printf("%d\n", mesLen);

  printf("Message: ");
  //if (mesLen < 2) printf("Your friend has nothing to say :P. Do you want to say anything?\n");
  printf("%s \n", mes);


  printf("Well, you heard what your friend said.\n");
  printf("So, any response?: \n");
  fgets(inputMes, 2016, stdin);
  write(writeFile, inputMes, strlen(inputMes));
  close(writeFile);
  *memInfo = strlen(inputMes);

  buf.sem_num = 1;
  semop(sem, &buf, 1);


  return 0;
}
