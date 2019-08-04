CMAKE_MINIMUM_REQUIRED( VERSION 2.8)
project(hpack)

# Let cmake know that this is a release build.
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# Include Directories.
include_directories(.)
include_directories(include)

add_executable(hpack include/char2hex.h include/logger.h include/hwriter.h src/char2hex.c src/logger.c src/hwriter.c src/main.c)
target_include_directories(hpack PUBLIC . include)
install(
	TARGETS hpack
	RUNTIME DESTINATION bin
)
