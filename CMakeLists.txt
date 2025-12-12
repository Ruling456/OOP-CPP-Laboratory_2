cmake_minimum_required(VERSION 3.10)
project(Laboratory_2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавление опций компиляции только для GCC/Clang
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=maybe-uninitialized")
endif()

# Установка Google Test
include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.0
    TLS_VERIFY false
)

# Отключаем использование статической библиотеки и переключаем на динамическую
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Основная библиотека проекта
add_library(${PROJECT_NAME}_lib src/Four.cpp)
target_include_directories(${PROJECT_NAME}_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Основной исполняемый файл
add_executable(${PROJECT_NAME}_exe main.cpp)
target_link_libraries(${PROJECT_NAME}_exe PRIVATE ${PROJECT_NAME}_lib)
target_include_directories(${PROJECT_NAME}_exe PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Тесты
enable_testing()
add_executable(Laboratory_2_tests test/test_four.cpp)
target_link_libraries(Laboratory_2_tests PRIVATE ${PROJECT_NAME}_lib gtest_main)
target_include_directories(Laboratory_2_tests PRIVATE ${CMAKE_SOURCE_DIR}/include)
add_test(NAME Laboratory_2_tests COMMAND Laboratory_2_tests)