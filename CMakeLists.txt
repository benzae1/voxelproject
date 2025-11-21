cmake_minimum_required(VERSION 3.16)
project(OpenGLProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ------------------------------
# Paths to GLFW and GLAD
# ------------------------------

# GLFW include + library
set(GLFW_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/glfw-3.4/include")
set(GLFW_LIB_DIR "${CMAKE_SOURCE_DIR}/glfw-3.4/build/src/Release")

# GLAD include + source file
set(GLAD_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(GLAD_SRC "${CMAKE_SOURCE_DIR}/src/glad.c")

# ------------------------------
# Build executable
# ------------------------------

file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS "src/*.cpp" "include/*.hpp")

add_executable(OpenGLProject
    ${PROJECT_SOURCES}
    ${GLAD_SRC}
)


file(COPY ${CMAKE_SOURCE_DIR}/shaders
     DESTINATION ${CMAKE_BINARY_DIR})

# ------------------------------
# Include directories
# ------------------------------
target_include_directories(OpenGLProject PRIVATE
    ${GLFW_INCLUDE_DIR}
    ${GLAD_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/include
)

# ------------------------------
# Link libraries
# ------------------------------
target_link_directories(OpenGLProject PRIVATE
    ${GLFW_LIB_DIR}
)

target_link_libraries(OpenGLProject
    glfw3
    opengl32    # Required on Windows
)
