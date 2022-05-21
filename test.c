#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "unbounded_int.h"
#include "unbounded_int.c"

typedef struct variable{
    char* nom;
    unbounded_int valeur;
}variable;

static size_t variable_array_allocated_size=1;
static size_t variable_array_size=1;
static variable* listeVar;

variable* getVariable(char* var){
    for (int i = 0; i < variable_array_size; i++) {
        if((listeVar+i)->nom!=NULL){
            if(strcmp(((listeVar+i)->nom),var)==0){
                return (listeVar+i);
            }
        }

    }
    return NULL;
}



char* checkStringSize(char* string,int tailleVar,size_t* tailleMalloc){
    if(tailleVar==*(tailleMalloc)){
        *(tailleMalloc)*=2;
        string=realloc(string,sizeof(char)*(*tailleMalloc));
    }
    return string;
}

static int isnumber(char* s){
  int len = strlen(s);
  for(int i = 0; i < len; i++){
    if(i == 0 && (s[i]=='+' || s[i]=='-') && len > 1)
      continue;
    if(!isdigit(s[i])){
      return 0;
    }
  }
  return 1;
}

//prend un expression print a * 3 et affiche la valeur de a * 3
/*
void process_print(char* rhs, FILE* out){
  printf("Print expression: \t%s\n",rhs);

    char* res = malloc(sizeof(char) * (strlen(rhs) + 6+ 6));
    res = sprintf("%s = %s\n\n",rhs,unbounded_int2string(string2unbounded_int("0")));
    fputs("a\n",out);
}
*/

void printError(char* errorMessage){
    printf("Erreur: %s\n",errorMessage);
    exit(EXIT_FAILURE);
}

char* process_print(const char *ligne, FILE *output) {
    size_t* tailleMalloc=malloc(sizeof(size_t));
    *tailleMalloc=1;
    int tailleVar=0;
    int compteur=0;
    int foundSpace=0;
    char* var=malloc(sizeof(char)*(*(tailleMalloc)));
    char c=*ligne;
    char* stringOutput;
    variable* tmpVar;

    while(c==' '){ // on avance dans la ligne tant qu'il s'agit d'un espace
        compteur++;
        c=*(ligne+compteur);
    }

    while(c!=EOF && c!='\n'){
        if(c==' '){ // cas d'un espace dans la ligne
            foundSpace=1;
        }
        else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) { // cas d'une lettre dans la variable
            if (foundSpace) { // si un espace a déjà été trouvé après un caractère, à l'encontre d'un nouveau caractère on provoque une erreur
                printError("espace invalide dans le print");
            }

            var=checkStringSize(var,tailleVar,tailleMalloc);

            *(var+tailleVar)=c;
            tailleVar++;
        }
        compteur++;
        c=*(ligne+compteur);
    }

    // récupération de notre pointeur de structure si la variable existe
    tmpVar=getVariable(var);

    if(tmpVar!=NULL){ // cas ou la variable existe
        char* tmpVarValeur=unbounded_int2string(tmpVar->valeur);
        stringOutput=malloc(sizeof(char)*(strlen(tmpVarValeur)+strlen(tmpVar->nom)+4));
        sprintf(stringOutput,"%s = %s\n",var,tmpVarValeur);
        fputs(stringOutput,output);
    }
    else if(tailleVar!=0){ // on affiche dans le fichier que la variable vaut 0 sinon
        stringOutput=malloc(sizeof(char)* strlen(var)+5);
        sprintf(stringOutput,"%s = 0\n",var);
        fputs(stringOutput,output);
    }
}

void interpreter(FILE* source, FILE* sortie){
  printf("%d\n", sortie==stdout);
    int taille_max=1024;
    char* ligne=malloc(sizeof(char)*taille_max);
    while(fgets(ligne,taille_max,source)!=0){
      printf("%s\n",ligne);
      char rhs = malloc(sizeof(char)*taille_max);
      if(sscanf(ligne, "print %s",rhs)){
        process_print(rhs,stdout);
      }
      else {
        //process_exp(ligne);
      }
    }
}

int main(int argc,char* argv[]){

    listeVar=malloc(sizeof(variable)*variable_array_allocated_size);
  if(argc>5){
      printf("Erreur: nombre d'arguments invalides");
      return EXIT_FAILURE;
  }

  FILE* fichierEntree;
  FILE* fichierSortie;
  if(argc>1 && strcmp(argv[1],"-i")==0){
      fichierEntree=fopen(argv[2],"r");
      if(fichierEntree==NULL){
          printf("Erreur \"%s\": chemin d'accès invalide",argv[2]);
          return EXIT_FAILURE;
      }
      if(argc>3 && strcmp(argv[3],"-o")==0){
          fichierSortie=fopen(argv[4],"w");
          interpreter(fichierEntree,fichierSortie);
      }
      else{
          interpreter(fichierEntree,stdout);
      }
  }
  else if(argc>1 && strcmp(argv[1],"-o")==0){
      fichierSortie=fopen(argv[2],"w");
      interpreter(stdin,fichierSortie);
  }
  else{
      interpreter(stdin,stdout);
  }


  /* TODO FREE ET FERMER LES FICHIERS A LA FIN DU MAIN ??
   * TODO AJOUTER TESTS ERREUR MALLOC ET REALLOC
   * TODO possible d'inverser -i et -o
   */
}
