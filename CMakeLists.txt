cmake_minimum_required(VERSION 3.27.7)
project(FindDuplicateFilesInDir VERSION 0.1.0 LANGUAGES C)

include(CTest)
enable_testing()

add_executable(FindDuplicateFilesInDir main.c lib.c Vector.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
