#include "Encryption.h"

Int *RSAEP(Int *n, Int *e, Int *M)
{
  Int *ret = Int_init();
  if (Compare(M, n) >= 0)
  {
    SetError(ret);
    return ret;
  }
  Int *Me = FastPower(M, e);
  ret = Mod(Me, n);
  Free(Me);
  return ret;
}

OctetString *EME_Encoding(OctetString *M, int k)
{

  OctetString *EM = Octet_init(k);

  if (M->len > k - 11)
  {
    Octet_assignDescription(EM, "message too long");
    return EM;
  }
  OctetString *ps = Octet_generatePS(k - M->len - 3);

  // 0x00
  Octet_appendVal(EM, 0);
  // 0x02
  Octet_appendVal(EM, 2);
  // PS
  for (int i = 0; i < ps->len; i++)
  {
    Octet_appendVal(EM, ps->arr[i]);
  }
  // 0x00
  Octet_appendVal(EM, 0);
  // M
  for (int i = 0; i < M->len; i++)
  {
    Octet_appendVal(EM, M->arr[i]);
  }
  return EM;
}

OctetString *I2OSP(Int *x, int x_len)
{

  OctetString *array = Octet_init(x_len);

  Int *base256 = Convert(256);
  Int *zero = Convert(0);
  if (Compare(x, FastPower(base256, Convert(x_len))) >= 0)
  {
    Octet_assignDescription(array, "integer too large\n");
    return array;
  }

  while (Compare(x, zero) != 0)
  {
    Int *mod = Mod(x, base256);
    Int *t = x;
    x = Div(x, base256);
    Octet_appendVal(array, GetInt(mod));
    Free(mod);
    Free(t);
  }

  int pad_num = x_len - Octet_size(array);
  for (int i = 0; i < pad_num; i++)
  {
    Octet_appendVal(array, 0);
  }
  Octet_reverse(array);

  return array;
}

Int *OS2IP(OctetString *array)
{

  Int *num = Int_init();
  Int *base256 = Convert(256);

  int *arr = array->arr;
  for (int i = array->pos - 1; i >= 0; i--)
  {

    Int *t = num;
    Int *power_256 = FastPower(base256, Convert(i));
    Int *c = Product_with_num(power_256, arr[array->pos - 1 - i]);
    num = Plus(num, c);

    Free(t);
    Free(power_256);
    Free(c);
  }
  return num;
}

// (e, n) 为 接收者的 public key
OctetString *Encryption(Int *n, Int *e, OctetString *M)
{
  int k = Size(n);
  OctetString *C = Octet_init(k);

  OctetString *EM = EME_Encoding(M, k);

  if (EM->isError)
  {
    Octet_assignDescription(C, EM->description);
    return C;
  }

  Int *m = OS2IP(EM);

  Int *c = RSAEP(n, e, m);
  if (c->isError)
  {
    Octet_assignDescription(C, "message representative out of range");
    return C;
  }

  C = I2OSP(c, k);
  return C;
}