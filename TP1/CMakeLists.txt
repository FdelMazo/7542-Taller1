cmake_minimum_required(VERSION 3.10)

project(TP1 C)
include_directories(.)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-pedantic -pedantic-errors \
                  -O3 \
                  -ggdb -DDEBUG -fno-inline")

set(CMAKE_C_CPPLINT "cpplint;\
--extensions=h,hpp,c,cpp;\
--filter=-,+build/class,+build/deprecated,+build/include_what_you_use,+build/namespaces,+build/printf_format,\
+readability/braces,+readability/check,+readability/fn_size,+readability/function,+readability/multiline_comment,+readability/multiline_string,+readability/utf8,\
+runtime/arrays,+runtime/casting,+runtime/explicit,+runtime/init,+runtime/invalid_increment,+runtime/memset,+runtime/operator,+runtime/printf,+runtime/printf_format,+runtime/rtti,+runtime/string,+runtime/threadsafe_fn,\
+whitespace/blank_line,+whitespace/empty_loop_body,+whitespace/ending_newline,+whitespace/line_length,+whitespace/newline,+whitespace/parens,+whitespace/semicolon")

add_executable(TP1
        main.c
        sudoku/board.c
        sudoku/board.h
        sudoku/cell.c
        sudoku/cell.h
        sudoku/sudoku.c
        sudoku/sudoku.h
        network/client.c
        network/client.h
        network/server.c
        network/server.h
        network/socket.c
        network/socket.h
        aux/strutil.c
        aux/strutil.h
)

add_executable(sudoku_tests
        sudoku/tests.c
        sudoku/board.c
        sudoku/board.h
        sudoku/cell.c
        sudoku/cell.h
        sudoku/sudoku.c
        sudoku/sudoku.h
        aux/strutil.c
        aux/strutil.h
)

add_executable(network_tests
        network/tests.c
        network/client.c
        network/client.h
        network/server.c
        network/server.h
        network/socket.c
        network/socket.h
        aux/strutil.c
        aux/strutil.h
)