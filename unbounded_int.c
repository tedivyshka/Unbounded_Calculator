
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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
static unbounded_int diff(unbounded_int a,unbounded_int b){
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
        int g=m-n+r;
        if(g>=0){
           current->c = (m-n+r)+ '0';
           r=0;
        }else{
           current->c = (m-n+r+10) + '0';
           r=-1;
        }
       
       
        
        ajoutDebut(&res, current);
    }

    if(r > 0){
        chiffre* current = malloc(sizeof(chiffre));
        current->c = r + '0';
        ajoutDebut(&res, current);
    }

    return res;
}
static unbounded_int Vrai_unbounded(unbounded_int a){
   chiffre * l;
    while(a.premier->c=='0'){
       
          a.len--;
        l=a.premier;
        a.premier=l->suivant;
      
    }
  return a;
}

static int Max(unbounded_int a,unbounded_int b){
 
  if(a.len<b.len){
    return 0;
  }
  if(a.len>b.len){
    return 1;
  }
  if(a.len==b.len){
    chiffre *tmp1 =a.premier;
    chiffre *tmp2=b.premier;
    while(tmp1!=NULL && tmp2!=NULL){
      if(tmp1->c>tmp2->c){
      return 1;
      }
     if(tmp1->c<tmp2->c){
      return 0;
      }
      if(tmp1->c==tmp2->c){
        tmp1=tmp1->suivant;
        tmp2=tmp2->suivant;
      }
    }
  }
    return -1;

}
unbounded_int unbounded_int_somme(unbounded_int a, unbounded_int b){
      if(a.signe=='+' && b.signe=='+'){
         return Vrai_unbounded(somme(a,b));
      }
      if(a.signe=='-' && b.signe=='-'){
        unbounded_int c=somme(a,b);
        c.signe='-';
        return Vrai_unbounded(c);
      }
      if(a.signe=='+' && b.signe=='-') {
            if((Max(a,b)==1) || (Max(a,b)==-1)){
                return Vrai_unbounded(      diff(a,b));
            }else{
                
                unbounded_int c= diff(b,a);
                c.signe='-';
              return Vrai_unbounded(c);
            }
        }
      if(a.signe=='-' && b.signe=='+'){
        if((Max(a,b)==1) || (Max(a,b)==-1)){
                unbounded_int c= diff(a,b);
                c.signe='-';
              return Vrai_unbounded(c);
        }else{
          return Vrai_unbounded(diff(b,a));
        }
         
      }  
}
unbounded_int unbounded_int_difference( unbounded_int a, unbounded_int b){  
        if(a.signe=='+' && b.signe=='+'){
            if((Max(a,b)==1)||(Max(a,b)==-1)){
                return Vrai_unbounded(diff(a,b));
            }else{
                 unbounded_int c=diff(b,a);
                 c.signe='-';
                 return Vrai_unbounded(c);
                 //return c;
            }
           
        }
        if(a.signe=='-' && b.signe=='-'){
           if((Max(a,b)==1)||(Max(a,b)==-1)){
               unbounded_int c=diff(a,b);
                 c.signe='-';
                  return Vrai_unbounded(c);
                 //return c;
            }else{
                 unbounded_int c=diff(b,a);
                 c.signe='+';
                  return Vrai_unbounded(c);
                 //return c;
            }
        }
        if(a.signe=='+' && b.signe=='-'){
            return Vrai_unbounded(somme(a,b));
          
         
        }
        if(a.signe=='-' && b.signe=='+'){
            unbounded_int c=somme(a,b);
            c.signe='-';
          return Vrai_unbounded(c);
          
        }

    }
chiffre * newChiffre(char c){
    chiffre* res = malloc(sizeof(chiffre));
    res->c = c;
    return res;
}

static unbounded_int multiplication(unbounded_int a,unbounded_int b){
    unbounded_int res;
    res.len = 0;
    res.signe = '+';
    int r = 0, m, n;
    int nombreDeZeros = 0, i;
    
    chiffre * tmp2=b.dernier;
    
    while(tmp2 != NULL){
        chiffre * tmp1=a.dernier;
        unbounded_int line;
        line.signe = '+';
        line.len = 0;
        r = 0;
        m = tmp2->c - '0';
        
        if(m == 0){
            nombreDeZeros++;
            tmp2 = tmp2->precedent;
            continue;
        }
        
        for(i = 0; i < nombreDeZeros; i++)
            ajoutDebut(&line, newChiffre('0'));
        
        while(tmp1 != NULL){
            n = tmp1->c - '0';
            
            ajoutDebut(&line, newChiffre((m*n+r)%10 + '0'));
            r=(m*n+r)/10;
            
            tmp1 = tmp1->precedent;
        }
        
        if(r > 0)
            ajoutDebut(&line, newChiffre(r + '0'));
        
        
        res = res.len != 0 ? somme(res, line) : line;
        
        nombreDeZeros++;
        tmp2 = tmp2->precedent;
    }
    
    return res;
}
