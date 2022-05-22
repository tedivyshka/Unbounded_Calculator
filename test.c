#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "unbounded_int.h"
#include "unbounded_int.c"

int main(int argc,char* argv[]){

  unbounded_int a = string2unbounded_int("252");
  unbounded_int b = string2unbounded_int("252");
  printf("%s == %d\n",unbounded_int2string(unbounded_int_quotient(a,b)),2502/5);


}
