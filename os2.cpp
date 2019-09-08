#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h>  
#include <stdlib.h> 
#include <errno.h>   
#include <sys/wait.h> 
#include<string.h>
  
void read(char command[],char *par[])
{
char line[1024];
int count=0,i=0,j=0;
char *array[100],*pch;
while(1)
{
int c=fgetc(stdin);
line[count++]=(char)c;
if(c=='\n')break;
}
if(count==1)return ;
pch=strtok(line," \n");
while(pch!=NULL)
{  
array[i++]=strdup(pch);
pch=strtok(NULL," \n");
}
strcpy(command,array[0]);
for(int j=0;j<i;j++)
par[j]=array[j];
par[i]=NULL;

}



void prompt() 
{ 
   static int first=1;

if(first)
{
const char *CLEAR_SCREEN_ANSI=" \e[1;1H\e[2J";
write(STDOUT_FILENO,CLEAR_SCREEN_ANSI,12);
first=0;
 printf("Welcome to IIITH SHELL\n");
}
printf(">>>");
} 

void pipe_handle(char**inp,int i)
{
int fd[2];
int k=0;
int f=0;
while(*inp !=NULL)
{
pipe(fd);
int pi=fork();
if(pi<0)
perror("error");
else if(pi==0)
{dup2(f,0);
if(*(inp+1)!=NULL)
dup2(fd[1],1);
close(fd[1]);
close(fd[0]);
execvp(inp[0],inp);

}
else
{
wait(NULL);
close(fd[1]);
f=fd[0];
inp++;
}
}
}
/*void shellprint_welcome() {
    printf("Welcome to IIITH SHELL\n");
}*/
int main()
{ 
   pid_t  pid; 
char cmd[100],command[100],*parameters[20];
char *envp[]={(char*) "PATH=/bin",0};   
   //pid = fork();

while(1)
{
//shellprint_welcome(); 
prompt();
read(command,parameters);
pid=fork();
  if ( pid== -1)
{ 
  
      printf("error"); 
      exit(1); 
   } 
   if (pid == 0)
{   
      strcpy(cmd,"/bin/");
     strcat(cmd,command);
//cmd="/bin/";
//cmd=cmd+command;
      execve(cmd,parameters,envp);
//int size= 
   // pipe_handle(parameters,strlen(command));
      //exit(0); 
   } 
   else
  { 
  wait(NULL);
   }
if(strcmp(command,"exit")==0)
break;
} 
   return 0; 
} 
