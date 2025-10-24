# Cub3D

[![Language](https://img.shields.io/badge/language-C-blue.svg)]()
[![Repo Size](https://img.shields.io/github/repo-size/Oussama-Bensarjane/cub3D)]()
[![License](https://img.shields.io/badge/license-MIT-green.svg)](./LICENSE.md)
[![Platform](https://img.shields.io/badge/platform-macOS%20%7C%20Linux-lightgrey.svg)]()

<p align="center">
  <picture>
    <source media="(prefers-color-scheme: dark)" srcset="./media/readme/cub3d.gif">
    <source media="(prefers-color-scheme: light)" srcset="./media/readme/cub3d.gif">
    <img src="./media/readme/cub3d.gif" alt="Cub3D Gameplay" width="640">
  </picture>
</p>

---

## Authors

**[med-el-hamidi](https://github.com/med-el-hamidi/)**
**Roles in this project:**  
- Gameplay & Engine Logic  
- Player Movement & Camera  
- Raycasting & DDA Implementation  
- Minimap System && Door Mechanics

**[Oussama-Bensarjane](https://github.com/Oussama-Bensarjane/)**
**Roles in this project:**
- Parsing of configuration file `.cub`  
- Loading and rendering textures for walls  
- Weapons rendering and animations

---

## About Cub3D

**Cub3D** is a semi-3D game engine project inspired by *Wolfenstein 3D*.  
The goal is to build a **raycasting-based rendering engine** from scratch, using **MiniLibX (mlx)** for graphics to render a first-person view of a maze from a 2D map.

### ✨ Features
- Raycasting engine (DDA algorithm)
- 3D walls, doors, and textures
- Player movement with rotation and strafing
- Mouse & keyboard controls
- open/close doors
- Circular minimap with field of view
- Flip-view camera system
- Weapon rendering
  
---

## med-el-hamidi Contribution (Gameplay & Engine Logic)

This documentation covers my full part of the project — **gameplay systems, player movement, minimap, and door mechanics** — built entirely in C with trigonometry-based rendering.

---

### 📦 Core Files
| File | Description |
|------|--------------|
| `gameplay.c` | Main render loop, frame update |
| `player.c`, `player_move.c` | Player motion, strafing, rotation |
| `raycaster.c`, `init_dda.c` | DDA raycasting algorithm |
| `door.c` | Door open/close system |
| `minimap.c`, `minimap_player.c` | Circular minimap rendering |
| `utils.c` |Utility functions for rendering pixels, handling mouse movement, and collision detection |
| `exit.c` | Resource cleanup |

---

### 🧭 Overview
The gameplay engine handles:
- Player control (movement, rotation, door interaction)
- Real-time raycasting for 3D projection
- Dynamic minimap rendering
- Interactive doors and flip camera system
- Frame rendering via `mlx_loop_hook`

The logic is centralized in `t_game`, which contains all structures (`t_player`, `t_ray`, `t_config`, `t_door`, etc.).

---

### 🔢 Raycasting Math

Raycasting simulates a 3D view from a 2D map using the **DDA (Digital Differential Analyzer)** algorithm.  
Each vertical line on the screen corresponds to one **ray** projected into the world from the player’s position.  
This means that with our window setup of **`WIDTH = 1280`** and **`HEIGHT = 720`**, we cast **1280 individual rays** — one per column of pixels — to compute what the player sees.

Our **Field of View (FOV)** is set to **60°**, which equals **π/3 radians**.  
To calculate the angle between each consecutive ray, we divide the total FOV by the number of vertical screen columns:

\[
\text{fraction} = \frac{\text{FOV}}{\text{WIDTH}} = \frac{π/3}{1280} ≈ 0.00042 \text{ radians per ray}
\]

So for each frame:
- The first ray starts at `player.angle - (FOV / 2)` (left edge of the screen).  
- The last ray ends at `player.angle + (FOV / 2)` (right edge).  
- Each subsequent ray increases by **`fraction`**, creating a fan-like projection.

This setup ensures a smooth and accurate 3D projection across the entire screen, giving a realistic sense of depth.  
Each ray uses the **DDA algorithm** to find the nearest wall intersection, calculate its **perpendicular distance**, and determine how tall the wall slice should be on screen — typically using:

```c
dist_proj_plane = WIDTH / (2 * tan((FOV * PI) / 360.0)); // FOV = 60 
wall->height = dist_proj_plane / (wall->dist * cos(game->ray.angle - game->player.angle));
```
What’s happening here:

`dist_proj_plane`
Represents the distance from the player to the projection plane (the virtual screen in 3D space).
It depends only on the screen width and field of view and works like a focal length in a camera.
A larger value means a narrower, more zoomed-in view.
`dist_proj_plane = (WIDTH / 2) / tan(PI / 3)`

`wall->dist`
The raw distance from the player to the wall along the ray’s direction.
Using this directly would cause fish-eye distortion, especially at the edges of the FOV.

`cos(game->ray.angle - game->player.angle)`
This is the cosine correction.
It removes distortion by converting the ray distance into the perpendicular distance to the wall —
the distance that truly represents how far the wall is from the camera plane.

`perpWallDist = wall->dist * cos(rayAngle - playerAngle)`
Why it matters ?
Without the cosine correction, walls viewed at an angle appear too large because the ray travels a longer diagonal path.
The correction ensures every wall slice is projected perpendicularly to the player’s view, preserving correct proportions.

Final formula
`wallHeight = dist_proj_plane / perpWallDist`
Close walls → taller slices
Far walls → shorter slices

This simple yet powerful relation makes the 3D illusion accurate, producing a perspective-correct view similar to early FPS engines like DOOM or Wolfenstein 3D.

![Raycasting Math Diagram](https://lodev.org/cgtutor/images/raycastperpwalldist2.png)

More references:
- [Lode’s Computer Graphics Tutorial](https://lodev.org/cgtutor/raycasting.html)
- [Permadi Raycasting Figures](https://permadi.com/tutorial/raycast/)
- [Wall Height Diagram](https://www.scottsmitelli.com/articles/we-can-fix-your-raycaster/wall-height.png)
- [Ray Casting in Tiled Worlds using DDA](https://www.youtube.com/watch?v=NbSee-XM7WA)

---

### 🚶Player System

**Controls**
| Key | Action |
|-----|---------|
| `W` / `S` | Move forward / backward |
| `A` / `D` | Strafe left / right |
| `←` / `→` | Rotate camera |
| `Mouse` | Smooth rotation |
| `E` | Open / close door |
| `V` | Flip view 180° |
| `R` | Reload |
| `H` | Help overlay |
| `ESC` | Quit |

**Movement Logic**
- Uses `cos(angle)` / `sin(angle)` for direction vectors.
- Collision detection prevents wall or door clipping:
  - Collision detection is handled via radius checks against nearby map tiles.
Before any position update I call can_move() which tests whether the point (and points offset by PLAYER_RADIUS = 5.0f) would intersect a wall '1' or a closed door 'D'.
This prevents the player from clipping through solid tiles while still allowing smooth movement along corners and door edges.

- Sliding into walls (corner sliding):
  - To avoid the player getting stuck when running into an obstacle at an angle, the movement update attempts three moves in order:
    1. Try to move to the full new position (new_x, new_y).
    2. If that is blocked, try moving only in X: (new_x, current_y).
    3. If that is blocked, try moving only in Y: (current_x, new_y).
  - This makes the player slide along walls rather than stopping dead when hitting corners — a much smoother and expected behaviour in FPS-style movement.

- Angle updates are frame-rate independent.

---

### 🚪 Door Mechanics

Doors in our raycaster are implemented as **dynamic map tiles** that can change state between open and closed during gameplay.

| Symbol | State   |
|:------:|:-------|
| `'D'`  | Closed |
| `'O'`  | Open   |

---

#### Interaction

- The **player toggles nearby doors** using the **`E`** key.  
- When pressed, the game checks if the player is **facing a door within a small interaction distance (2 Tiles)**.  
- If a door is found and the player is allowed to interact, its **state is toggled**, updating both the **map array** and the corresponding `t_door` structure.

---

#### Unique Identification

- Each door has a **unique ID**, calculated using the **Cantor pairing function** on its grid coordinates:

```c
ray->door_hit = ray->map_x + ray->map_y;
ray->door_hit = (ray->door_hit * (ray->door_hit + 1)) / 2 + ray->map_y;
```
This ensures that multiple doors hit by different rays can be tracked accurately during raycasting and animation updates.

#### Raycasting Integration

Doors are treated as normal solid tiles during raycasting:
  Closed doors ('D') block rays.
  Open doors ('O') are treated as empty space.

When a ray hits a door, the engine simply checks its current state and either blocks or lets the ray pass.

#### Collision & Safety

Players cannot close a door while standing inside it.

The `is_player_in_door_tile()` function ensures that closing is only allowed if the player's hitbox is fully outside the door tile.

Collision checks use player radius offsets in all four directions `(x ± radius, y ± radius)` for robust detection.

#### State Synchronization

Door states are updated in both:
  1. door->is_open boolean in the t_door structure.
  2 .The map matrix game->config.map (from 'D' → 'O' or vice versa).

This ensures consistency across:
  - Rendering (3D view and minimap)
  - Collision detection
  - Raycasting calculations

#### Example Behavior

  1. Press E while facing a door → door opens.
  2. If the door is closed ('D'), the player cannot pass through; if open ('O'), the player can move freely.
  3. Closing follows the same process, blocked if the player is too close.

This system allows smooth, interactive doors — visually consistent with the environment and integrated directly into raycasting and collision logic.

---

### 🗺️ Minimap System

The minimap provides a **real-time overview** of the surrounding map area, rendered as a **circular radar** centered on the player.

- **Circular shape:**  
  The minimap uses a simple radius check to draw only pixels within the circle boundary:
  ```c
  if ((x - center_x)² + (y - center_y)² <= radius²)
      put_pixel(x, y, color, &img);
  ```
  This creates a clean circular appearance while skipping unnecessary pixel draws.

- **Centered on the player:**
  The player’s position is always drawn at the minimap’s center.
  The map scrolls relative to player movement, keeping orientation stable and intuitive.

- **Visual elements:**
  Walls → rendered as solid blocks (e.g. white or dark colors).
  Doors → rendered with a unique color (e.g. blue when closed, green when open).
  Player → drawn as a tile scale size dot at the center.
  Field of View (FOV) → shown as a “Pac-Man”-like cone extending from the player’s position.

  The FOV area is calculated using the dot product between each minimap pixel’s direction vector and the player’s facing direction.
  If the result falls within the FOV angle threshold:
  ```c
  len = sqrt(d.x * d.x + d.y * d.y); // len != 0;
  cos_theta = (d.x * player_dir_x + d.y * player_dir_y) / len;
  if (cos_theta > 0 && cos_theta > cos(PI / 6)) // PI / 6 is FOV / 2
      put_pixel(d.x, d.y, floor_color, &img);
  ```
  Then that pixel is rendered using the same color as the floor, giving the illusion of a triangular “light cone” — similar to a Pac-Man mouth that rotates smoothly with the player’s angle.

 - **Rendering method:**
  The minimap is drawn pixel-by-pixel using the same low-level rendering function put_pixel().
  This allows per-pixel control and avoids dependency on MLX shapes or primitives.
