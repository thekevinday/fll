#include <stdio.h>

extern void print_f();
extern void print_a();
extern void print_k();
extern void print_e();

int main(int argc, char *argv[]) {
  print_f();
  print_a();
  print_k();
  print_e();

  printf("\n");

  return 0;
}
