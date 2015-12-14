//
// Created by Razim on 12/11/2015.
//

#ifndef CPP3D_SHADERS_H
#define CPP3D_SHADERS_H


#include <GL/gl.h>

class Shaders {
public:

    Shaders();
    ~Shaders();

    GLuint loadShaders(const char * vertexFilePath, const char * fragFilePath);

};


#endif //CPP3D_SHADERS_H
