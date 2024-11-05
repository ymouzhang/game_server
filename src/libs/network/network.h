#pragma once

#include <iostream>

#ifndef WIN32
// linux
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#define SOCKET int
#define INVALID_SOCKET -1
#define _sock_init()
#define _sock_nonblock(sockfd)                      \
    {                                              \
        int flags = fcntl(sockfd, F_GETFL, 0);     \
        fcntl(sockfd, F_SETFL, flags | O_NONBLOCK); \
    }
#define _sock_exit()
#define _sock_err() errno
#define _sock_close(sockfd) ::close(sockfd)

#else
// TODO windows

#endif

inline int GetListenBacklog()
{
    int backlog = 10;
#ifndef WIN32
    char *ptr;
    if ((ptr = getenv("LISTENQ")) != nullptr)
        backlog = atoi(ptr);
#endif
    return backlog;
}