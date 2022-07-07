######################################################################
# @author      : alex (alex@mac.local)
# @file        : CMakeLists
# @created     : Joi Iul 07, 2022 06:51:23 EEST
######################################################################

cmake_minimum_required(VERSION 3.22)
project(parcurs)

add_executable(final_program excel.c)

find_package(OpenSSL REQUIRED)
if (OPENSSL_FOUND)
  # Add the include directories for compiling
  target_include_directories(${PROJECT_NAME} PUBLIC ${OPENSSL_INCLUDE_DIR})

  # Add the static lib for linking
  target_link_libraries(${PROJECT_NAME} OpenSSL::SSL OpenSSL::Crypto)

  message(STATUS "Found OpenSSL ${OPENSSL_VERSION}")

else()

  message(STATUS "OpenSSL Not Found")

endif()

