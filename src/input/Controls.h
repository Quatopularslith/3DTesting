//
// Created by Razim on 12/12/2015.
//

#ifndef CPP3D_CONTROLS_H
#define CPP3D_CONTROLS_H


class Controls {
public:

    //Controls();
    //~Controls();

    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();
    void computeMatricesFromInput();

};


#endif //CPP3D_CONTROLS_H
