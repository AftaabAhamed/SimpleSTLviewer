#pragma once 

#include <vector>
#include <array>
#include <string>

struct point3d{
    float x,y,z;
};

struct triangle{
    int a,b,c;
};

struct tf_vec{
    float x,y,z;
};

struct rot_vec{
    float x,y,z;
};

using vertices = std::vector<point3d>;
using facets = std::vector<triangle>;

class Mesh {
    public:
        void loadSTL(std::string filepath = "teapot.stl");
        // void translate(const tf_vec &tf_vec);
        // void rotate(const rot_vec &rot_vec);
        void center_mesh();
        // mesh get_mesh();
        vertices meshpoints;
        facets triangles;
};