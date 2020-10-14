#include "RSA.h"

Int *RSAEP(Int *n, Int *e, Int *M)
{
  printf("RSAEP: \nM: ");
  Print(M);
  printf("n: ");
  Print(n);
  printf("e: ");
  Print(e);

  Int *ret = Int_init();
  if (Compare(M, n) >= 0)
  {
    SetError(ret);
    return ret;
  }
  Int *Me = FastPower(M, e);
  printf("\nMe: ");
  Print(Me);

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

OctetString *EME_decoding(OctetString *EM)
{
  OctetString *ret = Octet_init(1);
  int ps_pos = EM->pos - 1;
  int ps_len = ps_pos - 2;
  while (ps_pos > 1 && EM->arr[ps_pos] != 0)
  {
    ps_pos--;
  }
  if (EM->arr[0] != 0 || EM->arr[1] != 2 || ps_pos <= 1 || ps_len < 8)
  {
    Octet_assignDescription(ret, "decryption error");
    return ret;
  }

  int m_len = EM->len - ps_len - 2;
  OctetString *M = Octet_init(m_len);
  for (int i = 0; i < m_len; i++)
  {
    Octet_appendVal(M, EM->arr[ps_pos + i + 1]);
  }

  return M;
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
    Int *ii = Convert(i);
    Int *power_256 = FastPower(base256, ii);
    int bit = arr[array->pos - 1 - i];
    Int *c = Product_with_num(power_256, bit);
    num = Plus(num, c);

    Print(num);
    Free(ii);
    Free(t);
    Free(power_256);
    Free(c);
  }

  return num;
}

// (e, n) 为 接收者的 public key
OctetString *Encryption(Int *n, Int *e, OctetString *M)
{
  int k = Octet_Size(n);
  printf("k: %d\n", k);

  printf("n: ");
  Print(n);

  printf("e: ");
  Print(e);

  printf("M: ");
  Octet_print(M);
  OctetString *C = Octet_init(k);

  OctetString *EM = EME_Encoding(M, k);

  OctetString *REM = EME_decoding(EM);

  printf("EM: ");
  Octet_print(EM);

  printf("REM: ");
  Octet_print(REM);

  if (EM->isError)
  {
    Octet_assignDescription(C, EM->description);
    return C;
  }

  Int *m = OS2IP(EM);
  printf("m: ");
  Print(m);

  Int *c = RSAEP(n, e, m);
  if (c->isError)
  {
    Octet_assignDescription(C, "message representative out of range");
    return C;
  }

  printf("c: ");
  Print(c);

  C = I2OSP(c, k);

  printf("C");
  Octet_print(C);

  printf("recovery: ");
  Print(OS2IP(C));
  return C;
}

Int *RSADP(Int *n, Int *d, Int *c)
{

  Int *ret = Int_init();

  // c >= n-1, 返回ciphertext representative out of range
  if (Compare(n - 1, c) <= 0)
  {
    ret->isError = 1;
    return ret;
  }

  Int *cd = FastPower(c, d);
  ret = Mod(cd, n);
  Free(cd);

  return ret;
}

// (n, d) 为接收者的私钥，C为密文
OctetString *Decryption(Int *n, Int *d, OctetString *C)
{
  OctetString *s = Octet_init(2);

  int k = Octet_Size(n);
  int lenC = C->len;

  if (k != lenC)
  {
    Octet_assignDescription(s, "decryption error");
    return s;
  }

  Int *c = OS2IP(C);

  Int *m = RSADP(n, d, c);

  if (m->isError)
  {
    Octet_assignDescription(s, "ciphertext representative out of range");
    return s;
  }

  OctetString *EM = I2OSP(m, k);
  OctetString *M = EME_decoding(EM);

  return M;
}
