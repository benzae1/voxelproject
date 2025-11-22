#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <shader.hpp>
#include <texture.hpp>
#include <mesh.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;

    // Initialise glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



    // Create window
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "GLAD not working";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);



    // Initialise glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);



    // prep for 3d
    glEnable(GL_DEPTH_TEST);


    
    //cube vertices 
    std::vector<float> cubeVertices = {
        // Back face
        -0.5f, -0.5f, -0.5f, 1,0,0, 0,0,
         0.5f, -0.5f, -0.5f, 0,1,0, 1,0,
         0.5f,  0.5f, -0.5f, 0,0,1, 1,1,
        -0.5f,  0.5f, -0.5f, 1,1,0, 0,1,

        // Front face
        -0.5f, -0.5f,  0.5f, 1,0,0, 0,0,
         0.5f, -0.5f,  0.5f, 0,1,0, 1,0,
         0.5f,  0.5f,  0.5f, 0,0,1, 1,1,
        -0.5f,  0.5f,  0.5f, 1,1,0, 0,1,

        // Left face
        -0.5f, -0.5f, -0.5f, 1,0,1, 0,0,
        -0.5f, -0.5f,  0.5f, 0,1,1, 1,0,
        -0.5f,  0.5f,  0.5f, 0,1,0, 1,1,
        -0.5f,  0.5f, -0.5f, 1,1,0, 0,1,

        // Right face
         0.5f, -0.5f, -0.5f, 1,0,1, 0,0,
         0.5f, -0.5f,  0.5f, 0,1,1, 1,0,
         0.5f,  0.5f,  0.5f, 0,1,0, 1,1,
         0.5f,  0.5f, -0.5f, 1,1,0, 0,1,

         // Bottom
         -0.5f, -0.5f, -0.5f, 1,0,1, 0,1,
          0.5f, -0.5f, -0.5f, 1,1,1, 1,1,
          0.5f, -0.5f,  0.5f, 1,1,0, 1,0,
         -0.5f, -0.5f,  0.5f, 1,0,1, 0,0,

         // Top
         -0.5f,  0.5f, -0.5f, 1,1,0, 0,1,
          0.5f,  0.5f, -0.5f, 0,1,1, 1,1,
          0.5f,  0.5f,  0.5f, 0,1,1, 1,0,
         -0.5f,  0.5f,  0.5f, 1,1,0, 0,0
    };



    std::vector<unsigned int> cubeIndices = {
        0,1,2, 2,3,0,       // back
        4,5,6, 6,7,4,       // front
        8,9,10, 10,11,8,    // left
        12,13,14, 14,15,12, // right
        16,17,18, 18,19,16, // bottom
        20,21,22, 22,23,20  // top
    };




    //Shader loading
    Shader shader("shaders/vertex.vs", "shaders/fragment.fs");



    //Texture loading
    Texture texture("textures/noise.jpg");



    // load vertices into mesh
    Mesh mesh = Mesh();
    mesh.update(cubeVertices, cubeIndices);



    // render loop
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // draw as wireframe

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();
        shader.setInt("texture1", 0);
        
        texture.bind(0);


        // Model transform
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
        shader.setMat4("model", model);

        // View transform (camera)
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
        shader.setMat4("view", view);

        // Projection (perspective)
        glm::mat4 projection = glm::perspective(
            glm::radians(45.0f),
            (float)SCR_WIDTH / (float)SCR_HEIGHT,
            0.1f,
            100.0f
        );
        shader.setMat4("projection", projection);

        mesh.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}