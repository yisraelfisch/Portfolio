/*********************************
 * Reviewer: 
 * Author: yisrael.fisch
 * File: nbd_comm.c
 * ******************************/

#define _POSIX_C_SOURCE (200809L)

#include <assert.h>
#include <errno.h>
#include <fcntl.h> /* open */
#include <netinet/in.h> /* htonl, ntohl */
#include <stdio.h>  /* printf, perror */
#include <stdlib.h> /* malloc,free */
#include <string.h> /* memcpy */
#include <sys/ioctl.h>  /* ioctl */
#include <sys/socket.h> /* socketpair */
#include <sys/stat.h>
#include <unistd.h> /* fork, close, exit, read, write */
#include <stddef.h> /* offsetof */

#include "nbd_comm.h"

#define BLKSIZE 1024

typedef struct nbd_message
{
    NbdRequest  nbd_req;
    int         nbd_sock;
    nbd_reply_t reply;
    char        buffer[1];
} nbd_message_t;

/* -------------------static-functions-dclr----------------- */

static u_int64_t ntohll(u_int64_t a);
static int read_all(int fd, char *buf, size_t count);/*read from socket to buf*/
static int write_all(int fd, char *buf, size_t count);/*write from buffer to socket*/
static void CleanUp(int fd1, int fd2, int fd3);

/* -----------------------function-impl--------------------- */

int NbdDevOpen(const char* dev_name, uint64_t size)
{
    int socks[2] = {-1};
    int nbd = -1;
    pid_t pid = 0;

    do
    {
    
        if(-1 == (nbd = open(dev_name, O_RDWR)))
        {
            printf("failed to open '%s': \n ", dev_name);
            perror("open failed");
            break;
        }

        if((socketpair(AF_UNIX, SOCK_STREAM, 0, socks)))
        {
            perror("socketpair failed");
            break;
        }


        if(-1 == (ioctl(nbd, NBD_SET_BLKSIZE, BLKSIZE)))
        {
            perror("ioctl failed 1");
            break;
        }

        if(-1 == (ioctl(nbd, NBD_SET_SIZE, size)))
        {
            perror("ioctl failed 2");
            break;
        }


        if(-1 == (ioctl(nbd, NBD_SET_SIZE_BLOCKS, size/BLKSIZE)))
        {
            perror("ioctl failed 3");
            break;
        }

        if(-1 == (ioctl(nbd, NBD_CLEAR_QUE)))
        {
            perror("ioctl failed 4");
            break;
        }

        if(-1 == (ioctl(nbd, NBD_CLEAR_SOCK)))
        {
            perror("ioctl failed 5");
            break;
        }

        if(-1 == (ioctl(nbd, NBD_SET_SOCK, socks[1])))
        {
            perror("ioctl failed 6");
            break;
        }

        if(-1 == (ioctl(nbd, NBD_SET_TIMEOUT, 30)))
        {
            perror("ioctl failed 7");
            break;
        }

        if(-1 == (pid = fork()))
        {
            perror("fork failed");
            break;
        }

        if(!pid)
        {
            if(-1 == (close(socks[0])))
            {
                perror("close failed");
                break;
            }

            if(-1 == (ioctl(nbd, NBD_DO_IT)))
            {
                perror("ioctl failed 8");
                break;
            }

        }
        else
        {
            if(-1 == (close(socks[1])))
            {
                perror("close failed");
                break;
            }

            return socks[0];
        }
    } while (0);

    CleanUp(socks[0], socks[1], nbd);

    exit(EXIT_FAILURE);
}

NbdRequest *NbdRequestRead(int sock)
{
    struct nbd_request request = {0};
    nbd_message_t *new_message = NULL;
    read_all(sock, (char *)&request, sizeof(request));

    if(!(new_message = (nbd_message_t *)malloc(offsetof(nbd_message_t, buffer) + ntohl(request.len))))
    {
        perror("malloc");
        return NULL;
    }

    if(request.magic != htonl(NBD_REQUEST_MAGIC))
    {
        perror("request magic is not an NBD_REQUEST");
        return NULL;
    }

    new_message->nbd_req.reqType = ntohl(request.type);
    new_message->nbd_req.dataLen = ntohl(request.len);
    new_message->nbd_req.offset = ntohll(request.from);
    new_message->nbd_req.dataBuf = new_message->buffer;

    new_message->reply.magic = htonl(NBD_REPLY_MAGIC);
    new_message->reply.error = htonl(0);
    memcpy(new_message->reply.handle, request.handle, sizeof(new_message->reply.handle));

    new_message->nbd_sock = sock;

    if(new_message->nbd_req.reqType == NBD_CMD_WRITE)
    {
        read_all(sock, (char*)new_message->nbd_req.dataBuf, new_message->nbd_req.dataLen);
    }

    return (NbdRequest *)new_message;

}

void NbdRequestDone(NbdRequest* req, int error)
{
    nbd_message_t *message = (nbd_message_t *)req;
    int socket = message->nbd_sock;
    size_t len = sizeof(struct nbd_reply);
    assert(req);

    message->reply.error = htonl(error);
    

    if(req->reqType == NBD_CMD_READ)
    {
        len += req->dataLen;
    }

    write_all(socket, (char *)&(message->reply), len);

    free(message);

}

/* ----------------static-function-impl--------------------- */

#ifdef WORDS_BIGENDIAN
static u_int64_t ntohll(u_int64_t a)
{
    return a;
}
#else
static u_int64_t ntohll(u_int64_t a)
{
    u_int32_t lo = a & 0xffffffff;
    u_int32_t hi = a >> 32U;
    lo = ntohl(lo);
    hi = ntohl(hi);
    return ((u_int64_t)lo) << 32U | hi;
}
#endif
#define htonll ntohll

static int read_all(int fd, char *buf, size_t count)/*read from socket to buf*/
{
    int bytes_read;

    while (count > 0)
    {
        bytes_read = read(fd, buf, count);
        assert(bytes_read > 0);/*check if read didn't failed*/
        buf += bytes_read;
        count -= bytes_read;
    }
    assert(count == 0);/*double check for success*/

    return 0;
}

static int write_all(int fd, char *buf, size_t count)/*write from buffer to socket*/
{
    int bytes_written;

    while (count > 0)
    {
        bytes_written = write(fd, buf, count);
        assert(bytes_written > 0);/*check if write didn't failed*/
        buf += bytes_written;
        count -= bytes_written;
    }
    assert(count == 0);/*double check for succes*/

    return 0;
}

static void CleanUp(int fd1, int fd2, int fd3)
{
	if(errno == ENOENT)
	{
		printf("kernel module `nbd' loaded has not been loaded (modprobe nbd)\n");
	}

	if(errno == EACCES)
	{
		printf("you don't have permissions to access the device (sudo)\n");
	}

	if(-1 != fd1)
	{
		close(fd1);
	}

	if(-1 != fd2)
	{
		close(fd2);
	}

	if(-1 != fd3)
	{
		close(fd3);
	}

}

