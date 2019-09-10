#ifndef TP1_PROTOCOL_H
#define TP1_PROTOCOL_H

#define MAX_LENGTH_COMMAND 15

#define REQUEST_LENGTH 1
#define ARGUMENTS_LENGTH 3

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
//
// The protocol for the client sending side is as follows:
//    The user request is in natural language. 'verify' 'put 5 in 1,2'
//    The protocol receives this. If it is a supported command, converts it
//    The put command is a char 'P' followed by 3 unsigned ints of 1 byte
//    The rest of the commands are just the initial letter, as a single char
//    That char (and if neccesary,the uints) are the message sent to the server
ssize_t protocol_client_send(protocol_t *self, char *request);

// Gets an empty buffer to fill with the server response to the client
// This is for when the client asks the server it's response to one command
// Returns:
//    -1 or 0 when the server closed the connection
//    n  when a n byte message was received and stored in the buffer
//
// The protocol for the client receiving side is as follows:
//    The protocol gets a 4 byte big-endian unsigned int
//    That number is the length of the incoming message
//    Then, it receives a message of that length
ssize_t protocol_client_receive(protocol_t *self, char *buffer);

// The server accepts the incoming client
void protocol_server_accept(protocol_t *self);

// Gets an empty buffer to fill with the client request to the server
// This is for when the client asks the server it's response to one command
// Returns:
//    -1 or 0 when the server closed the connection
//    n  when a n byte message was received and stored in the buffer
//
// The protocol for the server receiving side is as follows:
//    The protocol gets at most 4 bytes
//    The first one is the initial letter of the command
//    If the command is a put one, it then gets 3 unsigned 1-byte ints
//    The server will never get anything other than specified
ssize_t protocol_server_receive(protocol_t *self, char *request);

// Gets a buffer with a message, encodes it to follow the protocol and sends it
// This is for when the server has to answer the client's command
// Returns:
//    -1 when there was an unexpected error in the send
//    0  if nothing was sent
//    n  when a n byte message was sent
//
// The protocol for the server sending side is as follows:
//    The protocol gets a message to send
//    Then, it sends one big-endian 4-byte uint, with the length of that message
//    Finally, it sends the whole message
ssize_t protocol_server_send(protocol_t *self, char *buffer);


// Releases the different allocations per attributes
void protocol_release(protocol_t *self);

#endif //TP1_PROTOCOL_H
