#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "unbounded_int.h"
#include "unbounded_int.c"

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

int main(){
  printf("%d %d \n",isnumber("123"), isnumber("-234"));
  printf(unbounded_int2string(unbounded_int_produit(ll2unbounded_int(-974430611887344),ll2unbounded_int(0))));
}
