cmake_minimum_required(VERSION 3.20)

project(ChatSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_VERSION "1.1")

file(GLOB SOURCES "src/*.cpp")

add_library(ChatLib SHARED src/ChatServer.cpp src/ChatClient.cpp)

add_executable(ChatSystem src/main.cpp)

target_link_libraries(ChatSystem ChatLib ${Boost_LIBRARIES})

find_package(Boost 1.65 REQUIRED COMPONENTS system)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(CMAKE_INSTALL_RPATH "$ORIGIN")

set(INSTALL_DIR "${CMAKE_BINARY_DIR}/ChatSystem-Linux-${PROJECT_VERSION}")

install(TARGETS ChatSystem ChatLib
    RUNTIME DESTINATION ${INSTALL_DIR}
    LIBRARY DESTINATION ${INSTALL_DIR}
    ARCHIVE DESTINATION ${INSTALL_DIR}
)

set(CPACK_GENERATOR "TGZ")
set(CPACK_PACKAGE_NAME "ChatSystem")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_CONTACT "contact@example.com")
include(CPack)
