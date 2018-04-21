cmake_minimum_required(VERSION 3.10)
project(SIC_XE_Assembler C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(include)
include_directories(include/cs222)

add_executable(SIC_XE_Assembler
        include/cs222/Instruction.h
        include/cs222/Operand.h
        include/cs222/Operation.h
        include/cs222/OpTable.h
        include/cs222/Symbol.h include/cs222/IO.h src/main.cpp)
