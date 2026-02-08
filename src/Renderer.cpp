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
    SDL_RenderDrawLine(Renderer::window.renderer, p1.x, p1.y, p2.x, p2.y);
}

// vertices Renderer::translate(vertices ver, const tf_vec &tf_vec){
    
//     for(auto& point : ver){
//         point.x += tf_vec.x;
//         point.y += tf_vec.y;
//         point.z += tf_vec.z;
//     }
//     return ver;
// }

// vertices Renderer::rotate(vertices ver, const rot_vec &rot_vec){
//     Eigen::Matrix3f R, Rx,Ry,Rz;
//     Rx << 1,              0,              0,
//           0, cos(rot_vec.x),-sin(rot_vec.x),
//           0, sin(rot_vec.x), cos(rot_vec.x);

//     Ry <<  cos(rot_vec.y), 0, sin(rot_vec.y),
//            0,              1,              0,
//           -sin(rot_vec.y), 0, cos(rot_vec.y);

//     Rz << cos(rot_vec.z), -sin(rot_vec.z), 0,
//           sin(rot_vec.z),  cos(rot_vec.z), 0,
//           0,               0,              1;

//     R = Rz*Ry*Rx;

//     for(auto& point : ver){
//         Eigen::Vector3f P;
//         P << point.x, 
//             point.y, 
//             point.z;

//         P = R*P;

//         point.x = P[0] ;
//         point.y = P[1] ;
//         point.z = P[2] ;
//     }
    
    
//     return ver;
// }


point2d Renderer::project2d(const point3d &p3d){
 
    float f = 400.0f;
    int x0 = Renderer::window.origin[0];
    int y0 = Renderer::window.origin[1];
    
    Eigen::Vector3f P(p3d.x, p3d.y, p3d.z);
    
    P = camera_rotation*P + camera_translation;
    float X = P[0];
    float Y = P[1];
    float Z = P[2];

    int x_ = f*(X/Z);
    int y_ = f*(Y/Z);

   
    return {
        .x = x_ + x0 ,
        .y = y0 - y_ 
    };
}

void Renderer::draw(const Mesh &mesh){
    
    SDL_SetRenderDrawColor(Renderer::window.renderer,2,255,2,255);

    for(int i=0;i<mesh.meshpoints.size();i=i+3){

        point2d a,b,c;
        // if(i>0){
        a = project2d(mesh.meshpoints[i]);
        b = project2d(mesh.meshpoints[i+1]);
        c = project2d(mesh.meshpoints[i+2]);
        Renderer::draw_line(a, b);
        Renderer::draw_line(b, c);
        Renderer::draw_line(c, a);
        // }
    }
}

void Renderer::draw_all(){
    for(auto& mesh : Renderer::mesh_list){
        // Mesh m = update_camera_pose(mesh, translation, rotation);
        Renderer::draw(mesh);
    }
}

void Renderer::update_camera_pose(const tf_vec &translation, const rot_vec &rotation){
    
    Eigen::Matrix3f Rx, Ry, Rz;
    float cx = cos(rotation.x), sx = sin(rotation.x);
    float cy = cos(rotation.y), sy = sin(rotation.y);
    float cz = cos(rotation.z), sz = sin(rotation.z);
    Rx << 1, 0, 0, 0, cx, -sx, 0, sx, cx;
    Ry << cy, 0, sy, 0, 1, 0, -sy, 0, cy;
    Rz << cz, -sz, 0, sz, cz, 0, 0, 0, 1;

    camera_rotation = Rz * Ry * Rx;
    camera_translation << translation.x, translation.y, translation.z;
}