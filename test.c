#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "unbounded_int.h"
#include "unbounded_int.c"

int main(int argc,char* argv[]){
  unbounded_int a = string2unbounded_int("-784146697574936990");
  unbounded_int b = string2unbounded_int("9035256552061111068");
  printf("%s\n",unbounded_int2string(unbounded_int_difference(a,b)));
}

//-9223372036854775808
