cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLTemplate LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# Include Box2D
FetchContent_Declare(box2d
    GIT_REPOSITORY https://github.com/erincatto/box2d.git
    GIT_TAG v2.4.1  # Replace with the desired version
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(box2d)

set(RESOURCE_DIR ${CMAKE_SOURCE_DIR}/res)
set(GENERATED_HEADER ${CMAKE_BINARY_DIR}/embedded_resources.hpp)

add_custom_command(
    PRE_BUILD
    OUTPUT ${GENERATED_HEADER}
    COMMAND ${CMAKE_SOURCE_DIR}/src/Engine/ResourceHandler/generate_header.exe ${RESOURCE_DIR} ${GENERATED_HEADER}
    DEPENDS ${RESOURCE_DIR} {CMAKE_SOURCE_DIR}/src/Engine/ResourceHandler/generate_header.exe
    COMMENT "Compressing resources and generating header from resource directory"
)

add_custom_target(GenerateResourceHeader ALL DEPENDS ${GENERATED_HEADER})

include_directories(${CMAKE_SOURCE_DIR}/external/miniz)

# Gather all source and header files from the src directory
file(GLOB_RECURSE ALL_FILES "${CMAKE_SOURCE_DIR}/src/*")

# Add these files to the executable
add_executable(main ${ALL_FILES})

# Function to create a single filter that includes both sources and headers
function(create_source_group FILES BASE_DIR)
    foreach(FILE ${FILES})
        # Get the directory path relative to the base directory (CMAKE_SOURCE_DIR/src)
        get_filename_component(FILE_PATH "${FILE}" PATH)
        file(RELATIVE_PATH REL_PATH "${BASE_DIR}" "${FILE_PATH}")

        # Replace "/" with "\\" to create proper Visual Studio filters
        string(REPLACE "/" "\\" FILTER_GROUP "${REL_PATH}")

        # Create the source group (same filter for all files)
        source_group("${FILTER_GROUP}" FILES "${FILE}")
    endforeach()
endfunction()

# Call the function for all files (both sources and headers)
create_source_group("${ALL_FILES}" "${CMAKE_SOURCE_DIR}/src")

add_dependencies(main GenerateResourceHeader)
target_include_directories(main PRIVATE ${CMAKE_BINARY_DIR})
target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(main PRIVATE sfml-graphics box2d)
target_compile_features(main PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET main
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:main>
        VERBATIM)
endif()
