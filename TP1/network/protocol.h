//
// Created by delmazo on 9/8/19.
//

#ifndef TP1_PROTOCOL_H
#define TP1_PROTOCOL_H

#define MAX_ARGUMENTS 4
#define MAX_LENGTH 50
#define PUT "PUT"
#define GET "GET"


void protocol_encode(char *buf, char* message);

#endif //TP1_PROTOCOL_H
