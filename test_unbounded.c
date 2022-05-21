#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "unbounded_int.h"
#include "unbounded_int.c"
#define SAMPLESIZE 10000

static long long randomLongLong(){
  int length = (random() % 18) + 1;
  long long r = ((long long)random() << 25) + random();
  for(int i = 0; i < length; i++) r /= 10;
  int key = rand() % 2;
  if(key == 0) r *= -1;
  return r;
}

static void testSomme(){
    int resultat = 0;
    for(int i = 0; i < SAMPLESIZE; i++){
      long long a = randomLongLong();
      unbounded_int u1 = ll2unbounded_int(a);

      long long b = randomLongLong();
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
  if(resultat == SAMPLESIZE)
    printf("\033[0;32m");
  printf("Correct answers for sum test : %d/%d\n",resultat,SAMPLESIZE);
  if(resultat == SAMPLESIZE)
    printf("\033[0m");
  printf("\n");
}

static void testDifference(){
    int resultat = 0;
    for(int i = 0; i < SAMPLESIZE; i++){

        long long a = randomLongLong();
        unbounded_int u1 = ll2unbounded_int(a);

        long long b = randomLongLong();
        unbounded_int u2 = ll2unbounded_int(b);

        long long expectedLong = a - b;
        unbounded_int returnedUI = unbounded_int_difference(u1,u2);
        long long returnedLong = atoll(unbounded_int2string(returnedUI));

        if(expectedLong == returnedLong){
            resultat += 1;
        }else{
          printf("Difference of: %lld and %lld\nExpected: %lld\nReturned: %lld\n",a,b,expectedLong,returnedLong);
        }
    }
    if(resultat == SAMPLESIZE)
      printf("\033[0;32m");
    printf("Correct answers for difference test : %d/%d\n",resultat,SAMPLESIZE);
    if(resultat == SAMPLESIZE)
      printf("\033[0m");
    printf("\n");
}

static void testProduit(){
  int resultat = 0;
  for(int i = 0; i < SAMPLESIZE; i++){
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
  if(resultat == SAMPLESIZE)
    printf("\033[0;32m");
  printf("Correct answers for product test : %d/%d\n",resultat,SAMPLESIZE);
  if(resultat == SAMPLESIZE)
    printf("\033[0m");
  printf("\n");
}

static void testlonglongToUnboundedInt(){
    int resultat = 0;
    for(int j = 1; j <= SAMPLESIZE; j++){
        long long randLong = randomLongLong();
        unbounded_int resultUnbounded = ll2unbounded_int(randLong);
        long long resultLongLong = atoll(unbounded_int2string(resultUnbounded));
        if(randLong == resultLongLong){
          resultat += 1;
        }
        else{
          printf("Conversion of: %lld \nReturned: %lld\n",randLong,resultLongLong);
        }
    }
    if(resultat == SAMPLESIZE)
      printf("\033[0;32m");
    printf("Conversion from long long to unbounded int : %d / %d \n", resultat,SAMPLESIZE);
    if(resultat == SAMPLESIZE)
      printf("\033[0m");
    printf("\n");
}

static void testUIcmpUIandUIcmpll(){
    int gradeTrue = 0;
    int gradeFalse = 0;
    int gradeSign = 0;

    int grade_ui_llTrue = 0;
    int grade_ui_llFalse = 0;
    int grade_ui_llSign = 0;
    for(int i = 1; i <= 100; i++){
        long long base = randomLongLong();
        long long base2 = -1 * base;
        long long base3 = randomLongLong();

        if(base3 == base){
            base3 += 1;
        }
        unbounded_int ui1 = ll2unbounded_int(base);
        unbounded_int ui2 = ll2unbounded_int(base);
        unbounded_int ui3 = ll2unbounded_int(base2);
        unbounded_int ui4 = ll2unbounded_int(base3);

        //test equals unbounded int
        if(unbounded_int_cmp_unbounded_int(ui1,ui2) == 0) {
            gradeTrue += 1;
        }

        // test equals unbounded int and long long
        int result_unbounded_int_cmp_ll= unbounded_int_cmp_ll(ui1,base);
        if(result_unbounded_int_cmp_ll == 0){
            grade_ui_llTrue += 1;
        }



        // test sign unbounded int
        int result_cmp_sign = unbounded_int_cmp_unbounded_int(ui1,ui3);
        if(result_cmp_sign != 0){
            if(base > base2 && result_cmp_sign == 1){
                gradeSign += 1;
            }else if(base < base2 && result_cmp_sign == -1){
                gradeSign += 1;
            }
        }else{
            if(base == 0) gradeSign += 1;
        }


        // test sign long long
        int result_cmp_sign_ui_ll = unbounded_int_cmp_ll(ui1,base2);
        if(result_cmp_sign_ui_ll != 0){
            if(base > base2 && result_cmp_sign_ui_ll == 1){
                grade_ui_llSign += 1;
            }else if(base < base2 && result_cmp_sign_ui_ll == -1){
                grade_ui_llSign += 1;
            }
        }else{
            if(base == 0) grade_ui_llSign += 1;
        }




        // test non equals unbounded int
        int result_cmp_ui_ui = unbounded_int_cmp_unbounded_int(ui1,ui4);
        if(result_cmp_ui_ui != 0){
            if(base > base3 && result_cmp_ui_ui == 1){
                gradeFalse += 1;
            }
            else if(base < base3 && result_cmp_ui_ui == -1){
                gradeFalse += 1;
            }
        }else{
            if(base == base3) gradeFalse += 1;
        }

        // test non equals unbounded int and long long
        int result_cmp_ui_ll = unbounded_int_cmp_ll(ui1,base3);
        if(result_cmp_ui_ll != 0){
            if(base > base3 && result_cmp_ui_ll == 1){
                grade_ui_llFalse += 1;
            }else if(base < base3 && result_cmp_ui_ll == -1){
                grade_ui_llFalse += 1;
            }
        }else{
            if(base == base3) grade_ui_llFalse += 1;
        }
    }



    printf("test comparison unbounded_int and unbounded_int : \n    "
           "- comparison between two identical unbounded_int  %d/100\n    "
           "- comparison with only the sign varying %d/100\n   "
           "- comparison with two different unbounded_int %d/100\n"
           ,gradeTrue,gradeSign,gradeFalse);
    printf("test comparison unbounded_int and long long : \n    "
           "- comparison between two identical numbers  %d/100\n    "
           "- comparison with only the sign varying %d/100\n   "
           "- comparison with two different numbers %d/100\n"
            ,grade_ui_llTrue,grade_ui_llSign,grade_ui_llFalse);
}

static void test(){
  printf("Initializing tests.\n\n");

  testlonglongToUnboundedInt();
  testSomme();
  testDifference();
  testProduit();

//TODO change testUIcmpUIandUIcmpll
  testUIcmpUIandUIcmpll();
}

int main(){
    test();
    return 0;
}
