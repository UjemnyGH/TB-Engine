#pragma once

namespace tbe
{
    struct vec2
    {
        float x;
        float y;

        vec2()
        {

        }

        template<typename T>
        vec2(T vX, T vY)
        {
            x = vX;
            y = vY;
        }
    };

    struct vec3
    {
        float x;
        float y;
        float z;

        vec3()
        {

        }

        template<typename T>
        vec3(T vX, T vY, T vZ)
        {
            x = vX;
            y = vY;
            z = vZ;
        }
    };

    struct vec4
    {
        float x;
        float y;
        float z;
        float w;

        vec4()
        {

        }

        template<typename T>
        vec4(T vX, T vY, T vZ, T vW)
        {
            x = vX;
            y = vY;
            z = vZ;
            w = vW;
        }
    };

    struct dvec2
    {
        double x;
        double y;

        dvec2()
        {

        }

        template<typename T>
        dvec2(T vX, T vY)
        {
            x = vX;
            y = vY;
        }
    };

    struct dvec3
    {
        double x;
        double y;
        double z;

        dvec3()
        {

        }

        template<typename T>
        dvec3(T vX, T vY, T vZ)
        {
            x = vX;
            y = vY;
            z = vZ;
        }
    };

    struct dvec4
    {
        double x;
        double y;
        double z;
        double w;

        dvec4()
        {

        }

        template<typename T>
        dvec4(T vX, T vY, T vZ, T vW)
        {
            x = vX;
            y = vY;
            z = vZ;
            w = vW;
        }
    };   
}
