cmake_minimum_required(VERSION 2.8)
project(CryptoPals)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#Development
add_executable(Dev main.cpp)


# Challenge1
#HexBase
add_executable(HexBase64 Challenge1/HexBase64/main.cpp Challenge1/HexBase64/HexBase64.cpp Challenge1/HexBase64/HexBase64.h)

#XOR Converter
add_executable(XORED Challenge1/FixedXOR/main.cpp Challenge1/FixedXOR/Converter.cpp Challenge1/FixedXOR/Converter.h)

#SingleByteXOR
add_executable(SingleByteXOR Challenge1/SingleByteXOR/main.cpp Challenge1/SingleByteXOR/Converter.cpp Challenge1/SingleByteXOR/Converter.h)

#DetectSingleCharXOR
add_executable(DetectSingleCharXOR Challenge1/DetectSingleCharXOR/main.cpp Challenge1/DetectSingleCharXOR/Converter.cpp Challenge1/DetectSingleCharXOR/Converter.h)


#RepeatingKeyXOR
add_executable(RepeatingKeyXOR Challenge1/RepeatingKeyXOR/main.cpp Challenge1/RepeatingKeyXOR/Encrypter.cpp Challenge1/RepeatingKeyXOR/Encrypter.h)


#Break Repeating XOR
add_executable(BreakRepeatingXOR Challenge1/BreakRepeatingXOR/main.cpp
        Challenge1/BreakRepeatingXOR/XORBreaker.cpp Challenge1/BreakRepeatingXOR/XORBreaker.h
        Challenge1/BreakRepeatingXOR/LanguageChecker.h Challenge1/BreakRepeatingXOR/LanguageChecker.cpp
        )
