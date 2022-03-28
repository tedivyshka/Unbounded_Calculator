tydef struct{
  char signe;
  size_t len ;
  chiffre *premier;
  chiffre *dernier;
}unbounded_int;
unbounded_int string2unbounded(const char *e);
unbounded_int ll2unbouded_int(long long i);
char *unbounded_int2string(unbounded_int i);
int unbounded_int_cmp_unbounded_int(unbounded_int a,unbounded_int b);
int unbounded_int_cmp_ll(unbounded_inta,long long b);
unbounded_int unbounded_int_somme(unbounded_inta,unbounded_int b);
unbounded_int unbounded_int_difference(unbounded_inta,unbounded_int b);
unbounded_int unbounded_int_produit(unbounded_inta,unbounded_int b);
