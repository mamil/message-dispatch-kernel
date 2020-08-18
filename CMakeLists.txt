cmake_minimum_required(VERSION 2.8)

set(CXX_FLAGS
    -std=c++11
    -pthread
)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread" CACHE STRING "Set C++ Compiler Flags" FORCE)

project (message-dispatch-kernel)

set(SOURCES
    ./main.cpp
    ./ClientKernel.cpp
    command/ServiceCommand.cpp
    globe/Kernel.cpp
    service/Service.cpp
    service/ServiceGold.cpp
)

# for win
IF (WIN32)
	set(SOURCES_WIN
        globe/ExceptionBase.cpp
    )
ENDIF ()

add_executable(message-dispatch-kernel ${SOURCES} ${SOURCES_WIN})

target_include_directories(message-dispatch-kernel
    PRIVATE
        ${PROJECT_SOURCE_DIR}
)
