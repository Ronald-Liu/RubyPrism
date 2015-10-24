#ifndef __SEND_H_
#define __SEND_H_
#include <unistd.h>
#include "../core/packet.h"

int writeData(int fd, const void* src, size_t size, struct RP_CryptConfigBlock*);

#endif
