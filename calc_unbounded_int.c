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


static void exitError(char *error){
  printf("An error occurred: %s\n",error);
  exit(EXIT_FAILURE);
}

static void initList(){
  list = malloc(sizeof(var) * 4);
  if(list == NULL){
    exitError("Malloc error.");
  }
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


static char* reallocString(char* s,size_t* maxSize, int length){
    if(length==*(maxSize)){
        *(maxSize)*=2;
        s = realloc(s,sizeof(char)* *(maxSize));
        if(s == NULL){
          exitError("Realloc fail.");
        }
    }
    return s;
}

static void addToList(char* name, unbounded_int val){
  if(tabLen+1 >= tabCapacity){
    tabCapacity*=2;
    list = realloc(list,sizeof(var)*tabCapacity);
    if(list == NULL){
      exitError("Realloc fail.");
    }
  }
  var temp;
  temp.value = val;
  temp.name = name;
  list[tabLen] = temp;
  tabLen++;
}

//exemple: a = 3 * b
static void execute_op(char* lvar, char* rvar1, char op, char* rvar2){
  //
  // effectue rvar1 op rvar2 et ajoute le resultat a lvar
  //
  var* v = getVar(lvar);


  unbounded_int leftUnbounded;
  if( isnumber(rvar1) ){
    leftUnbounded = string2unbounded_int(rvar1);
  }else{
    var* v = getVar(rvar1);
    if(v == NULL){
      exitError("Variable in expression not initialized.");
    }
    leftUnbounded = v->value;
  }

  unbounded_int rightUnbounded;
  if( isnumber(rvar2) ){
    rightUnbounded = string2unbounded_int(rvar2);
  }else{
    if(getVar(rvar2) == NULL){
      exitError("Variable in expression not initialized.");
    }
    rightUnbounded = getVar(rvar2)->value;
  }

  if(rightUnbounded.signe == '*' || leftUnbounded.signe == '*'){
    exitError("Assign value error.");
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
    case '/':
      value = unbounded_int_quotient(leftUnbounded,rightUnbounded);
      break;
  }

  if(value.signe == '*'){
    exitError("Assign value error.");
  }
  if(v == NULL){
      addToList(lvar,value);
  }else{
    v->value = value;
  }

  return;
}

//exemple: a = 123123
static void assign_var(char* lvar, char* rvar){
  unbounded_int value = string2unbounded_int(rvar);
  if(value.signe == '*'){
    var* rv = getVar(rvar);
    if(rv == NULL)
      exitError("Assign value error.");
    value = rv->value;
  }

  var* v = getVar(lvar);
  if(v != NULL){
    v->value = value;
  }
  else{
    addToList(lvar,value);
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
  if(lvar == NULL || rvar1 == NULL || rvar1 == NULL){
    exitError("Malloc error.");
  }

  int i = 0;
  int foundSpace=0;

  while(isspace(*currentChar)){
      currentChar++;
  }
  //add lvar name
  while(*currentChar != '\0'){
    if(isspace(*currentChar)){
      foundSpace = 1;
      currentChar++;
      continue;
    }
    if(*currentChar == '='){
      currentChar++;
      break;
    }
    if(foundSpace){
      exitError("Illegal expression.");
    }
    lvar[i] = *currentChar;
    currentChar++;
    i++;
  }
  lvar[i] = '\0';
  lvar = realloc(lvar, sizeof(char) * (strlen(lvar)+1));
  if(lvar == NULL){
    exitError("Realloc fail.");
  }


  while(isspace(*currentChar)){
      currentChar++;
  }

  i = 0;
  foundSpace = 0;
  while(*currentChar != '\0'){
    if(isspace(*currentChar)){
      foundSpace = 1;
      currentChar++;
      continue;
    }
    if(!isalnum(*currentChar)){
      break;
    }
    if(foundSpace){
      exitError("Illegal expression.");
    }
    rvar1[i] = *currentChar;
    currentChar++;
    i++;
  }
  rvar1[i] = '\0';
  rvar1 = realloc(rvar1, sizeof(char) * (strlen(rvar1)+1));
  if(rvar1 == NULL){
    exitError("Realloc fail.");
  }

  i = 0;
  while(*currentChar != '\0'){
    if(isspace(*currentChar)){
      currentChar++;
      continue;
    }
    break;
  }
  if(*currentChar == '\0'){
    if(strlen(rvar1) == 0){
      exitError("Assign value error\n");
    }
    assign_var(lvar,rvar1);
    return;
  }

  if(strchr("+-*/",*currentChar ) == NULL){
    exitError("Invalid character in assignment.");
  }

  op = *currentChar;
  currentChar++;

  while(isspace(*currentChar)){
      currentChar++;
  }
  //finished writing op
  //write rvar2
  i = 0;
  foundSpace = 0;
  while(*currentChar != '\0'){
    if(isspace(*currentChar)){
      foundSpace = 1;
      currentChar++;
      continue;
    }
    if(!isalnum(*currentChar) && (strchr("+-",*currentChar ) == NULL)){
      exitError("Invalid character in assignment.");
      break;
    }
    if(foundSpace){
      exitError("Illegal expression.");
    }
    rvar2[i] = *currentChar;
    currentChar++;
    i++;
  }
  rvar2[i] = '\0';
  rvar2 = realloc(rvar2, sizeof(char) * (strlen(rvar2)+1));
  if(rvar2 == NULL){
    exitError("Realloc fail.");
  }

  while(*currentChar != '\0'){
    if(isspace(*currentChar)){
      currentChar++;
      continue;
    }
    else{
      break;
    }
  }
  if(*currentChar != '\0'){
    exitError("Invalid assignment.");
  }
  execute_op(lvar,rvar1,op,rvar2);
  return;
}

void process_print(const char *ligne, FILE *output) {
  int strLength=0;
  int count = 0;
  size_t* maxSize = malloc(sizeof(size_t));
  if(maxSize == NULL){
    exitError("Malloc error.");
  }
  *maxSize = 1;
  char* var = malloc(sizeof(char)* *(maxSize));
  if(var == NULL){
    exitError("Malloc error.");
  }
  char current = *ligne;

  while(current!='\0'){
    if (isalnum(current)) {
      var=reallocString(var,maxSize,strLength);
      *(var+strLength)=current;
      strLength++;
    }
    else{
      exitError("Illegal character in print.");
    }
    count++;
    current = *(ligne + count);
  }
  while(isspace(current)){
      count++;
      current = *(ligne + count);
  }
  if(*(ligne + count) != '\0'){
    exitError("Illegal character in print.");
  }
  var=realloc(var,(strLength+1)*sizeof(char));
  if(var == NULL){
    exitError("Realloc fail.");
  }
  *(var+strLength) = '\0';

  char* stringOutput;
  if(getVar(var)!=NULL){
      char* tmpVarValeur=unbounded_int2string(getVar(var)->value);
      stringOutput=malloc(sizeof(char)*(strlen(tmpVarValeur)+strlen(getVar(var)->name)+4));
      if(stringOutput == NULL){
        exitError("Malloc error.");
      }

      sprintf(stringOutput,"%s = %s\n",var,tmpVarValeur);
      stringOutput[strlen(stringOutput)] = '\0';
      fputs(stringOutput,output);
  }
  else if(strLength!=0){
    if(strcmp(var,"print") == 0){
      exitError("Variable name can not be the keyword print.");
    }
    addToList(var,ll2unbounded_int(0));

    stringOutput=malloc(sizeof(char)* (strlen(var)+5));
    if(stringOutput == NULL){
      exitError("Malloc error.");
    }

    sprintf(stringOutput,"%s = +0\n",var);
    fputs(stringOutput,output);
  }
  fflush(output); // ecrire le dernier print avant de terminer le programme
}

static void exitProgram(FILE* fout){
  fflush(fout);
  exit(0);
}

static void interpreter(FILE* fin, FILE* fout){
    int taille_max=1024;
    char* ligne=malloc(sizeof(char)*taille_max);
    if(ligne == NULL){
      exitError("Malloc error.");
    }

    while(fgets(ligne,taille_max,fin)!=0){
      char* rhs = malloc(sizeof(char)*taille_max);
      char* rhs2 = malloc(sizeof(char)*taille_max);
      if(rhs == NULL || rhs2 == NULL){
        exitError("Malloc error.");
      }

      if(sscanf(ligne, "print %s %s",rhs,rhs2)){
        if(strlen(rhs2)>0 || strlen(rhs)<1)
          exitError("Illegal print expression.");
        process_print(rhs,fout);
      }
      else if(sscanf(ligne, "end%s",rhs)){
        exitProgram(fout);
      }
      else {
        process_exp(ligne);
      }
    }
}


int main(int argc,char* argv[]){
  initList();
  if(argc>5){
      exitError("Invalid argument number");
  }

  FILE* fin;
  FILE* fout;
  if(argc>1 && strcmp(argv[1],"-i")==0){
      fin=fopen(argv[2],"r");
      if(fin==NULL){
        exitError("Input file could not be found or opened.");
      }
      if(argc>3 && strcmp(argv[3],"-o")==0){
          fout=fopen(argv[4],"w");
          if(fout==NULL){
              exitError("Output file could not be opened nor created.");
          }
          interpreter(fin,fout);
      }
      else{
          interpreter(fin,stdout);
      }
  }
  else if(argc>1 && strcmp(argv[1],"-o")==0){
      fout=fopen(argv[2],"w");
      if(fout==NULL){
        exitError("Output file could not be opened nor created.");
      }
      if(argc>3 && strcmp(argv[3],"-i")==0){
          fin=fopen(argv[4],"r");
          if(fin==NULL){
            exitError("Input file could not be found or opened.");
          }
          interpreter(fin,fout);
      }
      else{
          interpreter(stdin,fout);
      }
  }
  else{
      interpreter(stdin,stdout);
  }

  if(fin != NULL)
    fclose(fin);
  if(fout != NULL)
    fclose(fout);
  return 0;
}
