#ifndef __CRYPT_INTF_H_
#define __CRYPT_INTF_H_
#include <unistd.h>
struct RP_CryptConfigBlock;

typedef int (*InitConfigBlockFunc)(void* key, size_t keySize, struct RP_CryptConfigBlock* context);
typedef int (*UpdateIVFunc)(void* iv, size_t size, struct RP_CryptConfigBlock* context);
typedef int (*EncryptFunc)(const void* src, size_t srcLen, void** dst, size_t* dstLen, struct RP_CryptConfigBlock* context);
typedef int (*DecryptFunc)(const void* src, size_t srcLen, void** dst, size_t* dstLen, struct RP_CryptConfigBlock* context);
typedef int (*RandomFunc)(void* dst, size_t length, struct RP_CryptConfigBlock* context);
typedef size_t (*EstCipherLen)(size_t origin);

struct CryptoSuite{
    InitConfigBlockFunc init;
    EncryptFunc enc;
    DecryptFunc dec;
    UpdateIVFunc updateIV;
    RandomFunc rand;
    EstCipherLen estLen;
    size_t typicalHeaderLen;
};

struct RP_CryptConfigBlock{
    void* context;
    struct CryptoSuite* cryptoSuite;
};

#endif
