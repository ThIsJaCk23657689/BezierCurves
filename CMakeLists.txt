cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

set(MY_PROJECT "Bezier Curves")
set(MY_EXECUTABLE "bezier_curves")

project(${MY_PROJECT})

add_executable(${MY_EXECUTABLE})

set_target_properties(${MY_EXECUTABLE}
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
)

message(STATUS)
message(STATUS "========== Build Information ==========")
message(STATUS "\tHost System Name:         ${CMAKE_HOST_SYSTEM_NAME}")
message(STATUS "\tHost System Version:      ${CMAKE_HOST_SYSTEM_VERSION}")
message(STATUS "\tHost System Processor:    ${CMAKE_HOST_SYSTEM_PROCESSOR}")
message(STATUS)
message(STATUS "\tC Compiler:               ${CMAKE_C_COMPILER_ID} ${CMAKE_C_COMPILER_VERSION}")
message(STATUS "\tC Compiler Path:          ${CMAKE_C_COMPILER}")
message(STATUS)
message(STATUS "\tC++ Compiler:             ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "\tC++ Compiler Path:        ${CMAKE_CXX_COMPILER}")
message(STATUS)
if (MSVC)
    message(STATUS "\tMSVC Version:             ${MSVC_VERSION}")
    message(STATUS "\tMSVC Toolset:             ${MSVC_TOOLSET_VERSION}")
endif ()
message(STATUS "\tVCPKG Path:               ${CMAKE_TOOLCHAIN_FILE}")
message(STATUS)
message(STATUS "========================================")

find_package(wxWidgets CONFIG REQUIRED)
find_package(glad REQUIRED)
target_include_directories(${MY_EXECUTABLE} PRIVATE "include")
file(GLOB MY_SOURCE CONFIGURE_DEPENDS "src/*.cpp")
target_sources(${MY_EXECUTABLE} PRIVATE ${MY_SOURCE})
target_link_libraries(${MY_EXECUTABLE} PRIVATE
    wx::core wx::base wx::gl
    glad::glad
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9)
        target_link_libraries(${MY_EXECUTABLE} PRIVATE stdc++fs) # C++ filesystem
    endif ()
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_link_options(${MY_EXECUTABLE} PUBLIC /SUBSYSTEM:WINDOWS)
endif()