cmake_minimum_required(VERSION 4.2)
project(circle LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(nlohmann_json CONFIG REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

# ChatGPT says that GLOB is isn't used in real-world projects
# due to issues with control and predictability.
# Heading are added either explicitly or via generation.
# TODO: Something to look into.
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.h)

add_executable(circle
        main.cpp
        ${SOURCES}
)

target_link_libraries(circle PRIVATE
        nlohmann_json::nlohmann_json
        Qt6::Core
        Qt6::Widgets
)

target_include_directories(circle PRIVATE src)