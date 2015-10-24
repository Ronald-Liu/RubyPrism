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
    assert(tmp[0] == '1');
    assert(tmp[1] == '2');
    assert(0);
    return 0;
}

int main(){
    freopen("tmp1", "w", stdout);
    freopen("tmp2", "r", stdin);
    struct RP_CryptConfigBlock block;
    cryptStubSuite.init((void*)"123", 3, &block);
    writeData(STDOUT_FILENO, (void*) "abc", 3, &block);
    struct RP_StreamStateMachine state;
    initStreamStateMachine(&state, &block, NULL);
    uint8_t tmpData[256];
    ssize_t len = read(0, tmpData, 256);
    assert(pushNewData(&state, tmpData, len, myHandler) == 0);

    return 0;
}