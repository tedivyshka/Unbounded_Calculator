#include <stdio.h>
#include <string.h>
#include "unbounded_int.h"


int main(int argc, char const *argv[])
{
    FILE * tmp=fopen("src","r"); 
    char ligne[100];
    char var[50];
    char dig[50];
    int i=0;
    
    while(!feof(tmp)){
        char c=fgetc(tmp);
        if(c!=' ' && c!='\n'){
            ligne[i]=c;
            i++;
            
        }
        if(c=='\n'){
            int k=0;
            int z=0;
                for(int i=0;i<strlen(ligne);i++){
                    
                    if(ligne[i]=='='){
                       continue;
                    }
                    if(ligne[i]<='z' || ligne[i]>='a'){
                       var[z]=ligne[i];
                       z++;
                    }
                   if(isdigit(ligne[i])){
                       dig[k]=ligne[i];
                       k++;
                    }
                    
                }
            }
        
       
        
    }

}



