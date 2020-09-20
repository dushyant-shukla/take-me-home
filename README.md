# Take Me Home
'Take Me Home' is a 2D platformer built on top of a custom game engine I developed as a requirement for class CS529 while studying at DigiPen Institute of Technology.

Exciting features of the game engine:
1. **Hardware accelerated graphics:** A 2D renderer written in OpenGL.
2. **Entity Component system:** Component based game-object composition.
3. **Serialization:** Json based data-externalization for game archetypes.
4. **Collision System:** AABB-AABB collision with impulse based collision resolution.

### Requirements
 - OS: Windows.
 - IDE: Microsoft Visual Studio 2019.
 - Run the project on x86 configuration in Visual Studio.

### External Dependencies
- #### Core:
  * Programming language: C++
  * Engine architecture: Entity Component System
  * Serialization: JSON ([jsoncpp](https://github.com/open-source-parsers/jsoncpp))
  * Window Manager: [glfw](https://www.glfw.org/)
- #### Graphics:
  * Graphics API: OpenGL 4.0
  * Shader Language: GLSL version 400
  * Gl Loader-Generator: [glad](https://glad.dav1d.de/)
  * Image loader: [stb_image](https://github.com/nothings/stb)

![](./Assets/play-test.gif)

It is a work in progress. Features on the way:
1. Health system: The only way for player to die currently is by falling in the water. With health-system in place, player's heath will get affected on every collision with enemy objects.
2. Level management.
