#ifndef TP1_CLIENT_H
#define TP1_CLIENT_H

#include "protocol.h"
#include <stdbool.h>


typedef struct {
    protocol_t *protocol;
} client_t;

// Client entry point
int client_main(int argc, char *argv[]);

// Initializes the structure
// Returns false if any of the subsequent initializations fail
bool client_init(client_t *self, char *host, char *port);

// Enters in a while true loop which constantly talks with the server
// Asks for user input (a command) and if pertinent, sends it to the server
// Then, it receives the server response, and prints it
// Breaks the loop if the command was an exit one or if the server shutdown
//   (the latter would only happen abruptly)
void client_communicate(client_t *self);

// Releases the different allocations per attributes
void client_release(client_t *self);

#endif //TP1_CLIENT_H
