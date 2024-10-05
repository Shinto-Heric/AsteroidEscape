Overview

Asteroid Escape is a simple 2D space game developed using SFML (Simple and Fast Multimedia Library). The player controls a spaceship, navigating through space and destroying incoming asteroids. The game challenges players to survive and score points by shooting asteroids while progressing through increasingly difficult levels. The game features smooth controls, efficient object management, particle effects for destroyed asteroids, and a scoring system based on successful asteroid destruction.

Game Features

Spaceship Control: The player can move the spaceship left or right using the arrow keys(Left and Right) or A and D.
Asteroid Destruction: Players can shoot asteroids with bullets to earn points. Asteroids increase and spawn rate with each new level.
Levels and Difficulty: Players level up by destroying asteroids, with each level bringing more frequently spawning asteroids.
Shooting Mechanic: The spaceship fires bullets to destroy asteroids. The number of points earned depends on the asteroids destroyed.
Particle System: Particle effects are displayed when asteroids are destroyed, providing visual feedback for successful hits.
Object Pooling: Asteroids and bullets are managed by an object pool to improve performance and memory usage.
Game Over Screen: The game ends when the player's health reaches 0, hit by an asteroid, showing the final score and the level reached.

Game Structure

The game follows a modular structure, separating logic into well-organized .hpp (header) and .cpp (source) files for easier maintainability and scalability.
Main Components

Game Class:

Controls the main game loop, event handling, updating game states, and rendering.
Manages transitions between the start screen, gameplay, and game over screen.

GameObject Class:

A base class for all in-game objects like the player, asteroids, and bullets.
Includes common properties like position, sprite, active state, and update/draw functions.

Asteroid, Player, and Bullet Classes:

Inherits from the GameObject class and implements specific behavior for asteroids, the player-controlled spaceship, and bullets.

ParticleSystem and Particle Classes:

Responsible for generating particle effects when asteroids are destroyed.
The ParticleSystem manages individual particles and their behavior, such as movement in random directions after asteroid destruction.

GenericObjectPool Class:

A template-based object pool that manages reusable objects like bullets, asteroids, and particle effects to optimize memory usage.

AssetManager Class:

For managing and loading textures

SoundManager Class:

Singleton class that handles sound effects for actions like shooting, asteroid destruction, and game over.

Core Game Mechanics

Spaceship Movement

The spaceship is controlled by the player using the arrow key(LEFT and RIGHT) or A and D for movement. The spaceship is restricted from moving beyond the screen boundaries.

Asteroid Destruction (Scoring)

Points are awarded when asteroids are shot down by bullets. Simply dodging asteroids does not guarantee any points. Each asteroid destroyed increases the score by an amount based on the asteroid's size or type.

Level Progression

The player advances to the next level based on the total points earned from destroying asteroids.
As levels increase, the spawn rate of the asteroids rise, making the game more challenging.
The game becomes progressively more difficult by increasing the rate of asteroid appearance

Particle System

When an asteroid is destroyed, a burst of particles is generated in all directions to visually represent the explosion.
The ParticleSystem manages the creation, behavior, and removal of these particle effects.

Collision and Game Over

If an asteroid collides with the player's spaceship, health reduces.
A final game over screen displays the total score and the level reached by the player.

Game Flow

1. Start Screen
Displays the game title and provides options to Start or Quit.
The player starts the game by clicking the "Start" button.

2. Gameplay
The player controls the spaceship, avoiding and shooting asteroids.
Points are awarded for destroying asteroids.
The game progresses to higher levels as the player scores more points.
Particle effects are displayed when asteroids are destroyed.
The game becomes more challenging with each new level.

3. Game Over Screen
If the player's health reaches 0 , the game ends, showing a Game Over screen.
The player's final score and the level they reached are displayed.

Code Structure

Key Classes and Files:

Game.hpp / Game.cpp

Handles the main game loop, rendering, and event processing.
Manages game state transitions (start, gameplay, game over).

GameObject.hpp / GameObject.cpp

A base class for all objects (player, asteroids, bullets) that provides common functionality like position, active status, and rendering.

Player.hpp / Player.cpp

Controls the player’s movement, shooting, and collision detection with asteroids.

Asteroid.hpp / Asteroid.cpp

Manages individual asteroid movement, behavior, and collision detection.

Bullet.hpp / Bullet.cpp

Handles bullet movement and collision detection with asteroids.

ParticleSystem.hpp / ParticleSystem.cpp and Particle.hpp / Particle.cpp

Manages the particle effects generated when asteroids are destroyed. Each Particle object moves in a random direction, simulating an explosion.

GenericObjectPool.hpp

A template-based object pool for managing reusable objects like bullets, asteroids, and particle effects to optimize memory and performance.

AssetManager.hpp / AssetManager.cpp

For loading and managing textures used in the game.

SoundManager.hpp / SoundManager.cpp

Singleton class for managing the game’s sound effects like shooting and destruction.

Object Pooling System

The game uses object pools to manage reusable game objects efficiently, such as asteroids, bullets, and particles. Object pools allow the game to reuse existing objects, minimizing the overhead of frequent memory allocation and deallocation.

Key Pools:

AsteroidPool: Manages a pool of asteroids, enabling the game to reuse asteroids without frequently creating new ones.

BulletPool: Manages a pool of bullets for shooting mechanics.

Collision Handling

The game uses bounding box collision detection to handle interactions between the spaceship, asteroids, and bullets:
If the spaceship collides with an asteroid, player loses a part of his health.
If a bullet collides with an asteroid, the asteroid is destroyed, the player earns points, and a particle effect is triggered.

Game Controls

Movement: Arrow keys or WASD
Shoot: Spacebar
Quit: ESC key


Future Improvements

Power-Ups: Add power-ups that can enhance the player's shooting abilities 
or grant temporary shields.
High Score System: Implement a system to save and display high scores.
Different Asteroid Types: Introduce various asteroid types with different properties, such as size, speed, or behavior.
Enhanced Particle Effects: Improve particle effects for more realistic or visually appealing explosions.


Conclusion

Asteroid Escape is a simple fun and challenging 2D game that tests the player’s reflexes and shooting skills. The game uses a combination of object pooling for efficient performance, particle effects for visual feedback, and progressively difficult levels for engaging gameplay. The scoring and leveling system provides a competitive edge, encouraging players to shoot asteroids and progress to higher levels while avoiding destruction.
