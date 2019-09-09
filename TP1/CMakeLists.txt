cmake_minimum_required(VERSION 3.10)

project(TP1 C)
include_directories(.)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "-Wall -Werror -pedantic -pedantic-errors -ggdb -DDEBUG -fno-inline")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

set(CMAKE_C_CPPLINT "cpplint;--extensions=h,hpp,c,cpp;\
--filter=-,+build/class,+build/deprecated,+build/include_what_you_use,+build/namespaces,+build/printf_format,\
+readability/braces,+readability/check,+readability/fn_size,+readability/function,+readability/multiline_comment,+readability/multiline_string,+readability/utf8,\
+runtime/arrays,+runtime/casting,+runtime/explicit,+runtime/init,+runtime/invalid_increment,+runtime/memset,+runtime/operator,+runtime/printf,+runtime/printf_format,+runtime/rtti,+runtime/string,+runtime/threadsafe_fn,\
+whitespace/blank_line,+whitespace/empty_loop_body,+whitespace/ending_newline,+whitespace/line_length,+whitespace/newline,+whitespace/parens,+whitespace/semicolon")

add_custom_target(zip COMMAND
        ${CMAKE_COMMAND} -E tar "cfv" "sercom.zip" --format=zip
            "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

add_custom_target(make COMMAND
        make -f SercomMakefile)

add_executable(tp
        main.c
        board.c
        board.h
        cell.c
        cell.h
        2d_array.c
        2d_array.h
        sudoku.c
        sudoku.h
        protocol.c
        debug.h
        protocol.h
        sudoku_dispatcher.c
        sudoku_dispatcher.h
        client.c
        client.h
        server.c
        server.h
        socket.c
        socket.h
)

add_executable(sudoku_tests
        sudoku_tests.c
        board.c
        board.h
        cell.c
        cell.h
        sudoku.c
        sudoku.h
        2d_array.c
        2d_array.h
)