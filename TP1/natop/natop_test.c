#include <stdio.h>
#include <stdlib.h>
#include "nat.h"
#include "natio.h"
#include "natop.h"

#define TEST_N(opr, x, y)                                                      \
  {                                                                            \
    printf("%s(", #opr);                                                       \
    output(stdout, x);                                                         \
    printf(", ");                                                              \
    output(stdout, y);                                                         \
    printf(") = ");                                                            \
    output(stdout, opr(x, y));                                                 \
    printf("\n");                                                              \
  }

#define TEST_B(opr, x, y)                                                      \
  {                                                                            \
    printf("%s(", #opr);                                                       \
    output(stdout, x);                                                         \
    printf(", ");                                                              \
    output(stdout, y);                                                         \
    printf(") = %s\n", opr(x, y) ? "true" : "false");                         \
  }

int main(void) {
  nat x;
  nat y;
  while (input(stdin, &x) != EOF && input(stdin, &y) != EOF) {
    // Tests des opérations
    TEST_N(sum, x, y);
    TEST_N(min, x, y);
    TEST_N(max, x, y);
    TEST_N(dist, x, y);

    // Tests des fonctions booléennes
    TEST_B(is_eq, x, y);
    TEST_B(is_neq, x, y);
    TEST_B(is_leq, x, y);
    TEST_B(is_lth, x, y);
    TEST_B(is_geq, x, y);
    TEST_B(is_gth, x, y);
  }
  
  if (!feof(stdin) || ferror(stdout)) {
    fprintf(stderr, "An error occurred on standard input or output\n");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
