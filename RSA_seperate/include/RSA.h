#ifndef RSA_H
#define RSA_H

#include "Int.h"
#include "OctetString.h"

Int *RSAEP(Int *n, Int *e, Int *M);

OctetString *EME_Encoding(OctetString *M, int k);

OctetString *I2OSP(Int *x, int x_len);

Int *OS2IP(OctetString *array);

Int *RSADP(Int *n, Int *d, Int *c);

OctetString *EME_decoding(OctetString *EM);

// (e, n) 为 接收者的 public key
OctetString *Encryption(Int *n, Int *e, OctetString *M);

// (n, d) 为接收者的私钥，C为密文
OctetString *Decryption(Int *n, Int *d, OctetString *C);

Int *RSADP(Int *n, Int *d, Int *c);

#endif