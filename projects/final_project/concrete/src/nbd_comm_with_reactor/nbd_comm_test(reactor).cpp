/*********************************
 * Reviewer: 
 * Author: yisrael.fisch
 * File: nbd_comm_test.cpp
 * ******************************/

#include <stdlib.h> /* malloc */
#include <string.h> /* memcpy */
#include "function.hpp"
#include "reactor.hpp"
#include "select.hpp"
#include "nbd_comm.h"

int Handler(int nbdSock);

char* storage;

int main()
{
    static const int StorageSize = 0x100000;
    storage = new char[StorageSize];
    int nbdSock = NbdDevOpen("/dev/nbd0", StorageSize);

    ilrd::Reactor<ilrd::Select> reactor;

    reactor.RegisterReadHandler(nbdSock, ilrd::Function<int(void)>(Handler, nbdSock));
    reactor.Run();
}

int Handler(int nbdSock)
{
    NbdRequest* req = NbdRequestRead(nbdSock);
    switch (req->reqType)
    {
    case NBD_CMD_READ:
        memcpy(req->dataBuf, storage + req->offset, req->dataLen);
        break;

    case NBD_CMD_WRITE:
        memcpy(storage + req->offset, req->dataBuf, req->dataLen);
        break;

    default:
        break;
    }
    NbdRequestDone(req, 0);

    return 0;
}

/*before exec:
a. sudo modprobe nbd
run exec with sudo.

from another terminal:
b. sudo mkfs.ext4 /dev/nbd0
c. sudo mount /dev/nbd0 /mnt
d. sodu copy something to /mnt
e.sudo umount /dev/nbd0 /mnt
f.sudo mount /dev/nbd0 /mnt
see if it was copied

to close:
g.sudo umount /dev/nbd0 /mnt
h.sudo nbd-client -d /dev/nbd0*/