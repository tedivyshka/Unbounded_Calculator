#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct chiffre{
  struct chiffre *suivant;
  char c;
  struct chiffre *precedent;
} chiffre;

typedef struct{
  char signe;
  size_t len ;
  chiffre *premier;
  chiffre *dernier;
} unbounded_int;

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

static void ajoutDebut(unbounded_int * res, chiffre * current){
    if(res->len == 0) {
        res->premier = current;
        res->dernier = current;
    }else {
        current->suivant = res->premier;
        res->premier->precedent = current;
        res->premier = current;
    }
    res->len = res->len + 1;
}

static unbounded_int somme(unbounded_int a,unbounded_int b){
    unbounded_int res;
    res.len = 0;
    res.signe = '+';
    int len = 0, r = 0;
    
    chiffre * tmp1=a.dernier;
    chiffre * tmp2=b.dernier;
    
    while(tmp1!= NULL || tmp2 != NULL){
        int m=0, n = 0;
        if(tmp1 != NULL) {
            m = tmp1->c - '0';
            tmp1 = tmp1->precedent;
        }
        if(tmp2 != NULL) {
            n = tmp2->c - '0';
            tmp2 = tmp2->precedent;
        }
        
        chiffre* current = malloc(sizeof(chiffre));
        current->c = (m+n+r)%10 + '0';
        r=(m+n+r)/10;
        
        ajoutDebut(&res, current);
    }
    
    if(r > 0){
        chiffre* current = malloc(sizeof(chiffre));
        current->c = r + '0';
        ajoutDebut(&res, current);
    }
    
    return res;
}

int main() {
    unbounded_int a = string2unbounded_int("999");
    unbounded_int b = string2unbounded_int("9999");
    unbounded_int c = somme(a, b);

    printf("a = %s\n", unbounded_int2string(a));
    printf("b = %s\n", unbounded_int2string(b));
    printf("c = %s\n", unbounded_int2string(c));
    
    return 0;
}