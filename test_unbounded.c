#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "unbounded_int.h"


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

static void testSomme(){
    int resultat = 0;
    for(int i = 0; i < 10000; i++){
      long long a = random();
      unbounded_int u1 = ll2unbounded_int(a);

      long long b = random();
      unbounded_int u2 = ll2unbounded_int(b);

      long long expectedLong = a + b;
      unbounded_int returnedUI = unbounded_int_somme(u1,u2);
      long long returnedLong = atoll(unbounded_int2string(returnedUI));

      if(expectedLong == returnedLong){
          resultat += 1;
      }else{
        printf("Sum of: %lld and %lld\nExpected: %lld\nReturned: %lld\n",a,b,expectedLong,returnedLong);
      }
  }
  printf("Correct answers for sum test : %d/10000\n",resultat);
}

static void testDifference(){
    int resultat = 0;
    for(int i = 0; i < 10000; i++){

        long long a = random();
        unbounded_int u1 = ll2unbounded_int(a);

        long long b = random();
        unbounded_int u2 = ll2unbounded_int(b);

        long long expectedLong = a - b;
        unbounded_int returnedUI = unbounded_int_difference(u1,u2);
        long long returnedLong = atoll(unbounded_int2string(returnedUI));

        if(expectedLong == returnedLong){
            resultat += 1;
        }else{
          printf("Sum of: %lld and %lld\nExpected: %lld\nReturned: %lld\n",a,b,expectedLong,returnedLong);
        }
    }
    printf("Correct answers for difference test : %d/10000\n",resultat);
}

static void testProduit(){
  int resultat = 0;
  for(int i = 0; i < 10000; i++){
    long long a = random();
    unbounded_int u1 = ll2unbounded_int(a);

    long long b = random();
    unbounded_int u2 = ll2unbounded_int(b);

    long long expectedLong = a * b;
    unbounded_int returnedUI = unbounded_int_produit(u1,u2);
    long long returnedLong = atoll(unbounded_int2string(returnedUI));

    if(expectedLong == returnedLong){
        resultat += 1;
    }else{
      printf("Product of: %lld and %lld\nExpected: %lld\nReturned: %lld\n",a,b,expectedLong,returnedLong);
    }
  }
  printf("Correct answers for product test : %d/10000\n",resultat);
}

static void testlonglongToUnboundedInt(){
    int resultat = 0;
    for(int j = 1; j <= 10000; j++){
        long long randLong = random();
        unbounded_int resultUnbounded = ll2unbounded_int(randLong);
        long long resultLongLong = atoll(unbounded_int2string(resultUnbounded));
        if(randLong == resultLongLong){
          resultat += 1;
        }
        else{
          printf("Conversion of: %lld \nReturned: %lld\n",randLong,resultLongLong);
        }
    }
    printf("Conversion from long long to unbounded int : %d / 10000 \n", resultat);
}

static void test(){
  testlonglongToUnboundedInt();
  testSomme();
  testDifference();
  testProduit();
}

int main(){
    test();
    return 0;
}
