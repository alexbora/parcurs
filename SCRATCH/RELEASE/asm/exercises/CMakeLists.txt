######################################################################
# @author      : alex (alex@mac.local)
# @file        : CMakeLists
# @created     : Joi Iul 07, 2022 07:53:56 EEST
######################################################################


cmake_minimum_required(VERSION 3.21)
project(example)

find_package(PkgConfig REQUIRED)
pkg_check_modules(OpenSSL REQUIRED IMPORTED_TARGET "openssl")

add_executable(main main.c)
target_link_libraries(main PRIVATE PkgConfig::OpenSSL)


