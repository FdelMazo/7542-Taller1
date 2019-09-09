#ifndef TP1_DEBUG_H
#define TP1_DEBUG_H

#include <stdio.h>

#ifdef DEBUG
#define DEBUG_PRINT(...) do{ fprintf( stdout, __VA_ARGS__ ); } while( false )
#else
#define DEBUG_PRINT(...) do{ } while ( false )
#endif

#endif //TP1_DEBUG_H
