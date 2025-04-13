#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
    pid_t pid = fork();
    //Erreur de creation du processus(pid < 0)
    if (pid < 0){
    perror("Erreur de creation");
    exit(EXIT_FAILURE);
    }
    //Le fils a bel et bien ete cree
    else if(pid == 0){
        printf("Je suis le fils (PID = %d)", getpid());
        execlp("ps","ps","aux",NULL);
    }
    //Le fils a fini de s'executer(est mort) et donc un signal est envoye au pere
    else{
        wait(NULL);
        printf("Fin d'execution du fils");
    }
    return 0;
}
