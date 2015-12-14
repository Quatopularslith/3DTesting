//
// Created by Razim on 12/11/2015.
//

#include <GL/glew.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "Shaders.h"

using namespace std;

GLuint ProgramID;

Shaders::Shaders() { }
Shaders::~Shaders() {
    glDeleteProgram(ProgramID);
    cout << "Shaders deconstructed" << endl;
}

GLuint Shaders::loadShaders(const char * vertexFilePath, const char * fragFilePath) {

    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    string vertexShaderCode;
    ifstream vertexShaderStream(vertexFilePath, ios::in);

    if(vertexShaderStream.is_open()){
        string line = "";
        while(getline(vertexShaderStream, line))
            vertexShaderCode += "\n" + line;
        vertexShaderStream.close();
    }else{
        printf("Failed to open %s", vertexFilePath);
        getchar();
    }

    string fragShaderCode;
    ifstream fragShaderStream(fragFilePath, ios::in);
    if(fragShaderStream.is_open()){
        string line = "";
        while(getline(fragShaderStream, line))
            fragShaderCode += "\n" + line;
        fragShaderStream.close();
    }

    GLint result = GL_FALSE;
    int infoLogLength;

    printf("Compiling shader: %s\n", vertexFilePath);
    char const * vertexSourcePointer = vertexShaderCode.c_str();
    glShaderSource(vertexShaderID, 1, &vertexSourcePointer, NULL);
    glCompileShader(vertexShaderID);

    glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);

    if(infoLogLength > 0){
        vector<char> vertexShaderErrorMessage(infoLogLength+1);
        glGetShaderInfoLog(vertexShaderID, infoLogLength, NULL, &vertexShaderErrorMessage[0]);
        printf("%s\n", &vertexShaderErrorMessage[0]);
    }

    printf("Compiling shader: %s\n", fragFilePath);
    char const * fragSourcePointer = fragShaderCode.c_str();
    glShaderSource(fragShaderID, 1, &fragSourcePointer, NULL);
    glCompileShader(fragShaderID);

    glGetShaderiv(fragShaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if(infoLogLength > 0){
        vector<char> fragShaderErrorMessage(infoLogLength+1);
        glGetShaderInfoLog(fragShaderID, infoLogLength, NULL, &fragShaderErrorMessage[0]);
        printf("%s\n", &fragShaderErrorMessage[0]);
    }

    cout << "Linking program" << endl;

    GLuint programID = glCreateProgram();
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragShaderID);
    glLinkProgram(programID);

    glGetProgramiv(programID, GL_LINK_STATUS, &result);
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if(infoLogLength > 0){
        vector<char> programErrorMessage(infoLogLength+1);
        glGetProgramInfoLog(programID, infoLogLength, NULL, &programErrorMessage[0]);
        printf("%s\n", &programErrorMessage[0]);
    }

    glDetachShader(programID, vertexShaderID);
    glDetachShader(programID, fragShaderID);
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragShaderID);

    ProgramID = programID;
    return programID;

}