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
  unbounded_int a = string2unbounded_int("1795353528689353091375753130");
  unbounded_int b = ll2unbounded_int(-9223372036854775806);
  unbounded_int c = ll2unbounded_int(7867656443555498966543);

  printf("%s \n",unbounded_int2string(unbounded_int_difference(a,c)));
}
