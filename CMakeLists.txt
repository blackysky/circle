cmake_minimum_required(VERSION 4.2)
project(circle)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

file(GLOB_RECURSE HEADERS src/*.h)

add_executable(circle main.cpp ${HEADERS}
        src/domain/RelationshipGraph.cpp
        src/query/GraphQueries.cpp
        src/persistence/GraphSerializer.cpp)

find_package(nlohmann_json CONFIG REQUIRED)
find_package(Qt6 COMPONENTS Core Widgets REQUIRED)

target_link_libraries(circle PRIVATE
        nlohmann_json::nlohmann_json
        Qt6::Core
        Qt6::Widgets)

target_include_directories(circle PRIVATE src)