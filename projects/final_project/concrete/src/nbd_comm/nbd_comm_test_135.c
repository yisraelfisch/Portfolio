/*********************************
 * Reviewer: 
 * Author: yisrael.fisch
 * File: nbd_comm_test.c
 * ******************************/

#include <stdlib.h> /* malloc */
#include <string.h> /* memcpy */

#include "nbd_comm.h"


int main()
{
    static const int StorageSize = 0x100000;
    char* storage = malloc(StorageSize);
    int nbdSock = NbdDevOpen("/dev/nbd0", StorageSize);

    while (1)
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
    }
}
