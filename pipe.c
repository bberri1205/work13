/*Write a program that does the following:
  Creates 2 unnamed pipes----
  Forks off a child process
  Sends a number from the parent to the child
  The child should perform some arithmetic operation on that number, then send the new value to the parent
  Do whatever math your heart desires
  Display messages for each step of the process
  Example output:
  [parent] sending: 15
  [child] doing maths on: 15
  [parent] received: 225*/

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){

  int fd[2];
  int fd1[2];
  int child;
  int status;
  int i=15;
  int READ= 0;
  int WRITE=1;

  pipe(fd);
  pipe(fd1);
  child=fork();

  if(child==-1){
    printf("error forking");
    exit(1);
  }

  if (child!=0){//parent sending
    // close(fd[READ]);
    write(fd[WRITE],&i,sizeof(i));
    // wait(&status);
    printf("parent sending: %d\n",i);
  }

  else{
    read(fd[READ],&i,sizeof(i));
    printf("[child] doing maths on: %d\n",i);
    i=i*i;
    write(fd1[WRITE],&i,sizeof(i));
    printf("parent received: %d\n",i);
  }
}
