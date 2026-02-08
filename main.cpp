#include <iostream>

#include "include/Mesh.hpp"
#include "include/Renderer.hpp"
#include "include/Window.hpp"


int main(int argc, char* argv[]){
    
    if (argc != 4){
        std::cerr << "Usage: " << argv[0] << " <width> <height> <path>" << std::endl;
        return 1;
    }
    
    int width = std::stoi(argv[1]);
    int height = std::stoi(argv[2]);
    std::string path = argv[3];
    
    Window window;
    window.init(width, height, 10);
    
    Mesh mesh;
    mesh.loadSTL(path);
    // mesh.center_mesh();

    Renderer renderer(window);

    renderer.add_mesh(mesh);

    tf_vec cam_translation;
    rot_vec cam_rotation;

    bool running = true;

    while(running){
        window.handle_inputs(running, cam_translation, cam_rotation);
        renderer.update_camera_pose(cam_translation, cam_rotation);
        renderer.draw_all();
        window.update();
    }

    window.close();
}