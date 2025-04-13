#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*int main(){
    int pid = fork();
    if (pid == 0){
        char *args[]={"ps","-aux",NULL};
        execvp("ps",args);
    }
    else{
        int statut = wait(NULL);
    }
    return 0;
}*/

int main(){
    system("ps -aux");
    return 0;
}
