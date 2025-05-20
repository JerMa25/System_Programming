#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
    pid_t child_pid, grandchild_pid;
    child_pid = fork();
    //Erreur de creation du processus(pid < 0)
    if (child_pid < 0){
        printf("Erreur de creation du fils!!!");
        exit(EXIT_FAILURE);
    }
    //Le fils a bel et bien ete cree
    else if (child_pid == 0){
        printf("Je suis le fils (PID = %d). ", getpid());
        printf("Voici l'identifiant de mon pere: PPID = %d\n", getppid());
        grandchild_pid = fork();
        //Erreur de creation du processus(pid < 0)
        if (grandchild_pid < 0){
            printf("Erreur de creation du petit-fils!!!\n");
            exit(EXIT_FAILURE);
        }
        //Le petit-fils a bel et bien ete cree
        else if (grandchild_pid == 0){
            printf("Je suis le petit-fils (PID = %d). ", getpid());
            printf("Voici l'identifiant de mon pere: PPID = %d\n", getppid());
            execlp("ps", "ps", "aux", NULL);
        }
        //Le petit-fils a fini de s'executer(est mort) et donc un signal est envoye au pere
        else{
            wait(NULL);
            printf("Je suis le pere et voici l'identifiant de mon fils: %d\n", grandchild_pid);
        }
    }
    //Le fils a fini de s'executer(est mort) et donc un signal est envoye au pere
    else{
        wait(NULL);
        printf("Je suis le grand-pere et voici l'identifiant de mon fils: %d\n", child_pid);
    }
    return 0;
}
