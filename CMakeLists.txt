cmake_minimum_required(VERSION 3.16)
project(OpenGLProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ------------------------------
# Paths
# ------------------------------
set(GLFW_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/glfw-3.4/include")
set(GLFW_LIB_DIR "${CMAKE_SOURCE_DIR}/glfw-3.4/build/src/Release")

set(GLAD_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(GLAD_SRC "${CMAKE_SOURCE_DIR}/src/glad.c")

set(STB_IMAGE_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")

set(GLM_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/glm-1.0.2")

# ------------------------------
# Source files
# ------------------------------
file(GLOB_RECURSE PROJECT_SOURCES "src/*.cpp" "include/*.hpp")

# ------------------------------
# Build executable
# ------------------------------
add_executable(OpenGLProject
    ${PROJECT_SOURCES}
    ${GLAD_SRC}
)

# Copy shaders and textures
file(COPY ${CMAKE_SOURCE_DIR}/shaders DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/textures DESTINATION ${CMAKE_BINARY_DIR})

# ------------------------------
# Include directories
# ------------------------------
target_include_directories(OpenGLProject PRIVATE
    ${GLFW_INCLUDE_DIR}
    ${GLAD_INCLUDE_DIR}
    ${STB_IMAGE_INCLUDE_DIR}
    ${GLM_INCLUDE_DIR}
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
    opengl32    # Windows OpenGL
)
