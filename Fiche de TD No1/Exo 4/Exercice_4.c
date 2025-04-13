#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#define PASSWORD "GI2027"

void verify(){
    char password[10];
    printf("Entrez le mot de passe: ");
    scanf("%s", password);
    if (strcmp(password, PASSWORD) == 0){
        exit(0);
    }
    else{
        printf("Mot de passe incorrect\n");
    }
}

int main(){
    signal(SIGINT, verify);

    while(1){
        printf("Appuyez sur CTRL+C pour terminer\n");
        sleep(5);
    }
    return 0;
}
