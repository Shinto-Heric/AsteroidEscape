# 🚀 Asteroid Escape

Asteroid Escape is a 2D space shooter game built with C++ and SFML. Control your spaceship, destroy incoming asteroids, survive through increasingly difficult levels, and aim for the highest score! The game features smooth controls, particle effects, object pooling for performance, and a modular state-based architecture.

Note: Uses 3rd party assets that are downloaded randomly from the internet. Created just for study purposes.

---

## 📌 Table of Contents

- [Features](#-features)
- [Gameplay & Controls](#-gameplay--controls)
- [Screenshots](#-screenshots)
- [Project Structure](#-project-structure)
- [Dependencies](#-dependencies)
- [Future Improvements](#-future-improvements)
- [Conclusion](#-conclusion)

---

## 🌟 Features

- Smooth spaceship movement with arrow keys / A & D
- Shoot asteroids to earn points
- Increasing difficulty with each level
- Particle effects for destroyed asteroids
- Object pooling for bullets, asteroids, and particles for efficient memory usage
- Start menu, gameplay, and game over screens
- HUD showing score, level, and health
- Modular architecture using State Machine

---

## 🎮 Gameplay & Controls

- Movement: Arrow keys / A & D
- Shoot: Spacebar
- Quit: ESC key
- Avoid collisions with asteroids
- Destroy asteroids to earn points and progress levels
- Each asteroid destroyed generates particle effects for visual feedback
- Game ends when player health reaches 0, showing final score and level

---

## 📷 Screenshots

**Main Menu**  

*Insert screenshot here*

**Gameplay**  

*Insert screenshot here*

**Game Over Screen**  

*Insert screenshot here*

---

## 🗂 Project Structure

| Folder / File          | Description                                                      |
| ---------------------- | ---------------------------------------------------------------- |
| `Game.cpp / Game.h`    | Main game loop, state management, HUD, and initialization        |
| `GameState.h`          | Base class for all states (StartMenu, Playing, GameOver)         |
| `StartMenuState.cpp/h` | Start menu with title, Start, and Quit options                   |
| `PlayingState.cpp/h`   | Gameplay logic, spawning asteroids, collision handling           |
| `GameOverState.cpp/h`  | Game over screen, score, and restart/quit options                |
| `GameObject.cpp/h`     | Base class for all game objects (Player, Asteroid, Bullet)       |
| `Player.cpp/h`         | Player movement, shooting, and health management                 |
| `Asteroid.cpp/h`       | Asteroid movement and collision detection                        |
| `Bullet.cpp/h`         | Bullet movement and collision detection                          |
| `Particle.cpp/h`       | Individual particle for explosion effects                        |
| `ParticleSystem.cpp/h` | Manages all particle effects                                     |
| `AssetManager.cpp/h`   | Loading and managing textures                                    |
| `SoundManager.cpp/h`   | Playing sound effects and music                                  |
| `GenericObjectPool.h`  | Template-based object pool for bullets, asteroids, and particles |

---

## ⚙ Dependencies

- C++17 or later
- SFML 2.5+ (Graphics, Window, Audio modules)

---

## 💡 Future Improvements

- Power-Ups: Add power-ups that can enhance the player's shooting abilities or grant temporary shields.
- High Score System: Implement a system to save and display high scores.
- Different Asteroid Types: Introduce various asteroid types with different properties, such as size, speed, or behavior.
- Enhanced Particle Effects: Improve particle effects for more realistic or visually appealing explosions.

---

## 🏁 Conclusion

Asteroid Escape is a fun and challenging 2D space shooter that tests reflexes and strategy.  
It combines smooth controls, modular state management, particle effects, and object pooling for efficient performance.  
Players are encouraged to improve their score and progress through increasingly difficult levels while enjoying responsive gameplay and visual feedback.
