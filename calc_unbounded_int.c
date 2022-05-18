#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "unbounded_int.h"


//exemple: a = 3 * b
void execute_op(char* lvar, char* rvar1, char op, char* rvar2){
  printf("Execute %c on %s\n",op,lvar);
  //
  //TODO: prend la variable lvar ou le cree si elle n'existe pas
  // effectue rvar1 op rvar2 et ajoute le resultat a lvar
  //
  return;
}

//exemple: a = 123123
void assign_var(char* lvar, char* rvar1){
  printf("Assign %s to %s\n",rvar1,lvar);
  //
  //TODO: prend la variable lvar ou le cree si elle n'existe pas
  // effectue rvar1 a lvar
  //
  return;
}

//prend un expression a = 3 * b ou a = 123123 et change la valeur de a
void process_exp(char* buffer){
  char* currentChar = buffer;
  char lvar[100];
  char rvar1[100]; char rvar2[100];
  char op;

  int i = 0;
  //add lvar name
  while(*currentChar != '\0'){
    if(isspace(*currentChar)){
      currentChar++;
      continue;
    }
    if(*currentChar == '='){
      currentChar++;
      break;
    }
    lvar[i] = *currentChar;
    currentChar++;
    i++;
  }
  lvar[i] = '\0';
  i = 0; //finished writing lvar name

  while(*currentChar != '\0'){
    if(isspace(*currentChar)){
      currentChar++;
      continue;
    }
    if(!isdigit(*currentChar) && !isalpha(*currentChar)){
      break;
    }
    rvar1[i] = *currentChar;
    currentChar++;
    i++;
  }
  rvar1[i] = '\0';
  //printf("rvar1: %s\n",rvar1);
  i = 0; //finished writing rvar1 name

  while(*currentChar != '\0'){
    if(isspace(*currentChar)){
      currentChar++;
      continue;
    }
    break;
  }
  if(*currentChar == '\0'){
    //op == null, expression de forme a = 123123
    assign_var(lvar,rvar1);
    return;
  }

  //op != null, expression de forme a = 3 * b
  //next char: op
  op = *currentChar;
  currentChar++;
  //printf("Op: %c\n",op);

  i = 0; //finished writing op
  while(*currentChar != '\0'){
    if(isspace(*currentChar)){
      currentChar++;
      continue;
    }
    rvar2[i] = *currentChar;
    currentChar++;
    i++;
  }
  rvar2[i] = '\0';
  //printf("rvar2: %s\n\n",rvar2);
  //finished writing rvar2
  execute_op(lvar,rvar1,op,rvar2);
  return;
}

//prend un expression print a * 3 et affiche la valeur de a * 3
void process_print(char* rhs){
  printf("Print expression: \t%s\n",rhs);
  //
  //TODO: prend le rhs et affiche le resultat de la variable ou
  // simplement l'expression
  //
}

int main(int argc, char **argv)
{
    //
    //  TODO: creer une tableau avec les noms des variables
    //  TODO: ecrire le resultat dans un fichier output
    //

    FILE * fp;
    char buffer[1024];

    fp = fopen(argv[2], "r");
    if (fp == NULL){
      printf("Problem with file");
      exit(EXIT_FAILURE);
    }

    //
    //TODO: prend input directement du terminal avec scanf
    //
    while (fgets(buffer, 1024, fp)) {
      char rhs[100];
      if(sscanf(buffer, "print %s",rhs)){
        process_print(rhs);
      }
      else {
          process_exp(buffer);
      }
    }
    fclose(fp);
    exit(EXIT_SUCCESS);
}
