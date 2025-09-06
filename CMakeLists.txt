cmake_minimum_required(VERSION 3.10)
project(AsteroidEscape)

set(CMAKE_CXX_STANDARD 17)

# Collect all .cpp files
file(GLOB SOURCES
    "${CMAKE_SOURCE_DIR}/AsteroidEscape/Source/*.cpp"
)

add_executable(AsteroidEscape ${SOURCES})

# Tell CMAKE where to find SFML
set(SFML_DIR "${CMAKE_SOURCE_DIR}/AsteroidEscape/External/SFML/lib/cmake/SFML")

# Find required SFML packages. 'network' is not included because it's not used.
find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)


# Add SFML include directory
target_include_directories(AsteroidEscape PRIVATE
    "${CMAKE_SOURCE_DIR}/AsteroidEscape/External/SFML/include"
)


# List of SFML COMPONENTS required without config suffix
set(SFML_COMPONENTS
    sfml-system
    sfml-window
    sfml-graphics
    sfml-audio
)

target_link_libraries(AsteroidEscape
    ${SFML_COMPONENTS}
)

# -----------------------------
# Copy Assets to build output
# -----------------------------
add_custom_command(TARGET AsteroidEscape POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/AsteroidEscape/Assets"
    "${CMAKE_BINARY_DIR}/Assets"
)




# Copy SFML DLLs based on build type
foreach(dll ${SFML_COMPONENTS})
    add_custom_command(TARGET AsteroidEscape POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<$<CONFIG:Debug>:${CMAKE_SOURCE_DIR}/AsteroidEscape/External/SFML/bin/${dll}-d-2.dll>"
            "$<$<CONFIG:Release>:${CMAKE_SOURCE_DIR}/AsteroidEscape/External/SFML/bin/${dll}-2.dll>"
            $<TARGET_FILE_DIR:AsteroidEscape>
    )
endforeach()

# Copy OpenAL DLL (same for all configurations)
add_custom_command(TARGET AsteroidEscape POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/AsteroidEscape/External/SFML/bin/openal32.dll"
        $<TARGET_FILE_DIR:AsteroidEscape>
)