#pragma once 

#include <Eigen/Dense>
#include <vector>
#include <array>
#include <string>
#include <SDL2/SDL.h>
#include "Mesh.hpp"
#include "Window.hpp"
struct point2d{
    int x,y;
};
using points = std::vector<point2d>;

class Renderer
{
private:
    points project2d(const vertices& vertices);
    std::vector<Mesh> mesh_list;
    Window& window;
    Eigen::Vector3f camera_translation;
    Eigen::Matrix3f camera_rotation;
public:
    Renderer(Window &window);
    ~Renderer();
    // vertices translate(vertices ver, const tf_vec &tf_vec);
    // vertices rotate(vertices ver, const rot_vec &rot_vec);
    void update_camera_pose(const tf_vec &translation, const rot_vec &rotation);
    void add_mesh(const Mesh &mesh);
    void draw(const Mesh &mesh);
    void draw_all();
    void draw_line(const point2d &p1, const point2d &p2);
};



