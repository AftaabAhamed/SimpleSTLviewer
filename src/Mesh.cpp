#include <SDL2/SDL.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>
#include <string>
#include <Eigen/Dense>

#include "Mesh.hpp"

void Mesh::loadSTL(std::string filepath){

    std::ifstream input_file(filepath);
    std::string line;

    int vertex_count = 0;
    while(std::getline(input_file, line)){
    
        std::stringstream ss;
        ss << line;
        
        size_t found_vertex =  line.find(std::string("vertex"));
        
        if(found_vertex != std::string::npos){
                      
            std::string label;
            float x,y,z;
            ss >> label >> x >> y >> z; 
            point3d p3d = {
                .x = x,
                .y = y,
                .z = z
            };
            Mesh::meshpoints.emplace_back(p3d);

            if (vertex_count > 0 && vertex_count%3 == 0){
                Mesh::triangles.emplace_back(triangle{
                    .a = vertex_count -3,
                    .b = vertex_count -2,
                    .c = vertex_count -1
                });  
            }

            vertex_count++;
        }
    }

    Mesh::center_mesh();
}

// void Mesh::translate(const tf_vec &tf_vec){
//     for(auto &point : Mesh::meshpoints){
//         point.x += tf_vec.x;
//         point.y += tf_vec.y;
//         point.z += tf_vec.z;
//     }
// }

// void Mesh::rotate(const rot_vec &rot_vec){
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

//     for(auto &point : Mesh::meshpoints){
//         Eigen::Vector3f P;
//         P << point.x, 
//              point.y, 
//              point.z;

//         P = R*P;
//         point.x = P[0] ;
//         point.y = P[1] ;
//         point.z = P[2] ;
//     }    
// }

void Mesh::center_mesh(){
    float sumx=0.0f;
    float sumy=0.0f;
    float sumz=0.0f;
    
    tf_vec center_translation;
    
    for (auto pts : Mesh::meshpoints){
        sumx+=pts.x;
        sumy+=pts.y;
        sumz+=pts.z;
    }

    center_translation.x = -sumx/meshpoints.size();
    center_translation.y = -sumy/meshpoints.size();
    center_translation.z = -sumz/meshpoints.size();
    // Mesh::translate(center_translation);

    for (auto& pts : Mesh::meshpoints){
        pts.x += center_translation.x;
        pts.y += center_translation.y;
        pts.z += center_translation.z;
    }

}
