#include "KeyProducing.h"

// returns (x^y) % p
Int *power(Int *x, Int *y, Int *p)
{

  Int *res = Convert(1); // Initialize result
  x = Mod(x, p);         // Update x if it is more than or
                         // equal to p

  while (Compare(y, Convert(0)) > 0)
  {
    // If y is odd, multiply x with result
    if (IsOdd(y))
    {

      Int *res_x = Product(res, x);
      res = Mod(res_x, p);
    }

    // y must be even now

    y = Div(y, Convert(2));

    // y = y/2
    Int *x_x = FastPower(x, Convert(2));

    // x = x^2 % p
    x = Mod(x_x, p);
  }
  return res;
}

// This function is called for all k trials. It returns
// false if n is composite and returns false if n is
// probably prime.
// d is an odd number such that  d*2<sup>r</sup> = n-1
// for some r >= 1
int miillerTest(Int *d, Int *n)
{
  // Pick a random number in [2..n-2]
  // Corner cases make sure that n > 4

  Int *rand_num = Convert(rand());
  Int *mod_num = Minus(n, Convert(4));
  Int *mod_rand_num = Mod(rand_num, mod_num);
  Int *a = Plus(Convert(2), mod_rand_num);

  // Compute a^d % n
  Int *copy_d = Copy(d);

  Int *x = power(a, copy_d, n);

  Int *n_1 = Minus(n, Convert(1));
  // x == 1 || x == n - 1
  if (Compare(x, Convert(1)) == 0 || Compare(x, n_1) == 0)
    return 1;

  // Keep squaring x while one of the following doesn't
  // happen
  // (i)   d does not reach n-1
  // (ii)  (x^2) % n is not 1
  // (iii) (x^2) % n is not n-1

  // d != n-1
  while (Compare(d, n_1) != 0)
  {
    Int *x_x = FastPower(x, Convert(2));

    // x = x^2 %n
    x = Mod(x_x, n);

    d = Product(d, Convert(2));

    // x == 1
    if (Compare(x, Convert(1)) == 0)
      return 0;

    if (Compare(x, n_1) == 0)
      return 1;
  }

  // Return composite
  return 0;
}

int isPrime(Int *n, int k)
{
  // Corner cases
  if (Compare(n, Convert(1)) <= 0 || Compare(n, Convert(4)) == 0)
    return 0;
  if (Compare(n, Convert(3)) == 0)
    return 1;

  // Find r such that n = 2^d * r + 1 for some r >= 1
  Int *n_1 = Minus(n, Convert(1));
  Int *d = Copy(n_1);
  while (!IsOdd(d))
  {
    // d /= 2
    d = Div(d, Convert(2));
  }

  // Iterate given nber of 'k' times
  for (int i = 0; i < k; i++)
    if (!miillerTest(d, n))
      return 0;

  return 1;
}

int LowLevelTest(Int *num)
{
  for (int i = 0; i < 60; i++)
  {
    Int *div_num = Convert(first_prime_list[i]);

    Int *div_res = Mod(num, div_num);

    // 能够整除
    if (Compare(num, div_num) != 0 && Compare(div_res, Convert(0)) == 0)
    {
      return 0;
    }
  }
  return 1;
}

Int *BigPrime(int k)
{
  while (1)
  {
    Int *num = ProduceKRandom(k);
    if (LowLevelTest(num) && isPrime(num, 4))
    {
      return num;
    }
  }
}
