project(UnitTests)
set(CMAKE_CXX_STANDARD 20)

################################
# HtmlTableHandlerImpl
################################
include_directories(${UnitTests_SOURCE_DIR}/../Impl)

################################
# GTest
################################
ADD_SUBDIRECTORY(gtest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

################################
# Unit Tests
################################
# Add test cpp file
add_executable( UnitTests test.cpp HtmlTableHandlerImplTests.cpp ${UnitTests_SOURCE_DIR}/../Impl/HtmlTableHandlerImpl.cpp)
# Link test executable against gtest & gtest_main
target_link_libraries(UnitTests gtest gtest_main)
add_test( UnitTests ./UnitTests)
