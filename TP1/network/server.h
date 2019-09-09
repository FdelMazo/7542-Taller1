#ifndef TP1_SERVER_H
#define TP1_SERVER_H

#include "protocol.h"
#include <stdbool.h>
#include "sudoku.h"

#define BOARD_PATH "board.txt"

typedef struct {
    protocol_t *protocol;
    sudoku_t *sudoku;
} server_t;

// Server entry point
// Keep in mind this server is written to take only one client per lifetime!
// Once the client closed its connection, the server will shut down
int server_main(int argc, char *argv[]);

// Initializes the structure
// Returns false if any of the subsequent initializations fail
bool server_init(server_t *self, char *port);

// Enters in a while true loop which constantly talks with the client
// Receives from the client a command (which, because a protocol was followed,
//   is only a valid command)
// Then, the command is executed on the sudoku
// Finally, it sends a reponse to the client
// Breaks the loop once the client closed its connection
void server_communicate(server_t *self);

// Releases the different allocations per attributes
void server_release(server_t *self);

#endif //TP1_SERVER_H
