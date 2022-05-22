#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "unbounded_int.h"

#define SAMPLE_SIZE 10000




static long long randomLongLong(){
  int length = (random() % 18) + 1;
  long long r = ((long long)random() << 32) + random();
  for(int i = 0; i < length; i++) r /= 10;
  if(random() % 2 == 0) r *= -1;
  return r;
}

static void testSomme(){
    int result = 0;
    for(int i = 0; i < SAMPLE_SIZE; i++){
      long long a = randomLongLong();
      unbounded_int u1 = ll2unbounded_int(a);

      long long b = randomLongLong();
      unbounded_int u2 = ll2unbounded_int(b);

      long long expectedLong = a + b;
      unbounded_int returnedUI = unbounded_int_somme(u1,u2);
      long long returnedLong = atoll(unbounded_int2string(returnedUI));

      if(expectedLong == returnedLong){
          result += 1;
      }else{
        printf("Sum of: %lld and %lld\nExpected: %lld\nReturned: %lld\n",a,b,expectedLong,returnedLong);
      }
  }
  if(result == SAMPLE_SIZE)
    printf("\033[0;32m");
  printf("Correct answers for sum test : %d/%d\n",result,SAMPLE_SIZE);
  if(result == SAMPLE_SIZE)
    printf("\033[0m");
  printf("\n");
}

static void testDifference(){
    int result = 0;
    for(int i = 0; i < SAMPLE_SIZE; i++){

        long long a = randomLongLong();
        unbounded_int u1 = ll2unbounded_int(a);

        long long b = randomLongLong();
        unbounded_int u2 = ll2unbounded_int(b);

        long long expectedLong = a - b;
        unbounded_int returnedUI = unbounded_int_difference(u1,u2);
        long long returnedLong = atoll(unbounded_int2string(returnedUI));

        if(expectedLong == returnedLong){
            result += 1;
        }else{
          printf("Difference of: %lld and %lld\nExpected: %lld\nReturned: %lld\n",a,b,expectedLong,returnedLong);
        }
    }
    if(result == SAMPLE_SIZE)
      printf("\033[0;32m");
    printf("Correct answers for difference test : %d/%d\n",result,SAMPLE_SIZE);
    if(result == SAMPLE_SIZE)
      printf("\033[0m");
    printf("\n");
}

static void testProduit(){
  int result = 0;
  for(int i = 0; i < SAMPLE_SIZE; i++){
    long long a = random();
    unbounded_int u1 = ll2unbounded_int(a);

    long long b = random();
    unbounded_int u2 = ll2unbounded_int(b);

    long long expectedLong = a * b;
    unbounded_int returnedUI = unbounded_int_produit(u1,u2);
    long long returnedLong = atoll(unbounded_int2string(returnedUI));

    if(expectedLong == returnedLong){
        result += 1;
    }else{
      printf("Product of: %lld and %lld\nExpected: %lld\nReturned: %lld\n",a,b,expectedLong,returnedLong);
    }
  }
  if(result == SAMPLE_SIZE)
    printf("\033[0;32m");
  printf("Correct answers for product test : %d/%d\n",result,SAMPLE_SIZE);
  if(result == SAMPLE_SIZE)
    printf("\033[0m");
  printf("\n");
}

static void testConversions(){
    int result = 0;
    for(int j = 1; j <= SAMPLE_SIZE; j++){
        long long randLong = randomLongLong();
        unbounded_int resultUnbounded = ll2unbounded_int(randLong);
        long long resultLongLong = atoll(unbounded_int2string(resultUnbounded));
        if(randLong == resultLongLong){
          result += 1;
        }
        else{
          printf("Conversion of: %lld \nReturned: %lld\n",randLong,resultLongLong);
        }
    }
    if(result == SAMPLE_SIZE)
      printf("\033[0;32m");
    printf("Conversion from long long to unbounded int : %d / %d \n", result,SAMPLE_SIZE);
    if(result == SAMPLE_SIZE)
      printf("\033[0m");
    printf("\n");
}

static void testUIcmpUI(){
  int result = 0;
  for(int j = 1; j <= SAMPLE_SIZE; j++){
      long long randLong = randomLongLong();
      unbounded_int unb1 = ll2unbounded_int(randLong);

      long long randLong2 = randomLongLong();
      unbounded_int unb2 = ll2unbounded_int(randLong2);

      int comparison = unbounded_int_cmp_unbounded_int(unb1,unb2);
      if(randLong == randLong2 && comparison == 0){
        result += 1;
      }
      else if(randLong > randLong2 && comparison == 1){
        result += 1;
      }
      else if(randLong < randLong2 && comparison == -1){
        result += 1;
      }
      else{
        printf("Comparison of:%lld and %lld \nReturned: %d\n",randLong,randLong2,comparison);
      }
  }
  if(result == SAMPLE_SIZE)
    printf("\033[0;32m");
  printf("Comparison between unbounded int and unbounded int : %d / %d \n", result,SAMPLE_SIZE);
  if(result == SAMPLE_SIZE)
    printf("\033[0m");
  printf("\n");
}

static void testUIcmpLL(){
  int result = 0;
  for(int j = 1; j <= SAMPLE_SIZE; j++){
      long long randLong = randomLongLong();
      unbounded_int unb1 = ll2unbounded_int(randLong);

      long long randLong2 = randomLongLong();

      int comparison = unbounded_int_cmp_ll(unb1,randLong2);
      if(randLong == randLong2 && comparison == 0){
        result += 1;
      }
      else if(randLong > randLong2 && comparison == 1){
        result += 1;
      }
      else if(randLong < randLong2 && comparison == -1){
        result += 1;
      }
      else{
        printf("Comparison of:%lld and %lld \nReturned: %d\n",randLong,randLong2,comparison);
      }
  }
  if(result == SAMPLE_SIZE)
    printf("\033[0;32m");
  printf("Comparison between unbounded int and long long : %d / %d \n", result,SAMPLE_SIZE);
  if(result == SAMPLE_SIZE)
    printf("\033[0m");
  printf("\n");
}

static void testQuotient(){

  int result = 0;
  for(int i = 0; i < SAMPLE_SIZE; i++){
    long long a = random()%1024;
    unbounded_int u1 = ll2unbounded_int(a);

    long long b = random()%1024;
    while (b == 0){
       b = random()%1024;
    }
    unbounded_int u2 = ll2unbounded_int(b);

    long long expectedLong = a / b;
    unbounded_int returnedUI = unbounded_int_quotient(u1,u2);
    long long returnedLong = atoll(unbounded_int2string(returnedUI));

    if(expectedLong == returnedLong){
        result += 1;
    }else{
      printf("Quotient of: %lld and %lld\nExpected: %lld\nReturned: %lld\n",a,b,expectedLong,returnedLong);
    }
  }
  if(result == SAMPLE_SIZE)
    printf("\033[0;32m");
  printf("Correct answers for quotient test : %d/%d\n",result,SAMPLE_SIZE);
  if(result == SAMPLE_SIZE)
    printf("\033[0m");
  printf("\n");

}

static void test(){
  printf("Initializing tests.\n\n");

  testConversions();

  testUIcmpUI();
  testUIcmpLL();

  testSomme();
  testDifference();
  testProduit();
  testQuotient();
}


int main(){
    test();
    return 0;
}
