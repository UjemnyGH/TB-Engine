#pragma once

#include <vector>
#include "TB_buffers.h"
#include "TB_shaders.h"
#include "TB_engine_variables.h"

namespace tbe
{
    class TB_terrain
    {
    private:
        Vao vao;
        Vbo vbo[2];
        Ebo ebo;
        Shader sh;

        float cpX, cpY, cpZ, csX, csY, csZ, crX, crY, crZ;

        std::vector<float> vertices;
        std::vector<unsigned int> indices;
        std::vector<color> col; 

    public:
        
    };

    typedef TB_terrain Terrain;  
}