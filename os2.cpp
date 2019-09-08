#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h>  
#include <stdlib.h> 
#include <errno.h>   
#include <sys/wait.h> 
#include<string.h>
#include <fstream>
#include<iostream>
using namespace std;
void init()
{
//char *src_path;
//long int src_fd;
 // char *des_path;
    //src_path="/home/deeksha/Desktop/bashrc.txt";
   // des_path=file[2];
    FILE *fptr = fopen("/home/deeksha/Desktop/bashrc.txt", "w+"); 
 char * user_name=getenv("USER");
 char * log =getenv("LOGNAME");
char * path=getenv("PATH");
char * home=getenv("HOME");
fprintf(fptr,"%s\n", user_name); 
fprintf(fptr,"%s\n", log); 
fprintf(fptr,"%s\n", path); 
fprintf(fptr,"%s\n", home); 
fclose(fptr); 

}
 
void pipe_handle(char*inp[],int i)
          {
            int fd[2]={0,1};
                int k=0;
                int f=0;
                int j=0;
              char * pch, *pch1;
             char * array[100];
               char * array1[100];
              pch=strtok(inp[0]," /n");
             pch1=strtok(inp[1]," /n");
            while(pch!=NULL)
              {  
                array[j++]=strdup(pch);
                pch=strtok(NULL," /n");
              }
printf(inp[0]);
            j=0;
           while(pch1!=NULL)
              {  
                  array1[j++]=strdup(pch1);
                  pch1=strtok(NULL," /n");
              }
          while(*inp !=NULL)
             {
                pipe(fd);
               int pi=fork();
               if(pi<0)
            perror("error");
           else if(pi==0)
                 {              
                  dup2(f,0);
                  if(*(inp+1)!=NULL)
                 dup2(fd[1],1);
               close(fd[1]);
             close(fd[0]);

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
void fun(char line[],char *par[],int n)
{
char *array[100],*pch;
int i=0,j=0;
pch=strtok(line,"|");
while(pch!=NULL)
{  
array[i++]=strdup(pch);
pch=strtok(NULL,"|");
}
for(int j=0;j<i;j++)
par[j]=array[j];
par[i]=NULL;
pipe_handle(par,n);
}



char **  read()
{
char line[1024];
init();
int count=0,i=0,j=0,p=0;
char *pch,**par=(char**)malloc(sizeof(char *)*100);
while(1)
{
par[i]=(char*)malloc(sizeof(char )*100);
int c = getchar();
line[count++]=c;
if(char(c)=='|')
p++;
if(c=='\n')break;
}
line[count]='\0';
FILE *fp=fopen("history.txt","a");
fputs(line,fp);
fclose(fp);
if(count==1)return NULL;
pch=strtok(line," \n");
while(pch!=NULL)
{  
par[i++]=strdup(pch);
pch=strtok(NULL," \n");
}
par[i]=NULL;
return par;
}

/*void printDir() 
{ 
    char trr[1024]; 
    printf("\nDir: %s",getcwd(trr, sizeof(trr)),trr);  
} */

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
void fun(char **parameters)
{
ifstream f1;
 f1.open("/home/deeksha/Desktop/bashrc.txt");
if(strcmp(parameters[0],"$PATH")==0)
        {
 
           
             int i=1;
            string line;
            while(i<=4)
           {
                getline(f1,line);
              if(i==3)
              cout<<line;
//c=fgetc(f);
                i++;
                }
       }
            if(strcmp(parameters[0],"$USER")==0)
         {
 
      // f1.open("/home/deeksha/Desktop/bashrc.txt");
       int i=1;
      string line;
         while(i<=4)
        {
         getline(f1,line);
        if(i==1)
       cout<<line;
//c=fgetc(f);
           i++;
        }
      }
      if(strcmp(parameters[0],"$LOG")==0)
   {
 
      //f1.open("/home/deeksha/Desktop/bashrc.txt");
    int i=1;
string line;
while(i<=4)
{
getline(f1,line);
if(i==2)
cout<<line;
//c=fgetc(f);
i++;
}
}
 if(strcmp(parameters[0],"$HOME")==0)
{
 
//f1.open("/home/deeksha/Desktop/bashrc.txt");
int i=1;
string line;
while(i<=4)
{
getline(f1,line);
if(i==4)
cout<<line;
//c=fgetc(f);
i++;
}
}
}
int main()
{ 
   pid_t  pid; 
char cmd[100];
//char *envp[]={(char*) "PATH=/bin",0};   
//printDir();
printf("   ");

while(1)
{

char **parameters=(char**)malloc(sizeof(char *)*100);
 prompt();
 parameters =read();
if(strcmp(parameters[0],"cd")==0)
chdir(parameters[1]);
else if(strcmp(parameters[0],"exit")==0)
break;
  else if(strcmp(parameters[0],"$HOME")==0||strcmp(parameters[0],"$LOG")==0||strcmp(parameters[0],"$USER")==0||strcmp(parameters[0],"$PATH")==0)
          fun(parameters);


else
{
pid=fork();
  if ( pid<0)
{ 
  
      printf("error"); 
      exit(1); 
   } 
   if (pid == 0)
{   
      execvp(parameters[0],parameters);
   } 
   else
  { 
  wait(NULL);
   }


free(parameters);
}

} 

   return 0; 
} 
