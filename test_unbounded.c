#include <stdio.h>
#include <stdlib.h>
//#include "unbounded_int.h"
#include "unbounded_int.c"

static void affiche_unbounded_int(unbounded_int a){
    printf("%c",a.signe);
    chiffre *tmp=a.premier->suivant;
    printf("%c",a.premier->c);
    while(tmp!=NULL){
        printf("%c",tmp->c);
       
        if(tmp==a.dernier){
            break;
        }
         tmp=tmp->suivant;
        
    }
    printf("\n");
    
}
static void test(){
   
    unbounded_int a = string2unbounded_int("-634");
    printf("a = ");
    affiche_unbounded_int(a);
    unbounded_int b = ll2unbounded_int(-239424923948);
    printf("b = ");
    affiche_unbounded_int(b);
    unbounded_int c = string2unbounded_int("-414");
    printf("c = ");
    affiche_unbounded_int(c);
    char * f=unbounded_int2string(string2unbounded_int("-4543676543298" ));
    printf("d :%s\n",f);
    int x= unbounded_int_cmp_unbounded_int(a,b);
    printf("x = %d\n",x);
    int y= unbounded_int_cmp_unbounded_int(b,b);
    printf("y = %d\n",y);
    int z= unbounded_int_cmp_ll(b,4521524);
    printf("z = %d\n",z);
    int t= unbounded_int_cmp_unbounded_int(a,a);
    printf("t = %d\n",t);

     

}

int main(){
    test();

 

 
 
  

 
  return 0;
}
