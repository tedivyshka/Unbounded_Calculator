#include <stdio.h>
#include <stdlib.h>
#include "unbounded_int.h"


unbounded_int string2unbounded_int(const char *e){
  unbounded_int res;
  int count = 0;
  if(e[0]=='+' || e[0]=='-'){
    res.signe=e[0];
    count++;
  }
  else{
    res.signe=(e[0] >= '0' && e[0] <= '9')?'+':'*';
  }

  chiffre* current = malloc(sizeof(chiffre));
  current->c = e[count];
  if(!(e[count] >= '0' && e[count] <= '9'))
    res.signe = '*';
  res.premier = current;
  count += 1;

  while(e[count] != '\0'){
    chiffre* next = malloc(sizeof(chiffre));
    next->c = e[count];
    if(!(e[count] >= '0' && e[count] <= '9'))
      res.signe = '*';
    current->suivant = next;
    next->precedent = current;
    current = next;
    count+=1;
  }
  res.dernier = current;
  res.len = (res.signe == '-')?count-1:count;
  return res;
}

unbounded_int ll2unbounded_int(long long i) {
    unbounded_int res;
    res.signe = (i<0)?'-':'+';
    i = (i<0)?-i:i;
    int count = 0;

    chiffre* current = malloc(sizeof(chiffre));
    current->c = (char)((i%10) + '0');
    res.dernier = current;
    i = i/10;
    count += 1;

    while(i != 0){
      chiffre* precedent = malloc(sizeof(chiffre));
      precedent->c = (char)((i%10) + '0');
      current->precedent = precedent;
      precedent->suivant = current;
      current = precedent;
      i = i/10;
      count += 1;
    }
    res.premier = current;
    res.len = count;
    return res;
}

char *unbounded_int2string(unbounded_int i){
  char* res = malloc(sizeof(char)*i.len);
  *res = i.signe;
  chiffre* current = i.premier;
  int count = sizeof(char);
  while(current != NULL){
    *(res + count) = current->c;
    count+=sizeof(char);
    current = current->suivant;
  }
  return res;
}

int unbounded_int_cmp_unbounded_int(unbounded_int a, unbounded_int b){
  if(a.signe == '*'){
    return (b.signe == '*')?0:-1;
  }
  else if(b.signe == '*')
    return 1;

  if(a.signe == '+' && b.signe == '-')
    return 1;
  if(a.signe == '-' && b.signe == '+')
    return -1;

  if(a.len > b.len){
    return (a.signe == '+')?1:-1;
  }
  if(b.len > a.len){
    return (b.signe == '+')?-1:1;
  }

  chiffre* a_current = a.premier;
  chiffre* b_current = b.premier;

  while(a_current != NULL){
    if(a_current->c > b_current->c){
      return (a.signe=='-')?-1:1;
    }
    else if(a_current->c < b_current->c){
      return (b.signe=='-')?1:-1;
    }
    a_current = a_current->suivant;
    b_current = b_current->suivant;
  }
  return 0;
}

int unbounded_int_cmp_ll(unbounded_int a, long long b) {
  if(a.signe == '*'){
    return -1;
  }
  if(a.signe == '+' && b < 0)
    return 1;
  if(a.signe == '-' && b >= 0)
    return -1;

  long long temp = b;
  int nbDigits_b = 0;
  while(temp!=0){
     temp=temp/10;
     nbDigits_b++;
  }

  if(a.len > nbDigits_b){
    return (a.signe == '+')?1:-1;
  }
  if(nbDigits_b > a.len){
    return (b>0)?-1:1;
  }

  chiffre* a_current = a.dernier;
  long long b_current = (b<0)?-b:b;

  int res = 0;

  while(a_current != NULL){
    if(a_current->c-'0' > b_current%10){
      res = (a.signe=='-')?-1:1;
    }
    else if(a_current->c-'0' < b_current%10){
      res = (b<0)?1:-1;
    }
    a_current = a_current->precedent;
    b_current /= 10;
  }
  return res;
}
