cmake_minimum_required(VERSION 3.15)

project(zura)

set(CMAKE_CXX_STANDARD 20)

enable_testing()
#include_directories(${GTEST_INCLUDE_DIRS})

find_package(GTest CONFIG REQUIRED)

# Specify header and source files
set(ZURA_HEADER_FILES
    src/helper/error/error.hpp
    src/helper/flags.hpp
    inc/colorize.hpp

    # Lexer Files
    src/lexer/lexer.hpp
    src/lexer/maps.hpp

    # Ast Files
    src/ast/ast.hpp
    src/ast/expr.hpp
    src/ast/stmt.hpp
    src/ast/types.hpp

    # Parser Files
    src/parser/parser.hpp

    inc/update.hpp
    src/common.hpp
)

set(ZURA_SOURCE_FILES
    src/helper/error/error.cpp
    src/helper/flags.cpp
    src/lexer/lexer.cpp

    # Parser Files
    src/parser/parser.cpp
    src/parser/expr.cpp
    src/parser/stmt.cpp
    src/parser/type.cpp
    src/parser/tmaps.cpp
    src/parser/map.cpp 
    
    src/main.cpp
)

# Create executable
add_executable(zura ${ZURA_HEADER_FILES} ${ZURA_SOURCE_FILES})

add_executable(zura_test test/zura_test.cpp)
# target_link_libraries(zura_test ${GTEST_LIBRARIES} pthread)
target_link_libraries( PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)


# Add test
# add_test(NAME zura_test COMMAND zura_test)
add_test(AllTestsInMain main)
    

#add_test(AllTestsInMain main)