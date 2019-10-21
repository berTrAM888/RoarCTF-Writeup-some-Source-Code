// ./clang -mllvm -fla -mllvm -split -mllvm -bcf polyre.c -o polyre
// strip polyre
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

const uint8_t cmp[48] = {0x96, 0x62, 0x53, 0x43, 0x6d, 0xf2, 0x8f, 0xbc, 0x16, 0xee, 0x30, 0x05, 0x78, 0x00, 0x01, 0x52, 0xec, 0x08, 0x5f, 0x93, 0xea, 0xb5, 0xc0, 0x4d, 0x50, 0xf4, 0x53, 0xd8, 0xaf, 0x90, 0x2b, 0x34, 0x81, 0x36, 0x2c, 0xaa, 0xbc, 0x0e, 0x25, 0x8b, 0xe4, 0x8a, 0xc6, 0xa2, 0x81, 0x9f, 0x75, 0x55};

const uint64_t mask64 = 0xb0004b7679fa26b3;


int main(){
    uint8_t s[48] = {0};
    uint8_t res[48] = {0};
    printf("Input:");
    scanf("%s", s);
    int i, j;
    for(i = 0;i<64;i++){
        if(s[i] == 10){
            s[i] = 0;
            break;
        }
    }
    uint64_t tmp64;
    for(j = 0;j<6;j++){
        tmp64 = *(((uint64_t*)s) + j);
        for(i = 0;i<64;i++){
            if((int64_t)tmp64 < 0){
                tmp64 <<= 1u;
                tmp64 ^= mask64;
            }
            else{
                tmp64 <<= 1u;
            }
        }
        memcpy(&res[8*j], &tmp64, 8);
    }


//    for(i = 0; i < 48;i++){
//        printf("0x%02x, ", res[i]);
//    }
//    printf("\n");
    if(!memcmp(res, cmp, 48)){
        puts("Correct!");
    }
    else{
        puts("Wrong!");
    }
}



