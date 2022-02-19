#include <stdio.h>

extern void print_f(void);
extern void print_a(void);
extern void print_k(void);
extern void print_e(void);

int main(int argc, char *argv[], char *envp[]) {

  print_f();
  print_a();
  print_k();
  print_e();

  printf("\n");

  return 0;
}
