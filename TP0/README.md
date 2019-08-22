---
title: "TP0: Contador de Palabras"
author: Federico del Mazo - 100029
date: |
  | Facultad de Ingeniería, Universidad de Buenos Aires
  | [75.42] Taller de Programación
  | 
  | 27 de agosto de 2019
---

# Paso 0: Entorno de Trabajo

![aaa](screenshots/paso0.png){ width=550px }

1. ¿Para qué sirve ​ Valgrind​ ? ¿Cuáles son sus opciones más comunes?

2. ¿Qué representa ​` sizeof()`​ ? ¿Cuál sería el valor de salida de s
izeof(char)​ y ​ sizeof(int)​ ?

3. ¿El ​ sizeof()​ de una struct de C es igual a la suma del s
izeof() ​ de cada uno sus elementos?
Justifique mediante un ejemplo

4. Investigar la existencia de los archivos estándar: STDIN, STDOUT, STDERR. Explicar
brevemente su uso y cómo redirigirlos en caso de ser necesario (caracteres >
​ y ​ < ​ ) y como
conectar la salida estándar de un proceso a la entrada estándar de otro con un p
ipe​ (carácter
|​ ).

# Paso 1:

![aaa](screenshots/paso1-entrega.png){ width=550px }

ESTILO

```bash
./paso1_wordscounter.c:27:  Missing space before ( in while(  [whitespace/parens] [5]
./paso1_wordscounter.c:41:  Mismatching spaces inside () in if  [whitespace/parens] [5]
./paso1_wordscounter.c:41:  Should have zero or one spaces inside ( and ) in if  [whitespace/parens] [5]
./paso1_wordscounter.c:47:  An else should appear on the same line as the preceding }  [whitespace/newline] [4]
./paso1_wordscounter.c:47:  If an else has a brace on one side, it should have it on both  [readability/braces] [5]
./paso1_wordscounter.c:48:  Missing space before ( in if(  [whitespace/parens] [5]
./paso1_wordscounter.c:53:  Extra space before last semicolon. If this should be an empty statement, use {} instead.  [whitespace/semicolon] [5]
Done processing ./paso1_wordscounter.c
./paso1_main.c:12:  Almost always, snprintf is better than strcpy  [runtime/printf] [4]
./paso1_main.c:15:  An else should appear on the same line as the preceding }  [whitespace/newline] [4]
./paso1_main.c:15:  If an else has a brace on one side, it should have it on both  [readability/braces] [5]
Done processing ./paso1_main.c
./paso1_wordscounter.h:5:  Lines should be <= 80 characters long  [whitespace/line_length] [2]
Done processing ./paso1_wordscounter.h
Total errors found: 11
```

CODIGO

```
  CC  paso1_main.o
paso1_main.c: In function 'main':
paso1_main.c:22:9: error: unknown type name 'wordscounter_t'
         wordscounter_t counter;
         ^
paso1_main.c:23:9: error: implicit declaration of function 'wordscounter_create' [-Wimplicit-function-declaration]
         wordscounter_create(&counter);
         ^
paso1_main.c:24:9: error: implicit declaration of function 'wordscounter_process' [-Wimplicit-function-declaration]
         wordscounter_process(&counter, input);
         ^
paso1_main.c:25:24: error: implicit declaration of function 'wordscounter_get_words' [-Wimplicit-function-declaration]
         size_t words = wordscounter_get_words(&counter);
                        ^
paso1_main.c:27:9: error: implicit declaration of function 'wordscounter_destroy' [-Wimplicit-function-declaration]
         wordscounter_destroy(&counter);
         ^
<builtin>: recipe for target 'paso1_main.o' failed
make: *** [paso1_main.o] Error 1
```


## PASO 2

![aaa](screenshots/paso2-entrega.png){ width=550px }

a. Describa ​ en breves palabras​ las correcciones realizadas respecto de la versión anterior.

![aaa](screenshots/paso2-meld.png){ width=550px }

Estilo: 

Done processing ./paso2_main.c
Done processing ./paso2_wordscounter.c
Done processing ./paso2_wordscounter.h
Total errors found: 0

CODIGO

  CC  paso2_wordscounter.o
In file included from paso2_wordscounter.c:1:0:
paso2_wordscounter.h:7:5: error: unknown type name 'size_t'
     size_t words;
     ^
paso2_wordscounter.h:20:1: error: unknown type name 'size_t'
 size_t wordscounter_get_words(wordscounter_t *self);
 ^
paso2_wordscounter.h:25:49: error: unknown type name 'FILE'
 void wordscounter_process(wordscounter_t *self, FILE *text_file);
                                                 ^
paso2_wordscounter.c:17:8: error: conflicting types for 'wordscounter_get_words'
 size_t wordscounter_get_words(wordscounter_t *self) {
        ^
In file included from paso2_wordscounter.c:1:0:
paso2_wordscounter.h:20:8: note: previous declaration of 'wordscounter_get_words' was here
 size_t wordscounter_get_words(wordscounter_t *self);
        ^
paso2_wordscounter.c: In function 'wordscounter_next_state':
paso2_wordscounter.c:30:25: error: implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     char* delim_words = malloc(7 * sizeof(char));
                         ^
paso2_wordscounter.c:30:25: error: incompatible implicit declaration of built-in function 'malloc' [-Werror]
paso2_wordscounter.c:30:25: note: include '<stdlib.h>' or provide a declaration of 'malloc'
cc1: all warnings being treated as errors
<builtin>: recipe for target 'paso2_wordscounter.o' failed
make: *** [paso2_wordscounter.o] Error 1


## Paso 3

![aaa](screenshots/paso3-entrega.png){ width=550px }


  CC  paso3_wordscounter.o
  CC  paso3_main.o
  LD  tp
paso3_main.o: In function `main':
/home/sercom_backend/build/paso3_main.c:27: undefined reference to `wordscounter_destroy'
collect2: error: ld returned 1 exit status
Makefile:141: recipe for target 'tp' failed
make: *** [tp] Error 1

## paso 4

![aaa](screenshots/paso4-entrega.png){ width=550px }

Pruebas | 
- | -
![aaa](screenshots/paso4-pruebas1.png){ width=300px } | ![aaa](screenshots/paso4-pruebas2.png){ width=300px }

==00:00:00:00.000 549== Memcheck, a memory error detector
==00:00:00:00.000 549== Copyright (C) 2002-2015, and GNU GPL'd, by Julian Seward et al.
==00:00:00:00.000 549== Using Valgrind-3.11.0 and LibVEX; rerun with -h for copyright info
==00:00:00:00.000 549== Command: ./tp input_tda.txt
==00:00:00:00.000 549== Parent PID: 548
==00:00:00:00.000 549== 
==00:00:00:00.567 549== 
==00:00:00:00.567 549== FILE DESCRIPTORS: 3 open at exit.
==00:00:00:00.567 549== Open file descriptor 2: input_tda.txt
==00:00:00:00.567 549==    at 0x4113813: __open_nocancel (syscall-template.S:84)
==00:00:00:00.567 549==    by 0x40A79BF: _IO_file_open (fileops.c:221)
==00:00:00:00.567 549==    by 0x40A7B40: _IO_file_fopen@@GLIBC_2.1 (fileops.c:328)
==00:00:00:00.567 549==    by 0x409C2D0: __fopen_internal (iofopen.c:86)
==00:00:00:00.567 549==    by 0x409C33D: fopen@@GLIBC_2.1 (iofopen.c:97)
==00:00:00:00.567 549==    by 0x8048517: main (paso4_main.c:14)
==00:00:00:00.567 549== 
==00:00:00:00.567 549== Open file descriptor 1: /mnt/data/sercom/tmp/prueba.392420.stdout
==00:00:00:00.567 549==    <inherited from parent>
==00:00:00:00.567 549== 
==00:00:00:00.567 549== Open file descriptor 0: /home/sercom_backend/test/valgrind.out
==00:00:00:00.567 549==    <inherited from parent>
==00:00:00:00.567 549== 
==00:00:00:00.567 549== 
==00:00:00:00.567 549== HEAP SUMMARY:
==00:00:00:00.567 549==     in use at exit: 1,849 bytes in 216 blocks
==00:00:00:00.567 549==   total heap usage: 218 allocs, 2 frees, 10,041 bytes allocated
==00:00:00:00.567 549== 
==00:00:00:00.568 549== 344 bytes in 1 blocks are still reachable in loss record 1 of 2
==00:00:00:00.568 549==    at 0x402D17C: malloc (in /usr/lib/valgrind/vgpreload_memcheck-x86-linux.so)
==00:00:00:00.568 549==    by 0x409C279: __fopen_internal (iofopen.c:69)
==00:00:00:00.568 549==    by 0x409C33D: fopen@@GLIBC_2.1 (iofopen.c:97)
==00:00:00:00.568 549==    by 0x8048517: main (paso4_main.c:14)
==00:00:00:00.568 549== 
==00:00:00:00.568 549== 1,505 bytes in 215 blocks are definitely lost in loss record 2 of 2
==00:00:00:00.568 549==    at 0x402D17C: malloc (in /usr/lib/valgrind/vgpreload_memcheck-x86-linux.so)
==00:00:00:00.568 549==    by 0x8048685: wordscounter_next_state (paso4_wordscounter.c:35)
==00:00:00:00.568 549==    by 0x8048755: wordscounter_process (paso4_wordscounter.c:30)
==00:00:00:00.568 549==    by 0x8048535: main (paso4_main.c:24)
==00:00:00:00.568 549== 
==00:00:00:00.568 549== LEAK SUMMARY:
==00:00:00:00.568 549==    definitely lost: 1,505 bytes in 215 blocks
==00:00:00:00.568 549==    indirectly lost: 0 bytes in 0 blocks
==00:00:00:00.568 549==      possibly lost: 0 bytes in 0 blocks
==00:00:00:00.568 549==    still reachable: 344 bytes in 1 blocks
==00:00:00:00.568 549==         suppressed: 0 bytes in 0 blocks
==00:00:00:00.568 549== 
==00:00:00:00.568 549== For counts of detected and suppressed errors, rerun with: -v
==00:00:00:00.568 549== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
[SERCOM] Summary
[SERCOM] Command Line: /usr/bin/valgrind --tool=memcheck --trace-children=yes --track-fds=yes --time-stamp=yes --num-callers=20 --error-exitcode=42 --leak-check=full --leak-resolution=med --log-file=valgrind.out --show-reachable=yes --suppressions=suppressions.txt
[SERCOM] Error code configured for Valgrind: 42.
[SERCOM] Valgrind execution result: 42.
[SERCOM] Valgrind result: Failure.



==00:00:00:00.000 510== Memcheck, a memory error detector
==00:00:00:00.000 510== Copyright (C) 2002-2015, and GNU GPL'd, by Julian Seward et al.
==00:00:00:00.000 510== Using Valgrind-3.11.0 and LibVEX; rerun with -h for copyright info
==00:00:00:00.000 510== Command: ./tp input_extremely_long_filename.txt
==00:00:00:00.000 510== Parent PID: 509
==00:00:00:00.000 510== 
**00:00:00:00.547 510** *** memcpy_chk: buffer overflow detected ***: program terminated
==00:00:00:00.547 510==    at 0x402FD97: ??? (in /usr/lib/valgrind/vgpreload_memcheck-x86-linux.so)
==00:00:00:00.547 510==    by 0x40346EB: __memcpy_chk (in /usr/lib/valgrind/vgpreload_memcheck-x86-linux.so)
==00:00:00:00.547 510==    by 0x804850A: memcpy (string3.h:53)
==00:00:00:00.547 510==    by 0x804850A: main (paso4_main.c:13)
==00:00:00:00.564 510== 
==00:00:00:00.564 510== FILE DESCRIPTORS: 2 open at exit.
==00:00:00:00.564 510== Open file descriptor 1: /mnt/data/sercom/tmp/prueba.392411.stdout
==00:00:00:00.564 510==    <inherited from parent>
==00:00:00:00.564 510== 
==00:00:00:00.564 510== Open file descriptor 0: /home/sercom_backend/test/valgrind.out
==00:00:00:00.564 510==    <inherited from parent>
==00:00:00:00.564 510== 
==00:00:00:00.564 510== 
==00:00:00:00.564 510== HEAP SUMMARY:
==00:00:00:00.564 510==     in use at exit: 0 bytes in 0 blocks
==00:00:00:00.564 510==   total heap usage: 0 allocs, 0 frees, 0 bytes allocated
==00:00:00:00.564 510== 
==00:00:00:00.564 510== All heap blocks were freed -- no leaks are possible
==00:00:00:00.564 510== 
==00:00:00:00.564 510== For counts of detected and suppressed errors, rerun with: -v
==00:00:00:00.564 510== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
[SERCOM] Summary
[SERCOM] Command Line: /usr/bin/valgrind --tool=memcheck --trace-children=yes --track-fds=yes --time-stamp=yes --num-callers=20 --error-exitcode=42 --leak-check=full --leak-resolution=med --log-file=valgrind.out --show-reachable=yes --suppressions=suppressions.txt
[SERCOM] Error code configured for Valgrind: 42.
[SERCOM] Valgrind execution result: 1.
[SERCOM] Valgrind result: Success.

## paso 5

![aaa](screenshots/paso5-entrega.png){ width=550px }

Pruebas | 
- | -
![aaa](screenshots/paso5-pruebas1.png){ width=300px } | ![aaa](screenshots/paso5-pruebas2.png){ width=300px }


## paso 6

![aaa](screenshots/paso6-entrega.png){ width=550px }

Pruebas | 
- | -
![aaa](screenshots/paso6-pruebas1.png){ width=300px } | ![aaa](screenshots/paso6-pruebas2.png){ width=300px }

## paso 7

![aaa](screenshots/paso7-todo.png){ width=550px }