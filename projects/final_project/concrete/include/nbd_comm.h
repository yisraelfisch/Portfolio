/*********************************
 * Reviewer: 
 * Author: yisrael.fisch
 * File: nbd_comm.h
 * ******************************/

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <linux/nbd.h>  /* nbd */
/* enum TYPE{NBD_CMD_READ, NBD_CMD_WRITE} */

typedef struct
{
    uint32_t reqType;
    uint32_t dataLen;
    uint64_t offset;
    char *dataBuf;
}NbdRequest;

typedef struct nbd_reply nbd_reply_t;
typedef struct nbd_request nbd_request_t;

int NbdDevOpen(const char* dev_name, uint64_t size);

NbdRequest *NbdRequestRead(int sock);

void NbdRequestDone(NbdRequest* req, int error);

#ifdef __cplusplus
}
#endif
