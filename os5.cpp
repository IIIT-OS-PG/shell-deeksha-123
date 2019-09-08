#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>



void readdata(char arr[],char *brr[])
{
char drr[1024];
int count=0,i=0,j=0;
char *array[100],*parsech;
while(1)
{
int c=fgetc(stdin);
drr[count++]=(char)c;
if(c=='\n')break;
}
if(count==1)return ;
parsech=strtok(drr," \n");
while(parsech!=NULL)
{  
array[i++]=strdup(parsech);
parsech=strtok(NULL," \n");
}
strcpy(arr,array[0]);
for(int j=0;j<i;j++)
brr[j]=array[j];
brr[i]=NULL;


}

void printDir() 
{ 
    char trr[1024]; 
    printf("\nDir: %s",getcwd(trr, sizeof(trr)),trr);  
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
/*void shellprint_welcome() {
    printf("Welcome to IIITH SHELL\n");
}*/

int main()
{
char arr[100];
char *brr[20];
char crr[100];
char *vp[]={(char*) "PATH=/bin",0};  
 //pid = fork();
printDir();
printf("   ");
while(1)
{
prompt();
readdata(arr,brr);
if(strcmp(brr[0],"cd")==0)
chdir(brr[1]);
pid_t p=fork();
if(p<0)
{
printf("error");
exit(1);
}
else if(p==0)
{
//cmd="/bin/";
//cmd=cmd+command;
strcpy(crr,"/bin/");
strcat(crr,arr);
execve(crr,brr,vp);
}
else
{wait(NULL);
//if(strcmp(brr[0],"cd")==0)

if(strcmp(arr,"exit")==0)
break;}
}

}
