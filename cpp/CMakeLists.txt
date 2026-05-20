cmake_minimum_required(VERSION 3.15)

project(cpp)

find_package(Boost REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 17)

add_executable(main
    src/main.cpp
)

target_link_libraries(main PRIVATE
    Boost::boost
    nlohmann_json::nlohmann_json
)