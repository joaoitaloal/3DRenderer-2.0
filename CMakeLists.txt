cmake_minimum_required(VERSION 3.14)
project(Renderer)

set(CMAKE_CXX_STANDARD 17)

if(NOT WIN32)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(RAYLIB REQUIRED raylib)
endif()

file(GLOB_RECURSE SRC_FILES "src/*.cpp")

add_executable(Renderer ${SRC_FILES})

if(NOT WIN32)
    target_include_directories(Renderer PRIVATE ${RAYLIB_INCLUDE_DIRS})
    target_link_libraries(Renderer PRIVATE ${RAYLIB_LIBRARIES})
    target_compile_options(Renderer PRIVATE ${RAYLIB_CFLAGS_OTHER})
else()
    include_directories(dependencies/include)

    # Supressing warnings from raygui
    target_include_directories(Renderer
        SYSTEM
        PRIVATE
        dependencies/include
    )

    target_link_libraries(Renderer
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/lib/raylib.dll
    )

    add_custom_command(TARGET Renderer POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/lib/raylib.dll"
            $<TARGET_FILE_DIR:Renderer>
    )
endif()