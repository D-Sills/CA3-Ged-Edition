cmake_minimum_required(VERSION 3.21)
project(LastLight LANGUAGES CXX)

# Fetch and setup SFML
include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

# Add your main executable
file(GLOB_RECURSE PROJECT_SOURCES
        "${CMAKE_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_SOURCE_DIR}/src/*.h")
add_executable(LastLight ${PROJECT_SOURCES}
        src/engine/loading_screen.cpp
        src/engine/scene.h
        src/player/player.cpp
        src/player/player.h
        src/components/cmp_interactable.cpp
        src/components/cmp_interactable.h)

# Copy resources
add_custom_command(TARGET LastLight POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/res"
        $<TARGET_FILE_DIR:LastLight>/res
)
target_link_libraries(LastLight PRIVATE sfml-graphics)
target_compile_features(LastLight PRIVATE cxx_std_17)

# Windows specific options
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET LastLight POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:LastLight> $<TARGET_FILE_DIR:LastLight> COMMAND_EXPAND_LISTS)
endif()

# Add libraries
# B2D library
add_subdirectory("lib/b2d/Box2D")

# Let's simplify the include and link process for Box2D
target_include_directories(Box2D INTERFACE "lib/b2d/Box2D/")

# ECM library
file(GLOB_RECURSE ECM_SOURCES
        "${CMAKE_SOURCE_DIR}/lib/ecm/*.cpp"
        "${CMAKE_SOURCE_DIR}/lib/ecm/*.h")
add_library(lib_ecm STATIC ${ECM_SOURCES})
target_include_directories(lib_ecm INTERFACE "${CMAKE_SOURCE_DIR}/lib/ecm")

# Maths library
add_library(lib_maths INTERFACE)
target_sources(lib_maths INTERFACE "${CMAKE_SOURCE_DIR}/lib/maths/maths.h")
target_include_directories(lib_maths INTERFACE "${CMAKE_SOURCE_DIR}/lib/maths")

# Tile level loader library
file(GLOB_RECURSE TILE_LOADER_SOURCES
        "${CMAKE_SOURCE_DIR}/lib/tile_level_loader/*.cpp"
        "${CMAKE_SOURCE_DIR}/lib/tile_level_loader/*.h")
add_library(lib_tile_level_loader STATIC ${TILE_LOADER_SOURCES})
target_include_directories(lib_tile_level_loader INTERFACE "${CMAKE_SOURCE_DIR}/lib/tile_level_loader")

# World gen library (add similar block if needed)

# CSV Reader library
file(GLOB_RECURSE CSV_READER_SOURCES
        "${CMAKE_SOURCE_DIR}/lib/csv_reader/*.cpp"
        "${CMAKE_SOURCE_DIR}/lib/csv_reader/*.h")
add_library(lib_csv_reader STATIC ${CSV_READER_SOURCES})
target_include_directories(lib_csv_reader INTERFACE "${CMAKE_SOURCE_DIR}/lib/csv_reader")


# Linking libraries
target_link_libraries(LastLight PRIVATE sfml-graphics sfml-audio Box2D lib_ecm lib_maths lib_tile_level_loader)
target_link_libraries(lib_ecm sfml-graphics lib_maths)
target_link_libraries(lib_tile_level_loader sfml-graphics lib_maths)

# Installation (if needed)
install(TARGETS LastLight)

