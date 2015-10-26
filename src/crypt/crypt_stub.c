#include "crypt_stub.h"
#include <stdlib.h>
#include <string.h>
#include "../core/packet.h"
#include "crypt_intf.h"

struct stubContext{
    uint8_t key[16];
    uint8_t iv[16];
};

static int init(void* key, size_t keySize, struct RP_CryptConfigBlock* block){
    block->cryptoSuite = &cryptStubSuite;
    struct stubContext* context = (struct stubContext*) malloc(sizeof(struct stubContext));
    if (context == NULL)
        return -1;
    memcpy(context->key, key, keySize);
    for (int i = keySize; i < 16; i++)
        context->key[i] = i;
    block->context = context;

    return 0;
}

static int updateIV(void* iv, size_t size, struct RP_CryptConfigBlock* block){
    if (size > 16)
        size = 16;
    struct stubContext* context = (struct stubContext*) block->context;
    memcpy(context->iv, iv, size);
    for (int i = size; i < 16; i++)
        context->iv[i] = i;
    return 0;
}

static int enc(const void* src, size_t srcLen, void** dst, size_t* dstLen, struct RP_CryptConfigBlock* block){
    uint8_t *dstTmp = (uint8_t*) malloc(srcLen);
    if (dstTmp == NULL)
        return -1;
    
    *dstLen = srcLen;
    uint8_t *srcTmp = (uint8_t*) src;
    struct stubContext* context = (struct stubContext*) block->context;
    for (int i = 0; i < srcLen; i++)
        dstTmp[i] = (srcTmp[i] ^ context->key[i%16] ^ context->iv[i%16]);
        
    *dst = dstTmp;
    return 0;
}

static int mrand(void* dst, size_t length, struct RP_CryptConfigBlock* block){
    uint8_t* dstTmp = (uint8_t*) dst;
    for (int i = 0; i < length; i++)
        dstTmp[i] = (rand() & 0xff);
    return 0;
}

static size_t estLen(size_t origin){
    return origin;
}


struct CryptoSuite cryptStubSuite = {
        init,
        enc,
        enc,
        updateIV,
        mrand,
        estLen,
        sizeof(RP_PacketHeader) + sizeof(struct RP_ShadowHeader)
};
