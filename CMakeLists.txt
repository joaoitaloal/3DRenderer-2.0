cmake_minimum_required(VERSION 3.14)
project(Renderer)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SRC_FILES "src/*.cpp")

add_executable(Renderer ${SRC_FILES})

if(NOT WIN32)
    target_include_directories(Renderer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
    target_link_libraries(Renderer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/deps/include/libraylib.a)
else()
    include_directories(deps/include)

    # Supressing warnings from raygui
    target_include_directories(Renderer
        SYSTEM
        PRIVATE
        deps/include
    )

    target_link_libraries(Renderer
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/deps/lib/windows/raylib.dll
    )

    add_custom_command(TARGET Renderer POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_SOURCE_DIR}/deps/lib/windows/raylib.dll"
            $<TARGET_FILE_DIR:Renderer>
    )
endif()