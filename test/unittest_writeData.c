
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
    freopen("tmp1", "wb", stdout);
    struct RP_CryptConfigBlock block;
    cryptStubSuite.init((void*)"123", 3, &block);
    writeData(STDOUT_FILENO, (void*) "abc", 3, &block);

    return 0;
}
