cmake_minimum_required(VERSION 3.10)
project(SIC_XE_Assembler)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(include)
include_directories(include/cs222)

add_executable(SIC_XE_Assembler
        include/cs222/Instruction.h
        include/cs222/Operand.h
        include/cs222/Operation.h
        include/cs222/OpTable.h
        include/cs222/Parser.h
        src/cs222/Instruction.cpp
        src/cs222/Operand.cpp
        src/cs222/Parser.cpp
        src/cs222/pass1.cpp
        src/cs222/Utility.cpp
        src/cs222/Validator.cpp
        )
