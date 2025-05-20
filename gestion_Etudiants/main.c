#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Etudiant{
    char Nom[20];
    char Prenom[20];
    int Age;
    char Matricule[7];
    float Notes[11];
    float moy;
    struct Etudiant *next;
}Etudiant;

void ajouterEtudiant(Etudiant **head, Etudiant **tail, Etudiant newEtud){
    Etudiant *nouveau = malloc(sizeof(Etudiant));

    if(!nouveau){
        printf("Erreur d'allocation memoire!!!");
    }

    *nouveau = newEtud;
    nouveau->next = NULL;

    if(*head == NULL){
        *head = nouveau;
        *tail = *head;
    }
    else{
        (*tail)->next = nouveau; //L'ancienne queue pointe vers la nouvelle
        *tail = nouveau; //la valeur de la queue "tail" est mise a jour
    }
}

void supprimerEtudiant(Etudiant **head, int position){
    if(*head == NULL || position < 0){
        printf("Suppression impossible!!! Liste vide ou position invalide.");
    }

    Etudiant *tmp = *head;

    //Suppression en tete
    if(position == 0){
        *head = tmp->next;
        free(tmp);
        return;
    }

    //tmp prend le pointeur vers la position-1 structure
    for(int i = 0; tmp !=NULL && i < position - 1; i++){
        tmp = tmp->next;
    }

    //Si position invalide(trop grande)
    if(tmp == NULL || tmp->next==NULL){
        printf("Position invalide(hors de portee)!!!");
        return;
    }

    //on affecte a del le pointeur vers la position structure(Etudiant a supprimer) et on la supprime
    Etudiant *del = tmp->next;
    tmp->next = del->next;
    free(del);
}

float Moyenne(Etudiant e){
    float somme = 0;
    for(int i=0; i < 11; i++){
        somme += e.Notes[i];
    }
    return somme/11;
}

void echange(Etudiant *A, Etudiant *B){
    Etudiant C = *A;
    *A = *B;
    *B = C;

}

int PARTITION(Etudiant tab[], int p, int r){
   int x = tab[r].moy;
   int i = p-1;

   for(int j = p; j < r; j++){
        if(tab[j].moy <= x){
            i++;
            echange(&tab[i], &tab[j]);
        }
    }

    echange(&tab[i + 1], &tab[r]);
    return i + 1;
}

void triRapide(Etudiant tab[], int debut, int fin){
    if(debut < fin){
        int q = PARTITION(tab, debut, fin);
        triRapide(tab, debut, q - 1);
        triRapide(tab, q + 1, fin);
    }
}


int main()
{
    Etudiant *head = NULL, *tail = NULL;

    Etudiant e;

    for (int i = 0; i < 3; i++) {
        printf("Entrez les informations sur l'etudiant numero %d:\n", i + 1);
        printf("Nom: ");
        scanf("%s", e.Nom);
        printf("Prenom: ");
        scanf("%s", e.Prenom);
        printf("Age: ");
        scanf("%d", &e.Age);
        printf("Matricule: ");
        scanf("%s", e.Matricule);

        printf("Entrez ses notes:\n");
        char *matières[] = {"CSI", "Projet BD", "Reseaux", "IA", "Algo", "Management", "AnaNum", "Tech Comm", "ProgSys", "POO", "Anglais"};
        for (int j = 0; j < 11; j++) {
            printf("%s: ", matières[j]);
            scanf("%f", &e.Notes[j]);
        }

        e.moy = Moyenne(e);

        ajouterEtudiant(&head, &tail, e);
    }

    printf("\n**********************LISTE DES ETUDIANTS CLASSES PAR ORDRE DE MERITE**********************\n");
    if(head == NULL){
        printf("Liste vide");
    }else{
        printf("Nom\t Prenom\t Age\t Matricule\t Moyenne\n");
        Etudiant *temp = head;
        int taille = 0;
        Etudiant tab[10];
        while(temp != NULL){
            tab[taille] = *temp;
            taille++;
            temp = temp->next;
        }

        triRapide(tab, 0, taille-1);

        for(int i = taille - 1; i >= 0; i--){
            printf("%s\t %s\t %d\t %s\t %0.01f\n", tab[i].Nom, tab[i].Prenom, tab[i].Age, tab[i].Matricule, tab[i].moy);
        }

    }

    return 0;
}
