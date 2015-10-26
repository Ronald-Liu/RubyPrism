//
// Created by Ronald Liu on 18/9/15.
//

#include <crypt/crypt_stub.h>
#include <crypt/crypt_intf.h>
#include "crypt/crypt_stub.h"
#include <unistd.h>
#include <network/rp_send.h>
#include <core/packet.h>
#include <assert.h>
#include <stdio.h>

int myHandler(void* data, size_t size, void* context){
    char* tmp = (char*) data;
    assert(tmp[0] == 'a');
    assert(tmp[1] == 'b');
    assert(tmp[2] == 'c');
    return 0;
}

int main(){
    freopen("tmp1", "rb", stdin);
    struct RP_StreamStateMachine state;
    struct RP_CryptConfigBlock block;
    cryptStubSuite.init((void*)"123", 3, &block); 
    initStreamStateMachine(&state, &block, NULL);
    uint8_t tmpData[256];
    ssize_t len = read(0, tmpData, 256);
    assert(pushNewData(&state, tmpData, len, myHandler) == 0);

    return 0;
}
