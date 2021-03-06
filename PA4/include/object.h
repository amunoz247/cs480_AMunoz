#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "graphics_headers.h"

/*struct Vert {
    GLfloat position[3];
    GLfloat color[3];
};*/

class Object
{
  public:
    Object();
    ~Object();
    bool loadObjFile(const char *fileName, std::vector < glm::vec3 > & outVertices,
        std::vector < glm::vec2 > & outUVS,
        std::vector < glm::vec3 > & outNormals);
    void Update(unsigned int dt);
    void Render();

    glm::mat4 GetModel();

    //Vert geometry[3];

  private:
    glm::mat4 model;
    //std::vector<Vertex> Vertices;
    //std::vector<unsigned int> Indices;
    std::vector< glm::vec3 > Vertices;
    std::vector< glm::vec2 > UVS;
    std::vector< glm::vec3 > Normals;
    GLuint VB;
    GLuint IB;

    float angle;
};

#endif /* OBJECT_H */
