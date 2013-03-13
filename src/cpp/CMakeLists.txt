
CMAKE_MINIMUM_REQUIRED (VERSION 2.8)
PROJECT (C11PARSER)

# create c11 preprocessor library (libcpp)
ADD_LIBRARY (cpp cpp.c)

# create c11 preprocessor executable
ADD_EXECUTABLE (c11-cpp main.c)

# link executable with library
TARGET_LINK_LIBRARIES (c11-cpp cpp)
