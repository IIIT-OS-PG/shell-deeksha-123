#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h>  
#include <stdlib.h> 
#include <errno.h>   
#include <sys/wait.h> 
#include<string.h>
#include <fstream>
#include<iostream>
#include <fcntl.h>
using namespace std;
void init()
{
//char *src_path;
//long int src_fd;
 // char *des_path;
    //src_path="/home/deeksha/Desktop/bashrc.txt";
   // des_path=file[2];
    FILE *fileptr = fopen("/home/deeksha/Desktop/bashrc.txt", "w+"); 
 char * user_name=getenv("USER");
 char * log =getenv("LOGNAME");
char * path=getenv("PATH");
char * home=getenv("HOME");
pid_t pid=getppid();
char p[10];

fprintf(fileptr,"%s\n", user_name); 
fprintf(fileptr,"%s\n", log); 
fprintf(fileptr,"%s\n", path); 
fprintf(fileptr,"%s\n", home); 
sprintf(p,"%d",pid);
fprintf(fileptr,"%s\n",p);
fclose(fileptr); 

}
char **  read(char  *cmd)
{
char line[1024];
char *pl=line;
init();
int count=0,i=0,j=0,p=0;
char *pc,**par=(char**)malloc(sizeof(char *)*100);
while(1)
{
par[i]=(char*)malloc(sizeof(char )*100);
int c = getchar();
cmd[count++]=c;
if(char(c)=='|')
p++;
if(c=='\n')break;
}
cmd[count]='\0';
strcpy(pl,cmd);
//cout<<line;
FILE *fp=fopen("history.txt","a");
fputs(line,fp);
fclose(fp);
if(count==1)return NULL;
pc=strtok(line," \n");
while(pc!=NULL)
{  
par[i++]=strdup(pc);
pc=strtok(NULL," \n");
}
par[i]=NULL;
return par;
}
void pipe_parse(char * parameters[],char *cmd,int n)
{
//cout<<"";

   char*pipe_d;
  strcpy(pipe_d,cmd);
//cout<<cmd;
char* array[1000];
int i=0,j=0;
char * pch;
int fd[2],f=0;
pch=strtok(pipe_d,"|");

cout<<pipe_d;
while(pch!=NULL)
{  
array[i++]=strdup(pch);
pch=strtok(pipe_d, "|");
}
//array[1][2]=NULL;
array[i]=NULL;
int k=0;
pid_t pi;
for(int l=0;l<i;l++)
{
char **par=(char**)malloc(sizeof(char *)*100);
par=read(array[l]);

                pipe(fd);
                pi=fork();
               if(pi<0)
            printf("error");
           else if(pi==0)
                 {              
                  dup2(f,0);
                  if(k!=i-1)
                 dup2(fd[1],1);
                 close(fd[0]);
                 close(fd[1]);
                 execvp(par[0],par);
              }
                  else
            {
                 wait(NULL);
                close(fd[1]);
                f=fd[0];
               //execvp([1],array);
            }
       free(par);  
}

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
void fun(char **parameters)
{
ifstream f1;
//FILE * f1;
//char c;
 f1.open("/home/deeksha/Desktop/bashrc.txt");
if(strcmp(parameters[0],"$PATH")==0)
        {
 
           
             //int i=1;
            string line;
            for(int i=1;i<=5;i++)
           {
                getline(f1,line);
              if(i==3)
              cout<<line;
                //i++;
                }
cout<<endl;
       }
            if(strcmp(parameters[0],"$USER")==0)
         {
 
      // f1.open("/home/deeksha/Desktop/bashrc.txt");
      // int i=1;
      string line;
         for(int i=1;i<=5;i++)
        {
         getline(f1,line);
        if(i==1)
       cout<<line;
//c=fgetc(f);
           
        }
cout<<endl;
      }
      if(strcmp(parameters[0],"$LOG")==0)
   {
 
      //f1.open("/home/deeksha/Desktop/bashrc.txt");
    //int i=1;
string line;
for(int i=1;i<=5;i++)
{
getline(f1,line);
if(i==2)
cout<<line;
//c=fgetc(f);
//i++;
}
cout<<endl;
}
if(strcmp(parameters[0],"$$")==0)
{
 cout<<"3840"<<endl;
f1.open("/home/deeksha/Desktop/bashrc.txt");
//int i=1;
string line;
for(int i=1;i<=5;i++)
{
getline(f1,line);
if(i==5)
cout<<line;
//c=fgetc(f);
//i++;
}
}
 if(strcmp(parameters[0],"$HOME")==0)
{
 
//f1.open("/home/deeksha/Desktop/bashrc.txt");
//int i=1;
string line;
for(int i=1;i<=5;i++)
{
getline(f1,line);
if(i==4)
cout<<line;
//c=fgetc(f);
//i++;
}
cout<<endl;
}

}

void redirection(char ** parameters,int j)
{
long int src_fd;
int fd;
src_fd=open(parameters[j-1],O_CREAT|O_WRONLY,0700);


//string s=parameters[0];
//cout<<s;
parameters[j-2]=NULL;
dup2(src_fd,1);
execvp(parameters[0],parameters);
close(src_fd);
}


void redirection1(char ** parameters,int k)
{
long int src_fd;
int fd;
src_fd=open(parameters[k-1],O_CREAT|O_WRONLY|O_APPEND,0700);

//cout<<k<<endl;
//string s=parameters[k-2];
//cout<<s<<endl;
parameters[k-2]=NULL;
dup2(src_fd,1);
execvp(parameters[0],parameters);
close(src_fd);
}



int main()
{ 
   pid_t  pid; 
char cmd[1024];
//char *envp[]={(char*) "PATH=/bin",0};   
//printDir();
printf("   ");
int i=0,n=0,n1=0,j=0,k=0,n2=0;

while(1)
{

char **parameters=(char**)malloc(sizeof(char *)*100);
 prompt();
 parameters =read(cmd);
//cout<<cmd[3];
while(parameters[i]!=NULL)
{
if(strcmp(parameters[i],"|")==0)
n++;
i++;
}
while(parameters[j]!=NULL)
{
if(strcmp(parameters[j],">")==0)
n1++;
j++;
}
while(parameters[k]!=NULL)
{
if(strcmp(parameters[k],">>")==0)
n2++;
k++;
}
//cout<<n;
if(strcmp(parameters[0],"cd")==0)
chdir(parameters[1]);
else if(strcmp(parameters[0],"$$")==0)
cout<<"3840"<<endl;
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
//cout<<n;
         if(n==1) 
          {

            pipe_parse(parameters,cmd,i);
          }
else if(n1==1)
{

redirection(parameters,j);
}
else if(n2==1)
{
redirection1(parameters,k);
}
          else
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
