cmake_minimum_required(VERSION 3.10)
project(TP3)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall -Werror -pedantic -pedantic-errors -ggdb -DDEBUG -fno-inline -pthread -lm")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

set(CPPLINT_FILTER_OPTIONS
        "-,+build/class,+build/deprecated,+build/include_what_you_use,+build/namespaces,+build/printf_format,\
+readability/braces,+readability/check,+readability/fn_size,+readability/function,+readability/multiline_comment,+readability/multiline_string,+readability/utf8,\
+runtime/arrays,+runtime/casting,+runtime/explicit,+runtime/init,+runtime/invalid_increment,+runtime/memset,+runtime/operator,+runtime/printf,+runtime/printf_format,+runtime/rtti,+runtime/string,+runtime/threadsafe_fn,\
+whitespace/blank_line,+whitespace/empty_loop_body,+whitespace/ending_newline,+whitespace/line_length,+whitespace/newline,+whitespace/parens,+whitespace/semicolon"
        )
set(CMAKE_CXX_CPPLINT "cpplint;--extensions=h,hpp,c,cpp;--filter=${CPPLINT_FILTER_OPTIONS}")

add_custom_target(informe
        COMMAND plantuml diagrams/*.puml
        COMMAND convert diagrams/server.png -rotate 90 diagrams/server.png
        COMMAND pandoc README.md -H header.tex -o Informe.pdf --pdf-engine=xelatex
        )

add_custom_target(lint_headers
        COMMAND cpplint --filter=${CPPLINT_FILTER_OPTIONS} "*.h"
        )

add_custom_target(zip
        DEPENDS server
        DEPENDS client
        DEPENDS lint_headers
        DEPENDS sercom
        COMMAND ${CMAKE_COMMAND} -E tar "cfv" "sercom.zip" --format=zip "*cpp" "*.h"
        )

add_custom_target(sercom
        COMMAND make -f ${PROJECT_SOURCE_DIR}/SercomMakefile
        )

add_executable(server
        server_main.cpp
        server_HoneyPot.cpp server_HoneyPot.h
        server_DirectoryList.h server_DirectoryList.cpp
        server_Command.cpp server_Command.h
        server_CommandUser.cpp server_CommandUser.h
        server_CommandHelp.cpp server_CommandHelp.h
        server_CommandWorkingDir.cpp server_CommandWorkingDir.h
        server_CommandPassword.cpp server_CommandPassword.h
        server_CommandSystemInfo.cpp server_CommandSystemInfo.h
        server_CommandListDirs.cpp server_CommandListDirs.h
        server_CommandMakeDir.cpp server_CommandMakeDir.h
        server_CommandRemoveDir.cpp server_CommandRemoveDir.h
        common_Socket.cpp common_Socket.h
        server_Server.cpp server_Server.h
        common_CommunicationProtocol.cpp common_CommunicationProtocol.h
        server_Thread.cpp server_Thread.h
        server_ClientListener.cpp server_ClientListener.h
        server_ClientTalker.cpp server_ClientTalker.h
        server_CommandQuit.cpp server_CommandQuit.h)

add_executable(client
        client_main.cpp
        client_Client.cpp client_Client.h
        common_Socket.cpp common_Socket.h
        common_CommunicationProtocol.cpp common_CommunicationProtocol.h
        )