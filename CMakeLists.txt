cmake_minimum_required(VERSION 3.10)
project(TokenParser VERSION 1.00 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
find_package(GTest)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")

set(SOURCE_FILES src/MultipurposeSequence.h
        src/BasicGraph.h src/RegularExpressionParser.cpp src/RegularExpressionParser.h src/REBinaryTree.h
        src/TokenParser.cpp src/TokenParser.h src/Initialize.cpp src/Initialize.h)
add_executable(TokenParser ${SOURCE_FILES} src/main.cpp)
set(TEST_FILES test/GraphTest.cpp
        test/RegularExpressionParserTest.cpp test/SequenceTest.cpp test/TokenParserTest.cpp)
add_executable(TokenParserTest ${TEST_FILES} ${SOURCE_FILES} test/test_main.cpp)
target_link_libraries(TokenParserTest gtest pthread)
