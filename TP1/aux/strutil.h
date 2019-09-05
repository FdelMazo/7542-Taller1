#ifndef STRUTIL
#define STRUTIL

char** split(const char* cadena_orig, char sep);
char* join(char** strv, char sep);
void free_strv(char* strv[]);

#endif // STRUTIL
