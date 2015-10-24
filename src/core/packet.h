#ifndef __PACKET_H_
#define __PACKET_H_

#include <stdint.h>
#include <stddef.h>
#include <sys/_pthread/_pthread_mutex_t.h>
#include "../crypt/crypt_intf.h"

typedef uint8_t RP_PacketHeader[4];

struct RP_ShadowHeader{
    uint16_t payloadLength;
    uint16_t rawLength;
    uint32_t checksum;
};

int calcHeader(const void* src, size_t size, struct RP_CryptConfigBlock* crypt_config, void* dst, size_t* padding);

enum StreamState{
    SS_WAITING_HEADER,
    SS_WAITING_PAYLOAD
};

struct streamFragment{
    struct streamFragment* prev, *next;
    void* data;
    size_t size;
};

struct RP_StreamStateMachine{
    pthread_mutex_t mutex;
    struct RP_CryptConfigBlock* currentCryptConfig;
    enum StreamState state;
    struct streamFragment fragList;
    struct RP_ShadowHeader currentHeader;
    size_t currentLength;
    size_t expectLength;
    void* context;
};

typedef int (*RawDataHandler)(void* data, size_t size, void* context);
void initStreamStateMachine(struct RP_StreamStateMachine* streamState, struct RP_CryptConfigBlock* crypt_config, void* context);
int pushNewData(struct RP_StreamStateMachine* streamState, void* data, size_t size, RawDataHandler);

#endif
