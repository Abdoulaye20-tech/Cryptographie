#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int valeur_chiffre(int x,int k){
    return (x+k)%26;
}

int valeur_dechiffre(int x,int k){
    return (x-k)%26;
}

char *chiffrement(char mot[],int k){
    int n=strlen(mot);
    char *mot_chiffre=(char*)malloc((n+1)*sizeof(char));
    for(int i=0;i<n;i++){
        int nb=mot[i]-'A';
        int nb_chiffre=valeur_chiffre(nb,k);
        if(nb_chiffre<0){
            nb_chiffre=nb_chiffre+26;
        }
        char lettre_chiffre=(char)(nb_chiffre+'A');
        mot_chiffre[i]=lettre_chiffre;
    }
    mot_chiffre[n]='\0';
    return mot_chiffre;
}

void affichage(char mot[]){
    int n=strlen(mot);
    for(int i=0;i<n;i++){
        putchar(mot[i]);
    }
    printf("\n");
}

void dechiffrement(char mot[]){
    int n=strlen(mot);
    char *mot_chiffre=(char*)malloc((n+1)*sizeof(char));
    for(int k=0;k<26;k++){
        mot_chiffre=chiffrement(mot,-k);
        printf("cle ->%d ",k);
        affichage(mot_chiffre);
        free(mot_chiffre);
    }
}

int main()
{
    char mot[]="BONJOUR";
    char *mot_chiffre=chiffrement(mot,13);
    printf("Mot obtenu apres chiffrement : ");
    affichage(mot_chiffre);

    char mot1[]="OBAWBHE";
    printf("Ensemble des cles et mots obtenus apres dechiffrement :\n");
    dechiffrement(mot1);
    return 0;
}
