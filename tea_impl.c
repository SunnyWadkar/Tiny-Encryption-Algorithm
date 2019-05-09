#include "stdio.h"

typedef long uint32_t;

void encrypt (uint32_t v[2], uint32_t k[4]);
void decrypt (uint32_t v[2], uint32_t k[4]);

const uint32_t delta = 0x9E3779B9;

int main()
{
  uint32_t num[2]={10,20};
  uint32_t key[4]={30,40,50,60};
  encrypt(num,key);
  printf("%ld,%ld \n",num[0],num[1]);
  decrypt(num,key);
  printf("%ld,%ld \n",num[0],num[1]);
  return 0;
}

void encrypt (uint32_t v[2], uint32_t k[4]) {
    uint32_t v0=v[0], v1=v[1], sum=0, i;
    uint32_t k0=k[0], k1=k[1], k2=k[2], k3=k[3];   /* cache key */
    for (i=0; i<32; i++) {
        sum += delta;
        v0 += ((v1<<4) + k0) ^ (v1 + sum) ^ ((v1>>5) + k1);
        v1 += ((v0<<4) + k2) ^ (v0 + sum) ^ ((v0>>5) + k3);
    }
    v[0]=v0; v[1]=v1;
}

void decrypt (uint32_t v[2], uint32_t k[4]) {
    uint32_t v0=v[0], v1=v[1], sum, i;
    uint32_t k0=k[0], k1=k[1], k2=k[2], k3=k[3];
    sum = delta<<5;
    for (i=0; i<32; i++) {
        v1 -= ((v0<<4) + k2) ^ (v0 + sum) ^ ((v0>>5) + k3);
        v0 -= ((v1<<4) + k0) ^ (v1 + sum) ^ ((v1>>5) + k1);
        sum -= delta;
    }
    v[0]=v0; v[1]=v1;
}
