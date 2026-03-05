#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int valeur_chiffre(int x,int a,int b){
    return (a*x+b)%26;
}

int inverse_modulaire(int a){
    for(int x=1;x<26;x++){
        if(((a%26)*(x%26))%26==1)
            return x;
    }
    return 1;
}

int valeur_dechiffre(int y,int a,int b){
    int a_inv = inverse_modulaire(a);
    int resultat=(a_inv*(y-b))%26;
    if (resultat< 0)
         resultat=resultat+26; 
    return resultat;
}

char *chiffrement(char mot[],int a,int b){
    int n=strlen(mot);
    char *mot_chiffre=(char*)malloc((n+1)*sizeof(char));
    for(int i=0;i<n;i++){
        int nb=mot[i]-'A';
        int nb_chiffre=valeur_chiffre(nb,a,b);
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

char *dechiffrement(char mot_chiffre[],int a,int b){
    int n=strlen(mot_chiffre);
    char *mot_clair=(char*)malloc((n+1)*sizeof(char)); 
    for(int i=0;i<n;i++) {
        int y=mot_chiffre[i]-'A';
        int x=valeur_dechiffre(y,a,b);
        mot_clair[i]=(char)(x+'A');
    }
    mot_clair[n]='\0';
    return mot_clair;
}

int main(){
    char mot[]="ELECTION";
    char *mot_chiffre=chiffrement(mot,3,5);
    printf("Mot obtenu apres chiffrement : ");
    affichage(mot_chiffre);

    char mot_chiff[]="RMRLKDVS";
    char *mot_dechiffre=dechiffrement(mot_chiff,3,5);
    printf("\nEnsemble des cles et mots obtenus apres dechiffrement :\n");
    affichage(mot_dechiffre);
    return 0;
}