<a id="readme-top"></a>

<!-- PROJECT SHIELDS -->
![C++](https://img.shields.io/badge/C%2B%2B-20-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)
![DirectX](https://img.shields.io/badge/DirectX-11-107C10?style=for-the-badge&logo=xbox&logoColor=white)
![FMOD](https://img.shields.io/badge/FMOD-000000?style=for-the-badge&logo=fmod&logoColor=white)
![Windows](https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)
[![Apache 2.0 License][license-shield]][license-url]

<!-- PROJECT TITLE -->
<div align="center">
  <h1>Daemonstein</h1>
  <p>A DOOM-inspired 3D first-person shooter with sprite-based enemies, split-screen multiplayer, and data-driven design</p>
</div>

<!-- TODO: Replace with actual gameplay GIF or screenshot -->
<!-- <div align="center">
  <img src="docs/images/demo.gif" alt="Daemonstein Gameplay" width="720">
</div> -->

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [How to Install](#how-to-install)
- [How to Use](#how-to-use)
- [Project Structure](#project-structure)
- [License](#license)
- [Contact](#contact)

## Overview

Daemonstein is a 3D first-person shooter inspired by classic DOOM. Players control a Marine (100 HP) armed with a Pistol and Plasma Rifle, fighting through tile-based maps populated by Demon enemies (160 HP) that use sight-based AI with a 120° field of view. The game supports local 2-player split-screen via a lobby system, with both keyboard/mouse and Xbox controller input.

Built as a course project at SMU Guildhall, the game runs on a custom [Daemon Engine](https://github.com/dadavidtseng/Engine) providing DirectX 11 rendering with diffuse lighting, FMOD 3D audio, sprite-based 8-directional animations, and a developer console with V8 JavaScript integration.

## Features

- **Sprite-based 8-directional enemies** — Demons rendered as billboarded sprites with walk, attack, hurt, and death animations from 8 viewing angles
- **3 weapon types** — Pistol (hitscan, 10–15 dmg), Plasma Rifle (projectile, rapid-fire), and Demon Melee (180° arc, AI-only)
- **Local 2-player split-screen** — Lobby-based join system with horizontal viewport splitting and independent cameras
- **Sight-based AI** — Enemies detect targets within a 64-unit radius and 120° cone, chase using turn-toward steering, and engage in melee range
- **Data-driven design** — XML files define all actors, weapons, maps, tiles, and spawn configurations

## How to Install

### Prerequisites

- Visual Studio 2022 (or 2019) with C++ desktop development workload
- Windows 10/11 (x64)
- DirectX 11 compatible GPU
- [Daemon Engine](https://github.com/dadavidtseng/Engine) cloned as a sibling directory

### Build

```bash
# Clone both repos side by side
git clone https://github.com/dadavidtseng/Engine.git
git clone https://github.com/dadavidtseng/Daemonstein.git

# Directory layout should be:
# ├── Engine/
# └── Daemonstein/
```

1. Open `Doomenstein.sln` in Visual Studio
2. Set configuration to `Debug | x64`
3. Build the solution (the Engine project is referenced automatically)
4. The executable is deployed to `Run/` via post-build event

## How to Use

### Controls (Keyboard & Mouse)

| Action | Key |
|--------|-----|
| Move | W / A / S / D |
| Look | Mouse |
| Shoot | Left Mouse Button |
| Sprint | Shift |
| Switch to Pistol | 1 |
| Switch to Plasma Rifle | 2 |
| Free camera toggle | F |
| Possess next actor | N |

### Controls (Xbox Controller)

| Action | Button |
|--------|--------|
| Move | Left Stick |
| Look | Right Stick |
| Shoot | Right Trigger |
| Sprint | A |
| Switch weapon | D-Pad Up / Down, X / Y |

### Debug Controls

| Action | Key |
|--------|-----|
| Developer console | ` |

### Game Flow

1. **Attract Mode** — Title screen (press Space or Start to join)
2. **Lobby** — Players join/leave; press Space/Start again to begin or add a second player
3. **In-Game** — FPS combat on tile-based maps (TestMap, MPMap)

### Running

Launch `Run/Doomenstein_Debug_x64.exe` from the `Run/` directory (working directory must be `Run/` for asset loading).

## Project Structure

```
Daemonstein/
├── Code/Game/
│   ├── Definition/                # Data-driven definitions
│   │   ├── ActorDefinition        # Actor stats, visuals, sounds, inventory
│   │   ├── MapDefinition          # Map image, spawn info, tile sheets
│   │   ├── TileDefinition         # Tile type properties
│   │   └── WeaponDefinition       # Weapon stats, HUD, projectiles
│   ├── Framework/                 # Application framework
│   │   ├── Main_Windows.cpp       # WinMain entry point
│   │   ├── App                    # Application lifecycle
│   │   ├── GameCommon             # Global pointers and constants
│   │   ├── Controller             # Base controller (viewport, cameras)
│   │   ├── PlayerController       # Keyboard/mouse & gamepad input
│   │   ├── AIController           # Sight-based enemy AI
│   │   ├── Animation              # Sprite animation playback
│   │   └── AnimationGroup         # 8-directional animation sets
│   ├── Gameplay/                  # Core game logic
│   │   ├── Game                   # State machine, lobby, split-screen
│   │   ├── Map                    # Tile world, raycasting, actor management
│   │   ├── Actor                  # Entity with physics, combat, inventory
│   │   ├── Tile                   # Individual tile in the grid
│   │   ├── Weapon                 # Hitscan, projectile, melee systems
│   │   ├── HUD                    # Weapon sprite, reticle, health display
│   │   └── Sound                  # FMOD audio wrapper
│   └── Subsystem/                 # Engine subsystems
│       ├── Light/                 # Diffuse lighting
│       └── Widget/                # UI widget framework
├── Run/                           # Runtime directory
│   ├── Data/Audio/                # SFX + music (WAV, MP2, MP3)
│   ├── Data/Definitions/          # XML config (Actors, Weapons, Maps, Tiles)
│   ├── Data/Fonts/                # Bitmap fonts (PNG)
│   ├── Data/Images/               # Sprite sheets and textures
│   ├── Data/Maps/                 # Map images (PNG, 32×32 grids)
│   └── Data/Shaders/              # HLSL shaders (Default, Diffuse)
├── Docs/                          # Documentation
└── Doomenstein.sln                # Visual Studio solution
```

## License

Copyright 2025 Yu-Wei Tseng

Licensed under the [Apache License, Version 2.0](../LICENSE).

## Contact

**Yu-Wei Tseng**
- Portfolio: [dadavidtseng.info](https://dadavidtseng.info)
- GitHub: [@dadavidtseng](https://github.com/dadavidtseng)
- LinkedIn: [dadavidtseng](https://www.linkedin.com/in/dadavidtseng/)
- Email: dadavidtseng@gmail.com

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- REFERENCE-STYLE LINKS -->
[license-shield]: https://img.shields.io/github/license/dadavidtseng/Daemonstein.svg?style=for-the-badge
[license-url]: https://github.com/dadavidtseng/Daemonstein/blob/main/LICENSE
