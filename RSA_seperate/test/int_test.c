#include "Test.h"

void test_Int()
{
  Int *a = Convert(67000);
  Int *b = Convert(256);

  printf("a: ");
  Print(a);
  printf("b: ");
  Print(b);
  printf("\n a + b: ");
  Print(Plus(a, b));

  printf("\n a - b: ");
  Print(Minus(a, b));

  printf("\n a * b: ");
  Print(Product(a, b));

  printf("\n a / b: ");
  Print(Div(a, b));

  printf("\n b / a: ");
  Print(Div(b, a));

  printf("\n a mod b: ");
  Print(Mod(a, b));

  printf("\n a ^ a: ");
  Print(FastPower(a, Convert(200)));
}