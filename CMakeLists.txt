cmake_minimum_required(VERSION 3.24)
project(editor)

set(CMAKE_CXX_STANDARD 17)

################## GOOGLE TEST ##################
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
        piece_table_test
        test/PieceTableTest.cpp
        src/PieceTable.cpp src/PieceTable.h)
target_link_libraries(
        piece_table_test
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(piece_table_test)

################## MAIN EXECUTABLE ##################
add_executable(editor src/main.cpp src/PieceTable.cpp src/PieceTable.h test/PieceTableTest.cpp)
