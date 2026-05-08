# HeadSoccer3D

A 3D 1v1 arcade soccer game built from scratch using C++ and OpenGL. The project is currently in development and focuses heavily on implementing custom engine architecture and physics rather than using existing game engines.

https://github.com/user-attachments/assets/099ddd4e-6a0e-4034-9c3e-e6771e155155  
  
*Current development state: Core physics and ECS testing.*
## Architecture & Features

This project serves as a practical implementation of low-level game engine systems:

* **Custom ECS (Entity Component System):** The game logic is decoupled from data. It uses a custom-built ECS architecture to manage game entities, improving memory layout and scalability.
* **Custom Physics Engine:** Physics calculations are implemented from scratch based on Ian Millington's *Game Physics Engine Development*. It features a basic Newton integrator, custom collision detection (spheres/AABB), and contact resolution via impulses.
* **Rendering:** Uses standard modern OpenGL (3.3+) pipeline with custom shaders.

## Tech Stack

* **Language:** C++ (C++17/20)
* **Graphics API:** OpenGL
* **Window & Input:** [GLFW](https://www.glfw.org/)
* **Function Loader:** [GLAD](https://glad.dav1d.de/)
* **Mathematics:** [GLM](https://github.com/g-truc/glm)
* **3D Model Loading:** [tinyobjloader](https://github.com/tinyobjloader/tinyobjloader)
* **Texture Loading:** [stb_image.h](https://github.com/nothings/stb/blob/master/stb_image.h)

## Controls (Testing environment)
* `W`, `A`, `S`, `D` - Move
* `Space` - Jump
* `Left ctrl` - Shoot
* `Mouse` - Look around
  
## Build Instructions

The project uses CMake for the build process.

```bash
# Clone the repository
git clone https://github.com/Kamil-Karwacki/HeadSoccer3D.git
cd HeadSoccer3D
```
```bash
# Create a build directory and compile
mkdir build && cd build
cmake ..
make
```
```bash
# Run the executable
./HeadSoccer3D
```

### Current Status
The project is a Work in Progress (WIP).

### References

    Ian Millington - Game Physics Engine Development
