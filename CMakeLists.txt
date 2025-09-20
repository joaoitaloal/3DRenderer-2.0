cmake_minimum_required(VERSION 3.14)
project(3DRenderer-2.0)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SRC_FILES "src/*.cpp")

add_executable(Renderer ${SRC_FILES})

include_directories(dependencies/include)

target_include_directories(Renderer
    SYSTEM
    PRIVATE
    dependencies/include
)

# windows only
target_link_libraries(Renderer
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/lib/raylib.dll
)

add_custom_command(TARGET Renderer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/lib/raylib.dll"
        $<TARGET_FILE_DIR:Renderer>
)