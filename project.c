
#include<stdio.h> 
#include<string.h>
#include<criu/criu.h>
#include<stdlib.h>
#include<sys/types.h> 
#include<unistd.h> 

int myfork(){

    // child process because return value zero 
    int pid=fork();
    if (pid==0) 
    {
        sleep(5);
        //printf("Hello from Child! %d \n", getpid()); 
        return 0;
     }
        // parent process because return value non-zero. 
        int newpid= getpid();
        printf("%d \n",newpid);
        char str[10];
        char comm[100];
        memset(comm, 0, 100);
        sprintf(str, "%d", pid); 
        printf("%s \n",str);
        strcat(comm,"sudo criu dump --shell-job -D /home/eman/img -t ");
        strcat(comm,str);
        system(comm);
        system("scp -r img eman@10.0.2.5:/home/eman");
        system("clear");
        //printf("Hello from Parent! %d \n", getpid()); 
        system("./client 10.0.2.5 1234");
        
     return 1; 
}

int main()
{ 
    int pr=myfork();
    if (pr == 0){
        printf("Hello from Child! \n");
     }
    if (pr ==1){
        printf("Hello from parent! \n");
    }
    printf("Hello world, this is eman!\n"); 
    return 0; 
} 

