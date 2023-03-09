#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"

// SQUARE
Mesh* object2D::CreateSquare(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), glm::vec3(color.x - 0.5,color.y - 0.3, color.z - 0.1)),
        VertexFormat(corner + glm::vec3(0, length, 0), glm::vec3(color.x - 0.5,color.y - 0.3, color.z - 0.1))
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

// TRIANGLE
Mesh* object2D::CreateTriangle(
    const std::string& name,
    glm::mat3 coords,
    glm::vec3 color,
    bool fill)
{
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(glm::vec3(coords[0]), color),
        VertexFormat(glm::vec3(coords[1]), color),
        VertexFormat(glm::vec3(coords[2]),glm::vec3(color.x - 0.5,color.y - 0.3, color.z - 0.3))
    };
    std::vector<unsigned int> indices =
    {
        0, 1, 2
    };

    Mesh* triangle = new Mesh(name);

    triangle->InitFromData(vertices, indices);
    return triangle;
}

Mesh* object2D::CreateCircle(
    const std::string& name,
    glm::vec3 coords,
    float radius,
    glm::vec3 color,
    bool fill)
{
    int i;
    int triangleAmount = 20; //# of triangles used to draw circle
    GLfloat twicePi = 2.0f * 3.141592653589793238f;

    Mesh* circle = new Mesh(name);

    std::vector<VertexFormat> vertices = {
        VertexFormat(glm::vec3(coords.x, coords.y, 0), glm::vec3(color.x - 0.5,color.y - 0.3, color.z - 0.3)),
        VertexFormat(glm::vec3(coords.x + (radius * cos(0 * twicePi / triangleAmount)), coords.y + (radius * sin(0 * twicePi / triangleAmount)), 0), color),
        VertexFormat(glm::vec3(coords.x + (radius * cos(1 * twicePi / triangleAmount)), coords.y + (radius * sin(1 * twicePi / triangleAmount)), 0), color),
        VertexFormat(glm::vec3(coords.x + (radius * cos(2 * twicePi / triangleAmount)), coords.y + (radius * sin(2 * twicePi / triangleAmount)), 0), color),
        VertexFormat(glm::vec3(coords.x + (radius * cos(3 * twicePi / triangleAmount)), coords.y + (radius * sin(3 * twicePi / triangleAmount)), 0), color),
        VertexFormat(glm::vec3(coords.x + (radius * cos(4 * twicePi / triangleAmount)), coords.y + (radius * sin(4 * twicePi / triangleAmount)), 0), color),

        VertexFormat(glm::vec3(coords.x + (radius * cos(5 * twicePi / triangleAmount)), coords.y + (radius * sin(5 * twicePi / triangleAmount)), 0), color),
        VertexFormat(glm::vec3(coords.x + (radius * cos(6 * twicePi / triangleAmount)), coords.y + (radius * sin(6 * twicePi / triangleAmount)), 0), color),
        VertexFormat(glm::vec3(coords.x + (radius * cos(7 * twicePi / triangleAmount)), coords.y + (radius * sin(7 * twicePi / triangleAmount)), 0), color),
        VertexFormat(glm::vec3(coords.x + (radius * cos(8 * twicePi / triangleAmount)), coords.y + (radius * sin(8 * twicePi / triangleAmount)), 0), color),
        VertexFormat(glm::vec3(coords.x + (radius * cos(9 * twicePi / triangleAmount)), coords.y + (radius * sin(9 * twicePi / triangleAmount)), 0), color),

        VertexFormat(glm::vec3(coords.x + (radius * cos(10 * twicePi / triangleAmount)), coords.y + (radius * sin(10 * twicePi / triangleAmount)), 0), color),
        VertexFormat(glm::vec3(coords.x + (radius * cos(11 * twicePi / triangleAmount)), coords.y + (radius * sin(11 * twicePi / triangleAmount)), 0), color),
        VertexFormat(glm::vec3(coords.x + (radius * cos(12 * twicePi / triangleAmount)), coords.y + (radius * sin(12 * twicePi / triangleAmount)), 0), color),
        VertexFormat(glm::vec3(coords.x + (radius * cos(13 * twicePi / triangleAmount)), coords.y + (radius * sin(13 * twicePi / triangleAmount)), 0), color),
        VertexFormat(glm::vec3(coords.x + (radius * cos(14 * twicePi / triangleAmount)), coords.y + (radius * sin(14 * twicePi / triangleAmount)), 0), color),

        VertexFormat(glm::vec3(coords.x + (radius * cos(15 * twicePi / triangleAmount)), coords.y + (radius * sin(15 * twicePi / triangleAmount)), 0), color),
        VertexFormat(glm::vec3(coords.x + (radius * cos(16 * twicePi / triangleAmount)), coords.y + (radius * sin(16 * twicePi / triangleAmount)), 0), color),
        VertexFormat(glm::vec3(coords.x + (radius * cos(17 * twicePi / triangleAmount)), coords.y + (radius * sin(17 * twicePi / triangleAmount)), 0), color),
        VertexFormat(glm::vec3(coords.x + (radius * cos(18 * twicePi / triangleAmount)), coords.y + (radius * sin(18 * twicePi / triangleAmount)), 0), color),
        VertexFormat(glm::vec3(coords.x + (radius * cos(19 * twicePi / triangleAmount)), coords.y + (radius * sin(19 * twicePi / triangleAmount)), 0), color),
    
        VertexFormat(glm::vec3(coords.x + (radius * cos(20 * twicePi / triangleAmount)), coords.y + (radius * sin(20 * twicePi / triangleAmount)), 0), color)
   
   };

    std::vector<unsigned int> indices =  
   {
        0, 1, 2,
        1, 2, 3,
        2, 3, 4,
        3, 4, 5,
        4, 5, 6,
        5, 6, 7,
        6, 7, 8,
        7, 8, 9,
        8, 9, 10,
        9, 10, 11,
        10, 11, 12,
        11, 12, 13,
        12, 13, 14,
        13, 14, 15,
        14, 15, 16,
        15, 16, 17,
        16, 17, 18,
        17, 18, 19,
        18, 19, 20,
        20, 0, 1,

        //fill
        0, 2, 3,
        0, 3, 4,
        0,4,5,
        0,5,6,
        0, 6,7, 
        0, 7,8,
        0,8,9,
        0,9,10,
        0,10,11,
        0,11,12,
        0,12,13,
        0,13,14,
        0,14,15,
        0,15,16,
        0,16,17,
        0,17,18,
        0,18,19,
        0,19,20
    };

    circle->InitFromData(vertices, indices);
    return circle;
}


// HALO
Mesh * object2D::CreateHalo(
    const std::string & name,
    glm::vec3 coords,
    float radius,
    glm::vec3 color,
    bool fill)
{
    int i;
    int triangleAmount = 20; //# of triangles used to draw circle
    GLfloat twicePi = 2.0f * 3.141592653589793238f;

    Mesh* halo = new Mesh(name);

    std::vector<VertexFormat> vertices = {
        VertexFormat(glm::vec3(coords.x + (radius * cos(0 * twicePi / triangleAmount)), coords.y + (radius * sin(0 * twicePi / triangleAmount)), 0), color),
        VertexFormat(glm::vec3(coords.x + (radius * cos(1 * twicePi / triangleAmount)), coords.y + (radius * sin(1 * twicePi / triangleAmount)), 0), color),
        VertexFormat(glm::vec3(coords.x + (radius * cos(2 * twicePi / triangleAmount)), coords.y + (radius * sin(2 * twicePi / triangleAmount)), 0), color),
        VertexFormat(glm::vec3(coords.x + (radius * cos(3 * twicePi / triangleAmount)), coords.y + (radius * sin(3 * twicePi / triangleAmount)), 0), color),
        VertexFormat(glm::vec3(coords.x + (radius * cos(4 * twicePi / triangleAmount)), coords.y + (radius * sin(4 * twicePi / triangleAmount)), 0), color),

        VertexFormat(glm::vec3(coords.x + (radius * cos(5 * twicePi / triangleAmount)), coords.y + (radius * sin(5 * twicePi / triangleAmount)), 0), color),
        VertexFormat(glm::vec3(coords.x + (radius * cos(6 * twicePi / triangleAmount)), coords.y + (radius * sin(6 * twicePi / triangleAmount)), 0), color),
        VertexFormat(glm::vec3(coords.x + (radius * cos(7 * twicePi / triangleAmount)), coords.y + (radius * sin(7 * twicePi / triangleAmount)), 0), color),
        VertexFormat(glm::vec3(coords.x + (radius * cos(8 * twicePi / triangleAmount)), coords.y + (radius * sin(8 * twicePi / triangleAmount)), 0), color),
        VertexFormat(glm::vec3(coords.x + (radius * cos(9 * twicePi / triangleAmount)), coords.y + (radius * sin(9 * twicePi / triangleAmount)), 0), color),

        VertexFormat(glm::vec3(coords.x + (radius * cos(10 * twicePi / triangleAmount)), coords.y + (radius * sin(10 * twicePi / triangleAmount)), 0), color),
        VertexFormat(glm::vec3(coords.x + (radius * cos(11 * twicePi / triangleAmount)), coords.y + (radius * sin(11 * twicePi / triangleAmount)), 0), color),
        VertexFormat(glm::vec3(coords.x + (radius * cos(12 * twicePi / triangleAmount)), coords.y + (radius * sin(12 * twicePi / triangleAmount)), 0), color),
        VertexFormat(glm::vec3(coords.x + (radius * cos(13 * twicePi / triangleAmount)), coords.y + (radius * sin(13 * twicePi / triangleAmount)), 0), color),
        VertexFormat(glm::vec3(coords.x + (radius * cos(14 * twicePi / triangleAmount)), coords.y + (radius * sin(14 * twicePi / triangleAmount)), 0), color),

        VertexFormat(glm::vec3(coords.x + (radius * cos(15 * twicePi / triangleAmount)), coords.y + (radius * sin(15 * twicePi / triangleAmount)), 0), color),
        VertexFormat(glm::vec3(coords.x + (radius * cos(16 * twicePi / triangleAmount)), coords.y + (radius * sin(16 * twicePi / triangleAmount)), 0), color),
        VertexFormat(glm::vec3(coords.x + (radius * cos(17 * twicePi / triangleAmount)), coords.y + (radius * sin(17 * twicePi / triangleAmount)), 0), color),
        VertexFormat(glm::vec3(coords.x + (radius * cos(18 * twicePi / triangleAmount)), coords.y + (radius * sin(18 * twicePi / triangleAmount)), 0), color),
        VertexFormat(glm::vec3(coords.x + (radius * cos(19 * twicePi / triangleAmount)), coords.y + (radius * sin(19 * twicePi / triangleAmount)), 0), color),

        VertexFormat(glm::vec3(coords.x + (radius * cos(20 * twicePi / triangleAmount)), coords.y + (radius * sin(20 * twicePi / triangleAmount)), 0), color)
    };

    std::vector<unsigned int> indices = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };

    halo->InitFromData(vertices, indices);
    return halo;
}
//EMPTY CIRCLE
Mesh* object2D::CreateEmptyCircle(
    const std::string& name,
    glm::vec3 coords,
    float radius,
    glm::vec3 color,
    bool fill)
{
    int i;
    int triangleAmount = 20; //# of triangles used to draw circle
    GLfloat twicePi = 2.0f * 3.141592653589793238f;

    Mesh* circle = new Mesh(name);

    std::vector<VertexFormat> vertices = {
        VertexFormat(glm::vec3(coords.x, coords.y, 0), color),
        VertexFormat(glm::vec3(coords.x + (radius * cos(0 * twicePi / triangleAmount)), coords.y + (radius * sin(0 * twicePi / triangleAmount)), 0), color),
        VertexFormat(glm::vec3(coords.x + (radius * cos(1 * twicePi / triangleAmount)), coords.y + (radius * sin(1 * twicePi / triangleAmount)), 0), color),
        VertexFormat(glm::vec3(coords.x + (radius * cos(2 * twicePi / triangleAmount)), coords.y + (radius * sin(2 * twicePi / triangleAmount)), 0), color),
        VertexFormat(glm::vec3(coords.x + (radius * cos(3 * twicePi / triangleAmount)), coords.y + (radius * sin(3 * twicePi / triangleAmount)), 0), color),
        VertexFormat(glm::vec3(coords.x + (radius * cos(4 * twicePi / triangleAmount)), coords.y + (radius * sin(4 * twicePi / triangleAmount)), 0), color),

        VertexFormat(glm::vec3(coords.x + (radius * cos(5 * twicePi / triangleAmount)), coords.y + (radius * sin(5 * twicePi / triangleAmount)), 0), color),
        VertexFormat(glm::vec3(coords.x + (radius * cos(6 * twicePi / triangleAmount)), coords.y + (radius * sin(6 * twicePi / triangleAmount)), 0), color),
        VertexFormat(glm::vec3(coords.x + (radius * cos(7 * twicePi / triangleAmount)), coords.y + (radius * sin(7 * twicePi / triangleAmount)), 0), color),
        VertexFormat(glm::vec3(coords.x + (radius * cos(8 * twicePi / triangleAmount)), coords.y + (radius * sin(8 * twicePi / triangleAmount)), 0), color),
        VertexFormat(glm::vec3(coords.x + (radius * cos(9 * twicePi / triangleAmount)), coords.y + (radius * sin(9 * twicePi / triangleAmount)), 0), color),

        VertexFormat(glm::vec3(coords.x + (radius * cos(10 * twicePi / triangleAmount)), coords.y + (radius * sin(10 * twicePi / triangleAmount)), 0), color),
        VertexFormat(glm::vec3(coords.x + (radius * cos(11 * twicePi / triangleAmount)), coords.y + (radius * sin(11 * twicePi / triangleAmount)), 0), color),
        VertexFormat(glm::vec3(coords.x + (radius * cos(12 * twicePi / triangleAmount)), coords.y + (radius * sin(12 * twicePi / triangleAmount)), 0), color),
        VertexFormat(glm::vec3(coords.x + (radius * cos(13 * twicePi / triangleAmount)), coords.y + (radius * sin(13 * twicePi / triangleAmount)), 0), color),
        VertexFormat(glm::vec3(coords.x + (radius * cos(14 * twicePi / triangleAmount)), coords.y + (radius * sin(14 * twicePi / triangleAmount)), 0), color),

        VertexFormat(glm::vec3(coords.x + (radius * cos(15 * twicePi / triangleAmount)), coords.y + (radius * sin(15 * twicePi / triangleAmount)), 0), color),
        VertexFormat(glm::vec3(coords.x + (radius * cos(16 * twicePi / triangleAmount)), coords.y + (radius * sin(16 * twicePi / triangleAmount)), 0), color),
        VertexFormat(glm::vec3(coords.x + (radius * cos(17 * twicePi / triangleAmount)), coords.y + (radius * sin(17 * twicePi / triangleAmount)), 0), color),
        VertexFormat(glm::vec3(coords.x + (radius * cos(18 * twicePi / triangleAmount)), coords.y + (radius * sin(18 * twicePi / triangleAmount)), 0), color),
        VertexFormat(glm::vec3(coords.x + (radius * cos(19 * twicePi / triangleAmount)), coords.y + (radius * sin(19 * twicePi / triangleAmount)), 0), color),

        VertexFormat(glm::vec3(coords.x + (radius * cos(20 * twicePi / triangleAmount)), coords.y + (radius * sin(20 * twicePi / triangleAmount)), 0), color)

    };

    std::vector<unsigned int> indices =
    {
         0, 1, 2,
         1, 2, 3,
         2, 3, 4,
          3, 4, 5,
          4, 5, 6,
          5, 6, 7,
          6, 7, 8,
          7, 8, 9,
          8, 9, 10,
          9, 10, 11,
          10, 11, 12,
          11, 12, 13,
          12, 13, 14,
          13, 14, 15,
          14, 15, 16,
          15, 16, 17,
          16, 17, 18,
          17, 18, 19,
          18, 19, 20,
          20, 0, 1,

          5, 6, 0,
          12, 13, 0,
          17, 18, 0
    };

    circle->InitFromData(vertices, indices);
    return circle;
}
