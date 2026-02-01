cmake_minimum_required(VERSION 3.15)
project(SimpleSTLviewer VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(SDL2 REQUIRED)

add_executable(SimpleSTLviewer
    main.cpp
    src/Mesh.cpp
    src/Renderer.cpp
    src/Window.cpp
)


target_include_directories(SimpleSTLviewer PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${SDL2_INCLUDE_DIRS}                      
    SYSTEM ${CMAKE_SOURCE_DIR}/thirdparty/eigen 
)

target_link_libraries(SimpleSTLviewer PRIVATE ${SDL2_LIBRARIES})