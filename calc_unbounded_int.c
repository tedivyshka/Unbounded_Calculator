#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "unbounded_int.h"
typedef struct{
  char* nom;
  char * contenu;
} variable;


static int est_nom_variable(const char *var){
    assert(var);
    if(isdigit(var)) return 0;
    return 1;
}



//exemple: a = 3 * b
char* execute_op(char* lvar, char* rvar1, char op, char* rvar2){
  unbounded_int tmp1;
  unbounded_int tmp2;
  if(est_nom_variable(rvar1)==0 && est_nom_variable(rvar2)==0){
     tmp1=string2unbounded_int(rvar1);
     tmp2=string2unbounded_int(rvar2);
  }
    
       
  unbounded_int result;
  if(op=='*'){
      result=unbounded_int_produit(tmp1,tmp2);
  }
  else if(op=='+'){
      result=unbounded_int_somme(tmp1,tmp2);
  }
  else if(op=='-'){
      result=unbounded_int_difference(tmp1,tmp2);
  }
 
  //
  //TODO: prend la variable lvar ou le cree si elle n'existe pas
  // effectue rvar1 op rvar2 et ajoute le resultat a lvar
  //
  lvar=unbounded_int2string(result);
  return;
}

//exemple: a = 123123
  variable assign_var(char* lvar, char* rvar1){
    variable a ;
    a.nom=lvar;
    a.contenu=rvar1;
    return a;
}

//prend un expression a = 3 * b ou a = 123123 et change la valeur de a
void process_exp(char* buffer){
  char* currentChar = buffer;
  char lvar[100];
  char rvar1[100]; char rvar2[100];
  char op;

  int i = 0;
  //add var name
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
void run(char * fic){

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
