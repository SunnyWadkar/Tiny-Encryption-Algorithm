#include "tea_impl.h"

void tea_encrypt (unsigned32_t plaintext[2])
{
    unsigned32_t plaintext_part1 = plaintext[0], plaintext_part2 = plaintext[1], key_schd_sum = 0;
    for (signed8_t i=0; i < NUMBER_OF_CIPHER_ROUNDS; i++)
    {
        key_schd_sum += KEY_SCHEDULING_CONST;
        plaintext_part1 += ((plaintext_part2<<4) + tea_encryption_key[0]) ^ (plaintext_part2 + key_schd_sum) ^ ((plaintext_part2>>5) + tea_encryption_key[1]);
        plaintext_part2 += ((plaintext_part1<<4) + tea_encryption_key[2]) ^ (plaintext_part1 + key_schd_sum) ^ ((plaintext_part1>>5) + tea_encryption_key[3]);
    }
    plaintext[0] = plaintext_part1;
    plaintext[1] = plaintext_part2;
}

void tea_decrypt (unsigned32_t crypttext[2])
{
    unsigned32_t crypttext_part1 = crypttext[0], crypttext_part2 = crypttext[1];
    unsigned32_t key_schd_sum = KEY_SCHED_SUM_CONST;
    for (signed8_t i=0; i < NUMBER_OF_CIPHER_ROUNDS; i++)
    {
        crypttext_part2 -= ((crypttext_part1<<4) + tea_encryption_key[2]) ^ (crypttext_part1 + key_schd_sum) ^ ((crypttext_part1>>5) + tea_encryption_key[3]);
        crypttext_part1 -= ((crypttext_part2<<4) + tea_encryption_key[0]) ^ (crypttext_part2 + key_schd_sum) ^ ((crypttext_part2>>5) + tea_encryption_key[1]);
        key_schd_sum -= KEY_SCHEDULING_CONST;
    }
    crypttext[0] = crypttext_part1;
    crypttext[1] = crypttext_part2;
}

int main(void)
{
  unsigned32_t num[2]={10,20}; // 8 byte input
  tea_encrypt(num);
  printf("After Encryption: %ld,%ld \n",num[0],num[1]);
  tea_decrypt(num);
  printf("After Decryption: %ld,%ld \n",num[0],num[1]);
  return 0;
}
