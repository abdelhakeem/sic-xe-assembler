cmake_minimum_required(VERSION 3.5)
project(SIC_XE_Assembler)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(ParserTest test/ParserTest.cpp)
add_executable(pass1 src/cs222/Pass1.cpp)
add_executable(assemble src/cs222/Pass2.cpp)

add_library(SIC_XE_Assembler
    src/cs222/Instruction.cpp
    src/cs222/Operand.cpp
    src/cs222/Operation.cpp
    src/cs222/Parser.cpp
    src/cs222/Utility.cpp
    src/cs222/Validator.cpp
    src/cs222/IntermediateParser.cpp
    src/cs222/Symbol.cpp
    )

target_link_libraries(ParserTest SIC_XE_Assembler)
target_link_libraries(pass1 SIC_XE_Assembler)
target_link_libraries(assemble SIC_XE_Assembler)
