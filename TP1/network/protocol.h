#ifndef TP1_PROTOCOL_H
#define TP1_PROTOCOL_H

#define MAX_LENGTH_COMMAND 15
#define MAX_LENGTH_OUTPUT 800
#define MAX_REQUEST_LENGTH 4
#define MAX_RESPONSE_LENGTH 800

#define PUT "put"
#define GET "get"
#define VERIFY "verify"
#define RESET "reset"
#define EXIT "exit"

#include "socket.h"
#include <sys/types.h>

typedef struct {
    socket_t *skt;
    socket_t *client_skt;
} protocol_t;

// Initializes the structure when called from the client
// Returns false if any of the subsequent initializations fail
bool protocol_client_init(protocol_t *self, char *host, char *port);

// Initializes the structure when called from the client
// Returns false if any of the subsequent initializations fail
bool protocol_server_init(protocol_t *self, char *port);

// Gets a buffer with a message, encodes it to follow the protocol and sends it
// This is for when the client sends to the server a command
// Returns:
//    -1 when the command was an exit one, or the server closed the connection
//    0  if nothing was sent (when a command is invalid,
//                                  like a bad 'put',
//                                  or something not in the specifications)
//    n  when a n byte message was sent
ssize_t protocol_client_send(protocol_t *self, char *request);

// Gets an empty buffer to fill with the server response to the client
// This is for when the client asks the server it's response to one command
// Returns:
//    -1 or 0 when the server closed the connection
//    n  when a n byte message was received and stored in the buffer
ssize_t protocol_client_receive(protocol_t *self, char *response);

// Gets an empty buffer to fill with the client request to the server
// This is for when the client asks the server it's response to one command
// Returns:
//    -1 or 0 when the server closed the connection
//    n  when a n byte message was received and stored in the buffer
ssize_t protocol_server_receive(protocol_t *self, char *request);

// Gets a buffer with a message, encodes it to follow the protocol and sends it
// This is for when the server has to answer the client's command
// Returns:
//    -1 when there was an unexpected error in the send
//    0  if nothing was sent
//    n  when a n byte message was sent
ssize_t protocol_server_send(protocol_t *self, char *response);


// Releases the different allocations per attributes
void protocol_release(protocol_t *self);

#endif //TP1_PROTOCOL_H
