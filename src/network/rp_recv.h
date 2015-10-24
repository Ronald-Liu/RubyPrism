//
// Created by Ronald Liu on 18/9/15.
//

#ifndef RUBYPRISM_RP_RECV_C_H
#define RUBYPRISM_RP_RECV_C_H

#include <stddef.h>
#include "../core/packet.h"
void registerRecvHandler(int fd, RawDataHandler , void* context);

#endif //RUBYPRISM_RP_RECV_C_H
