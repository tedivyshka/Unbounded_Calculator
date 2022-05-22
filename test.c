#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "unbounded_int.h"
#include "unbounded_int.c"

int main(int argc,char* argv[]){
  unbounded_int a = string2unbounded_int("0");
  unbounded_int b = string2unbounded_int("0");
  printf("%d\n",unbounded_int_cmp_unbounded_int(a,b));
}
