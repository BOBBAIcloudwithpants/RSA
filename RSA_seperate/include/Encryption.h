#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include "Int.h"
#include "OctetString.h"

Int *RSAEP(Int *n, Int *e, Int *M);

OctetString *EME_Encoding(OctetString *M, int k);

OctetString *I2OSP(Int *x, int x_len);

Int *OS2IP(OctetString *array);

// (e, n) 为 接收者的 public key
OctetString *Encryption(Int *n, Int *e, OctetString *M);

#endif