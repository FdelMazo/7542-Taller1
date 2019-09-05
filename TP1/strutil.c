// Federico del Mazo - 100029
// TP1 - STRUTIL
// Corrige Gonzalo

#define _POSIX_C_SOURCE 200809L // strdup(), stpcpy()
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strutil.h"

/* *****************************************************************
                         FUNCIONES AUXILIARES
 * *****************************************************************/

//Sacada de stackoverflow, retira todos los \n \0 y \t de una string
void strip(char *s) {
    char *p2 = s;
    while(*s != '\0') {
        if(*s != '\t' && *s != '\n') {
            *p2++ = *s++;
        } else {
            ++s;
        }
    }
    *p2 = '\0';
}

//Cuenta los separadores en una cadena
size_t cant_sep(const char* cadena, char sep){
    size_t cantidad = 0;
    while((cadena = strchr(cadena, sep)) != NULL){
        cantidad++;
        cadena++;
    }
    return cantidad;
}
//Cuenta el total de caracteres en un arreglo de cadenas
size_t cant_chars(char** strv){
    size_t cantidad = 0;
    size_t i = 0;
    while(strv[i]){
        cantidad+=strlen(strv[i])+1;
        i++;
    }
    return cantidad;
}

//Cuenta el total de cadenas en un arreglo de cadenas
size_t cant_cads(char** strv){
    size_t cantidad = 0;
    size_t i = 0;
    while(strv[i]){
        cantidad++;
        i++;
    }
    return cantidad;
}

/* *****************************************************************
                         SPLIT, JOIN y FREE_STVR
 * *****************************************************************/

char** split(const char* cadena_orig, char sep){
    char str_sep[2] = {sep, '\0'};
    size_t cant_cads = cant_sep(cadena_orig, sep) + 1;
    char **strv = malloc(sizeof(char*) * (cant_cads+2));
    char* cadena = malloc((strlen(cadena_orig) + 1) * sizeof(char));
    if(!strv || !cadena){
        free(strv);
        free(cadena);
        return NULL;
    }
    strcpy(cadena,cadena_orig);
    size_t restar = 0; //Cantidad de posiciones que avanzo mi cadena
    for(int i = 0; i<=cant_cads +1; i++)
        strv[i] = NULL;
    for(size_t i = 0; i<cant_cads; i++){
        strv[i] = NULL;
        size_t pos_sep = strcspn(cadena, str_sep);
        char* cadenita = calloc(pos_sep+1,sizeof(char));
        if(!cadenita) return NULL;
        strncpy(cadenita, cadena, pos_sep);
        strip(cadenita);
        strv[i] = cadenita;
        cadena+=pos_sep+1;
        restar +=pos_sep+1;
    }
    cadena-= restar; //Vuelvo a la posicion original para liberar la memoria
    free(cadena);
    return strv;
}

char* join(char** strv, char sep){
    if(!strv[0]){
        char* cad_vacia = malloc(sizeof(char)+1);
        if(!cad_vacia) return NULL;
        cad_vacia[0] = '\0';
        return cad_vacia;
    }
    char str_sep[2] = {sep, '\0'};
    char* cadena = calloc(cant_chars(strv),sizeof(char));
    if(!cadena) return NULL;
    char* puntero = cadena;
    strcpy(cadena,strv[0]);
    for (size_t i=1; strv[i]; i++){
        puntero+=strlen(puntero);
        strcat(puntero,str_sep);
        puntero++;
        strcat(puntero,strv[i]);
    }
    return cadena;
}

void free_strv(char* strv[]){
    for(size_t i = 0; strv[i]; i++)
        free(strv[i]);
    free(strv);
}