#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace object2D
{

    // Create square with given bottom left corner, length and color
    Mesh* CreateSquare(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    // Create triangle
    Mesh* CreateTriangle(const std::string& name, glm::mat3 coords, glm::vec3 color, bool fill = false);
    //Create circle
    Mesh* CreateCircle(const std::string& name, glm::vec3 coords, float radius, glm::vec3 color, bool fill = false);
    //Create halo
    Mesh* CreateHalo(const std::string& name, glm::vec3 coords, float radius, glm::vec3 color, bool fill = false);
    //Create empty circle
    Mesh* CreateEmptyCircle(const std::string& name, glm::vec3 coords, float radius, glm::vec3 color, bool fill = false);
}
