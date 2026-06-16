cmake_minimum_required(VERSION 3.10)
project(openssl LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenSSL REQUIRED)
find_package(Poco REQUIRED COMPONENTS Foundation Util Crypto)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(openssl
        src/crypto/digest.cpp
        src/crypto/digest.h
        src/crypto/sha1_digest.cpp
        src/crypto/sha1_digest.h
        src/tools/tools.cpp
        src/tools/tools.h
        src/util/base64.cpp
        src/util/base64.h
        src/util/types.cpp
        src/util/types.h
)

target_link_libraries(openssl PUBLIC 
        OpenSSL::Crypto
        Poco::Crypto
        Poco::Util
        Poco::Foundation
)

target_include_directories(openssl PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

enable_testing()

add_executable(openssl_tests
        src/crypto/ut/digest_ut.cpp
        src/tools/ut/tools_ut.cpp
        src/util/ut/base64_ut.cpp
)

target_link_libraries(openssl_tests PRIVATE
        openssl
        gtest_main
        ${Poco_LIBRARIES}
        Poco::Foundation
        Poco::Util
        Poco::Crypto
)

include(GoogleTest)
gtest_discover_tests(openssl_tests)
