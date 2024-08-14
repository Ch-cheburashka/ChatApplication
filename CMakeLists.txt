cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(ChatApplication)

add_library(thread_manager
            source/thread_manager.cpp
)

add_library(tcp_server
        source/tcp_server.cpp
)

add_library(client
            source/client.cpp
)

add_library(tcp_client
        source/tcp_client.cpp
)

add_library(server
        source/server.cpp
)

target_include_directories(client PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_include_directories(thread_manager PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_include_directories(server PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_include_directories(tcp_server PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_include_directories(tcp_client PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

add_library(i_client INTERFACE)

target_include_directories(i_client INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

add_executable(cli_server cli/cli_server.cpp)

add_executable(cli_client cli/cli_client.cpp)

target_link_libraries(cli_client tcp_client client)

target_link_libraries(cli_server tcp_server server)

target_link_libraries(tcp_server thread_manager)