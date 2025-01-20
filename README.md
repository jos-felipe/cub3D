# cub3D - A Wolfenstein 3D-style Game Engine

A raycasting-based 3D game engine inspired by Wolfenstein 3D, developed as part of the School 42 curriculum. This project implements fundamental computer graphics concepts to create a dynamic first-person perspective in a maze environment.

![Project Status](https://img.shields.io/badge/status-completed-brightgreen)
![Language](https://img.shields.io/badge/language-C-blue)
![License](https://img.shields.io/badge/license-GPL--3.0-green)

## 🎮 Features

- **3D Rendering Engine**
  - Raycasting-based rendering
  - Textured walls with different textures for each direction (N,S,E,W)
  - Dynamic view with proper perspective
  - Configurable floor and ceiling colors

- **Player Controls**
  - Smooth movement using W,A,S,D keys
  - Camera rotation with left/right arrow keys
  - Wall collision detection
  - Field of view management

- **Map System**
  - Custom map format (.cub)
  - Dynamic map loading
  - Support for different map sizes
  - Validated map parsing with error handling

## 🛠️ Technical Requirements

- GCC compiler
- Make build system
- MLX42 graphics library
- Math library (-lm)
- GLFW library (-lglfw)

## 📦 Installation

1. Clone the repository:
```bash
git clone https://github.com/yourusername/cub3D.git
cd cub3D
```

2. Install dependencies (Ubuntu/Debian):
```bash
sudo apt-get update
sudo apt-get install build-essential libglfw3-dev
```

3. Build the project:
```bash
make
```

## 🚀 Usage

Run the program with a map file:
```bash
./cub3D asset/map/ninja_temple.cub
```

### Map Format (.cub)
The map file should contain:
```
NO ./path_to_north_texture.png    # North wall texture
SO ./path_to_south_texture.png    # South wall texture
WE ./path_to_west_texture.png     # West wall texture
EA ./path_to_east_texture.png     # East wall texture

F 220,100,0                       # Floor RGB color
C 225,30,0                       # Ceiling RGB color

# Map layout (1 = wall, 0 = floor, N/S/E/W = player start position)
111111
100101
101001
1100N1
111111
```

## 🎮 Controls

- **W** - Move forward
- **S** - Move backward
- **A** - Strafe left
- **D** - Strafe right
- **←** - Rotate camera left
- **→** - Rotate camera right
- **ESC** - Exit game

## 🏗️ Project Structure

```
.
├── src/
│   ├── ch0/    # Scene/Map parsing
│   ├── ch1/    # Window management
│   ├── ch2/    # Raycasting engine
│   └── ch3/    # Texture management
├── include/    # Header files
├── lib/        # External libraries
└── assets/     # Textures and maps
```

## ✨ Completed Features

- [x] Scene parsing and map validation
- [x] Window and event management
- [x] Ray-casting engine implementation
- [x] Texture mapping system
- [x] Performance optimization
- [x] Wall collision detection
- [x] Player movement and rotation
- [x] Error handling and memory management

## 🤝 Contributing

1. Fork the project
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## 📜 License

This project is licensed under the GNU General Public License v3.0 - see the [LICENSE](LICENSE) file for details.

## 🙏 Acknowledgments

- School 42 for the project subject
- Id Software for the original Wolfenstein 3D
- MLX42 library maintainers
- The GLFW team

## 📧 Contact

J Felipe D Stieven - [@jos-felipe](https://github.com/jos-felipe)

Project Link: [https://github.com/jos-felipe/cub3D](https://github.com/jos-felipe/cub3D)
