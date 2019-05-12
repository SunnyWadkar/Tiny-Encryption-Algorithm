#include "stdio.h"
#include "portable_types.h"
#include "tea_impl.h"

int main(int argc, char *argv[])
{
  unsigned32_t num[4]={10,20,30,40};
  printf("Before Encryption: %ld,%ld,%ld,%ld \n",num[0],num[1],num[2],num[3]);
  teaOperateBlock(num,16,ENCRYPTION);
  printf("After Encryption: %ld,%ld,%ld,%ld \n",num[0],num[1],num[2],num[3]);
  teaOperateBlock(num,16,DECRYPTION);
  printf("After Decryption: %ld,%ld,%ld,%ld \n",num[0],num[1],num[2],num[3]);
  return 0;
}
