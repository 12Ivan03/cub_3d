# Cub3D 🎮

A 3D game engine inspired by the legendary Wolfenstein 3D, built using raycasting techniques. This project is part of the 42 School curriculum and demonstrates fundamental concepts of computer graphics, game development, and real-time rendering.

![42 Badge](https://img.shields.io/badge/42-Project-blue)
![Language](https://img.shields.io/badge/Language-C-orange)
![Library](https://img.shields.io/badge/Graphics-MLX42-green)

---

## 📖 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Project Structure](#project-structure)
- [Architecture](#architecture)
- [Installation](#installation)
- [Usage](#usage)
- [Map Format](#map-format)
- [Controls](#controls)
- [Technical Details](#technical-details)
- [Libraries Used](#libraries-used)
- [Authors](#authors)

---

## Overview

Cub3D is a raycasting-based 3D game engine that renders a maze-like environment from a first-person perspective. The engine uses the **Digital Differential Analysis (DDA)** algorithm to cast rays and calculate wall distances, creating a pseudo-3D effect similar to early 90s games like Wolfenstein 3D and Doom.

---

## Features

✅ Real-time 3D rendering using raycasting  
✅ Textured walls (North, South, East, West)  
✅ Configurable floor and ceiling colors  
✅ Player movement and rotation  
✅ Mouse look support  
✅ Mini-map display  
✅ Window resizing support  
✅ Collision detection  
✅ Custom map file format (`.cub`)

---

## Project Structure

```
cub_3d/
├── README.md                    # This file
├── code/                        # Main source code directory
│   ├── Makefile                 # Build configuration
│   ├── cub3d                    # Compiled executable
│   ├── include/                 # Header files
│   │   ├── cub3d.h              # Main header with function prototypes
│   │   └── cub3d_struct.h       # Data structures and constants
│   ├── lib/                     # External libraries
│   │   ├── get_next_line/       # GNL library for file reading
│   │   ├── libft/               # Custom C standard library
│   │   └── MLX42/               # Graphics library (OpenGL-based)
│   └── src/                     # Source files
│       ├── main.c               # Entry point
│       ├── error_handler/       # Error management
│       ├── free/                # Memory cleanup
│       ├── game_loop/           # Main game loop & raycasting
│       ├── graph/               # Wall rendering
│       ├── hooks/               # Input handling (keyboard/mouse)
│       ├── init/                # Initialization routines
│       ├── math/                # Mathematical utilities
│       ├── mini_map/            # Mini-map rendering
│       ├── parse_file/          # Map file parsing
│       └── utils/               # Helper utilities
├── texture/                     # Wall texture images (.png)
├── v_maps/                      # Valid test maps
└── w_maps/                      # Invalid/edge case test maps
```

---

## Architecture

### Core Components

#### 1. **Main Entry Point** (`src/main.c`)
The application entry point that orchestrates:
- Argument validation (expects exactly one `.cub` map file)
- Game initialization
- Map file parsing
- Setting up MLX42 hooks (keyboard, mouse, resize)
- Starting the main game loop
- Cleanup on exit

#### 2. **Game Initialization** (`src/init/`)
| File | Purpose |
|------|---------|
| `init_game.c` | Allocates and initializes the main `t_game` structure |
| `init_structs.c` | Initializes player state for each frame |

**Default Configuration:**
- Window: 1000x800 pixels
- Field of View: 60°
- Grid Size: 264 units
- Wall Height: 264 units
- Movement Speed: 5.0 units/frame

#### 3. **Map Parsing** (`src/parse_file/`)
| File | Purpose |
|------|---------|
| `valid_file.c` | Validates file extension (`.cub`) |
| `parse_file_content.c` | Orchestrates the parsing pipeline |
| `read_file_direction_f_c.c` | Parses texture paths and colors |
| `process_map.c` | Reads and stores the map grid |
| `eval_map.c` | Validates map structure (closed walls) |
| `eval_graph.c` | Loads texture images via MLX42 |

#### 4. **Game Loop & Raycasting** (`src/game_loop/`)
The heart of the engine - `start_game.c` implements:

```
For each vertical column of the screen:
  1. Calculate ray angle based on FOV and player direction
  2. Cast ray using DDA algorithm
  3. Find intersection with horizontal and vertical grid lines
  4. Determine which wall was hit (N/S/E/W)
  5. Calculate distance to wall (with fisheye correction)
  6. Render textured wall slice
```

**Key Functions:**
- `start_game()` - Main render loop called every frame
- `compute_ray_angle()` - Calculates individual ray direction
- `ray_hit_points()` - Computes potential wall intersections
- `select_ray_hit()` - Determines closest wall hit
- `advance_ray_intersection()` - Steps through the grid (DDA)

#### 5. **Graphics Rendering** (`src/graph/`)
| File | Purpose |
|------|---------|
| `graph.c` | Wall slice rendering with texture mapping |
| `graph_background.c` | Floor and ceiling color fill |

**Texture Mapping:**
- Each wall texture is mapped based on hit position
- X-coordinate: determined by where ray hits within grid cell
- Y-coordinate: scaled based on wall height on screen

#### 6. **Mini-Map** (`src/mini_map/`)
Renders a top-down 2D view showing:
- Wall tiles (gray)
- Empty spaces (transparent)
- Player position (cyan dot)
- Player direction (line indicator)

#### 7. **Input Handling** (`src/hooks/`)
| File | Purpose |
|------|---------|
| `key_hook.c` | Keyboard input (WASD, arrows, ESC) |
| `key_hook_helper.c` | Movement logic with collision detection |
| `resize_hook.c` | Window resize handling |

#### 8. **Utilities**
| Directory | Purpose |
|-----------|---------|
| `error_handler/` | Centralized error reporting |
| `free/` | Memory deallocation (map, textures, MLX) |
| `math/` | Distance calculation, angle conversion |
| `utils/` | File parsing helpers |

---

## Data Structures

### Main Game Structure (`t_game`)
```c
typedef struct s_game
{
    mlx_t       *mlx;           // MLX42 instance
    mlx_image_t *foreground;    // Wall rendering layer
    mlx_image_t *background;    // Floor/ceiling layer
    mlx_image_t *min_map_img;   // Mini-map layer
    char        **map;          // 2D map grid
    t_player    player;         // Player state
    int         height;         // Map height (tiles)
    int         width;          // Map width (tiles)
    int         fov;            // Field of view (degrees)
    int         height_window;  // Window height (pixels)
    int         width_window;   // Window width (pixels)
    t_graph     *graph;         // Graphics/textures
    ...
}   t_game;
```

### Player Structure (`t_player`)
```c
typedef struct s_player
{
    float           angle_alpha;  // View direction (0-360°)
    t_coordinates   position;     // Position in world units
    int             x_grid;       // Current tile X
    int             y_grid;       // Current tile Y
}   t_player;
```

### Graphics Structure (`t_graph`)
```c
typedef struct s_graph
{
    t_rgb       g_f;            // Floor RGB color
    t_rgb       g_c;            // Ceiling RGB color
    mlx_image_t *walls[4];      // Wall textures [NO, EA, SO, WE]
    float       proj_dist;      // Projection plane distance
}   t_graph;
```

---

## Installation

### Prerequisites
- GCC or Clang compiler
- CMake (for MLX42)
- GLFW3 library
- Make

### Linux (Ubuntu/Debian)
```bash
# Install dependencies
sudo apt-get update
sudo apt-get install build-essential cmake libglfw3-dev

# Clone the repository
git clone --recurse-submodules https://github.com/12Ivan03/cub_3d.git
cd cub_3d/code

# Build the project
make
```

### macOS
```bash
# Install dependencies
brew install cmake glfw

# Clone and build
git clone --recurse-submodules https://github.com/12Ivan03/cub_3d.git
cd cub_3d/code
make
```

---

## Usage

```bash
./cub3d <map_file.cub>
```

### Examples
```bash
# Run with a valid map
./cub3d ../v_maps/v1.cub

# Run with a larger map
./cub3d ../v_maps/v4_very_big.cub

# Run with minimal map
./cub3d ../v_maps/v5_small_map.cub
```

---

## Map Format

Map files use the `.cub` extension and contain:

### 1. Texture Paths (Required)
```
NO ./path/to/north_texture.png
SO ./path/to/south_texture.png
WE ./path/to/west_texture.png
EA ./path/to/east_texture.png
```

### 2. Colors (Required)
```
F 100,255,100    # Floor color (RGB)
C 100,100,255    # Ceiling color (RGB)
```

### 3. Map Grid (Required)
```
111111111
100000001
100N00001    # N = player start facing North
100000001
111111111
```

**Map Characters:**
| Char | Meaning |
|------|---------|
| `0` | Empty/walkable space |
| `1` | Wall |
| `N` | Player start (facing North) |
| `S` | Player start (facing South) |
| `E` | Player start (facing East) |
| `W` | Player start (facing West) |
| ` ` | Void (outside map) |

**Map Rules:**
- Map must be surrounded by walls (`1`)
- Exactly one player spawn point required
- No open edges (map must be "closed")

---

## Controls

| Key | Action |
|-----|--------|
| `W` / `↑` | Move forward |
| `S` / `↓` | Move backward |
| `A` | Strafe left |
| `D` | Strafe right |
| `←` | Rotate left |
| `→` | Rotate right |
| `Mouse` | Look around |
| `ESC` | Exit game |

---

## Technical Details

### Raycasting Algorithm
The engine uses the **DDA (Digital Differential Analyzer)** algorithm:

1. For each screen column, cast a ray from player position
2. Calculate intersections with horizontal and vertical grid lines
3. Step through the grid until a wall is hit
4. Use the shorter distance (horizontal vs vertical intersection)
5. Apply fisheye correction: `corrected_dist = dist * cos(ray_angle - player_angle)`
6. Calculate wall height: `height = WALL_HEIGHT / distance * projection_distance`

### Wall Direction Detection
```
hit = 0: East wall  (ray going left)
hit = 1: South wall (ray going up)
hit = 2: West wall  (ray going right)
hit = 3: North wall (ray going down)
```

### Coordinate System
- **World coordinates**: Floating-point position in game units
- **Grid coordinates**: Integer tile position (world / GRID_SIZE)
- **Screen coordinates**: Pixel position on window

### Constants (`cub3d_struct.h`)
```c
#define GRID_SIZE    264    // Size of one map tile
#define HEIGHT_WALL  264    // Wall height in world units
#define INIT_FOV     60     // Field of view in degrees
#define HEIGHT_WIN   800    // Default window height
#define WIDTH_WIN    1000   // Default window width
#define MOVE_SPEED   5.0f   // Player movement speed
```

---

## Libraries Used

### MLX42
Modern OpenGL-based graphics library for 42 projects.
- Repository: [codam-coding-college/MLX42](https://github.com/codam-coding-college/MLX42)
- Features: Window management, image rendering, input handling

### Libft
Custom implementation of standard C library functions.
- Repository: [12Ivan03/libft_42](https://github.com/12Ivan03/libft_42)

### Get Next Line
Line-by-line file reading utility.
- Repository: [12Ivan03/get_next_line_42](https://github.com/12Ivan03/get_next_line_42)

---

## Error Codes

| Code | Description |
|------|-------------|
| 1 | Invalid arguments (expected 2) |
| 2 | EOF: missing map |
| 3 | Invalid file extension |
| 4 | Memory allocation error |
| 5 | Map validation failed (open map) |
| 6 | MLX42 library error |
| 7 | Unable to create MLX42 object |
| 8 | Invalid map configuration |

---

## Test Maps

### Valid Maps (`v_maps/`)
| File | Description |
|------|-------------|
| `v1.cub` | Standard test map |
| `v2.cub` - `v4.cub` | Various layouts |
| `v4_very_big.cub` | Large map stress test |
| `v5_small_map.cub` | Minimal valid map |
| `v6_island.cub` | Island-style layout |
| `v7_have_fun.cub` | Complex maze |

### Invalid Maps (`w_maps/`)
Used for testing error handling:
- `open_map.cub` - Not fully enclosed
- `no_floor.cub` - Missing floor color
- `no_silling.cub` - Missing ceiling color
- `no_NO_SO_WE_EA.cub` - Missing textures

---

## Building

```bash
# Full build
make

# Clean object files
make clean

# Full clean (including executable)
make fclean

# Rebuild
make re
```

---

## Authors

- **ipavlov** - [@12Ivan03](https://github.com/12Ivan03)
- **aerokhina** - [@agerokhina](https://github.com/agerokhina)

---

## License

This project is part of the 42 School curriculum. Feel free to use it for learning purposes.

---

## Acknowledgments

- [42 School](https://42.fr/) for the project subject
- [Lode's Computer Graphics Tutorial](https://lodev.org/cgtutor/raycasting.html) for raycasting explanations
- [Wolfenstein 3D](https://en.wikipedia.org/wiki/Wolfenstein_3D) for the original inspiration
