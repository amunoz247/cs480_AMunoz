#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "graphics_headers.h"

struct Vert {
    GLfloat position[3];
    GLfloat color[3];
};

class Object
{
  public:
    Object();
    ~Object();
    bool loadObjFile(const char *filename, Vert geometry[]);
    void Update(unsigned int dt);
    void Render();

    glm::mat4 GetModel();

  private:
    glm::mat4 model;
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    //std::vector<unsigned int> vertIndices, uvIndices, normIndices;
    GLuint VB;
    GLuint IB;

    float angle;
};

#endif /* OBJECT_H */
