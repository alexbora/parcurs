######################################################################
# @author      : alex (alex@T400)
# @file        : CMakeLists
# @created     : vineri oct 28, 2022 13:02:02 EEST
######################################################################

cmake_minimum_required(VERSION 3.23)
project(server LANGUAGES C)

add_executable(server)
target_sources(server PRIVATE server.c)
install(TARGETS server)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(server PRIVATE Threads::Threads)
