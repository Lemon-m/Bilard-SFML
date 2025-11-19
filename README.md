# 🎱 8-Ball Pool

2D Pool Table game made with the SFML C++ library.

![Gameplay Screenshot](docs/screenshot.png)

## 🕹️ Controls

- Space - Turn on aiming Mode
- Left Click - Shoot Cue Ball when aiming / pick final 8-ball pocket / choose cue ball position when ball in hand is active

## 📜 Features

- Supports fullscreen and windowed mode.
- Includes a full tutorial for the game.
- Accurate mouse cursor aiming
- Ball rotation is simulated and can be toggled on/off.
- Official 8-Ball rules are integrated in the game logic.
- Volume can be adjusted in the main menu.
- Sound effects vary depending on collision force.
- Physics include collisions, friction, and cue ball-in-hand placement.

## ✅ Requirements
- C++17
- SFML 2.5.1 (see setup instructions below)  
- Visual Studio (recommended)

## 📥 SFML Setup
Link to the official SFML 2.5.1 setup guide  
[https://www.sfml-dev.org/tutorials/2.5/start-vc.php](https://www.sfml-dev.org/tutorials/2.5/start-vc.php)

## 🛠️ Build Instructions
1. Clone this repository:  
   ```
   git clone https://github.com/Lemon-m/8-Ball-Pool.git
   cd 8-Ball-Pool
   ```
2. Open `8-Ball Pool.sln` in Visual Studio.
3. Configure SFML (see guide above).  
4. Link SFML libraries.
5. Drag .dll files from `<SFML Installation>\bin` into the project directory.
6. Select the configuration (Debug/Release) and the platform (x64) in Visual Studio.
7. Build and run the project.  