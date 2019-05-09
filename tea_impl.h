#ifndef TEA_IMPL_H
#define TEA_IMPL_H

#include "stdio.h"
#include "portable_types.h"

#define KEY_SCHEDULING_CONST 0x9E3779B9  //key scheduling constant calculated as (2^32)/golden ratio 1.6180339887
#define NUMBER_OF_CIPHER_ROUNDS 32
#define KEY_SCHED_SUM_CONST 0x13C6EF3720 //0x9E3779B9 << 5 for 32 rounds

extern unsigned32_t tea_encryption_key[4];

void tea_encrypt (unsigned32_t [2]);
void tea_decrypt (unsigned32_t [2]);

#endif
