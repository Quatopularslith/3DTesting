#include <iostream>
#include <GL/glew.h>
#include <stdio.h>
#include <glfw3.h>
#include <stdlib.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include "Main.h"
#include "../graphics/Render.h"
#include "../graphics/shaders/Shaders.h"
#include "../input/Controls.h"

using namespace std;
using namespace glm;

GLFWwindow* Main::mainWindow;

int Main::height = 720;
int Main::width = 1280;

bool createWindow(){
    glfwWindowHint(GLFW_SAMPLES, 16);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    Main::mainWindow = glfwCreateWindow( 1024, 768, "Cpp3D", NULL, NULL);
    if( Main::mainWindow == NULL ){
        fprintf( stderr, "Failed to open GLFW window.\n" );
        getchar();
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(Main::mainWindow);
    return 0;
}

int main() {

    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        getchar();
        return -1;
    }

    createWindow();

    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return -1;
    }

    glfwSetInputMode(Main::mainWindow, GLFW_STICKY_KEYS, GL_TRUE);
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    Shaders shaders = Shaders();

    GLuint programID = shaders.loadShaders("shaders/Transform.shader", "shaders/ColorShader.shader");

    GLuint matrixID = glGetUniformLocation(programID, "MVP");

    Render render = Render();

    Controls controls = Controls();

    glEnable(GL_CULL_FACE);

    do{

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(programID);

        controls.computeMatricesFromInput();
        glm::mat4 projectionMatrix = controls.getProjectionMatrix();
        glm::mat4 viewMatrix = controls.getViewMatrix();
        glm::mat4 modelMatrix = glm::mat4(1.0);
        glm::mat4 mvp = projectionMatrix * viewMatrix * modelMatrix;
        glUniformMatrix4fv(matrixID, 1, GL_FALSE, &mvp[0][0]);

        render.renderScene();

        glfwSwapBuffers(Main::mainWindow);
        glfwPollEvents();

    }while(glfwGetKey(Main::mainWindow, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(Main::mainWindow) == 0);

    glfwTerminate();
    return 0;
}