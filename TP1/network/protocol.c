//
// Created by delmazo on 9/8/19.
//

#include "protocol.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void _protocol_encode_command(char* message, int argc, char *argv[]){
    char *args = message;
    if (strcmp(argv[0], "PUT")) {
        args[0] = 'P';
        args[1] = *argv[1];
        char *arx[2];
        sscanf(argv[3], "%s,%s", arx[0], arx[1]);
        printf("%s", *arx);
    }
    else if (strcmp(argv[0], "VERIFY")) {
        args[0] = 'V';
    }
    else if (strcmp(argv[0], "RESET")) {
        args[0] = 'R';
    }
    else if (strcmp(argv[0], "GET")) {
        args[0] = 'G';
    }
    printf("%s", message);
}

void protocol_encode(char *buf, char* message) {
    char *ptr = buf;
    int argc = 0;
    char **argv = calloc(MAX_ARGUMENTS,sizeof(char*));
    for (int i=0; i< MAX_ARGUMENTS; i++) {
        argv[i] = calloc(50, sizeof(char));
        sscanf(ptr, "%s", argv[i]);
        ptr += strlen(argv[i]) +1;
        argc++;
    }
    for (int i=argc; i< MAX_ARGUMENTS; i++) {
        free(argv[i]);
    }
    _protocol_encode_command(message, argc, argv);
}

