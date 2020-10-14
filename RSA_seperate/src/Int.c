#include "Int.h"

Int *Int_init()
{
  Int *bi = (Int *)malloc(sizeof(Int));
  bi->head = init(-1);
  bi->head->next = init(0);
  bi->isError = 0;
  return bi;
}

void Int_set_list(Int *b, Node *h)
{
  b->head = h;
}

Node *Int_get_list(Int *b)
{
  return b->head;
}

Int *Plus(Int *a, Int *b)
{
  Int *ret = Int_init();
  Int_set_list(ret, plus_list(Int_get_list(a), Int_get_list(b)));
  return ret;
}

Int *Minus(Int *a, Int *b)
{
  Int *ret = Int_init();
  Int_set_list(ret, minus_list(Int_get_list(a), Int_get_list(b)));
  return ret;
}

Int *Product(Int *a, Int *b)
{
  Int *ret = Int_init();
  Int_set_list(ret, product(Int_get_list(a), Int_get_list(b)));
  return ret;
}

Int *Product_with_num(Int *a, int num)
{
  Int *ret = Int_init();
  Int_set_list(ret, product_with_single_num(Int_get_list(a), num));

  return ret;
}

Int *Div(Int *a, Int *b)
{
  Int *ret = Int_init();
  Int_set_list(ret, divide(Int_get_list(a), Int_get_list(b)));
  return ret;
}

int Size(Int *a)
{
  return size(Int_get_list(a));
}

// 只适用于比较小的整数
Int *Convert(long long num)
{
  Int *ret = Int_init();
  Int_set_list(ret, convert_int_to_list(num));

  return ret;
}

Int *Mod(Int *a, Int *b)
{
  Int *ret = Int_init();
  Int_set_list(ret, mod(Int_get_list(a), Int_get_list(b)));
  return ret;
}

Int *Copy(Int *b)
{
  Int *ret = Int_init();
  Int_set_list(ret, copy(Int_get_list(b)));
  return ret;
}

void Free(Int *a)
{
  list_free(Int_get_list(a));
}

void SetError(Int *a)
{
  a->isError = 1;
}
void Print(Int *a)
{
  print(Int_get_list(a));
}
int IsError(Int *a)
{
  return a->isError;
}

Int *Power(Int *a, int times)
{
  Int *ret = Convert(1);
  for (int i = 0; i < times; i++)
  {
    Int *temp = Copy(ret);
    Free(ret);
    ret = Product(temp, a);
    Free(temp);
  }
  return ret;
}

int Compare(Int *a, Int *b)
{

  return compare(Int_get_list(a), Int_get_list(b));
}

int IsOdd(Int *a)
{
  Int *two = Convert(2);
  Int *mod = Mod(a, two);
  Int *zero = Int_init();
  if (Compare(mod, zero) == 0)
  {
    Free(two);
    Free(mod);
    Free(zero);
    return 0;
  }

  Free(two);
  Free(mod);
  Free(zero);
  return 1;
}

Int *FastPower(Int *a, Int *times)
{
  Int *zero = Int_init();
  Int *one = Convert(1);

  if (Compare(times, zero) == 0)
  {
    return Convert(1);
  }

  printf("num: ");
  Print(a);

  printf("times: ");
  Print(times);

  printf("\n");

  //    if (Compare(times, one) == 0) {
  //        return Copy(a);
  //    }

  Int *ret = NULL;

  if (IsOdd(times))
  {
    Int *new_t = Minus(times, one);
    Int *t1 = FastPower(a, new_t);
    ret = Product(a, t1);
    Free(t1);
    Free(new_t);
  }
  else
  {
    Int *div_num = Div(times, Convert(2));
    Int *t1 = FastPower(a, div_num);
    ret = Product(t1, t1);
    Free(t1);
    Free(div_num);
  }

  Free(zero);
  Free(one);
  return ret;
}

// 将 Int 转换为 long long
long long GetInt(Int *a)
{

  Node *p = Int_get_list(a);
  long long ret = 0;
  int len = size(p);
  p = p->next;
  for (int i = len - 1; i >= 0; i--)
  {
    ret += pow(10, i) * p->val;
    p = p->next;
  }
  return ret;
}

// 求这个整数在字节串下的长度
int Octet_Size(Int *x)
{
  Int *zero = Convert(0);
  Int *base256 = Convert(256);
  int ret = 0;
  Int *a = Copy(x);

  if (Compare(a, zero) == 0)
  {
    free(a);
    return 1;
  }

  while (Compare(a, zero) != 0)
  {
    ret++;
    Int *t = a;
    a = Div(a, base256);
    Free(t);
  }
  return ret;
}
