/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

/*
 *  cxsocket_api.h
 *  Bare-bones API for connection to a socket
 *  Copyright 1987-2022 Ansys Inc
 */
#ifndef _CXSOCKET_API_H_
#define _CXSOCKET_API_H_

#include <stddef.h>

typedef int Socket;

typedef enum
{
  ERROR_SOCKET_OK = -1,
  ERROR_SOCKET_CREATE = -2,
  ERROR_SOCKET_INIT = -3,
  ERROR_SOCKET_READ = -4,
  ERROR_SOCKET_WRITE = -5,
  ERROR_SOCKET_CLOSE = -6,
  ERROR_SOCKET_TIMEOUT = -7,
  ERROR_SOCKET_CONNECT = -8,
  ERROR_SOCKET_MAX_MESSAGES = 8
} SocketError;
#define SOCKET_MESSAGES \
      { \
  "No error", /* ERROR_SOCKET_OK = -1, */ \
        "Error during socket creation", /* ERROR_SOCKET_CREATE = -2, */ \
        "Error during initialization", /*ERROR_SOCKET_INIT = -3, */ \
        "Error during socket read", /* ERROR_SOCKET_READ = -4, */ \
        "Error during socket write", /* ERROR_SOCKET_WRITE = -5, */ \
        "Error during socket close", /* ERROR_SOCKET_CLOSE = -6, */ \
        "Timeout during socket operation", /* ERROR_SOCKET_TIMEOUT = -7, */ \
        "Error during socket connect", /* ERROR_SOCKET_CONNECT = -8, */ \
      };

/* Create a client-side socket given the port and address to connect to
 * Return:
 *   On Success : Handle to socket
 *   On failure: SocketError   */

Socket Socket_CreateClient(char *addr, int port);

/* Check if socket has data. This is a non-blocking call.
 * Return:
 *     if data available: ERROR_SOCKET_OK
 *     if no data available: ERROR_SOCKET_TIMEOUT
 *     if error: ERROR_SOCKET_CONNECT*/

int Socket_HasData(Socket socket, long waitSecs);

/* Read bytes from socket. This is a blocking call.
 *    buf: memory to read to.
 *    length: maximum no. of bytes to read.
 *    Return:
 *        On success: no. of bytes read
 *        On failure: ERROR_SOCKET_READ */
int Socket_Read(Socket socket, void *buf, size_t length);
/* Write bytes to socket.
 *    buf: memory to write from
 *    length: no. of bytes to write
 *    Return:
 *        On success: no. of bytes written
 *        On failure: ERROR_SOCKET_WRITE
 *    */
int Socket_Write(Socket socket, void *buf, size_t length);
/* Close a socket.
 * Return:
 *    ERROR_SOCKET_OK */
int Socket_Close(Socket socket);

/* Error message from message number */
char *Socket_ErrorMsg(SocketError msgId);

#endif
