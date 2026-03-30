cmake_minimum_required(VERSION 4.2)
project(circle)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE HEADERS src/*.h)

add_executable(circle main.cpp ${HEADERS}
        src/domain/RelationshipGraph.cpp
        src/query/GraphQueries.cpp
        src/persistence/GraphSerializer.cpp)

find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(circle PRIVATE nlohmann_json::nlohmann_json)
target_include_directories(circle PRIVATE src)