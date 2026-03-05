#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char code[] = "ADFGVX";
char table[6][6] = {
    {'K', 'J', '2', 'I', '5', 'D'},
    {'3', 'A', 'L', 'W', '0', '4'},
    {'G', '9', 'T', 'R', 'E', 'U'},
    {'X', 'B', 'M', 'V', '7', 'Q'},
    {'8', 'F', '1', 'Y', 'O', 'Z'},
    {'P', '6', 'H', 'N', 'C', 'S'}
};

void substituer(char c,char *p){
    c=toupper(c);
    for(int i=0;i<6;i++) {
        for(int j=0;j<6;j++){
            if(table[i][j]==c){
                p[0]=code[i];
                p[1]=code[j];
                return;
            }
        }
    }
    p[0]='\0';
}

void chiffrer(char *msg,char *cle,char *res){
    int n=strlen(cle),m=strlen(msg),l=(m+n-1)/n,k=0;
    typedef struct{
        char c;
        char *s; 
    }Col;
    Col *v=malloc(n*sizeof(Col));
    for(int i=0;i<n;i++){
        v[i].c=cle[i];
        v[i].s=calloc(l+1,1);
        for (int j=0;j<l;j++){
            if(j*n+i<m)
                v[i].s[j]=msg[j*n+i];
        }
    }

    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            if(v[i].c>v[j].c){
                Col t=v[i];v[i]=v[j];v[j]=t;
            }
        }
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<l;j++){
            if (v[i].s[j])
                res[k++]=v[i].s[j];
        }
        free(v[i].s);
    }
    res[k]='\0';
    free(v);
}

void dechiffrer(char*msg,char*cle,char*res){
    int n=strlen(cle),m=strlen(msg),l=m/n,r=m%n,k=0,cur=0,p_s=0;
    typedef struct{char c;int p;char*s;}Col;
    Col*v=malloc(n*sizeof(Col));
    for(int i=0;i<n;i++){
        v[i].c=cle[i];v[i].p=i;
        int len=l+(i<r?1:0);
        v[i].s=calloc(len+1,1);
    }
    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            if(v[i].c>v[j].c){Col t=v[i];v[i]=v[j];v[j]=t;}
        }
    }
    for(int i=0;i<n;i++){
        int len=l+(v[i].p<r?1:0);
        for(int j=0;j<len;j++)v[i].s[j]=msg[cur++];
    }
    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            if(v[i].p>v[j].p){Col t=v[i];v[i]=v[j];v[j]=t;}
        }
    }
    char*sub=malloc(m+1);
    for(int j=0;j<l+1;j++){
        for(int i=0;i<n;i++){
            if(j<(l+(i<r?1:0)))sub[p_s++]=v[i].s[j];
        }
    }
    for(int i=0;i<m;i+=2){
        int r_i=-1,c_i=-1;
        for(int g=0;g<6;g++){
            if(code[g]==sub[i])r_i=g;
            if(code[g]==sub[i+1])c_i=g;
        }
        if(r_i!=-1&&c_i!=-1)res[k++]=table[r_i][c_i];
    }
    res[k]='\0';
    for(int i=0;i<n;i++)free(v[i].s);
    free(v);free(sub);
}

int main(){
    char *message="devoirmardi5";
    char *cle="KARL";

    char *sub=malloc(strlen(message)*2+1);
    char paire[2];
    sub[0]='\0';
    
    for(int i=0;i<strlen(message);i++){
        substituer(message[i],paire);
        strncat(sub,paire,2);
    }

    char *final=malloc(strlen(sub)+1);
    chiffrer(sub,cle,final);
    printf("Message clair : %s\n", message);
    printf("Substitution : %s\n", sub);
    printf("Message chiffre : %s\n", final);

    printf("Dechiffrage du message : \n");
    char* chif= "XGGFGGAGAGFAVVGDXVFVFDAA";
    char dechif[25];
    dechiffrer(chif,cle,dechif);
    printf("Message chiffre : %s\n",chif);
    printf("Message decode  : %s\n",dechif);

    free(sub);
    free(final);
    return 0;
}