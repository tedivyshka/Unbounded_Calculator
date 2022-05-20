#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "unbounded_int.h"

typedef struct variable{
  char* name;
  unbounded_int value;
} var;

static int tabLen = 0;
static int tabCapacity = 4;
static var* list;

static void initList(){
  list = malloc(sizeof(var) * 4);
}

static var* getVar(char* name){
  for (int i = 0; i < tabLen; i++) {
        if((list+i)->name!=NULL){
            if(strcmp(((list+i)->name),name)==0){
                return (list+i);
            }
        }
    }
    return NULL;
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

static void addNameToList(char* name){
  if(tabLen+1 >= tabCapacity){
    tabCapacity*=2;
    list = realloc(list,sizeof(var)*tabCapacity);
  }
  var temp;
  temp.name = name;
  list[tabLen] = temp;
  tabLen++;
}

static void addToList(char* name, unbounded_int val){
  if(tabLen+1 >= tabCapacity){
    tabCapacity*=2;
    list = realloc(list,sizeof(var)*tabCapacity);
  }
  var temp;
  temp.value = val;
  temp.name = name;
  list[tabLen] = temp;
  tabLen++;
}

//exemple: a = 3 * b
static void execute_op(char* lvar, char* rvar1, char op, char* rvar2){
  printf("Execute %s %c %s on %s\n",rvar1, op , rvar2 ,lvar);
  //
  //TODO: prend la variable lvar ou le cree si elle n'existe pas
  // effectue rvar1 op rvar2 et ajoute le resultat a lvar
  //
  var* v = getVar(lvar);


  unbounded_int leftUnbounded;
  if( isnumber(rvar1) ){
    leftUnbounded = ll2unbounded_int(atoll(rvar1));
  }else{
    leftUnbounded = getVar(rvar1)->value;
    //TODO variable doesnt exist -> exit with error
  }

  unbounded_int rightUnbounded;
  if( isnumber(rvar2) ){
    rightUnbounded = ll2unbounded_int(atoll(rvar2));
  }else{
    if(getVar(rvar2) == NULL){
      printf("Did not find %s\n",rvar2);
      exit(2);
    }
    rightUnbounded = getVar(rvar2)->value;
    //TODO variable doesnt exist -> exit with error
  }

  unbounded_int value;

  switch(op){
    case '*':
      value = unbounded_int_produit(leftUnbounded,rightUnbounded);
      break;
    case '+':
      value = unbounded_int_somme(leftUnbounded,rightUnbounded);
      break;
    case '-':
      value = unbounded_int_difference(leftUnbounded,rightUnbounded);
      break;
  }

  if(v == NULL){
      addToList(lvar,value);
      printf("After execution, assigned %s to %s\n\n",unbounded_int2string(value),lvar);
  }else{
    v->value = value;
    printf("After execution, assigned %s to %s\n\n",unbounded_int2string(v->value),v->name);
  }

  return;
}

//exemple: a = 123123
static void assign_var(char* lvar, char* rvar){
  printf("Assign %s to %s\n\n",rvar,lvar);
  var* v = getVar(lvar);
  if(v != NULL){
    v->value = string2unbounded_int(rvar);
  }
  else{
    addToList(lvar,string2unbounded_int(rvar));
  }
  return;
}

//prend un expression a = 3 * b ou a = 123123 et change la valeur de a
static void process_exp(char* buffer){
  char* currentChar = buffer;

  char* lvar = malloc(sizeof(char) * 100);
  char* rvar1 = malloc(sizeof(char) * 100);
  char* rvar2 = malloc(sizeof(char) * 100);
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
  lvar = realloc(lvar, sizeof(char) * (strlen(lvar)+1));
  i = 0;

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
  rvar1 = realloc(rvar1, sizeof(char) * (strlen(rvar1)+1));

  i = 0;
  while(*currentChar != '\0'){
    if(isspace(*currentChar)){
      currentChar++;
      continue;
    }
    break;
  }
  if(*currentChar == '\0'){
    assign_var(lvar,rvar1);
    return;
  }

  op = *currentChar;
  currentChar++;

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
  rvar2 = realloc(rvar2, sizeof(char) * (strlen(rvar2)+1));
  execute_op(lvar,rvar1,op,rvar2);
  return;
}

//prend un expression print a * 3 et affiche la valeur de a * 3
void process_print(char* rhs){
  printf("Print expression: \t%s\n",rhs);

  var* v = getVar(rhs);
  if(v == NULL){

  }
  else{
    printf("%s = %s\n\n",rhs,unbounded_int2string(v->value));
  }
}


int main(int argc, char **argv)
{
  initList();
    //
    //  TODO: creer une list avec les noms des variables
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
