#include "rp_send.h"
#include <stdlib.h>

int writeFD(int fd, void* header, size_t headerSize, void* data, size_t dataSize){
    write(fd, header, headerSize);
    write(fd, data, dataSize);
    return 0;
}

int writeData(int fd, const void* src, size_t size, struct RP_CryptConfigBlock* context){
    uint8_t *header = (uint8_t*) malloc(context->cryptoSuite->typicalHeaderLen);
    if (header == NULL)
        goto returnErr;
    size_t paddingLength;
    calcHeader(src, size, context, header, &paddingLength);
    void* payloadData;
    size_t outputSize;
    if (context->cryptoSuite->enc(src, size, &payloadData, &outputSize, context)!=0)
        goto errFreeHeader;
    if (writeFD(fd, header, context->cryptoSuite->typicalHeaderLen, payloadData, outputSize)!=0)
        goto errFreePayload;
    return 0;
 errFreePayload:
    free(payloadData);
 errFreeHeader:
    free(header);
 returnErr:
    return -1;
}
