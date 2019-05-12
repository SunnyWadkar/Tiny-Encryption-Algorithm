#include "tea_impl.h"

void teaEncrypt (unsigned32_t plaintext[2])
{
    unsigned32_t plaintextPart1 = plaintext[0], plaintextPart2 = plaintext[1];
    unsigned32_t key_schd_sum = 0;
    for (signed8_t i=0; i < NUMBER_OF_CIPHER_ROUNDS; i++)
    {
        key_schd_sum += KEY_SCHEDULING_CONST;
        plaintextPart1 += ((plaintextPart2<<4) + tea_encryption_key[0]) ^ (plaintextPart2 + key_schd_sum) ^ ((plaintextPart2>>5) + tea_encryption_key[1]);
        plaintextPart2 += ((plaintextPart1<<4) + tea_encryption_key[2]) ^ (plaintextPart1 + key_schd_sum) ^ ((plaintextPart1>>5) + tea_encryption_key[3]);
    }
    plaintext[0] = plaintextPart1;
    plaintext[1] = plaintextPart2;
}

void teaDecrypt (unsigned32_t crypttext[2])
{
    unsigned32_t crypttextPart1 = crypttext[0], crypttextPart2 = crypttext[1];
    unsigned32_t key_schd_sum = KEY_SCHED_SUM_CONST;
    for (signed8_t i=0; i < NUMBER_OF_CIPHER_ROUNDS; i++)
    {
        crypttextPart2 -= ((crypttextPart1<<4) + tea_encryption_key[2]) ^ (crypttextPart1 + key_schd_sum) ^ ((crypttextPart1>>5) + tea_encryption_key[3]);
        crypttextPart1 -= ((crypttextPart2<<4) + tea_encryption_key[0]) ^ (crypttextPart2 + key_schd_sum) ^ ((crypttextPart2>>5) + tea_encryption_key[1]);
        key_schd_sum -= KEY_SCHEDULING_CONST;
    }
    crypttext[0] = crypttextPart1;
    crypttext[1] = crypttextPart2;
}

enc_return_type_t teaOperateBlock(unsigned32_t* bufferPointer, unsigned16_t blockLength, crypto_operation_t opType)
{
    enc_return_type_t rtn_status;
    unsigned16_t numberOfBlocks;
    unsigned32_t localBuffer[2];
    unsigned32_t* localBufferPointer = bufferPointer;
    if((blockLength % 8) != 0)
    {
        rtn_status = OPERATION_ERROR;
    }
    else
    {
        numberOfBlocks = blockLength/8;
        for(unsigned16_t i = 0; i < numberOfBlocks; i++)
        {
            localBuffer[0] = *(localBufferPointer);
            localBuffer[1] = *(localBufferPointer + 1);
            if(opType == ENCRYPTION)
            {
                teaEncrypt(localBuffer);
            }
            else
            {
                teaDecrypt(localBuffer);
            }
            *(localBufferPointer) = localBuffer[0];
            *(localBufferPointer + 1) = localBuffer[1];
            localBufferPointer = localBufferPointer + 2;
        }
        rtn_status = OPERATION_SUCCESS;
    }
    return rtn_status;
}
