#include "stdio.h"
#include "portable_types.h"
#include "tea_impl.h"

int main(void)
{
  unsigned32_t num[2]={10,20}; // 8 byte input
  tea_encrypt(num);
  printf("After Encryption: %ld,%ld \n",num[0],num[1]);
  tea_decrypt(num);
  printf("After Decryption: %ld,%ld \n",num[0],num[1]);
  return 0;
}
