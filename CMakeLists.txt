cmake_minimum_required(VERSION 3.17)
project(minishell C)

set(CMAKE_C_STANDARD 11)

include_directories(get_next_line)
include_directories(includes)
include_directories(libft)
include_directories(utils)
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D BUFFER_SIZE=32")
file(GLOB
        ENGINE "engine/*.c")

file(GLOB
        PARSER "parser/*.c")

file(GLOB
        UTILS "utils/*.c")

file(GLOB
        BUILTIN "builtin/*.c")

file(GLOB
        LIBFT "libft/*.c")

add_executable(minishell
        get_next_line/get_next_line.c
        get_next_line/get_next_line_utils.c
        ${LIBFT}
        ${ENGINE}
        ${PARSER}
        ${UTILS}
        ${BUILTIN}
        engine/gnl_minishell.c parser/states.c parser/parse_env.c)
