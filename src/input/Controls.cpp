//
// Created by Razim on 12/12/2015.
//

#include <glm.hpp>
#include <glfw3.h>
#include <gtc/matrix_transform.hpp>
#include "Controls.h"
#include "../core/Main.h"

glm::mat4 viewMatrix;
glm::mat4 projectionMatrix;

glm::mat4 Controls::getViewMatrix(){
    return viewMatrix;
}

glm::mat4 Controls::getProjectionMatrix(){
    return projectionMatrix;
};

glm::vec3 position = glm::vec3(0,0,5);
float horizontalAngle = 3.14f;
float verticalAngle = 0.0f;
float initialFoV = 45.0f;
float speed = 3.0f;
float mouseSpeed = 0.005f;

void Controls::computeMatricesFromInput(){

    static double lastTime = glfwGetTime();
    double currentTime = glfwGetTime();
    float deltaTime = float(currentTime - lastTime);

    double xpos, ypos;

    glfwGetCursorPos(Main::mainWindow, &xpos, &ypos);

    glfwSetCursorPos(Main::mainWindow, Main::width/2, Main::height/2);

    horizontalAngle += mouseSpeed * float(Main::width/2 - xpos);
    verticalAngle += mouseSpeed * float(Main::height/2 - ypos);

    glm::vec3 direction(
            cos(verticalAngle) * sin(horizontalAngle),
            sin(verticalAngle),
            cos(verticalAngle) * cos(horizontalAngle)
    );

    glm::vec3 right(
            sin(horizontalAngle - 3.14f/2.0f),
            0,
            cos(horizontalAngle - 3.14f/2.0f)
    );

    glm::vec3 up = glm::cross(right, direction);

    if(glfwGetKey(Main::mainWindow, GLFW_KEY_UP) == GLFW_PRESS){
        position += direction * deltaTime * speed;
    }

    if(glfwGetKey(Main::mainWindow, GLFW_KEY_DOWN) == GLFW_PRESS){
        position -= direction * deltaTime * speed;
    }

    if(glfwGetKey(Main::mainWindow, GLFW_KEY_RIGHT) == GLFW_PRESS){
        position += right * deltaTime * speed;
    }

    if(glfwGetKey(Main::mainWindow, GLFW_KEY_LEFT) == GLFW_PRESS){
        position -= right * deltaTime * speed;
    }

    float FoV = initialFoV;

    projectionMatrix = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);

    viewMatrix = glm::lookAt(position, position + direction, up);

    lastTime = currentTime;

}