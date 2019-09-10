cmake_minimum_required(VERSION 3.10)

project(TP1 C)
include_directories(.)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "-Wall -Werror -pedantic -pedantic-errors -ggdb -DDEBUG -fno-inline -Isudoku -Inetwork")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

set(CMAKE_C_CPPLINT "cpplint;--extensions=h,hpp,c,cpp;\
--filter=-,+build/class,+build/deprecated,+build/include_what_you_use,+build/namespaces,+build/printf_format,\
+readability/braces,+readability/check,+readability/fn_size,+readability/function,+readability/multiline_comment,+readability/multiline_string,+readability/utf8,\
+runtime/arrays,+runtime/casting,+runtime/explicit,+runtime/init,+runtime/invalid_increment,+runtime/memset,+runtime/operator,+runtime/printf,+runtime/printf_format,+runtime/rtti,+runtime/string,+runtime/threadsafe_fn,\
+whitespace/blank_line,+whitespace/empty_loop_body,+whitespace/ending_newline,+whitespace/line_length,+whitespace/newline,+whitespace/parens,+whitespace/semicolon")

add_custom_target(zip
        COMMAND mkdir sercom
        COMMAND cp "${CMAKE_CURRENT_SOURCE_DIR}/sudoku/*" sercom
        COMMAND cp "${CMAKE_CURRENT_SOURCE_DIR}/network/*" sercom
        COMMAND cp "${CMAKE_CURRENT_SOURCE_DIR}/main.c" sercom
        COMMAND cp "${CMAKE_CURRENT_SOURCE_DIR}/debug.h" sercom
        COMMAND
            cd sercom && ${CMAKE_COMMAND} -E tar "cfv" "../sercom.zip" --format=zip "*"
        COMMAND rm -rf sercom
)

add_custom_target(informe
        COMMAND plantuml diagrams/*.puml
        COMMAND pandoc README.md -H header.tex -o Informe.tex --latex-engine=xelatex
        COMMAND sed -i 's/@{}ll@{}/@{}l|l@{}/g' Informe.tex
        COMMAND pdflatex Informe.tex
        COMMAND rm Informe.tex)

add_executable(tp
        main.c
        sudoku/board.c
        sudoku/board.h
        sudoku/cell.c
        sudoku/cell.h
        sudoku/2d_array.c
        sudoku/2d_array.h
        sudoku/sudoku.c
        sudoku/sudoku.h
        network/protocol.c
        debug.h
        network/protocol.h
        network/sudoku_dispatcher.c
        network/sudoku_dispatcher.h
        network/client.c
        network/client.h
        network/server.c
        network/server.h
        network/socket.c
        network/socket.h
)

add_executable(sudoku_tests
        sudoku/sudoku_tests.c
        sudoku/board.c
        sudoku/board.h
        sudoku/cell.c
        sudoku/cell.h
        sudoku/sudoku.c
        sudoku/sudoku.h
        sudoku/2d_array.c
        sudoku/2d_array.h
)