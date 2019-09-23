cmake_minimum_required(VERSION 3.10)
project(TP2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall -Werror -pedantic -pedantic-errors -ggdb -DDEBUG -fno-inline -pthread")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

set(CPPLINT_FILTER_OPTIONS
        "-,+build/class,+build/deprecated,+build/include_what_you_use,+build/namespaces,+build/printf_format,\
+readability/braces,+readability/check,+readability/fn_size,+readability/function,+readability/multiline_comment,+readability/multiline_string,+readability/utf8,\
+runtime/arrays,+runtime/casting,+runtime/explicit,+runtime/init,+runtime/invalid_increment,+runtime/memset,+runtime/operator,+runtime/printf,+runtime/printf_format,+runtime/rtti,+runtime/string,+runtime/threadsafe_fn,\
+whitespace/blank_line,+whitespace/empty_loop_body,+whitespace/ending_newline,+whitespace/line_length,+whitespace/newline,+whitespace/parens,+whitespace/semicolon"
        )
set(CMAKE_CXX_CPPLINT "cpplint;--extensions=h,hpp,c,cpp;--filter=${CPPLINT_FILTER_OPTIONS}")

add_custom_target(lint_headers
        COMMAND cpplint --filter=${CPPLINT_FILTER_OPTIONS} "*.h"
        )

add_custom_target(zip
        DEPENDS tests
        DEPENDS sercom
        COMMAND ${CMAKE_COMMAND} -E tar "cfv" "sercom.zip" --format=zip "*cpp" "*.h"
)

add_custom_target(tests
        DEPENDS lint_headers
        DEPENDS tp
        COMMAND ${PROJECT_SOURCE_DIR}/tests.sh
)

add_custom_target(sercom
        COMMAND make -f ${PROJECT_SOURCE_DIR}/SercomMakefile
)

add_executable(tp
        main.cpp
        CompressedBlock.cpp CompressedBlock.h
        Thread.cpp Thread.h
        Minion.cpp Minion.h
        InputMonitor.cpp InputMonitor.h
        ThreadSafeQueue.cpp ThreadSafeQueue.h
        Writer.cpp Writer.h
)