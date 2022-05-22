#ifndef UNBOUNDED_INT
#define UNBOUNDED_INT

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

/*
prenant en argument l’adresse d’une chaîne de caractères représentant un entier (e.g. "421")
et renvoyant une valeur unbounded_int représentant cet entier
Si la chaîne pointée par e ne représente pas un entier la fonction retournera un
unbounded_int avec le champ signe == ’*’
*/
unbounded_int string2unbounded_int(const char *e);

/*
prend en argument un nombre long long et retourne
la structure unbounded_int représentant ce nombre
*/
unbounded_int ll2unbounded_int(long long i);

/*
prend en argument une structure unbounded_int représentant un entier et retourne
cet entier sous forme d’une chaîne de caractères
*/
char *unbounded_int2string(unbounded_int i);

/*
retourne une des valeurs −1, 0, 1 si, respectivement, a < b, a == b, a > b
(ou a, b sont les entiers représentés par a et b)
*/
int unbounded_int_cmp_unbounded_int(unbounded_int a,unbounded_int b);

/*
retourne une des valeurs −1, 0, 1 si, respectivement, a < b, a == b, a > b
le second argument est de type long long
*/
int unbounded_int_cmp_ll(unbounded_int a,long long b);

/*
renvoyant la représentation de la somme de deux entiers représentés par a et b
*/
unbounded_int unbounded_int_somme(unbounded_int a,unbounded_int b);

/*
renvoyant la représentation de la difference de deux entiers représentés par a et b
*/
unbounded_int unbounded_int_difference(unbounded_int a,unbounded_int b);

/*
renvoyant la représentation du produit de deux entiers représentés par a et b
*/
unbounded_int unbounded_int_produit(unbounded_int a,unbounded_int b);

/*
renvoyant la représentation du quotient de deux entiers représentés par a et b
*/
unbounded_int unbounded_int_quotient(unbounded_int a,unbounded_int b);


#endif
