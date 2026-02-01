#include <SDL2/SDL.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>
#include <string>
#include <Eigen/Dense>

#include "Renderer.hpp"

Renderer::Renderer(Window &window) : window(window){}

Renderer::~Renderer(){}


void Renderer::add_mesh(const Mesh &mesh){
    Renderer::mesh_list.emplace_back(mesh);
}

void Renderer::draw_line(const point2d &p1, const point2d &p2){
    SDL_SetRenderDrawColor(Renderer::window.renderer,2,255,2,255);
    SDL_RenderDrawLine(Renderer::window.renderer, p1.x, p1.y, p2.x, p2.y);
}

vertices Renderer::translate(vertices ver, const tf_vec &tf_vec){
    
    for(auto& point : ver){
        point.x += tf_vec.x;
        point.y += tf_vec.y;
        point.z += tf_vec.z;
    }
    return ver;
}

vertices Renderer::rotate(vertices ver, const rot_vec &rot_vec){
    Eigen::Matrix3f R, Rx,Ry,Rz;
    Rx << 1,              0,              0,
          0, cos(rot_vec.x),-sin(rot_vec.x),
          0, sin(rot_vec.x), cos(rot_vec.x);

    Ry <<  cos(rot_vec.y), 0, sin(rot_vec.y),
           0,              1,              0,
          -sin(rot_vec.y), 0, cos(rot_vec.y);

    Rz << cos(rot_vec.z), -sin(rot_vec.z), 0,
          sin(rot_vec.z),  cos(rot_vec.z), 0,
          0,               0,              1;

    R = Rz*Ry*Rx;

    for(auto& point : ver){
        Eigen::Vector3f P;
        P << point.x, 
            point.y, 
            point.z;

        P = R*P;

        point.x = P[0] ;
        point.y = P[1] ;
        point.z = P[2] ;
    }
    
    
    return ver;
}


points Renderer::project2d(vertices vertices){
    points p2d; 
    float f = 400.0f;
    int x0 = Renderer::window.origin[0];
    int y0 = Renderer::window.origin[1];
    vertices = rotate(vertices, Renderer::camera_rotation);
    vertices = translate(vertices, Renderer::camera_translation);
    for(auto point : vertices){
        
        float X = point.x;
        float Y = point.y;
        float Z = point.z;

        int x_ = f*(X/Z);
        int y_ = f*(Y/Z);

        point2d point2d = {
            .x = x_ + x0 ,
            .y = y0 - y_ 
        };
        p2d.emplace_back(point2d);
        
    }
    return p2d;
}

void Renderer::draw(const Mesh &mesh){
    
    points p2d = Renderer::project2d(mesh.meshpoints);
    for(auto& tri : mesh.triangles){
        point2d a,b,c;
        a = p2d[tri.a];
        b = p2d[tri.b];
        c = p2d[tri.c];
        Renderer::draw_line(a, b);
        Renderer::draw_line(b, c);
        Renderer::draw_line(c, a);
    }
}

void Renderer::draw_all(){
    for(auto& mesh : Renderer::mesh_list){
        // Mesh m = update_camera_pose(mesh, translation, rotation);
        Renderer::draw(mesh);
    }
}

void Renderer::update_camera_pose(const tf_vec &translation, const rot_vec &rotation){
    Renderer::camera_translation = translation;
    Renderer::camera_rotation = rotation;
}