cmake_minimum_required(VERSION 3.30)
project(ScientificGystogramm)
project(ScientificGystogramm_test)

set(CMAKE_CXX_STANDARD 17)

# Подключаем Google Test через FetchContent
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(ScientificGystogramm main.cpp
        Parser.cpp
        Parser.h
        Histogram.cpp
        Histogram.h
)

add_executable(ScientificGystogramm_test
        gtest.cpp
        Parser.cpp
        Parser.h
        Histogram.cpp
        Histogram.h
)

target_link_libraries(ScientificGystogramm_test GTest::gtest_main)

# Автоматически добавляем тесты
include(GoogleTest)
gtest_discover_tests(ScientificGystogramm_test)