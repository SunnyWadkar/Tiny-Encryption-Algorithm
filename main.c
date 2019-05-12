#include "stdio.h"
#include "portable_types.h"
#include "tea_impl.h"

int main(int argc, char *argv[])
{
  unsigned32_t num[4]={10,20,30,40};
  enc_return_type_t encOperationStat;
  printf("Before Encryption: %ld,%ld,%ld,%ld \n",num[0],num[1],num[2],num[3]);
  encOperationStat = teaOperateBlock(num,16,ENCRYPTION);
  if(encOperationStat == OPERATION_SUCCESS)
  {
      printf("After Encryption: %ld,%ld,%ld,%ld \n",num[0],num[1],num[2],num[3]); //Second argument is number of bytes
      teaOperateBlock(num,16,DECRYPTION);
      printf("After Decryption: %ld,%ld,%ld,%ld \n",num[0],num[1],num[2],num[3]);
  }
  else
  {
      printf("Encryption Failure!! \n");
  }
  return 0;
}
