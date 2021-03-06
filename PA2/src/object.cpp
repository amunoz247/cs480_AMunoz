#include "object.h"

Object::Object()
{  
  /*
    # Blender File for a Cube
    o Cube
    v 1.000000 -1.000000 -1.000000
    v 1.000000 -1.000000 1.000000
    v -1.000000 -1.000000 1.000000
    v -1.000000 -1.000000 -1.000000
    v 1.000000 1.000000 -0.999999
    v 0.999999 1.000000 1.000001
    v -1.000000 1.000000 1.000000
    v -1.000000 1.000000 -1.000000
    s off
    f 2 3 4
    f 8 7 6
    f 1 5 6
    f 2 6 7
    f 7 8 4
    f 1 4 8
    f 1 2 4
    f 5 8 6
    f 2 1 6
    f 3 2 7
    f 3 7 4
    f 5 1 8
  */

  Vertices = {
    {{1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 0.0f}},
    {{1.0f, -1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
    {{-1.0f, -1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
    {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 1.0f}},
    {{1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 0.0f}},
    {{1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 1.0f}},
    {{-1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 1.0f}},
    {{-1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}}
  };

  Indices = {
    2, 3, 4,
    8, 7, 6,
    1, 5, 6,
    2, 6, 7,
    7, 8, 4,
    1, 4, 8,
    1, 2, 4,
    5, 8, 6,
    2, 1, 6,
    3, 2, 7,
    3, 7, 4,
    5, 1, 8
  };

  // The index works at a 0th index
  for(unsigned int i = 0; i < Indices.size(); i++)
  {
    Indices[i] = Indices[i] - 1;
  }

  angle = 0.0f;
  rotAngle = 0.0f;

  // Set bools
  cubeOrbit = true;
  cubeOrbitReg = true;
  cubeRotation = true;
  cubeRotationReg = true;

  glGenBuffers(1, &VB);
  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

  glGenBuffers(1, &IB);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);
}

Object::~Object()
{
  Vertices.clear();
  Indices.clear();
}

void Object::Update(unsigned int dt, char input, bool newKeyIn)
{
  //Check for a keyboard input
  if (newKeyIn == true)
  {
    switch (input)
    {
      //Start/Stop planet orbit
      case 'b': // left mouse button 
        if (cubeOrbit == true)
          cubeOrbit = false;
        else if (cubeOrbit == false)
          cubeOrbit = true;
        break;
      
      // Reverse orbit
      case '/':
        if (cubeOrbitReg == true)
          cubeOrbitReg = false;
        else if (cubeOrbitReg == false)
          cubeOrbitReg = true;
        break;
        
      // Start/stop rotation
      case 'd':
        if (cubeRotation == true)
          cubeRotation = false;
        else if (cubeRotation == false)
          cubeRotation = true;
        break;
        
      // Reverse rotation
      case 'r':
        if (cubeRotationReg == true)
          cubeRotationReg = false;
        else if (cubeRotationReg == false)
          cubeRotationReg = true;
        break;
        
      //Stop/reset program
      case ' ':
        if (cubeOrbit == true || cubeOrbitReg == true ||cubeRotation == true || cubeRotationReg == true)
        {
          cubeOrbit = false;
          cubeOrbitReg = false;
          cubeRotation = false;
          cubeRotationReg = false;
        }
        else if (cubeOrbit == false && cubeOrbitReg == false && cubeRotation == false && cubeRotationReg == false)
        {
          cubeOrbit = true;
          cubeOrbitReg = true;
          cubeRotation = true;
          cubeRotationReg = true;
        }
       
      default:
        break;
    }
  }

  // Planet is orbiting and rotating
  if (cubeOrbit == true && cubeRotation == true)
  {
    // Regular orbit and rotation
    if (cubeOrbitReg == true && cubeRotationReg == true)
    {
      angle += dt * M_PI/1000;
      rotAngle += dt * M_PI/1000;
      model = (glm::rotate(glm::mat4(1.0f), (angle), glm::vec3(0.0, 12.0, 0.0)) * glm::translate(glm::mat4(1.0f), glm::vec3(4.0, 0.0, 0.0)))
              * glm::rotate(glm::mat4(1.0f), (rotAngle), glm::vec3(0.0, 12.0, 0.0));
    }

    //Reversed orbit / Normal Rotation
    else if (cubeOrbitReg == false && cubeRotationReg == true)
    {
      angle -= dt * M_PI/1000;
      rotAngle += dt * M_PI/500; // *2 to offset speed
      model = (glm::rotate(glm::mat4(1.0f), (angle), glm::vec3(0.0, 12.0, 0.0)) * glm::translate(glm::mat4(1.0f), glm::vec3(4.0, 0.0, 0.0)))
              * glm::rotate(glm::mat4(1.0f), (rotAngle), glm::vec3(0.0, 12.0, 0.0));
    }

    // Normal orbit / Reversed rotation
    else if (cubeOrbitReg == true && cubeRotationReg == false)
    {
      angle += dt * M_PI/1000;
      rotAngle -= dt * M_PI/1500; 
      model = (glm::rotate(glm::mat4(1.0f), (angle), glm::vec3(0.0, 12.0, 0.0)) * glm::translate(glm::mat4(1.0f), glm::vec3(4.0, 0.0, 0.0)))
              * glm::rotate(glm::mat4(1.0f), (rotAngle), glm::vec3(0.0, 12.0, 0.0));
    }

    // Reversed orbit / reversed rotation
    else if (cubeOrbitReg == false && cubeRotationReg == false)
    {
      angle -= dt * M_PI/1000;
      rotAngle -= dt * M_PI/1500;
      model = (glm::rotate(glm::mat4(1.0f), (angle), glm::vec3(0.0, 12.0, 0.0)) * glm::translate(glm::mat4(1.0f), glm::vec3(4.0, 0.0, 0.0)))
              * glm::rotate(glm::mat4(1.0f), (rotAngle), glm::vec3(0.0, 12.0, 0.0));
    }
  }

  // Orbiting / Not rotating
  else if (cubeOrbit == true && cubeRotation == false)
  {
    // Normal orbit
    if (cubeOrbitReg == true)
    {
      angle += dt * M_PI/1000;
      rotAngle += 0;
      model = (glm::rotate(glm::mat4(1.0f), (angle), glm::vec3(0.0, 12.0, 0.0)) * glm::translate(glm::mat4(1.0f), glm::vec3(4.0, 0.0, 0.0)))
              * glm::rotate(glm::mat4(1.0f), (rotAngle), glm::vec3(0.0, 12.0, 0.0));
    }

    // Reversed orbit
    else if (cubeOrbitReg == false)
    {
      angle -= dt * M_PI/1000;
      rotAngle += 0;
      model = (glm::rotate(glm::mat4(1.0f), (angle), glm::vec3(0.0, 12.0, 0.0)) * glm::translate(glm::mat4(1.0f), glm::vec3(4.0, 0.0, 0.0)))
              * glm::rotate(glm::mat4(1.0f), (rotAngle), glm::vec3(0.0, 12.0, 0.0));
    }
  }

  // Not orbiting / Rotating
  else if (cubeOrbit == false && cubeRotation == true)
  {
    // Normal rotation
    if (cubeRotationReg == true)
    {
      angle += 0;
      rotAngle += dt * M_PI/1000;
      model = (glm::rotate(glm::mat4(1.0f), (angle), glm::vec3(0.0, 12.0, 0.0)) * glm::translate(glm::mat4(1.0f), glm::vec3(4.0, 0.0, 0.0)))
              * glm::rotate(glm::mat4(1.0f), (rotAngle), glm::vec3(0.0, 12.0, 0.0));
    }

    // Reversed rotation
    else if (cubeRotationReg == false)
    {
      angle += 0;
      rotAngle -= dt * M_PI/1000;
      model = (glm::rotate(glm::mat4(1.0f), (angle), glm::vec3(0.0, 12.0, 0.0)) * glm::translate(glm::mat4(1.0f), glm::vec3(4.0, 0.0, 0.0)))
              * glm::rotate(glm::mat4(1.0f), (rotAngle), glm::vec3(0.0, 12.0, 0.0));
    }
  }

  // Not orbiting/rotating
  else if (cubeOrbit == false && cubeRotation == false)
  {
    angle += 0;
    rotAngle += 0;
    model = (glm::rotate(glm::mat4(1.0f), (angle), glm::vec3(0.0, 12.0, 0.0)) * glm::translate(glm::mat4(1.0f), glm::vec3(4.0, 0.0, 0.0)))
              * glm::rotate(glm::mat4(1.0f), (rotAngle), glm::vec3(0.0, 12.0, 0.0));
  }
}

glm::mat4 Object::GetModel()
{
  return model;
}

void Object::Render()
{
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,color));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);

  glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
}

